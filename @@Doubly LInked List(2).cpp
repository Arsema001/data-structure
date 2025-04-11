#include <iostream>             // Include input/output stream
using namespace std;            // Use standard C++ namespace

// Structure for a Person node in the Doubly Linked List
struct Person {
	string name;                // To store person's name
	int age;                    // To store person's age
	Person *prev;               // Pointer to the previous node
	Person *next;               // Pointer to the next node
};

// Head pointer to track the start of the list
Person *head = nullptr;         // Initially, the list is empty

// Function to create a new Person node with user input
Person *createPerson() {
	Person *newNode = new Person(); // Create a new node dynamically
	cout << "Enter name: ";
	cin >> newNode->name;           // Take name input from user
	cout << "Enter age: ";
	cin >> newNode->age;            // Take age input from user
	newNode->prev = nullptr;        // Initialize prev to null
	newNode->next = nullptr;        // Initialize next to null
	return newNode;                 // Return the new node
}

// Function to insert a node at the beginning of the list
void insertAtBeginning() {
	Person *newNode = createPerson();   // Create a new node
	if (head == nullptr) {             // If list is empty
		head = newNode;                // New node becomes the head
	} else {
		newNode->next = head;          // Point new node to current head
		head->prev = newNode;          // Set current head's prev to new node
		head = newNode;                // Update head to new node
	}
}

// Function to insert a node at the end of the list
void insertAtEnd() {
	Person *newNode = createPerson();  // Create a new node
	if (head == nullptr) {            // If list is empty
		head = newNode;               // Set new node as head
	} else {
		Person *temp = head;          // Start from head
		while (temp->next != nullptr) // Traverse to last node
			temp = temp->next;
		temp->next = newNode;         // Link last node to new node
		newNode->prev = temp;         // Set new node's prev to last node
	}
}

// Function to insert at a specific position
void insertAtPosition(int position) {
	if (position <= 0) {              // Invalid position
		cout << "Invalid position!" << endl;
		return;
	}
	if (position == 1) {              // Insert at beginning
		insertAtBeginning();
		return;
	}

	Person *newNode = createPerson(); // Create a new node
	Person *temp = head;              // Start from head
	for (int i = 1; i < position - 1 && temp != nullptr; i++) {
		temp = temp->next;            // Traverse to (position - 1) node
	}

	if (temp == nullptr) {            // If position is out of range
		cout << "Position out of bounds!" << endl;
		delete newNode;               // Free the unused node
		return;
	}

	newNode->next = temp->next;       // Link new node to next node
	newNode->prev = temp;             // Link new node to previous node

	if (temp->next != nullptr)        // If not inserting at end
		temp->next->prev = newNode;   // Set next node's prev to new node

	temp->next = newNode;             // Link previous node to new node
}

// Function to delete a node from the beginning
void deleteFromBeginning() {
	if (head == nullptr) {            // If list is empty
		cout << "List is empty!" << endl;
		return;
	}
	Person *temp = head;              // Temp pointer to delete node
	head = head->next;                // Move head to next node
	if (head != nullptr)
		head->prev = nullptr;         // Set new head's prev to null
	delete temp;                      // Delete old head
	cout << "Deleted from beginning.\n";
}

// Function to delete a node from the end
void deleteFromEnd() {
	if (head == nullptr) {            // If list is empty
		cout << "List is empty!" << endl;
		return;
	}

	if (head->next == nullptr) {      // If only one node exists
		delete head;
		head = nullptr;
		cout << "Deleted last remaining node.\n";
		return;
	}

	Person *temp = head;
	while (temp->next != nullptr) {   // Traverse to last node
		temp = temp->next;
	}
	temp->prev->next = nullptr;       // Unlink last node from list
	delete temp;                      // Delete it
	cout << "Deleted from end.\n";
}

// Function to delete a node from a specific position
void deleteFromPosition(int position) {
	if (head == nullptr || position <= 0) {
		cout << "List is empty or invalid position!" << endl;
		return;
	}

	if (position == 1) {              // If deleting first node
		deleteFromBeginning();
		return;
	}

	Person *temp = head;
	for (int i = 1; i < position && temp != nullptr; i++) {
		temp = temp->next;            // Traverse to target node
	}

	if (temp == nullptr) {
		cout << "Position out of bounds!" << endl;
		return;
	}

	if (temp->prev != nullptr)
		temp->prev->next = temp->next; // Link previous node to next

	if (temp->next != nullptr)
		temp->next->prev = temp->prev; // Link next node to previous

	delete temp;                      // Delete the target node
	cout << "Deleted from position " << position << ".\n";
}

// Function to display the list
void displayList() {
	if (head == nullptr) {
		cout << "List is empty!" << endl;
		return;
	}

	Person *temp = head;
	cout << "\n--- Person List ---\n";
	while (temp != nullptr) {
		cout << "Name: " << temp->name << ", Age: " << temp->age << endl;
		temp = temp->next;           // Move to next node
	}
}

// Main menu function
int main() {
	int choice, position;
	while (true) {
		// Show the user menu
		cout << "\n--- Doubly Linked List Menu ---\n";
		cout << "1. Insert at Beginning\n";
		cout << "2. Insert at End\n";
		cout << "3. Insert at Specific Position\n";
		cout << "4. Delete from Beginning\n";
		cout << "5. Delete from End\n";
		cout << "6. Delete from Specific Position\n";
		cout << "7. Display List\n";
		cout << "8. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		// Perform action based on user choice
		switch (choice) {
			case 1:
				insertAtBeginning();
				break;
			case 2:
				insertAtEnd();
				break;
			case 3:
				cout << "Enter position: ";
				cin >> position;
				insertAtPosition(position);
				break;
			case 4:
				deleteFromBeginning();
				break;
			case 5:
				deleteFromEnd();
				break;
			case 6:
				cout << "Enter position: ";
				cin >> position;
				deleteFromPosition(position);
				break;
			case 7:
				displayList();
				break;
			case 8:
				cout << "Exiting program.\n";
				return 0; // Exit the program
			default:
				cout << "Invalid choice. Try again.\n";
		}
	}
}
