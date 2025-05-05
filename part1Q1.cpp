#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// ------------------ Data Structures ------------------
struct Transaction {
    string customer_ID, product, category, date, payment_method;
    float price;
};

struct Review {
    string product_ID, customer_ID;
    int rating;
    string review_text;
};

// ------------------ Date Format Helper ------------------
string convertDate(const string& date) {
    int day, month, year;
    char ch;
    istringstream iss(date);
    iss >> day >> ch >> month >> ch >> year;
    ostringstream oss;
    oss << year;
    if (month < 10) oss << '0';
    oss << month;
    if (day < 10) oss << '0';
    oss << day;
    return oss.str(); // YYYYMMDD as string
}

// ------------------ Heap Sort by Date ------------------
void heapify(vector<Transaction>& arr, int n, int i) {
    int largest = i;      // root
    int l = 2 * i + 1;     // left
    int r = 2 * i + 2;     // right

    if (l < n && convertDate(arr[l].date) > convertDate(arr[largest].date))
        largest = l;

    if (r < n && convertDate(arr[r].date) > convertDate(arr[largest].date))
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<Transaction>& arr) {
    int n = arr.size();

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);     // Move current root to end
        heapify(arr, i, 0);       // Heapify reduced heap
    }
}

// ------------------ Main Program ------------------
int main() {
    vector<Transaction> transactions;
    vector<Review> reviews;

    // Load transactions.csv
    ifstream file1("transactions.csv");
    if (!file1) {
        cerr << "Error opening transactions.csv\n";
        return 1;
    }

    string line;
    getline(file1, line); // skip header

    while (getline(file1, line)) {
        Transaction t;
        string priceStr;
        stringstream ss(line);
        getline(ss, t.customer_ID, ',');
        getline(ss, t.product, ',');
        getline(ss, t.category, ',');
        getline(ss, priceStr, ',');
        t.price = stof(priceStr);
        getline(ss, t.date, ',');
        getline(ss, t.payment_method);
        transactions.push_back(t);
    }

    // Load reviews.csv
    ifstream file2("reviews_cleaned.csv");
    if (!file2) {
        cerr << "Error opening reviews_cleaned.csv\n";
        return 1;
    }

    getline(file2, line); // skip header

    while (getline(file2, line)) {
        Review r;
        string ratingStr;
        stringstream ss(line);
        getline(ss, r.product_ID, ',');
        getline(ss, r.customer_ID, ',');
        getline(ss, ratingStr, ',');
        getline(ss, r.review_text);

        try {
            r.rating = stoi(ratingStr);
            reviews.push_back(r);
        } catch (...) {
            continue; // skip invalid rows
        }
    }

    // Sort transactions by date using Heap Sort
    heapSort(transactions);

    // Output results
    cout << "Q1: Total transactions: " << transactions.size() << "\n";
    cout << "    Total reviews: " << reviews.size() << "\n";
    cout << "    First 5 transactions sorted by date:\n";
    for (int i = 0; i < 5 && i < transactions.size(); ++i) {
        cout << "    " << transactions[i].date << " - "
             << transactions[i].product << " - "
             << transactions[i].customer_ID << "\n";
    }

    return 0;
}
