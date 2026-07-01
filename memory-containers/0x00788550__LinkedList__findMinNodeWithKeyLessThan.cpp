// FUNC_NAME: LinkedList::findMinNodeWithKeyLessThan
// Address: 0x00788550
// Role: Searches a linked list for the node with the smallest key that is less than the given threshold.
// The list is stored as a pointer to the head node at offset 0 of the class (this->head = *this).
// Each node has the following layout (assuming 32-bit pointers):
//   +0x00: next pointer (Node*)
//   +0x04: padding (4 bytes, unused)
//   +0x08: key (float)
// Returns: pointer to the node with minimum key < threshold, or nullptr if none found.

struct Node {
    Node* next;   // +0x00
    int padding;  // +0x04 (unused, may be something else)
    float key;    // +0x08
};

struct LinkedList {
    Node* head;   // +0x00 (this points directly to this field)

    // Returns the node with the smallest key that is strictly less than 'threshold'.
    // If no such node exists, returns nullptr.
    Node* findMinNodeWithKeyLessThan(float threshold) {
        Node* result = nullptr;
        float minKey = threshold;   // tracks the smallest key seen so far
        for (Node* current = this->head; current != nullptr; current = current->next) {
            if (current->key < threshold) {
                if (result == nullptr || current->key < minKey) {
                    result = current;
                    minKey = current->key;
                }
            }
        }
        return result;
    }
};