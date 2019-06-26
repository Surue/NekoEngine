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

#include <gtest/gtest.h>
#include <engine/engine.h>
#include <city_graph.h>
#include <city_behavior_tree.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <imgui.h>
#include <Remotery.h>

class BehaviorTreeTest : public ::testing::Test, public neko::BasicEngine {
protected:
	void SetUp() override {
		jsonBehaviorTree_ = R"(
			{
				"type" : "composite_selector",
				"name" : "Application",
				"children" : [
					{
						"type" : "composite_sequence",
						"name" : "Keep alive",
						"children" : [
							{
								"type" : "leaf_condition",
								"name" : "Energy level is low",
								"condition" : "this.energy < 0.3"
							},
							{
								"type" : "leaf_move_to",
								"name" : "Move to energy source",
								"to" : "energy source"
							},
							{
								"type" : "leaf_wait",
								"name" : "Wait for reload",
								"delay" : "2.0"
							}
						]
					},
					{
						"type" : "composite_sequence",
						"name" : "Patrol",
						"children" : [
							{
								"type" : "leaf_move_to",
								"name" : "Move to A",
								"to" : "a"
							},
							{
								"type" : "leaf_wait",
								"name" : "Wait at point A",
								"delay" : "1.0"
							},
							{
								"type" : "leaf_move_to",
								"name" : "Move to B",
								"to" : "b"
							},								
							{
								"type" : "leaf_wait",
								"name" : "Wait at point B",
								"delay" : "1.0"
							}
						]
					}
				]
			}
		)"_json;
		neko::BasicEngine::Init();
	}

	void Update() override
	{
		neko::BasicEngine::Update();
	}

	void TearDown() override {
		neko::BasicEngine::Destroy();
	}

	json jsonBehaviorTree_;
	std::shared_ptr<neko::BehaviorTreeNode> behaviorTreeNodePtr_;
};

TEST_F(BehaviorTreeTest, IsInitFromJsonWorking) {
	EXPECT_TRUE(neko::ParseBehaviorTreeFromJson(jsonBehaviorTree_));
}

TEST_F(BehaviorTreeTest, IsBehaviorTreeCorrect) {
	behaviorTreeNodePtr_ = neko::ParseBehaviorTreeFromJson(jsonBehaviorTree_);
	EXPECT_TRUE(behaviorTreeNodePtr_);
	{	// Base selector
		const neko::BehaviorTreeCompositeSelector* selector =
			dynamic_cast<neko::BehaviorTreeCompositeSelector*>(behaviorTreeNodePtr_.get());
		ASSERT_NE(selector, nullptr);
		const std::vector<std::shared_ptr<neko::BehaviorTreeNode>>& selector_children =
			selector->GetChildrenList();
		EXPECT_EQ(selector_children.size(), 2);
		{	// First sequence
			const neko::BehaviorTreeCompositeSequence* sequence =
				dynamic_cast<neko::BehaviorTreeCompositeSequence*>(selector_children[0].get());
			ASSERT_NE(sequence, nullptr);
			const std::vector<std::shared_ptr<neko::BehaviorTreeNode>>& sequence_children =
				sequence->GetChildrenList();
			EXPECT_EQ(sequence_children.size(), 3);
			{
				const neko::BehaviorTreeLeafCondition* condition =
					dynamic_cast<neko::BehaviorTreeLeafCondition*>(sequence_children[0].get());
				ASSERT_NE(condition, nullptr);
				EXPECT_EQ(condition->GetVariable("condition"), "this.energy < 0.3");
			}
			{
				const neko::BehaviorTreeLeafMoveTo* move_to =
					dynamic_cast<neko::BehaviorTreeLeafMoveTo*>(sequence_children[1].get());
				ASSERT_NE(move_to, nullptr);
				EXPECT_EQ(move_to->GetVariable("to"), "energy source");
			}
			{
				const neko::BehaviorTreeLeafWait* leaf_wait =
					dynamic_cast<neko::BehaviorTreeLeafWait*>(sequence_children[2].get());
				ASSERT_NE(leaf_wait, nullptr);
				EXPECT_EQ(leaf_wait->GetVariable("delay"), "2.0");
			}
		}
		{	// Second sequence
			const neko::BehaviorTreeCompositeSequence* sequence =
				dynamic_cast<neko::BehaviorTreeCompositeSequence*>(selector_children[1].get());
			ASSERT_NE(sequence, nullptr);
			const std::vector<std::shared_ptr<neko::BehaviorTreeNode>>& sequence_children =
				sequence->GetChildrenList();
			EXPECT_EQ(sequence_children.size(), 4);
			{
				const neko::BehaviorTreeLeafMoveTo* move_to =
					dynamic_cast<neko::BehaviorTreeLeafMoveTo*>(sequence_children[0].get());
				ASSERT_NE(move_to, nullptr);
				EXPECT_EQ(move_to->GetVariable("to"), "a");
			}
			{
				const neko::BehaviorTreeLeafWait* leaf_wait =
					dynamic_cast<neko::BehaviorTreeLeafWait*>(sequence_children[1].get());
				ASSERT_NE(leaf_wait, nullptr);
				EXPECT_EQ(leaf_wait->GetVariable("delay"), "1.0");
			}
			{
				const neko::BehaviorTreeLeafMoveTo* move_to =
					dynamic_cast<neko::BehaviorTreeLeafMoveTo*>(sequence_children[2].get());
				ASSERT_NE(move_to, nullptr);
				EXPECT_EQ(move_to->GetVariable("to"), "b");
			}
			{
				const neko::BehaviorTreeLeafWait* leaf_wait =
					dynamic_cast<neko::BehaviorTreeLeafWait*>(sequence_children[3].get());
				ASSERT_NE(leaf_wait, nullptr);
				EXPECT_EQ(leaf_wait->GetVariable("delay"), "1.0");
			}
		}
	}
}

TEST_F(BehaviorTreeTest, IsBehaviorTreeExecuteCorrect) {
	behaviorTreeNodePtr_ = neko::ParseBehaviorTreeFromJson(jsonBehaviorTree_);
	EXPECT_TRUE(behaviorTreeNodePtr_);
	EXPECT_EQ(behaviorTreeNodePtr_->Execute(), neko::SUCCESS);
}