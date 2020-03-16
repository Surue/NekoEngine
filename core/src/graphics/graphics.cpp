/*
 MIT License

 Copyright (c) 2019 SAE Institute Switzerland AG

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#include <graphics/graphics.h>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <engine/globals.h>
#include <engine/window.h>
#include <engine/engine.h>
#include "engine/log.h"

#ifdef EASY_PROFILE_USE
#include "easy/profiler.h"
#endif

namespace neko
{
Renderer::Renderer()
{
	currentCommandBuffer_.reserve(MAX_COMMAND_NMB);
	nextCommandBuffer_.reserve(MAX_COMMAND_NMB);
}


void Renderer::Render(RenderCommandInterface* command)
{
	nextCommandBuffer_.push_back(command);
}

void Renderer::RenderAll()
{
#ifdef EASY_PROFILE_USE
	EASY_BLOCK("RenderAllCPU");
#endif
	for (auto* renderCommand : currentCommandBuffer_)
	{
		renderCommand->Render();
	}
}

void Renderer::Sync()
{
#if !defined(NEKO_SAMETHREAD)
#ifdef EASY_PROFILE_USE
	EASY_BLOCK("EngineRenderSync");
	EASY_BLOCK("EngineAppWaiting");
	EASY_BLOCK("AcquireRenderLock");
#endif
	std::unique_lock lock(renderMutex_);
#ifdef EASY_PROFILE_USE
	EASY_END_BLOCK;
#endif
	flags_ |= IS_APP_WAITING;
#ifdef EASY_PROFILE_USE
	EASY_BLOCK("WaitForRenderSignal");
#endif
	cv_.wait(lock);
#ifdef EASY_PROFILE_USE
	EASY_END_BLOCK;
	EASY_END_BLOCK;
	EASY_BLOCK("SwapRenderCommand");
#endif
#endif
	std::swap(currentCommandBuffer_, nextCommandBuffer_);
	nextCommandBuffer_.clear();
	//TODO copy all the new transform3d?
	auto* engine = BasicEngine::GetInstance();
	engine->ManageEvent();
	flags_ &= ~IS_APP_WAITING;
}

void Renderer::RenderLoop()
{
#if !defined(NEKO_SAMETHREAD)
	flags_ |= IS_RUNNING;
	window_->LeaveCurrentContext();
	renderThread_ = std::thread([this] {
		BeforeRenderLoop();

		std::chrono::time_point<std::chrono::system_clock> clock = std::chrono::system_clock::now();
		while (flags_ & IS_RUNNING)
		{
			const auto start = std::chrono::system_clock::now();
			const auto dt = std::chrono::duration_cast<seconds>(start - clock);
			dt_ = dt.count();
			clock = start;

			Update();
		}
		AfterRenderLoop();
		});
#endif
}

void Renderer::Destroy()
{
#ifdef EASY_PROFILE_USE
	EASY_BLOCK("ClosingFromEngine");
#endif
	flags_ &= ~IS_RUNNING;
#if !defined(NEKO_SAMETHREAD)
	renderThread_.join();
#endif
}

void Renderer::SetFlag(Renderer::RendererFlag flag)
{
	flags_ |= flag;
}

void Renderer::SetWindow(Window* window)
{
	window_ = window;
}

void Renderer::Update()
{
#ifdef EASY_PROFILE_USE
	EASY_BLOCK("RenderFullUpdateCPU");
#endif


	auto* engine = BasicEngine::GetInstance();
	{
#if !defined(NEKO_SAMETHREAD)
		std::unique_lock<std::mutex> lock(renderMutex_);
#endif
#ifdef EASY_PROFILE_USE
		EASY_BLOCK("RenderUpdateCPU");
#endif
		ClearScreen();
		engine->GenerateUiFrame();
		RenderAll();
#if !defined(NEKO_SAMETHREAD)
		lock.unlock();
#endif
		window_->RenderUi();
	}
	{
#if !defined(NEKO_SAMETHREAD)
		std::unique_lock<std::mutex> lock(renderMutex_);
#endif
#ifdef EASY_PROFILE_USE
		EASY_BLOCK("RenderSwapBufferCPU");
#endif
		window_->SwapBuffer();
	}
	{
#ifdef EASY_PROFILE_USE
		EASY_BLOCK("WaitForAppCPU");
#endif
#if !defined(NEKO_SAMETHREAD)
		while (!(flags_ & IS_APP_WAITING) && (flags_ & IS_RUNNING))
		{
			cv_.notify_one();
		}

		{
			cv_.notify_one();
		}
#endif

	}
}
void Renderer::BeforeRenderLoop()
{
#if !defined(NEKO_SAMETHREAD)
	window_->MakeCurrentContext();
#endif
}
void Renderer::AfterRenderLoop()
{
#if !defined(NEKO_SAMETHREAD)
	window_->LeaveCurrentContext();
#endif
}



}

