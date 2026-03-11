#include <iostream>
// including random and ctime for true randomness
#include <random>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20, SIZE = 15; // added SIZE for array sizes

// Goat class
class Goat {
    private:
        int age;
        string name;
        string color;
        // constant string of goat names to choose from, by ChatGPT
        string NAME[SIZE] = {
            "Billy",
            "Daisy",
            "Pepper",
            "Maple",
            "Nibbles",
            "Clover",
            "Rocky",
            "Luna",
            "Biscuit",
            "Hazel",
            "Oreo",
            "Willow",
            "Scout",
            "Juniper",
            "Mochi"
        }; 
        // const string of goat colors, by ChatGPT
        string COLOR[SIZE] = {
            "White",
            "Brown",
            "Black",
            "Gray",
            "Spotted",
            "Tan",
            "Cream",
            "Golden",
            "Black and White",
            "Chocolate",
            "Silver",
            "Rust",
            "Speckled",
            "Amber",
            "Charcoal"
        };
    
    public:
        // default constructor, adding random age, name, color
        Goat() { 
            age = rand() % 21;
            name = NAME[rand() % 16];
            color = COLOR[rand() % 16];
        }
        // parameter constructor with three elements
        Goat(int goatAge, string goatName, string goatColor) {
            age = goatAge;
            name = goatName;
            color = goatColor;
        }
        // printing Goat object
        void Print() {
            cout << name << " (" << color << ", " << age << ")" << endl; 
        }
};

class DoublyLinkedList {
private:
    struct Node {
        Goat data;
        Node* prev;
        Node* next;
        Node(Goat val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(Goat newGoat) {
        Node* newNode = new Node(newGoat);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Goat newGoat) {
        Node* newNode = new Node(newGoat);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(Goat value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_node(Goat value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            current->data.Print(); // edited to use Goat Print() function
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            current->data.Print(); // edited to use Goat Print() function
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0)); // starting RNG

    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i) {
        Goat newGoat;
        list.push_back(newGoat); // adding Goat objects to function
    }
    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}
