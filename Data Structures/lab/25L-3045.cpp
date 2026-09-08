#include <iostream>
#include <string>
using namespace std;

class Train
{
private:
    // ---------- Nested Node (Compartment) class ----------
    class Compartment
    {
    public:
        int id;
        string cargo; // Passengers, Coal, Mail, Toys
        Compartment *next;

        Compartment(int id, string cargo) : id(id), cargo(cargo), next(nullptr) {}
    };

    Compartment *head;

public:
    Train() : head(nullptr) {}

    // ---------- 1. Attach Compartment at Start (VIP) ----------
    void attachAtStart(int id, string cargo)
    {
        Compartment *newComp = new Compartment(id, cargo);
        newComp->next = head;
        head = newComp;
        cout << "Compartment " << id << " (" << cargo << ") attached at start.\n";
    }

    // ---------- 2. Attach Compartment at End (Normal) ----------
    void attachAtEnd(int id, string cargo)
    {
        Compartment *newComp = new Compartment(id, cargo);

        if (head == nullptr)
        {
            head = newComp;
        }
        else
        {
            Compartment *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newComp;
        }
        cout << "Compartment " << id << " (" << cargo << ") attached at end.\n";
    }

    // ---------- 3. Attach Compartment After a Specific Compartment ----------
    void attachAfter(int targetId, int newId, string cargo)
    {
        Compartment *temp = head;
        while (temp != nullptr && temp->id != targetId)
        {
            temp = temp->next;
        }

        if (temp == nullptr)
        {
            cout << "Target compartment " << targetId << " not found.\n";
            return;
        }

        Compartment *newComp = new Compartment(newId, cargo);
        newComp->next = temp->next;
        temp->next = newComp;
        cout << "Compartment " << newId << " (" << cargo << ") attached after " << targetId << ".\n";
    }

    // ---------- 4. Detach Compartment ----------
    void detach(int id)
    {
        if (head == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        // Special case: detaching the head
        if (head->id == id)
        {
            Compartment *toDelete = head;
            head = head->next;
            delete toDelete;
            cout << "Compartment " << id << " detached.\n";
            return;
        }

        Compartment *prev = head;
        Compartment *curr = head->next;

        while (curr != nullptr && curr->id != id)
        {
            prev = curr;
            curr = curr->next;
        }

        if (curr == nullptr)
        {
            cout << "Compartment " << id << " not found.\n";
            return;
        }

        prev->next = curr->next;
        delete curr;
        cout << "Compartment " << id << " detached.\n";
    }

    // ---------- 5. Search Compartment ----------
    void search(int id)
    {
        Compartment *temp = head;
        while (temp != nullptr)
        {
            if (temp->id == id)
            {
                cout << "Compartment " << id << " is in the train.\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Compartment " << id << " is not in the train.\n";
    }

    // ---------- 6. Display Train ----------
    void display()
    {
        if (head == nullptr)
        {
            cout << "Train is empty.\n";
            return;
        }

        cout << "Train Composition:\n";
        Compartment *temp = head;
        while (temp != nullptr)
        {
            cout << temp->id << " (" << temp->cargo << ") -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    // ---------- 7. Count Compartments ----------
    int count()
    {
        int c = 0;
        Compartment *temp = head;
        while (temp != nullptr)
        {
            c++;
            temp = temp->next;
        }
        return c;
    }

    // ---------- 9. Swap Two Compartments ----------
    // Swaps the data (id + cargo) of the two compartments with the given IDs.
    void swapCompartments(int id1, int id2)
    {
        if (id1 == id2)
        {
            cout << "Cannot swap a compartment with itself.\n";
            return;
        }

        Compartment *first = head;
        while (first != nullptr && first->id != id1)
        {
            first = first->next;
        }

        Compartment *second = head;
        while (second != nullptr && second->id != id2)
        {
            second = second->next;
        }

        if (first == nullptr || second == nullptr)
        {
            cout << "One or both compartments not found.\n";
            return;
        }

        // Swap data
        int tempId = first->id;
        string tempCargo = first->cargo;

        first->id = second->id;
        first->cargo = second->cargo;

        second->id = tempId;
        second->cargo = tempCargo;

        cout << "Compartments " << id1 << " and " << id2 << " swapped.\n";
    }

    // ---------- Destructor: Destruct the Train properly ----------
    ~Train()
    {
        Compartment *temp = head;
        while (temp != nullptr)
        {
            Compartment *toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        head = nullptr;
        cout << "Train destroyed. All compartments freed.\n";
    }
};

// ---------- Menu-driven main ----------
int main()
{
    Train train;
    int choice;

    do
    {
        cout << "\n=== Thomas & Friends: Train Compartment Manager ===\n";
        cout << "1. Attach Compartment at Start (VIP)\n";
        cout << "2. Attach Compartment at End (Normal)\n";
        cout << "3. Attach Compartment After a Specific Compartment\n";
        cout << "4. Detach Compartment\n";
        cout << "5. Search Compartment\n";
        cout << "6. Display Train\n";
        cout << "7. Count Compartments\n";
        cout << "9. Swap Two Compartments\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        int id, targetId, newId, id1, id2;
        string cargo;

        switch (choice)
        {
        case 1:
            cout << "Enter Compartment ID: ";
            cin >> id;
            cout << "Enter Cargo Type (Passengers, Coal, Mail, Toys): ";
            cin >> cargo;
            train.attachAtStart(id, cargo);
            break;

        case 2:
            cout << "Enter Compartment ID: ";
            cin >> id;
            cout << "Enter Cargo Type (Passengers, Coal, Mail, Toys): ";
            cin >> cargo;
            train.attachAtEnd(id, cargo);
            break;

        case 3:
            cout << "Enter Target Compartment ID: ";
            cin >> targetId;
            cout << "Enter New Compartment ID: ";
            cin >> newId;
            cout << "Enter Cargo Type (Passengers, Coal, Mail, Toys): ";
            cin >> cargo;
            train.attachAfter(targetId, newId, cargo);
            break;

        case 4:
            cout << "Enter Compartment ID to detach: ";
            cin >> id;
            train.detach(id);
            break;

        case 5:
            cout << "Enter Compartment ID to search: ";
            cin >> id;
            train.search(id);
            break;

        case 6:
            train.display();
            break;

        case 7:
            cout << "Total Compartments: " << train.count() << "\n";
            break;

        case 9:
            cout << "Enter first Compartment ID: ";
            cin >> id1;
            cout << "Enter second Compartment ID: ";
            cin >> id2;
            train.swapCompartments(id1, id2);
            break;

        case 0:
            cout << "Exiting... Train will be destructed properly.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    // train's destructor runs automatically here (stack object)
    return 0;
}
