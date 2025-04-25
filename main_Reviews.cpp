#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <chrono>
#include "Arrays.hpp"
#include "LinkedList.hpp"
using namespace std;
//// Measure Time Efficiency
using namespace chrono;
template<typename Func>
void Measure_Time(Func func){
    auto begin = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - begin);
    cout << "Time taken: "<< duration.count() << " ms"<<endl;
}
int main(){
    // ----- Reviews of Arrays -----
    int review_count = 0;
    ReviewsArray* ra = nullptr;
    ReviewsToArrays("reviews_cleaned.csv", ra, review_count);
    // for(int i = 0; i < review_count; ++i){
    //     cout << ra[i].product_ID <<", "<<ra[i].customer_ID<<", "<<ra[i].rating<<", "<<ra[i].review_text<<"\n";
    // }
    cout<<"Total lines to read (Review Arrays): "<<review_count<<endl;
    cout<<"Estimated Memory for Array: "<< sizeof(ReviewsArray) * review_count <<" bytes"<<endl;

    // ----- Reviews of LinkedList -----
    ReviewsNode* head = nullptr;
    ReviewsNode* tail = nullptr;
    ReviewsToLinkedList("reviews_cleaned.csv", head, tail);
    // for (ReviewsNode* temp = head; temp != nullptr; temp = temp->next) {
    //     std::cout << temp->product_ID << ", " << temp->customer_ID << ", " << temp->rating << ", "<< temp->review_text << "\n";
    // }
    cout<<"Total lines to read: (Review LinkedList): "<<countLinkedList(head)<<endl;
    int reviewsnodeSize = sizeof(ReviewsNode) + sizeof(ReviewsNode*) * 2;
    cout<<"Estimated Memory (Review Linked List): "<< reviewsnodeSize * review_count <<" bytes"<<endl;
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//// 3. Which words are most frequently used in product reviews rated 1-star?
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Koh Chun Wei TP067580 (Quick Sort & Recursion Search)
//// Array
    WordFrequency* wf = nullptr;
    int word_count = 0, total = 0;
    // countWordsFromOne(ra, review_count, wf, word_count);
    // quickSortWords(wf,0,word_count - 1);
    //// Print Total Result of Words
    // for (int i = 0; i < word_count; ++i) {
    //     cout << wf[i].word << ": " << wf[i].count << endl;
    //     total += wf[i].count;
    // }
    //// Print Each Words
    // for (int i = 0; i < word_count; ++i) {
    //     for (int j = 0; j < wf[i].count; ++j) {
    //         cout << wf[i].word << " - 1" << endl;
    //     }
    // }
    // cout<<"Total Words in 1-Star Reviews (Arrays): "<<total<<endl;
    cout<<"Quick Sorting & Recursion Searching for Array [Question03]: ";
    Measure_Time([&](){quickSortWords(wf, 0, word_count - 1);});
//// LinkedList
    WordFrequencyll* wf_head = nullptr;
    // int totalWordCount = 0;
    // countWordsFromOnell(head, wf_head, totalWordCount);
    // sortWordListByFrequency(wf_head);
    //// Print Total Result of Words
    // printWordOccurrences2(wf_head);
    // cout<<"Total Words in 1-Star Reviews (LinkedList): "<<totalWordCount<<endl;
    //// Print Each Words
    // printWordOccurrences(wf_head);
    cout<<"Quick Sorting & Recursion Searching for LinkedList [Question03]: ";
    Measure_Time([&](){sortWordListByFrequency(wf_head);});
//// U Guys Can Add+ Here below continue
    




/////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Clear the Pointer after Completed
    delete[] ra;
    clearLinkedList(head);
    return 0;
}