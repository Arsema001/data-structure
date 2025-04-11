#include <iostream>     // For input and output
using namespace std;

// Define the structure of a Person node
struct Person {
	string name;        // Person's name
	string phone;       // Person's phone number
	int age;            // Person's age
	Person *next;       // Pointer to next node
	Person *prev;       // Pointer to previous node
};

// Initialize the head pointer to null
Person *head = nullptr;

// Function to create a new Person node with input
Person *createPerson() {
	Person *newNode = new Person(); // Allocate memory for a new node

	// Take input from the user
	cout << "Enter name: ";
	cin >> newNode->name;
	cout << "Enter phone number: ";
	cin >> newNode->phone;
	cout << "Enter age: ";
	cin >> newNode->age;

	// Initialize pointers to null
	newNode->next = newNode->prev = nullptr;
	return newNode; // Return the new node
}

// Function to insert at the beginning
void insertAtBeginning() {
	Person *newNode = createPerson(); // Create new node

	if (head == nullptr) { // If list is empty
		head = newNode;
		head->next = head->prev = head; // Point to itself (circular)
	} else {
		Person *last = head->prev; // Get last node
		newNode->next = head;      // New node points to head
		newNode->prev = last;      // New node points to last node
		last->next = newNode;      // Last node points to new node
		head->prev = newNode;      // Head points back to new node
		head = newNode;            // New node becomes the new head
	}
}

// Function to insert at the end
void insertAtEnd() {
	Person *newNode = createPerson(); // Create new node

	if (head == nullptr) { // If list is empty
		head = newNode;
		head->next = head->prev = head;
	} else {
		Person *last = head->prev; // Get last node
		last->next = newNode;      // Last node points to new node
		newNode->prev = last;      // New node points back to last
		newNode->next = head;      // New node points to head
		head->prev = newNode;      // Head points back to new node
	}
}

// Function to insert at a specific position (1-based index)
void insertAtPosition(int pos) {
	if (pos <= 0) {
		cout << "Invalid position!\n";
		return;
	}

	if (pos == 1) {
		insertAtBeginning(); // Insert at beginning if pos is 1
		return;
	}

	Person *newNode = createPerson(); // Create new node
	Person *temp = head;

	int i = 1;
	while (i < pos - 1 && temp->next != head) {
		temp = temp->next;
		i++;
	}

	// Insert between temp and temp->next
	Person *nextNode = temp->next;
	temp->next = newNode;
	newNode->prev = temp;
	newNode->next = nextNode;
	nextNode->prev = newNode;

	cout << "Inserted at position " << pos << endl;
}

// Function to delete from the beginning
void deleteFromBeginning() {
	if (head == nullptr) {
		cout << "List is empty!\n";
		return;
	}

	if (head->next == head) { // Only one node
		delete head;
		head = nullptr;
	} else {
		Person *last = head->prev; // Get last node
		Person *temp = head;       // Node to delete
		head = head->next;         // Move head to next node
		head->prev = last;         // Head's previous points to last
		last->next = head;         // Last node points to head
		delete temp;               // Delete old head
	}

	cout << "Deleted from beginning.\n";
}

// Function to delete from the end
void deleteFromEnd() {
	if (head == nullptr) {
		cout << "List is empty!\n";
		return;
	}

	if (head->next == head) { // Only one node
		delete head;
		head = nullptr;
	} else {
		Person *last = head->prev;     // Last node
		Person *secondLast = last->prev; // Second last node
		secondLast->next = head;       // Second last points to head
		head->prev = secondLast;       // Head points back to second last
		delete last;                   // Delete last node
	}

	cout << "Deleted from end.\n";
}

// Function to delete from specific position
void deleteFromPosition(int pos) {
	if (head == nullptr || pos <= 0) {
		cout << "List is empty or invalid position!\n";
		return;
	}

	if (pos == 1) {
		deleteFromBeginning(); // Delete from beginning
		return;
	}

	Person *temp = head;
	int i = 1;
	while (i < pos && temp->next != head) {
		temp = temp->next;
		i++;
	}

	if (i != pos) {
		cout << "Position out of bounds!\n";
		return;
	}

	// Remove temp node
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	delete temp;

	cout << "Deleted from position " << pos << ".\n";
}

// Function to display the list
void displayList() {
	if (head == nullptr) {
		cout << "List is empty!\n";
		return;
	}

	Person *temp = head;
	int count = 1;

	cout << "\n--- Person List ---\n";
	do {
		cout << count++ << ". Name: " << temp->name
		     << ", Phone: " << temp->phone
		     << ", Age: " << temp->age << endl;
		temp = temp->next;
	} while (temp != head); // Stop when back to head
}

// Main function to handle menu
int main() {
	int choice, position;

	while (true) {
		// Display menu options
		cout << "\n--- Doubly Circular Linked List Menu ---\n";
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

		// Perform action based on user's choice
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
				cout << "Invalid choice! Try again.\n";
		}
	}
}
