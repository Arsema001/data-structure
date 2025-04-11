#include <iostream> // Include the input/output stream library
using namespace std; // Use the standard namespace

// Define the structure for an Employee node
struct Employee {
	string name;        // Employee name
	int id;             // Employee ID
	float salary;       // Employee salary
	Employee *next;     // Pointer to the next node
};

// Global pointer to the head of the linked list
Employee *head = nullptr;

// Function to create a new employee node with user input
Employee *createEmployee() {
	Employee *newNode = new Employee(); // Dynamically allocate memory for a new node

	cout << "Enter Employee Name: ";
	cin >> newNode->name; // Input name

	cout << "Enter Employee ID: ";
	cin >> newNode->id;   // Input ID

	cout << "Enter Employee Salary: ";
	cin >> newNode->salary; // Input salary

	newNode->next = nullptr; // Set next to null
	return newNode; // Return the new node
}

// Insert a new node at the beginning of the list
void insertAtBeginning() {
	Employee *newNode = createEmployee(); // Create new node
	newNode->next = head; // Link new node to current head
	head = newNode; // Make new node the new head
}

// Insert a new node at the end of the list
void insertAtEnd() {
	Employee *newNode = createEmployee(); // Create new node

	if (head == nullptr) {
		head = newNode; // If list is empty, set head to new node
	} else {
		Employee *temp = head; // Temporary pointer to traverse list
		while (temp->next != nullptr) // Go to the last node
			temp = temp->next;
		temp->next = newNode; // Link last node to new node
	}
}

// Insert a new node at a specific position
void insertAtPosition(int position) {
	if (position <= 0) {
		cout << "Invalid position!" << endl;
		return;
	}

	if (position == 1) {
		insertAtBeginning(); // Insert at head
		return;
	}

	Employee *newNode = createEmployee(); // Create new node
	Employee *temp = head;

	// Traverse to the node just before the desired position
	for (int i = 1; i < position - 1 && temp != nullptr; i++)
		temp = temp->next;

	if (temp == nullptr) {
		cout << "Position out of bounds!" << endl;
		delete newNode; // Free memory if position is invalid
	} else {
		newNode->next = temp->next; // Link new node to next node
		temp->next = newNode; // Link previous node to new node
	}
}

// Delete node from beginning of the list
void deleteFromBeginning() {
	if (head == nullptr) {
		cout << "List is empty!" << endl;
		return;
	}

	Employee *temp = head; // Point to current head
	head = head->next; // Move head to next node
	delete temp; // Delete old head
	cout << "Deleted node from beginning." << endl;
}

// Delete node from end of the list
void deleteFromEnd() {
	if (head == nullptr) {
		cout << "List is empty!" << endl;
		return;
	}

	if (head->next == nullptr) {
		delete head; // Only one node
		head = nullptr;
	} else {
		Employee *temp = head;
		while (temp->next->next != nullptr) // Go to second-last node
			temp = temp->next;
		delete temp->next; // Delete last node
		temp->next = nullptr; // Set second-last node's next to null
	}

	cout << "Deleted node from end." << endl;
}

// Delete node from specific position
void deleteFromPosition(int position) {
	if (head == nullptr || position <= 0) {
		cout << "List is empty or invalid position!" << endl;
		return;
	}

	if (position == 1) {
		deleteFromBeginning(); // Delete from head
		return;
	}

	Employee *temp = head;

	// Traverse to node before the one to be deleted
	for (int i = 1; i < position - 1 && temp->next != nullptr; i++)
		temp = temp->next;

	if (temp->next == nullptr) {
		cout << "Position out of bounds!" << endl;
	} else {
		Employee *toDelete = temp->next; // Node to delete
		temp->next = toDelete->next; // Skip the node to delete
		delete toDelete; // Delete the node
		cout << "Deleted node at position " << position << "." << endl;
	}
}

// Display the entire linked list
void displayList() {
	if (head == nullptr) {
		cout << "List is empty!" << endl;
		return;
	}

	Employee *temp = head;
	cout << "\nEmployee List:\n";

	while (temp != nullptr) {
		// Print employee data
		cout << "Name: " << temp->name
		     << ", ID: " << temp->id
		     << ", Salary: $" << temp->salary << endl;
		temp = temp->next; // Move to next node
	}
}

// Main function - displays menu and handles user input
int main() {
	int choice, pos;

	do {
		// Display menu
		cout << "\n=== Employee Linked List Menu ===\n";
		cout << "1. Insert at Beginning\n";
		cout << "2. Insert at End\n";
		cout << "3. Insert at Specific Position\n";
		cout << "4. Delete from Beginning\n";
		cout << "5. Delete from End\n";
		cout << "6. Delete from Specific Position\n";
		cout << "7. Display List\n";
		cout << "0. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		// Perform action based on choice
		switch (choice) {
			case 1:
				insertAtBeginning();
				break;
			case 2:
				insertAtEnd();
				break;
			case 3:
				cout << "Enter position to insert: ";
				cin >> pos;
				insertAtPosition(pos);
				break;
			case 4:
				deleteFromBeginning();
				break;
			case 5:
				deleteFromEnd();
				break;
			case 6:
				cout << "Enter position to delete: ";
				cin >> pos;
				deleteFromPosition(pos);
				break;
			case 7:
				displayList();
				break;
			case 0:
				cout << "Exiting program." << endl;
				break;
			default:
				cout << "Invalid choice!" << endl;
		}

	} while (choice != 0); // Repeat until user exits

	return 0; // End of program
}

