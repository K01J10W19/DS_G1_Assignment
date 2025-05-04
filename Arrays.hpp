#ifndef ARRAYS_HPP
#define ARRAYS_HPP
#include <string>
using namespace std;

// Import "Reviews.CSV" to Array
struct ReviewsArray{
    string product_ID;
    string customer_ID;
    int rating;
    string review_text;
};

// Import "Transaction.CSV" to Array
struct TransactionsArray{
    string customer_ID;
    string product;
    string category;
    float price;
    string date;
    string payment_method;
};

// Review Frequency
struct WordFrequency{
    string word;
    int count;
};

// Declaration Methods
void ReviewsToArrays(const string& file_name, ReviewsArray*& array, int& count);
void TransactionToArrays(const string& file_name, TransactionsArray*& array, int& count);
// Question 01
string convertDateFormat(const string& date);
int partitionbydate(TransactionsArray* arr, int low, int high);
void quickSortbydate(TransactionsArray* arr, int low, int high);
void recursiveSearchByCustomerID(TransactionsArray* arr, int index, int size, const string& targetID, int num);
// Yi Xian
void bubbleSortByDate(TransactionsArray* arr, int count);
int binarySearchCustomerID(TransactionsArray* arr, int size, const string& customerID);
void displayAllCustomerTransactions(TransactionsArray* arr, int size, const string& customerID); // Display all transactions for a given customer ID (expands from binary search result)

// Question 02
string normalize(string& str);
int partitionbycategory(TransactionsArray* arr, int low, int high);
void quickSortbycategory(TransactionsArray* arr, int low, int high);
int countElectronics(TransactionsArray* arr, int index, int size);
int countElectronicsCreditCard(TransactionsArray* arr, int index, int size);
//YiXian
void bubbleSortByCategory(TransactionsArray* arr, int count);
int binarySearchCategory(TransactionsArray* arr, int size, const string& category);
void countElectronicsAndCreditCard_Binary(TransactionsArray* arr, int size, int& total, int& creditCard);
string normalize(const string& text);
// Question 03
void countWordsFromOne(ReviewsArray* review, int& count, WordFrequency*& wf, int& wordCount);
int partitionbyword(WordFrequency* arr, int low, int high);
void quickSortWords(WordFrequency* arr, int low, int high);
#endif