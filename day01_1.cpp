#include <iostream> 
#include <cstdlib>

using namespace std;

typedef struct node {
    int data;
    struct node* next;
} NODE;

NODE* createNode();
NODE* addNodeBeg(NODE*, NODE*);
NODE* addNodeEnd(NODE*, NODE*);
NODE* addNodeAfter(NODE*, int, NODE*);
NODE* addNodeBefore(NODE*, int, NODE*);
NODE* deleteNodeBeg(NODE*);
NODE* deleteNodeEnd(NODE*);
NODE* deleteNodeAfter(NODE*, int);
NODE* deleteNodeBefore(NODE*, int);
void searchNode(NODE*, int);
void updateNode(NODE*, int, int);
int dispList(NODE*);
int dispMenu();
void freeNodes(NODE*);

int main() {
    NODE* head = NULL;
    int ch = 1;

    while (ch)
    {
        switch (dispMenu())
        {
        case 1:
            head = addNodeBeg(head, createNode());
            break;
        case 2:
            head = addNodeEnd(head, createNode());
            break;
        case 3:
        {
            int value;
            cout << "Enter the value after which to insert: ";
            cin >> value;
            head = addNodeAfter(head, value, createNode());
            break;
        }
        case 4:
        {
            int value;
            cout << "Enter the value before which to insert: ";
            cin >> value;
            head = addNodeBefore(head, value, createNode());
            break;
        }
        case 5:
            head = deleteNodeBeg(head);
            break;
        case 6:
            head = deleteNodeEnd(head);
            break;
        case 7:
        {
            int value;
            cout << "Enter the value after which to delete: ";
            cin >> value;
            head = deleteNodeAfter(head, value);
            break;
        }
        case 8:
        {
            int value;
            cout << "Enter the value before which to delete: ";
            cin >> value;
            head = deleteNodeBefore(head, value);
            break;
        }
        case 9:
        {
            int value;
            cout << "Enter the value to search: ";
            cin >> value;
            searchNode(head, value);
            break;
        }
        case 10:
        {
            int oldValue, newValue;
            cout << "Enter the value to update: ";
            cin >> oldValue;
            cout << "Enter the new value: ";
            cin >> newValue;
            updateNode(head, oldValue, newValue);
            break;
        }
        case 11:
            dispList(head);
            break;
        case 12:
            ch = 0;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
    freeNodes(head);
    cout << "Exiting program...." << endl;
    return 0;

}

int dispMenu() {
    int ch;
    cout << "\tPress,\n\t1. Add Node Beginning\n\t2. Add Node End\n";
    cout << "\t3. Add Node After\n\t4. Add Node Before\n";
    cout << "\t5. Delete Node Beginning\n\t6. Delete Node End\n";
    cout << "\t7. Delete Node After\n\t8. Delete Node Before\n";
    cout << "\t9. Search Node\n\t10. Update Node\n";
    cout << "\t11. Display List\n\t12. Exit\n\tChoice: ";
    cin >> ch;
    return ch;
}

int dispList(NODE* head) {
    cout << "\tList is " << endl;
    cout << "\t"; while (head != NULL) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
    return EXIT_SUCCESS;
}

NODE* addNodeEnd(NODE* head, NODE* nn) {
    NODE* temp = head;
    if (head == NULL) {
        head = nn;
        return head;
    }
    while (head->next != NULL)
        head = head->next;
    head->next = nn;
    head = temp;
    return head;
}

NODE* addNodeBeg(NODE* head, NODE* nn) {
    if (head == NULL) {
        head = nn;
        return head;
    }
    nn->next = head;
    head = nn;
    return head;
}

NODE* addNodeAfter(NODE* head, int value, NODE* nn) {
    NODE* temp = head;
    while (temp != NULL && temp->data != value) {
        temp = temp->next;
    }
    if (temp != NULL) {
        nn->next = temp->next;
        temp->next = nn;
    }
    else {
        cout << "Value " << value << " not found in the list." << endl;
        free(nn);
    }
    return head;
}

NODE* addNodeBefore(NODE* head, int value, NODE* nn) {
    if (head == NULL) {
        cout << "List is empty." << endl;
        free(nn);
        return head;
    }

    if (head->data == value)
    {
        nn->next = head;
        head = nn;
        return head;
    }

    NODE* prev = NULL;
    NODE* curr = head;

    while (curr != NULL && curr->data != value)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr != NULL)
    {
        nn->next = curr;
        prev->next = nn;
    }
    else
    {
        cout << "Value " << value << " not found in the list." << endl;
        free(nn);
    }

    return head;

}

NODE* deleteNodeBeg(NODE* head) {
    if (head == NULL) {
        cout << "List is empty." << endl;
        return head;
    }
    NODE* temp = head;
    head = head->next;
    free(temp);
    return head;
}

NODE* deleteNodeEnd(NODE* head) {
    if (head == NULL) {
        cout << "List is empty." << endl;
        return head;
    }

    if (head->next == NULL)
    {
        free(head);
        return NULL;
    }

    NODE* temp = head;
    while (temp->next->next != NULL)
        temp = temp->next;

    free(temp->next);
    temp->next = NULL;
    return head;

}

NODE* deleteNodeAfter(NODE* head, int value) {
    NODE* temp = head;
    while (temp != NULL && temp->data != value) {
        temp = temp->next;
    }

    if (temp != NULL && temp->next != NULL)
    {
        NODE* toDelete = temp->next;
        temp->next = toDelete->next;
        free(toDelete);
    }
    else
    {
        cout << "Node after value " << value << " not found." << endl;
    }

    return head;

}

NODE* deleteNodeBefore(NODE* head, int value) {
    if (head == NULL || head->next == NULL || head->data == value) {
        cout << "Node before value " << value << " not found." << endl;
        return head;
    }

    NODE* prev = NULL;
    NODE* curr = head;

    while (curr->next != NULL && curr->next->data != value)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr->next == NULL)
    {
        cout << "Node before value " << value << " not found." << endl;
        return head;
    }

    if (prev == NULL)
    {
        head = curr->next;
    }
    else
    {
        prev->next = curr->next;
    }

    free(curr);
    return head;

}

void searchNode(NODE* head, int value) {
    int pos = 0;
    while (head != NULL) {
        if (head->data == value) {
            cout << "Value " << value << " found at position " << pos << "." << endl;
            return;
        }
        head = head->next;
        pos++;
    }
    cout << "Value " << value << " not found in the list." << endl;
}

void updateNode(NODE* head, int oldValue, int newValue) {
    while (head != NULL)
    {
        if (head->data == oldValue) {
            head->data = newValue;
            cout << "Value " << oldValue << " updated to " << newValue << "." << endl;
            return;
        }
        head = head->next;
    }
    cout << "Value " << oldValue << " not found in the list." << endl;
}

NODE* createNode() {
    NODE* nn = (NODE*)malloc(sizeof(NODE));
    cout << "Enter the value of node: ";
    cin >> nn->data;
    nn->next = NULL;
    return nn;
}

void freeNodes(NODE* head)
{
    NODE* temp = head;
    while (head != NULL) {
        temp = head->next;
        free(head);
        head = temp;
    }
}
