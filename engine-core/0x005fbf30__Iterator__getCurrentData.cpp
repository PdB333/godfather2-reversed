// FUNC_NAME: Iterator::getCurrentData
#include <cstddef>

// Assertion failure function (from address 0x00b97aea)
void assertFail();

class Iterator {
public:
    // Assume a struct for the node with header of 8 bytes (e.g., two pointers)
    struct Node {
        Node* next;      // +0x00
        Node* prev;      // +0x04
        // Data follows at +0x08
    };

    // +0x00: Pointer to the collection/container (may be null)
    struct Collection {
        // ... 
        Node* endSentinel; // +0x18: sentinel node marking the end
    }* container;

    // +0x04: Current node pointer
    Node* current;

    // Returns a pointer to the data inside the current node (offset +0x08)
    void* getCurrentData() {
        if (container == nullptr) {
            assertFail();
        }
        if (current == container->endSentinel) {
            assertFail();
        }
        return reinterpret_cast<char*>(current) + sizeof(Node); // +0x08
    }
};