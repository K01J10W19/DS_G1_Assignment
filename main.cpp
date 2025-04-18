#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "algorithm(jw).cpp"
using namespace std;

// Import csv file to Doubly Linked List 
struct ReviewsNode{
    string product_ID;
    string customer_ID;
    string rating;
    string review_text;
    string product;
    string category;
    string price;
    string date;
    string payment_method;
    ReviewsNode* next = nullptr;
    ReviewsNode* prev = nullptr;
};
// Import csv file to Dynamic Array
struct ReviewsArray{
    string product_ID;
    string customer_ID;
    string rating;
    string review_text;
};
struct TransactionsArray{
    string customer_ID;
    string product;
    string category;
    string price;
    string date;
    string payment_method;
};

// declare function
void CSVToLinkedList(const string& file_name, ReviewsNode*& head, ReviewsNode*& tail);
void CSVToLinkedList2(const string& file_name, ReviewsNode*& head, ReviewsNode*& tail);
void CSVToArrays(const string& file_name, ReviewsArray*& array, int& count, int& capacity);
void CSVToArrays2(const string& file_name, TransactionsArray*& array, int& count, int& capacity);
void resizeArray(ReviewsArray*& array, int& capacity);
void resizeArray(TransactionsArray*& array, int& capacity);
int countCSVLines(const string& filename);

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
    CSVToLinkedList2("transactions_cleaned_csv.csv", head, tail);
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

    // ----- Sorting Algorithms (Quick Sort) && Searching Algorithms (Recursive Search) -----
    // 1. How can you efficiently sort customer transactions by date and display the total number of transactions in both datasets?
    quickSortbydate(ta, 0, transaction_count - 1);



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
        newNode -> rating = item;
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

void CSVToLinkedList2(const string& file_name, ReviewsNode*& head, ReviewsNode*& tail){ // Transactions_CSV
    ifstream file(file_name); // input the file
    string line; // variable called line

    head = tail = nullptr; // head and tail of doubly linked list default to nullptr

    getline(file,line); // Ignore header

    while(getline(file, line)){ // read the file line by line
        stringstream ss(line);  
        string item;
        ReviewsNode* newNode = new ReviewsNode(); // set pointer in doubly linked list

        getline(ss, item, ','); // attribute 01 Customer ID (str)
        newNode -> customer_ID = item;
        getline(ss, item, ','); // attribute 02 product (str)
        newNode -> product = item;
        getline(ss, item, ','); // attribute 03 Category (str)
        newNode -> category = item;
        getline(ss, item, ','); // attribute 04 price (str)
        newNode -> price = item; 
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
        array[count].rating = item; 
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
        array[count].price = item;
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