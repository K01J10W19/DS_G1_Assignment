#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm> // for transform
#include <cctype>    // for ispunct
#include <chrono>    // for timing
#include "Arrays.hpp" // <-- your header
using namespace std;
using namespace std::chrono;

void loadReviews(const string& filename, ReviewsArray*& array, int& count) {
    ifstream file(filename);
    string line;
    int capacity = 10;
    array = new ReviewsArray[capacity];
    getline(file, line); // Ignore header

    while (getline(file, line)) {
        if (count >= capacity) {
            int newCapacity = capacity * 2;
            ReviewsArray* temp = new ReviewsArray[newCapacity];
            for (int i = 0; i < count; ++i) {
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
            capacity = newCapacity;
        }

        stringstream ss(line);
        string item;

        getline(ss, item, ',');
        array[count].product_ID = item;

        getline(ss, item, ',');
        array[count].customer_ID = item;

        getline(ss, item, ',');
        array[count].rating = stoi(item);

        getline(ss, item, ',');
        array[count].review_text = item;

        count++;
    }
}

void cleanWord(string& word) {
    word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
    transform(word.begin(), word.end(), word.begin(), ::tolower);
}

void merge(WordFrequency* arr, int left, int mid, int right) {
    int sizeL = mid - left + 1;
    int sizeR = right - mid;

    WordFrequency* L = new WordFrequency[sizeL];
    WordFrequency* R = new WordFrequency[sizeR];

    for (int i = 0; i < sizeL; i++) L[i] = arr[left + i];
    for (int i = 0; i < sizeR; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < sizeL && j < sizeR) {
        if (L[i].count >= R[j].count) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < sizeL) arr[k++] = L[i++];
    while (j < sizeR) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(WordFrequency* arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void analyzeOneStarReviews(ReviewsArray* reviews, int count) {
    WordFrequency* wordCounts = new WordFrequency[5000];
    int wordCountSize = 0;

    for (int i = 0; i < count; ++i) {
        if (reviews[i].rating == 1) {
            stringstream ss(reviews[i].review_text);
            string word;
            while (ss >> word) {
                cleanWord(word);
                if (word.empty()) continue;

                bool found = false;
                for (int j = 0; j < wordCountSize; ++j) {
                    if (wordCounts[j].word == word) {
                        wordCounts[j].count++;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    wordCounts[wordCountSize].word = word;
                    wordCounts[wordCountSize].count = 1;
                    wordCountSize++;
                }
            }
        }
    }

    // Sort the words using merge sort
    mergeSort(wordCounts, 0, wordCountSize - 1);

    // Display all words sorted by frequency
    cout << "\nMost Frequent Words in 1-Star Reviews:\n";
    cout << "---------------------------------------\n";
    for (int i = 0; i < wordCountSize; ++i) {
        cout << wordCounts[i].word << ": " << wordCounts[i].count << endl;
    }

    delete[] wordCounts;

}

size_t estimateStringSize(const string& str) {
    return str.capacity(); // Only count dynamic allocation on heap
}

size_t estimateMemoryUsage(ReviewsArray* array, int count) {
    size_t total = 0;
    for (int i = 0; i < count; ++i) {
        total += sizeof(ReviewsArray);
        total += estimateStringSize(array[i].product_ID);
        total += estimateStringSize(array[i].customer_ID);
        total += estimateStringSize(array[i].review_text);
        total += sizeof(int); // rating
    }
    return total;
}


int main() {
    ReviewsArray* reviews = nullptr;
    int reviewCount = 0;

    loadReviews("reviews_cleaned.csv", reviews, reviewCount);

    // Time the analysis
    auto start = high_resolution_clock::now();

    analyzeOneStarReviews(reviews, reviewCount);
    

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Total number of review: " << reviewCount << endl;

    cout << "\nTime taken to analyze one-star reviews: " << duration.count() << " milliseconds\n";

    size_t memoryUsed = estimateMemoryUsage(reviews, reviewCount);
    cout << "\nEstimated memory used during execution: " << memoryUsed << " bytes\n";
    

    const size_t wordCountsMemory = sizeof(WordFrequency) * 5000;
    memoryUsed += wordCountsMemory;


    delete[] reviews;
    return 0;
}
