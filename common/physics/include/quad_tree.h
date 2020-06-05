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

#include "body_2d.h"
#include "contact.h"

namespace neko::physics {
/**
 * \brief Object used to do space partitionning used in the broad phase
 */
class QuadTree {

    /**
     * \brief This function is called to split a node into 4 smaller node.
     */
    void Split(){
        //TODO Complete this function
    }

    /**
     * \brief Return the index of the child tree of the given body.
     * \param body to test
     * \return index of the node
     */
    int GetIndex(const Body* body) {
        //TODO Complete this function
        return 0;
    }

    /**
     * \brief Insert a body into the quadtree
     * \param body
     */
    void Insert(const Body* body) {
    //TODO Complete this function
    }

    /**
     * \brief Return all possible contact
     * \details Those possible contact are checked only using their aabbs
     * \return
     */
    std::vector<Contact> Retrive(){
        //TODO Complete this function
        return {};
    }

private:
    static const int NB_CHILD_NODE = 4;

    std::vector<Body*> bodies_;
    std::unique_ptr<QuadTree> childNodes_[NB_CHILD_NODE];
};
} // namespace neko::physics