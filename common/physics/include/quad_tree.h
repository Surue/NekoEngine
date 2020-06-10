/*
 MIT License

 Copyright (c) 2020 SAE Institute Switzerland AG

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
#pragma once

#include "rigidbody.h"
#include "contact.h"

namespace neko::physics
{
/**
 * \brief Object used to do space partitioning used in the broad phase
 */
class QuadTree
{
public:
    /**
     * \brief Create a default node at depth 0 without any aabb.
     */
    QuadTree() = default;

    /**
     * \brief Constructor of quadtree with aabb
     * \param nodeDepth depth of the current node
     * \param aabb
     */
    QuadTree(uint8_t nodeDepth, AABB aabb) : bounds_(aabb) { }
    ~QuadTree() = default;

    /**
     * \brief This function is called to split a node into 4 smaller node.
     */
    void Split()
    {
        //TODO Create child nodes

        //TODO Inset bodies into child nodes
    }

    /**
     * \brief Return the index of the child tree of the given body.
     * \details by example if this node is divided, it returns the index of the quadrant
     * \param body to test
     * \return index of the child's node, if it's not in a child return -1
     */
    int GetIndex(const RigidBody* body)
    {
        //TODO Check if node has been split

        //TODO if has been Split => call children

        return -1;
    }

    /**
     * \brief Insert a body into the quadtree
     * \param body
     */
    void Insert(RigidBody* body)
    {
        //TODO Check has been split

        //TODO If not split => Add direct

        //TODO if too much body => Split()

        //TODO  IF has been split
    }

    /**
     * \brief Return all possible contact
     * \details Those possible contact are checked only using their aabbs
     * \return
     */
    std::vector<Contact> Retrieve()
    {
        std::vector<Contact> possibleContacts;

        //TODO if node has body, check every body against the other

        //TODO if node has zero body, call child.Retrieve()

        return possibleContacts;
    }

private:
    static const int NB_CHILD_NODE = 4;
    static const int MAX_BODY = 10;
    static const int MAX_DEPTH = 5;

    int nodeDepth_ = 0;

    AABB bounds_;

    std::vector<RigidBody*> bodies_;
    std::vector<QuadTree> children_;
};
} // namespace neko::physics