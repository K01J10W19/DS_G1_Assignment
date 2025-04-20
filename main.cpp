#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include "algorithm_jw.cpp"
#include <chrono>
using namespace std;
using namespace chrono;
template<typename Func>
// Calculate Time Efficiency
void Measure_Time(Func func){
    auto begin = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - begin);
    cout << "Time taken: "<< duration.count() << " ms"<<endl;
}
// // Import csv file to Doubly Linked List 
// struct ReviewsNode{
//     string product_ID;
//     string customer_ID;
//     int rating;
//     string review_text;
//     string product;
//     string category;
//     float price;
//     string date;
//     string payment_method;
//     ReviewsNode* next = nullptr;
//     ReviewsNode* prev = nullptr;
// };
// // Import csv file to Dynamic Array
// struct ReviewsArray{
//     string product_ID;
//     string customer_ID;
//     int rating;
//     string review_text;
// };
// struct TransactionsArray{
//     string customer_ID;
//     string product;
//     string category;
//     float price;
//     string date;
//     string payment_method;
// };

// declare function
void CSVToLinkedList(const string& file_name, ReviewsNode*& head, ReviewsNode*& tail);
void CSVToLinkedList2(const string& file_name, TransactionsNode*& head, TransactionsNode*& tail);
void CSVToArrays(const string& file_name, ReviewsArray*& array, int& count, int& capacity);
void CSVToArrays2(const string& file_name, TransactionsArray*& array, int& count, int& capacity);
void resizeArray(ReviewsArray*& array, int& capacity);
void resizeArray(TransactionsArray*& array, int& capacity);
int countCSVLines(const string& filename);
// declare function from algorithm(jw).cpp
void quickSortbydate(TransactionsArray* arr, int low, int high);
void recursiveSearchByCustomerID(TransactionsArray* arr, int index, int size, const string& targetID);
void quickSortbycategory(TransactionsArray* arr, int low, int high);
// Main 
int main(){
    // ----- check * information in file ----- 
    // string filename = "reviews_cleaned_csv.csv";
    // int totalLines = countCSVLines(filename);
    // cout <<"Total lines in CSV: "<< totalLines<< '\n';

    // ----- Read by Array -----
    int capacity = 10;
    int review_count = 0, transaction_count = 0;
    // int test_1a = 0, test_1b = 0;
    // ----- Print it from file as reviews -----
    ReviewsArray* ra = new ReviewsArray[capacity];
    CSVToArrays("reviews_cleaned_csv.csv", ra, review_count, capacity);
    // cout <<"Array - based Reviews\n";
    // for(int i = 0; i < review_count; ++i){
    //     cout << ra[i].product_ID <<", "<<ra[i].customer_ID<<", "<<ra[i].rating<<", "<<ra[i].review_text<<"\n";
    //     test_1a++;
    //     if ((test_1a + 1) % 1000 == 0) {
    //         std::cout << "\n--- Press Enter to continue ---";
    //         std::cin.ignore(); // Waits for Enter key
    //     }
    // }
    // cout<<"Total lines to read: "<<test_1a<<endl;
    // ----- Print it from file as transactions -----
    TransactionsArray* ta = new TransactionsArray[capacity];
    CSVToArrays2("transactions_cleaned_csv.csv", ta, transaction_count, capacity);
    // cout <<"Array - based Transactions\n";
    // for(int i = 0; i < transaction_count; ++i){
    //     cout << ta[i].customer_ID <<", "<<ta[i].product<<", "<<ta[i].category<<", "<<ta[i].price<<", "<<ta[i].date<<", "<<ta[i].payment_method<<"\n";
    //     test_1b++;
    //     if ((test_1b + 1) % 1000 == 0) {
    //         std::cout << "\n--- Press Enter to continue ---";
    //         std::cin.ignore(); // Waits for Enter key
    //     }
    // }
    // cout<<"Total lines to read: "<<test_1b<<endl;

    // ----- Read by Linked List -----
    ReviewsNode* head = nullptr;
    ReviewsNode* tail = nullptr;
    TransactionsNode* head2 = nullptr;
    TransactionsNode* tail2 = nullptr;
    ReviewFrequencyll* head3 = nullptr;
    ReviewFrequencyll* tail3 = nullptr;
    // int test_2a = 0, test_2b = 0;
    CSVToLinkedList("reviews_cleaned_csv.csv", head, tail);

    // ----- Print it from forward of reviews -----
    // for (ReviewsNode* temp = head; temp != nullptr; temp = temp->next) {
    //     std::cout << temp->product_ID << ", " << temp->customer_ID << ", " << temp->rating << ", "<< temp->review_text << "\n";
    //     test_2a++;
    //     if ((test_2a + 1) % 100 == 0) {
    //         std::cout << "\n--- Press Enter to continue ---";
    //         std::cin.ignore(); // Waits for Enter key
    //     }
    // }
    // cout<<"Total lines to read: "<<test_2a<<endl;

    // ----- Print it from forward of transactions -----
    CSVToLinkedList2("transactions_cleaned_csv.csv", head2, tail2);
    // for (ReviewsNode* temp = head; temp != nullptr; temp = temp->next) {
    //     std::cout << temp->customer_ID << ", " << temp->product << ", " << temp->category << ", "<< temp->price << ", "<< temp->date<<", "<< temp->payment_method << "\n";
    //     test_2b++;
    //     if ((test_2b + 1) % 100 == 0) {
    //         std::cout << "\n--- Press Enter to continue ---";
    //         std::cin.ignore(); // Waits for Enter key
    //     }
    // }
    // cout<<"Total lines to read: "<<test_2b<<endl;

    // ----- Print it from backward of reviews -----
    // for (ReviewsNode* temp = tail; temp != nullptr; temp = temp->prev) {
    //     std::cout << temp->product_ID << ", " << temp->customer_ID << ", " << temp->rating << ", "<< temp->review_text <<"\n";
    //     test_2a++
    // }
    // cout<<"Total lines to read: "<<test_2a<<endl;

    // ----- Print it from backward of transactions -----
    // for (ReviewsNode* temp = tail; temp != nullptr; temp = temp->prev) {
    //     std::cout << temp->customer_ID << ", " << temp->product << ", " << temp->category << ", "<< temp->price << ", "<< temp->date<<", "<< temp->payment_method << "\n";
    //     test_2b++;
    // }
    // cout<<"Total lines to read: "<<test_2b<<endl;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ----- Sorting Algorithms (Quick Sort) && Searching Algorithms (Recursive Search) OF ARRAYS-----
    // 1. How can you efficiently sort customer transactions by date and display the total number of transactions in both datasets?
    // quickSortbydate( ta , 0 , transaction_count - 1);
    // cout << "Sorted Transactions by Date (Array):\n";
    // for (int i = 0; i < transaction_count; ++i) {
    //     cout << ta[i].customer_ID << ", "<< ta[i].product << ", "<< ta[i].date << "\n";
    // }
    
    // cout << "\nTotal Transactions (Array): " << transaction_count << endl;

    // string cid;
    // cout << "----- Transactions History -----\n";
    // cout << "\nSearch for customer ID 'CUST1234': ";
    // cin >> cid;
    // transform(cid.begin(), cid.end(), cid.begin(), ::toupper);
    // recursiveSearchByCustomerID(ta, 0, transaction_count, cid, 1);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 2. What percentage of purchases in the “Electronics” category were made using Credit Card payments? 
    // quickSortbycategory(ta, 0, transaction_count - 1);
    // cout << "Sorted Category:\n";
    // for(int i = 0; i < transaction_count; ++i){
    //     cout << ta[i].customer_ID <<", "<< ta[i].product << ", "<<ta[i].category<<endl;
    // }
    // int totalElectronics = countElectronics(ta, 0, transaction_count);
    // int ccElectronics = countElectronicsCreditCard(ta, 0, transaction_count);
    // cout <<"Total Electronics in Category: "<<totalElectronics<<" / "<<transaction_count<<endl;
    // cout <<"Payment Method of Credit Card in Electronics: "<<ccElectronics<<" / "<<totalElectronics<<endl;
    // if(totalElectronics > 0){
    //     double percentage = (double)ccElectronics / totalElectronics * 100;
    //     cout <<"Electronics purchases with Credit Card: "<<percentage<<"%"<<endl;
    // }else{
    //     cout << "No Category of Electronics found.\n";
    // }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 3. Which words are most frequently used in product reviews rated 1-star? 
    // int sentencecount = 0;
    // ReviewFrequency* ra_review = new ReviewFrequency[capacity];
    // extractFrequentSentences(ra, review_count, ra_review, sentencecount, capacity);
    // quickSortsentencesbyfrequency(ra_review, 0, sentencecount - 1);
    // for(int i = 0; i < sentencecount; ++i){
    //     cout << ra_review[i].sentence <<", "<< ra_review[i].count <<endl;
    // }
    // showTopFrequentSentences(ra_review, sentencecount, 10);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ----- Sorting Algorithms (Quick Sort) && Searching Algorithms (Recursive Search) OF LINKED LIST -----
    // quickSortbydatell(head2, tail2);
    // cout<<"\nSorted Transactions by Date(Linked List):\n";
    // displayTransactions(head2);
    // int total = countTransactions(head2);
    // cout<<"\nTotal Transactions: (Linked List): "<< total << endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // int totalElectronics = countElectronicsTotal(head2);
    // int electronicsWithCreditCard = countElectronicsCredit(head2);
    // cout <<"Total Electronics in Category: "<<totalElectronics<<" / "<<countTransactions(head2)<<endl;
    // cout <<"Payment Method of Credit Card in Electronics: "<<electronicsWithCreditCard<<" / "<<totalElectronics<<endl;
    // if (totalElectronics > 0) {
    //     double percentage = (double)electronicsWithCreditCard / totalElectronics * 100;
    //     cout << fixed << setprecision(2);
    //     cout << "Percentage of Electronics purchases using Credit Card: " << percentage << "%" << endl;
    // } else {
    //     cout << "No Electronics purchases found." << endl;
    // }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // extract1StarSentences(head, head3, tail3);
    // quickSortll(head3, getTail(head3));
    // displayTopSentences(head3, 10);
    /// Measure Time Efficiency
    cout<<"Used Quick Sorting for Dynamic Arrays (Sorting Date): ";
    Measure_Time([&](){quickSortbydate(ta , 0 , transaction_count - 1);});
    cout<<"Used Quick Sorting for Doubly Linked List (Sorting Date): ";
    Measure_Time([&](){quickSortbydatell(head2, tail2);});
    cout<<"Estimated Memory (Review Array): "<< sizeof(ReviewsArray) * review_count <<" bytes"<<endl;
    cout<<"Estimated Memory (Transaction Array): "<< sizeof(TransactionsArray) * transaction_count <<" bytes"<<endl;
    int reviewsnodeSize = sizeof(ReviewsNode) + sizeof(ReviewsNode*) * 2;
    int TransactionsnodeSize = sizeof(TransactionsNode) + sizeof(TransactionsNode*) * 2;
    cout<<"Estimated Memory (Review Linked List): "<< reviewsnodeSize * review_count <<" bytes"<<endl;
    cout<<"Estimated Memory (Transaction Linked List): "<< TransactionsnodeSize * transaction_count <<" bytes"<<endl;
    return 0;
}


// function
void CSVToLinkedList(const string& file_name, ReviewsNode*& head, ReviewsNode*& tail){ // Reviews_CSV
    ifstream file(file_name); // input the file
    string line; // variable called line

    head = tail = nullptr; // head and tail of doubly linked list default to nullptr

    getline(file,line); // Ignore header

    while(getline(file, line)){ // read the file line by line
        stringstream ss(line);  
        string item;
        ReviewsNode* newNode = new ReviewsNode(); // set pointer in doubly linked list

        getline(ss, item, ','); // attribute 01 product ID (str)
        newNode -> product_ID = item;
        getline(ss, item, ','); // attribute 02 Customer ID (str)
        newNode -> customer_ID = item;
        getline(ss, item, ','); // attribute 03 Rating (int)
        newNode -> rating = stoi(item);
        getline(ss, item, ','); // attribute 04 Review Text (str)
        newNode -> review_text = item; 

        if(!head){ // if empty means this is a first node
            head = tail = newNode; // head and tail point to newNode
        } else{
            tail-> next = newNode; // link next to the new node
            newNode-> prev = tail; // link prev back to the current tail
            tail = newNode; // update tail to new last node
        }
    }
}

void CSVToLinkedList2(const string& file_name, TransactionsNode*& head, TransactionsNode*& tail){ // Transactions_CSV
    ifstream file(file_name); // input the file
    string line; // variable called line

    head = tail = nullptr; // head and tail of doubly linked list default to nullptr

    getline(file,line); // Ignore header

    while(getline(file, line)){ // read the file line by line
        stringstream ss(line);  
        string item;
        TransactionsNode* newNode = new TransactionsNode(); // set pointer in doubly linked list

        getline(ss, item, ','); // attribute 01 Customer ID (str)
        newNode -> customer_ID = item;
        getline(ss, item, ','); // attribute 02 product (str)
        newNode -> product = item;
        getline(ss, item, ','); // attribute 03 Category (str)
        newNode -> category = item;
        getline(ss, item, ','); // attribute 04 price (double)
        newNode -> price = stof(item); 
        getline(ss, item, ','); // attribute 05 date (str)
        newNode -> date = item;
        getline(ss, item, ','); // attribute 06 payment method (str)
        newNode -> payment_method = item;
        
        if(!head){ // if empty means this is a first node
            head = tail = newNode; // head and tail point to newNode
        } else{
            tail-> next = newNode; // link next to the new node
            newNode-> prev = tail; // link prev back to the current tail
            tail = newNode; // update tail to new last node
        }
    }
}

void resizeArray(ReviewsArray*& array, int& capacity) {
    int newCapacity = capacity * 2;
    ReviewsArray* newArray = new ReviewsArray[newCapacity];
    for (int i = 0; i < capacity; ++i) {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
    capacity = newCapacity;
}

void resizeArray(TransactionsArray*& array, int& capacity) {
    int newCapacity = capacity * 2;
    TransactionsArray* newArray = new TransactionsArray[newCapacity];
    for (int i = 0; i < capacity; ++i) {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
    capacity = newCapacity;
}

void CSVToArrays(const string& file_name, ReviewsArray*& array, int& count, int& capacity){ // Reviews_CSV
    ifstream file(file_name); // input the file
    string line; // variable called line
    getline(file,line); // Ignore header
    while(getline(file, line)){ // read the file line by line
        if(count >= capacity){
            resizeArray(array, capacity); // double the size of array if full
        }
        std::stringstream ss(line);
        std::string item;

        getline(ss, item, ','); // attribute 01 product ID (str)
        array[count].product_ID = item;
        getline(ss, item, ','); // attribute 02 Customer ID (str)
        array[count].customer_ID = item;
        getline(ss, item, ','); // attribute 03 Rating (int)
        array[count].rating = stoi(item); 
        getline(ss, item, ','); // attribute 04 Review Text (str)
        array[count].review_text = item;
        ++count;
    }
}

void CSVToArrays2(const string& file_name, TransactionsArray*& array, int& count, int& capacity){ // transactions_CSV
    ifstream file(file_name); // input the file
    string line; // variable called line
    getline(file,line); // Ignore header
    while(getline(file, line)){ // read the file line by line
        if(count >= capacity){
            resizeArray(array, capacity); // double the size of array if full
        }
        std::stringstream ss(line);
        std::string item;

        getline(ss, item, ','); // attribute 01 customer ID (str)
        array[count].customer_ID = item;
        getline(ss, item, ','); // attribute 02 product (str)
        array[count].product = item;
        getline(ss, item, ','); // attribute 03 category (int)
        array[count].category = item; 
        getline(ss, item, ','); // attribute 04 price (str)
        array[count].price = stof(item);
        getline(ss, item, ','); // attribute 05 date (str)
        array[count].date = item;
        getline(ss, item, ','); // attribute 06 payment method (str)
        array[count].payment_method = item;
        ++count;
    }
}

int countCSVLines(const string& filename) {
    ifstream file(filename);
    string line;
    int count = 0;

    while (getline(file, line)) {
        if (!line.empty()) {
            ++count;
        }
    }

    file.close();
    return count;
}



