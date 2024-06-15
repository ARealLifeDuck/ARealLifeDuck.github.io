//============================================================================
// Project Number : VectorSorting.cpp
// Name           : Seth Duck
// Course         : CS 499 Capstone Enhancement 2
// Date           : 06/10/2024
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

// Bid structure for inputing a new bid
struct Bid {
    string bidId; // unique identifier for each bid
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
    // Internal structure for list entries, housekeeping variables
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
    // Initialize housekeeping variables
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
    //Implement append logic
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
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    // Implement prepend logic
	Node* node = new Node(bid);

	if (head != nullptr) {
		node->next = head;
	}

	head = node;

	size++;
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    // Implement print logic
	Node* current = head;

	// loop over each node looking for a match
	while (current != nullptr) {
		cout << current->bid.bidId << ": " << current->bid.title << " | "
			 << current->bid.amount << " | " << current->bid.fund << endl;
		current = current->next;
	}
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // Implement remove logic
	if (head != nullptr) {
		if (head->bid.bidId.compare(bidId) ==0) {
			Node* tempNode = head->next;
			delete head;
			head = tempNode;
		}
	}

	Node* current = head;

	// loop over each node looking for a match
	while (current->next != nullptr) {
		if (current->next->bid.bidId.compare(bidId) == 0) {
			//save the next node (one to be removed)
			Node* tempNode = current->next;

			// made current node point beyond the next one (to be removed)
			current->next = tempNode->next;

			//now delete that temp node
			delete tempNode;

			// reduce count
			size--;

			return;
		}
		current = current->next;
	}
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) { // @suppress("No return")
	Node* current =  head;

		// loop over each node looking for a match
		while (current != nullptr) {
			if (current->bid.bidId.compare(bidId) == 0) {
				return current->bid;
			}
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
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(vector<Bid>& bids, int begin, int end) {
	int unsigned mid = 0;

	// If zero or only one bids
	if (begin >= end) {
		return;
	}

	mid = partition(bids, begin, end);

	// quickSort from beginning to midpoint value
	quickSort(bids, begin, mid);

	// quickSort from midpoint value to end
	quickSort(bids, mid + 1, end);
}

// Implement the selection sort logic over bid.title

/**
 * Perform a selection sort on bid title
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param bid address of the vector<Bid>
 *            instance to be sorted
 */
void selectionSort(vector<Bid>& bids) {
	// index of smallest remaining element
	int unsigned min;

	// i is the position pointer for min
	for (unsigned i = 0; i < bids.size(); ++i) {
		min = i;

		// find index of smallest remaining element
		for (unsigned j = i + 1; j < bids.size(); ++j) {
			if (bids.at(j).title.compare(bids.at(min).title) < 0) {
				min = j;
			}
		}

		// swap i and min
		if (min != i) {
			swap(bids.at(i), bids.at(min));
		}
	}
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
        // This path needs to be copied from the folder location where the eBid_Monthly_Sales_Dec_2016.csv file is residing
        //Below is an example of where it may be sitting.
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
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Enter a Bid" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Selection Sort All Bids" << endl;
        cout << "  5. Quick Sort All Bids" << endl;
        cout << "  6. Find Bid" << endl;
        cout << "  7. Remove Bid" << endl;
        cout << "  8. Prepend a Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        //Load the bids from the CSV file provided above
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

        // Enter a bid
        case 2:
        	bid = getBid();
        	            bidList.Append(bid);
        	            displayBid(bid);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

        	            break;

        //Display all bids
        case 3:
            // Loops and display the bids read
            for (int unsigned i = 0; i < bids.size(); ++i) {
                displayBid(bids[i]);
            }
            cout << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        // Invoke the selection sort and report timing results
        case 4:
        	// Initialize a timer variable before loading bids
        	ticks = clock();

        	// Complete the method call to load the bids
        	selectionSort(bids);

        	cout << bids.size() << " bids read" << endl;

        	// Calculate elapsed time and display result
        	ticks = clock() - ticks; // current clock ticks minus starting clock ticks
        	cout << "time: " << ticks << " clock ticks" << endl;
        	cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

        	break;


        // Invoke the quick sort and report timing results
        case 5:
        	// Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            quickSort(bids, 0, bids.size() - 1);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        // Find a bid
        case 6:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        // Remove a bid
        case 7:
            bidList.Remove(bidKey);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;
        // Prepends a bid
        case 8:
        	bid = getBid();
        	bidList.Prepend(bid);
        	displayBid(bid);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

        	break;

        }
    }

    cout << "Good bye." << endl;

    return 0;
}
