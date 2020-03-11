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
#include <utilities/file_utility.h>
#include <sstream>
#include <functional>
#include "engine/log.h"

#ifdef __APPLE__

#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#endif

#ifdef WIN32
#include <filesystem>
namespace fs = std::filesystem;
#endif

#if defined(__linux__) || defined (EMSCRIPTEN)
#include <filesystem>
namespace fs = std::filesystem;
#endif

namespace neko
{
bool FileExists(const std::string_view filename)
{
#ifdef __APPLE__
    const fs::path p = std::string(filename);
#else
    const fs::path p = filename;
#endif
    return fs::exists(p);
}

bool IsRegularFile(const std::string_view filename)
{
#ifdef __APPLE__
    const fs::path p = std::string(filename);
#else
    const fs::path p = filename;
#endif
    return fs::is_regular_file(p);

}

bool IsDirectory(const std::string_view filename)
{
#ifdef __APPLE__
    const fs::path p = std::string(filename);
#else
    const fs::path p = filename;
#endif
    return fs::is_directory(p);
}

void IterateDirectory(const std::string_view dirname, std::function<void(const std::string_view)> func, bool recursive)
{

    if (IsDirectory(dirname))
    {
#ifdef __APPLE__
        for (auto& p : fs::directory_iterator(std::string(dirname)))
#else
        for (auto& p : fs::directory_iterator(dirname))
#endif
        {
            if(IsRegularFile(p.path().generic_string()))
            {
                func(p.path().generic_string());
            }
            else if(recursive && IsDirectory(p.path().generic_string()))
            {
                IterateDirectory(p.path().generic_string(), func, recursive);
            }
        }
    }
}

std::ifstream::pos_type CalculateFileSize(const std::string& filename)
{
    std::ifstream in(filename, std::ifstream::binary | std::ifstream::ate);
    return in.tellg();
}

bool CreateDirectory(const std::string_view dirname)
{
#ifdef __APPLE__
    return fs::create_directory(std::string(dirname));
#else
    return fs::create_directory(dirname);
#endif
}

bool RemoveDirectory(const std::string_view dirname, bool removeAll)
{
    if (removeAll)
    {
#ifdef  __APPLE__
        return fs::remove_all(std::string(dirname));
#else
        return fs::remove_all(dirname);
#endif
    }
    else
    {
#ifdef __APPLE__
        return fs::remove(std::string(dirname));
#else
        return fs::remove(dirname);
#endif
    }
}

const std::string LoadFile(const std::string& path)
{
    std::ifstream t(path);
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    return str;
}

std::string GetFilenameExtension(const std::string_view path)
{
	const fs::path p = path;
    return p.extension().string();
}

std::string GetFileParentPath(const std::string_view path)
{
#ifdef __APPLE__
    fs::path p = std::string(path);
#else
    fs::path p = fs::path(path);
#endif
    return p.parent_path().string();
}

std::string LinkFolderAndFile(const std::string_view folderPath, const std::string_view filePath)
{
	
#ifdef __APPLE__
    fs::path f = std::string(folderPath);
    fs::path p = std::string(filePath);
#else
	const fs::path f = fs::path(folderPath);
	const fs::path p = fs::path(filePath);
#endif
	const fs::path l = f / p;
	
    return MakeGeneric(l.string());
}

void WriteStringToFile(const std::string& path, const std::string_view content)
{
    std::ofstream t(path);
    t << content;

}

std::string GetFilename(const std::string_view path)
{
	const fs::path p = path;
    return p.filename().string();
}

std::string GetStem(const std::string_view path)
{
	const fs::path p = path;
	return p.stem().string();
}

std::string MakeGeneric(const std::string_view path)
{
	std::string p = path.data();
	std::replace_if(p.begin(), p.end(), 
		[](char separator) {return separator == '\\'; }, '/');
	return p;
}

std::string GetRelativePath(const std::string_view path, const std::string_view relative)
{
    fs::path p = fs::path(path);
	//LogDebug(std::string("Relative path from: ") + path.data() + " to: " + relative.data());
    return MakeGeneric(fs::relative(p, relative).string());
}

std::string GetCurrentPath()
{
    return fs::current_path().string();
}
}
