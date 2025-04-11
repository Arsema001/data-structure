#include <iostream>           // For input/output
using namespace std;

// Define the structure for a Student node
struct Student {
	string name;              // Student's name
	int id;                   // Student's ID
	int age;                  // Student's age
	Student *next;            // Pointer to the next node
};

// Head pointer to track the first node
Student *head = nullptr;

// Function to create a new student node
Student *createStudent() {
	Student *newNode = new Student();  // Allocate memory for new node
	cout << "Enter student name: ";
	cin >> newNode->name;              // Input student name
	cout << "Enter student ID: ";
	cin >> newNode->id;                // Input student ID
	cout << "Enter student age: ";
	cin >> newNode->age;               // Input student age
	newNode->next = nullptr;           // Initialize next as null
	return newNode;                    // Return the created node
}

// Insert a node at the beginning
void insertAtBeginning() {
	Student *newNode = createStudent();  // Create new student
	if (head == nullptr) {               // If list is empty
		head = newNode;                  // New node is the head
		newNode->next = head;            // Points to itself (circular)
	} else {
		Student *temp = head;
		while (temp->next != head)       // Traverse to last node
			temp = temp->next;
		newNode->next = head;            // New node points to current head
		temp->next = newNode;            // Last node points to new node
		head = newNode;                  // New node becomes the new head
	}
}

// Insert a node at the end
void insertAtEnd() {
	Student *newNode = createStudent();  // Create new student
	if (head == nullptr) {               // If list is empty
		head = newNode;
		newNode->next = head;
	} else {
		Student *temp = head;
		while (temp->next != head)       // Traverse to last node
			temp = temp->next;
		temp->next = newNode;            // Last node points to new node
		newNode->next = head;            // New node points to head
	}
}

// Insert a node at a specific position (1-based index)
void insertAtPosition(int position) {
	if (position <= 0) {
		cout << "Invalid position!\n";
		return;
	}

	if (position == 1) {
		insertAtBeginning();             // Insert at beginning
		return;
	}

	Student *newNode = createStudent();  // Create new student
	Student *temp = head;

	// Traverse to the (position - 1)th node
	for (int i = 1; i < position - 1 && temp->next != head; i++) {
		temp = temp->next;
	}

	// If position is beyond current list size
	if (temp->next == head && position > 2) {
		cout << "Position out of bounds!\n";
		delete newNode;
		return;
	}

	newNode->next = temp->next;          // Point new node to next
	temp->next = newNode;                // Link previous node to new node
}

// Delete node from the beginning
void deleteFromBeginning() {
	if (head == nullptr) {
		cout << "List is empty!\n";
		return;
	}

	if (head->next == head) {            // Only one node
		delete head;
		head = nullptr;
		cout << "Deleted the only node.\n";
		return;
	}

	Student *temp = head;
	while (temp->next != head)           // Traverse to last node
		temp = temp->next;

	Student *toDelete = head;            // Node to be deleted
	head = head->next;                   // Move head to next node
	temp->next = head;                   // Last node points to new head
	delete toDelete;                     // Delete old head
	cout << "Deleted from beginning.\n";
}

// Delete node from the end
void deleteFromEnd() {
	if (head == nullptr) {
		cout << "List is empty!\n";
		return;
	}

	if (head->next == head) {            // Only one node
		delete head;
		head = nullptr;
		cout << "Deleted the only node.\n";
		return;
	}

	Student *temp = head;
	while (temp->next->next != head)     // Go to second last node
		temp = temp->next;

	Student *toDelete = temp->next;      // Last node
	temp->next = head;                   // Second last node points to head
	delete toDelete;                     // Delete last node
	cout << "Deleted from end.\n";
}

// Delete node from a specific position
void deleteFromPosition(int position) {
	if (head == nullptr || position <= 0) {
		cout << "List is empty or invalid position!\n";
		return;
	}

	if (position == 1) {
		deleteFromBeginning();           // Delete first node
		return;
	}

	Student *temp = head;

	// Traverse to (position - 1)th node
	for (int i = 1; i < position - 1 && temp->next != head; i++) {
		temp = temp->next;
	}

	if (temp->next == head) {
		cout << "Position out of bounds!\n";
		return;
	}

	Student *toDelete = temp->next;      // Node to be deleted
	temp->next = toDelete->next;         // Link previous to next
	delete toDelete;                     // Delete the node
	cout << "Deleted from position " << position << ".\n";
}

// Display the circular list
void displayList() {
	if (head == nullptr) {
		cout << "List is empty!\n";
		return;
	}

	Student *temp = head;
	cout << "\n--- Student List ---\n";
	do {
		cout << "Name: " << temp->name
		     << ", ID: " << temp->id
		     << ", Age: " << temp->age << endl;
		temp = temp->next;               // Move to next node
	} while (temp != head);              // Stop when back to head
}

// Main function with menu
int main() {
	int choice, position;

	while (true) {
		// Show menu
		cout << "\n--- Circular Linked List Menu ---\n";
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

		// Perform user-selected operation
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
				return 0;  // End program
			default:
				cout << "Invalid choice. Try again.\n";
		}
	}
}
