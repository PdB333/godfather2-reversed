// FUNC_NAME: EAList::removeAllByValue
// Function address: 0x00463520
// Purpose: Removes all elements from a singly linked list that match the given value.
// The list uses nodes with int value at offset 0 and next pointer at offset 4.
// The helper function at 0x004634b0 handles the actual removal and returns the next node.

class EAList {
private:
    struct Node {
        int value;      // +0x00
        Node* next;     // +0x04
    };
    Node* mHead;        // +0x00 in this

    // Internal: removes the current node from the list and returns the next node.
    // Defined at 0x004634b0.
    Node* removeCurrentNode(Node* node);

public:
    // Removes all nodes whose value equals the value pointed to by valuePtr.
    void removeAllByValue(const int* valuePtr) {
        Node* current = mHead;
        while (current != nullptr) {
            if (current->value == *valuePtr) {
                // Removal updates the list and current is advanced to the next node.
                current = removeCurrentNode(current);
            } else {
                current = current->next;
            }
        }
    }
};