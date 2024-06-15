//============================================================================
// Project Number : VectorSorting.cpp
// Name           : Daryl Miller
// Course         : CS-260-J1278
// Date           : 23 September 2019
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>
#include <string>
#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
    // FIXED (1): Internal structure for list entries, housekeeping variables
	struct Node {
		Bid bid;
		Node* next;

		// default constructor
		Node() {
			next = nullptr;
		}

		// initialize a node with a bid
		Node(Bid aBid) {
			bid = aBid;
			next = nullptr;
		}
	};

	Node* head;
	Node* tail;
	int size = 0;

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {
    // FIXED (2): Initialize housekeeping variables
	head = tail = nullptr;
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    //FIXED (3): Implement append logic
	Node* node = new Node(bid);

	if (head == nullptr) {
		head = node;
	} else {
		if (tail != nullptr) {
			tail->next = node;
		}
	}

	// new node is always the tail
	tail = node;

	size++;
}


/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    // FIXED (4): Implement print logic
	Node* current = head;

	// loop over each node looking for a match
	while (current != nullptr) {
		cout << current->bid.bidId << ": " << current->bid.title << " | "
			 << current->bid.amount << " | " << current->bid.fund << endl;
		current = current->next;
	}
}



/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}


//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information using console (std::in)
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int unsigned i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bids.push_back(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}

// Implement the quick sort logic over bid.title

/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(vector<Bid>& bids, int begin, int end) {
	int low = begin;
	int high = end;
	int pivot = begin + (end - begin) / 2;
	bool done = false;

	while (!done) {

		// increment low while it's less than pivot
		while (bids.at(low).title.compare(bids.at(pivot).title) < 0) {
			++low;
		}

		// decrement high while it's more than pivot
		while (bids.at(pivot).title.compare(bids.at(high).title) < 0) {
			--high;
		}

		// if zero or one element remaining, all numbers are partitioned
		if (low >= high) {
			done = true;
		}
		else {
			// swap low and high, update low and high
			swap(bids.at(low), bids.at(high));

			++low;
			--high;
		}
	}

	return high;
}


/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end()); // @suppress("Invalid arguments")
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "08109";
        break;
    case 3:
    	csvPath = argv[1];
    	bidKey = argv[2];
    	break;

    default:
        csvPath = "/Users/dad/Desktop/CS-260/VectorSorting/src/eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    LinkedList bidList;

    Bid bid;

    // Define a vector to hold all the bids
    vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 4) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Enter a Bid" << endl;
        cout << "  3. Display All Bids" << endl;        
        cout << "  4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            bids = loadBids(csvPath);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
        	bid = getBid();
        	            bidList.Append(bid);
        	            displayBid(bid);

        	            break;

        case 3:
            // Loop and display the bids read
            for (int unsigned i = 0; i < bids.size(); ++i) {
                displayBid(bids[i]);
            }
            cout << endl;

            break;      

        }
    }

    cout << "Good bye." << endl;

    return 0;
}
