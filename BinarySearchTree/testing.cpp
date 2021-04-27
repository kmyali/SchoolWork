/*
 * Copyright 2018 Jonathan Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "BST.h"

#include <iostream>

int main()
{
    struct studentID {
        uint16_t year_;
        uint32_t serial_;

        static bool compareYear(const studentID& a, const studentID& b) {
            return a.year_ < b.year_;
        }
        static bool compareSerial(const studentID& a, const studentID& b) {
            return a.serial_ < b.serial_;
        }

    };

    BinarySearchTree<int> bst;

    bst.insert(50);
    bst.insert(38);
    bst.insert(73);
    bst.insert(66);
    bst.insert(88);
    bst.insert(42);
    bst.insert(22);
    bst.insert(20);
    bst.insert(30);



    
    bst.printDot(std::cout);
    bst.rotateRight();
    bst.printDot(std::cout); 
    bst.rotateLeft();
    bst.printDot(std::cout); // 



    //bst.print(std::cout);

    return 0;
}