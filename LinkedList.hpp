#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
# include <string>
using namespace std;

// Import "Review.CSV" to LinkedList
struct ReviewsNode{
    string product_ID;
    string customer_ID;
    int rating;
    string review_text;
    ReviewsNode* next = nullptr;
    ReviewsNode* prev = nullptr;
};

// Import "Transaction.CSV" to LinkedList
struct TransactionsNode {
    string customer_ID;
    string product;
    string category;
    float price;
    string date;
    string payment_method;
    TransactionsNode* next = nullptr;
    TransactionsNode* prev = nullptr;
};

// Review Frequency
struct WordFrequencyll{
    string word;
    int count;
    WordFrequencyll* prev = nullptr;
    WordFrequencyll* next = nullptr;
};

// declaration Methods
void ReviewsToLinkedList(const string& file_name, ReviewsNode*& head, ReviewsNode*& tail);
void TransactionsToLinkedList(const string& file_name, TransactionsNode*& head, TransactionsNode*& tail);
int countLinkedList(ReviewsNode* head);
int countLinkedList(TransactionsNode* head);
void clearLinkedList(ReviewsNode*& head);
void clearLinkedList(TransactionsNode*& head);
// Question 01
string convertDateFormatll(const string& date);
TransactionsNode* partitionbydatell(TransactionsNode* low, TransactionsNode* high);
void quickSortbydatell(TransactionsNode* low, TransactionsNode* high);
void displayTransactions(TransactionsNode* head);
int countTransactions(TransactionsNode* head);
// Question 02
string normalizell(string& str);
int countElectronicsCredit(TransactionsNode* node);
int countElectronicsTotal(TransactionsNode* node);
TransactionsNode* partitionbycategoryll(TransactionsNode* low, TransactionsNode* high);
void quickSortbycategoryll(TransactionsNode* low, TransactionsNode* high);
void displayCategory(TransactionsNode* head);
// Question 03
void countWordsFromOnell(ReviewsNode* head, WordFrequencyll*& wf_head, int& totalWords);
void printWordOccurrences(WordFrequencyll* wf_head);
void printWordOccurrences2(WordFrequencyll* wf_head);
void sortWordListByFrequency(WordFrequencyll*& head);

#endif