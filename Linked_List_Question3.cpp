#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm> // for transform
#include <cctype>    // for ispunct
#include <chrono>    // for timing
#include "LinkedList.hpp"
using namespace std;
using namespace std::chrono;

// Load reviews from CSV into doubly linked list
void loadReviews(const string& filename, ReviewsNode*& head, ReviewsNode*& tail) {
    ifstream file(filename);
    string line;
    getline(file, line); // Ignore header

    head = tail = nullptr;

    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        ReviewsNode* newNode = new ReviewsNode();

        getline(ss, item, ',');
        newNode->product_ID = item;
        getline(ss, item, ',');
        newNode->customer_ID = item;
        getline(ss, item, ',');
        newNode->rating = stoi(item);
        getline(ss, item, ',');
        newNode->review_text = item;

        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
}

int countLinkedList(ReviewsNode* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

// Clean word: remove punctuation and make lowercase
void cleanWord(string& word) {
    word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
    transform(word.begin(), word.end(), word.begin(), ::tolower);
}

// Merge two sorted halves by count descending
WordFrequencyll* merge(WordFrequencyll* left, WordFrequencyll* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->count >= right->count) {
        left->next = merge(left->next, right);
        if (left->next) left->next->prev = left;
        left->prev = nullptr;
        return left;
    } else {
        right->next = merge(left, right->next);
        if (right->next) right->next->prev = right;
        right->prev = nullptr;
        return right;
    }
}

// Split linked list into two halves
void split(WordFrequencyll* head, WordFrequencyll*& left, WordFrequencyll*& right) {
    WordFrequencyll* slow = head;
    WordFrequencyll* fast = head->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    left = head;
    right = slow->next;
    slow->next = nullptr;
    if (right) right->prev = nullptr;
}

// Merge Sort
void mergeSort(WordFrequencyll*& head) {
    if (!head || !head->next) return;

    WordFrequencyll* left = nullptr;
    WordFrequencyll* right = nullptr;

    split(head, left, right);

    mergeSort(left);
    mergeSort(right);

    head = merge(left, right);
}

// Analyze one-star reviews
void analyzeOneStarReviews(ReviewsNode* reviewsHead) {
    WordFrequencyll* freqHead = nullptr;
    WordFrequencyll* freqTail = nullptr;

    for (ReviewsNode* current = reviewsHead; current != nullptr; current = current->next) {
        if (current->rating == 1) {
            stringstream ss(current->review_text);
            string word;
            while (ss >> word) {
                cleanWord(word);
                if (word.empty()) continue;

                // Linear search
                WordFrequencyll* temp = freqHead;
                bool found = false;
                while (temp != nullptr) {
                    if (temp->word == word) {
                        temp->count++;
                        found = true;
                        break;
                    }
                    temp = temp->next;
                }

                if (!found) {
                    WordFrequencyll* newNode = new WordFrequencyll();
                    newNode->word = word;
                    newNode->count = 1;
                    newNode->next = nullptr;
                    newNode->prev = nullptr;

                    if (!freqHead) {
                        freqHead = freqTail = newNode;
                    } else {
                        freqTail->next = newNode;
                        newNode->prev = freqTail;
                        freqTail = newNode;
                    }
                }
            }
        }
    }

    // Sort by frequency
    mergeSort(freqHead);

    cout << "\nMost Frequent Words in 1-Star Reviews:\n";
    cout << "---------------------------------------\n";
    WordFrequencyll* temp = freqHead;
    while (temp != nullptr) {
        cout << temp->word << ": " << temp->count << endl;
        temp = temp->next;
    }

    // Free memory
    while (freqHead != nullptr) {
        WordFrequencyll* toDelete = freqHead;
        freqHead = freqHead->next;
        delete toDelete;
    }
}

// Clear review linked list
void clearReviewsList(ReviewsNode*& head) {
    while (head != nullptr) {
        ReviewsNode* temp = head;
        head = head->next;
        delete temp;
    }
}

size_t estimateStringSize(const string& str) {
    return str.capacity();  // Approximates heap memory used for the string
}

size_t estimateMemoryUsage(ReviewsNode* head) {
    size_t total = 0;
    while (head) {
        total += sizeof(ReviewsNode);
        total += estimateStringSize(head->product_ID);
        total += estimateStringSize(head->customer_ID);
        total += estimateStringSize(head->review_text);
        total += sizeof(int); // rating
        head = head->next;
    }
    return total;
}

int main() {
    ReviewsNode* reviewsHead = nullptr;
    ReviewsNode* reviewsTail = nullptr;

    loadReviews("reviews_cleaned.csv", reviewsHead, reviewsTail);

    auto start = high_resolution_clock::now();

    analyzeOneStarReviews(reviewsHead);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Total Review: " << countLinkedList(reviewsHead) << endl;

    cout << "\nTime taken to analyze one-star reviews: " << duration.count() << " milliseconds\n";

    size_t memoryUsed = estimateMemoryUsage(reviewsHead);
    cout << "\nEstimated memory used: " << memoryUsed << " bytes\n";

    clearReviewsList(reviewsHead);

    return 0;
}
