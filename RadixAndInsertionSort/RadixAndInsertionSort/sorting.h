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

template<typename Iter, typename Comparator>
void bubbleSort(const Iter& begin, const Iter& end, Comparator compareFn)
{
}

template<typename Iter, typename Comparator>
void insertionSort(const Iter& begin, const Iter& end, Comparator compareFn)
{
    for (i = begin+1; i != end; i++) {
        for (j = i-1; j !=begin ;j-- ) {
            if(*i < *j) {
                swap(*i, *j);
            }
        }
    }
}

template<typename Iter>
void radixSort(const Iter& begin, const Iter& end) {
    auto divisor = 1;
    map<int, vector<auto>> buckets; zero, one, two, three, four, five, six, seven, eight, nine;
    for (auto i = begin; i / divisor != 0; i++) {
        
        auto remainder = i / divisor % 10;
        if (not buckets.find(remainder)) {
            vector<auto>* ptr= new vector<auto>
            buckets.insert(pair<int, vector<auto>(remainder, *ptr ));
            ptr->pushback.(*i);
        }
        else {
            buckets[remainder].pushback(*i)
        }
        divisor *= 10;
    }
    //Sorting the array
    for (size_t j = 0; j < 9; j++) {
        i
    }
}