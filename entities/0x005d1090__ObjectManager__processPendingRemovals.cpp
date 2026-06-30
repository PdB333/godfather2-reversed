// FUNC_NAME: ObjectManager::processPendingRemovals
// Address: 0x005d1090
// This function iterates over a linked list of objects, processing each and potentially removing nodes.
// The list is stored as a head pointer (+0x00) and a current iterator pointer (+0x04).
// Each node has a 'next' pointer at offset +0x94.

class ObjectManager {
public:
    struct Node {
        // ... other fields ...
        Node* next;  // +0x94
    };

    Node* head;      // +0x00
    Node* current;   // +0x04

    // Calls a per-node processing function (likely uses this->current)
    void processCurrentNode();  // FUN_005d1310

    void processPendingRemovals() {
        Node* node = head;
        while (node != nullptr) {
            node = current;
            if (node != nullptr) {
                // Advance current to the next node in the list
                current = node->next;  // +0x94
                // If the node being processed is the head, update head to its next
                if (head == node) {
                    head = node->next; // +0x94
                }
                // Process the node (may delete or modify it)
                processCurrentNode();
            }
            // If we've reached the end of the list, reset current to head
            if (current == nullptr) {
                current = head;
            }
            node = head;
        }
    }
};