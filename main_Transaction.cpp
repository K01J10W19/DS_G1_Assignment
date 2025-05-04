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
    //// ----- Transaction of Arrays -----
    int transaction_count = 0;
    TransactionsArray* ta = nullptr;
    TransactionToArrays("transactions_cleaned.csv", ta, transaction_count);
    // for(int i = 0; i < transaction_count; ++i){
    //     cout << ta[i].customer_ID <<", "<<ta[i].product<<", "<<ta[i].category<<", "<<ta[i].price<<", "<<ta[i].date<<", "<<ta[i].payment_method<<"\n";
    // }
    cout<<"Total lines to read (Transaction Arrays): "<<transaction_count<<endl;
    cout<<"Estimated Memory for Array: "<< sizeof(TransactionsArray) * transaction_count <<" bytes"<<endl;
    //// ----- Transaction of LinkedList -----
    TransactionsNode* head = nullptr;
    TransactionsNode* tail = nullptr;
    TransactionsToLinkedList("transactions_cleaned.csv",head, tail);
    // for (TransactionsNode* temp = head; temp != nullptr; temp = temp->next) {
    //     std::cout << temp->customer_ID << ", " << temp->product << ", " << temp->category << ", "<< temp->price << ", "<< temp->date<<", "<< temp->payment_method << "\n";
    // }
    cout<<"Total lines to read (Transaction LinkedList): "<<countLinkedList(head)<<endl;
    int TransactionsnodeSize = sizeof(TransactionsNode) + sizeof(TransactionsNode*) * 2;
    cout<<"Estimated Memory (Transaction Linked List): "<< TransactionsnodeSize * transaction_count <<" bytes"<<endl;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// 1. How can you efficiently sort customer transactions by date and display the total number of transactions in both datasets?    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Koh Chun Wei TP067580 (Quick Sort & Recursion Search)
//// Array
    // quickSortbydate(ta, 0, transaction_count - 1);
    // for (int i = 0; i < transaction_count; ++i) {
    //     cout << ta[i].customer_ID << ", "<< ta[i].product << ", "<< ta[i].date << "\n";
    // }
    // cout<<"Total Transaction Arrays: "<<transaction_count<<endl;
    // string cid;
    // cout << "----- Transactions History -----\n";
    // cout << "\nSearch for customer ID 'CUST1234': ";
    // cin >> cid;
    // transform(cid.begin(), cid.end(), cid.begin(), ::toupper);
    // recursiveSearchByCustomerID(ta, 0, transaction_count, cid, 1);
    //cout<<"Quick Sorting & Recursion Searching for Array [Question01]: ";
    //Measure_Time([&](){quickSortbydate(ta, 0, transaction_count - 1);});
//// LinkedList
    // quickSortbydatell(head,tail);
    // displayTransactions(head);
    // cout<<"\nTotal Transactions Linked List: "<< countTransactions(head) << endl;
    //cout<<"Quick Sorting & Recursion Searching for Linked List [Question01]: ";
    //Measure_Time([&](){quickSortbydatell(head, tail);});
//// U Guys Can Add+ Here below continue
//// Array YIxian
//     cout << "Sorting transactions by date using Bubble Sort.123..\n";
//     bubbleSortByDate(ta, transaction_count);
//     cout << "\nTotal Number of Transactions: " << transaction_count << endl;
//     cout << "Sorted Transactions (by Date):\n";
//     for (int i = 0; i < transaction_count; ++i) {
//         cout << ta[i].customer_ID << ", " 
//              << ta[i].product << ", " 
//              << ta[i].category << ", " 
//              << ta[i].price << ", "
//              << ta[i].date << ", " 
//              << ta[i].payment_method << "\n";
//     }    
//     string cid;
//     cout << "\nEnter a Customer ID to search (e.g., CUST1234): ";
//     cin >> cid;
//     transform(cid.begin(), cid.end(), cid.begin(), ::toupper);
//     displayAllCustomerTransactions(ta, transaction_count, cid);
//     cout<<"Bubble Search & Binary Search for Array [Question01]: ";
//     Measure_Time([&](){bubbleSortByDate(ta, transaction_count);});
// //// LinkedList
// bubbleSortByDateLL(head);
// displayTransactions(head);
// cout<<"\nTotal Transactions Linked List: "<< countTransactions(head) << endl;
// cout<<"Bubble Sort & Binary Search for Linked List [Question01]: ";
// Measure_Time([&](){bubbleSortByDateLL(head);});

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//// 2. What percentage of purchases in the “Electronics” category were made using Credit Card payments?   
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Koh Chun Wei TP067580 (Quick Sort & Recursion Search)
//// Array
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
    cout<<"Quick Sorting & Recursion Searching for Array [Question02]: ";
    Measure_Time([&](){quickSortbycategory(ta, 0, transaction_count - 1);});
//// LinkedList
    // quickSortbycategoryll(head,tail);
    // displayCategory(head);
    // int totalElectronics = countElectronicsTotal(head);
    // int electronicsWithCreditCard = countElectronicsCredit(head);
    // cout <<"Total Electronics in Category: "<<totalElectronics<<" / "<<countTransactions(head)<<endl;
    // cout <<"Payment Method of Credit Card in Electronics: "<<electronicsWithCreditCard<<" / "<<totalElectronics<<endl;
    // if (totalElectronics > 0) {
    //     double percentage = (double)electronicsWithCreditCard / totalElectronics * 100;
    //     cout << fixed << setprecision(2);
    //     cout << "Percentage of Electronics purchases using Credit Card: " << percentage << "%" << endl;
    // } else {
    //     cout << "No Electronics purchases found." << endl;
    // }
    cout<<"Quick Sorting & Recursion Searching for Linked List [Question02]: ";
    Measure_Time([&](){quickSortbycategoryll(head, tail);});
//// U Guys Can Add+ Here below continue
////Liew Yi Xian (Bubble Sort & Binary Search)
//// Array
bubbleSortByCategory(ta, transaction_count); // must be sorted by category for binary search

int totalElectronics = 0, ccElectronics = 0;
countElectronicsAndCreditCard_Binary(ta, transaction_count, totalElectronics, ccElectronics);

cout << "Total Electronics Transactions: " << totalElectronics << endl;
cout << "Electronics Transactions using Credit Card: " << ccElectronics << endl;

if (totalElectronics > 0) {
    double percentage = (double)ccElectronics / totalElectronics * 100.0;
    cout << fixed << setprecision(2);
    cout << "Percentage of Electronics purchases using Credit Card: " << percentage << "%\n";
} else {
    cout << "No Electronics transactions found.\n";
}
cout<<"Bubble Sort & Binary Search for Array [Question02]: ";
Measure_Time([&](){bubbleSortByCategory(ta, transaction_count);});
//// LinkedList
bubbleSortByCategoryLL(head);
int llSize = countLinkedList(head);

int total = 0, cc = 0;
countElectronicsCreditCardLL_Binary(head, llSize, total, cc);

cout << "\nBinary Search (Simulated) on Linked List:\n";
cout << "Total Electronics: " << total << endl;
cout << "Electronics with Credit Card: " << cc << endl;

if (total > 0) {
    double percent = (double)cc / total * 100.0;
    cout << fixed << setprecision(2);
    cout << "Percentage: " << percent << "%\n";
} else {
    cout << "No Electronics transactions found.\n";
}
cout<<"Bubble Sort & Binary Search for LinkedList [Question02]: ";
Measure_Time([&](){bubbleSortByCategoryLL(head);});
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Clear the Pointer after Completed
    delete[] ta;
    clearLinkedList(head);
    return 0;
}