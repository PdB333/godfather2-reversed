// FUNC_NAME: ListIterator::getCurrent
// Function address: 0x007eccf0
// Returns a pointer to the data at offset +8 from the current node.
// Asserts that the container is valid and the current node is not the end sentinel.

#include <cassert>

class ListIterator {
public:
    // +0x00: pointer to the container (List)
    void* container;
    // +0x04: pointer to the current node
    void* current;

    // Returns a pointer to the data stored at offset 8 within the current node.
    // The node structure is assumed to have:
    //   +0x00: next pointer
    //   +0x04: prev pointer (or other)
    //   +0x08: data (user payload)
    void* getCurrent() const {
        if (container == nullptr) {
            assert(!"Container is null");
        }
        // The container has a sentinel/end pointer at offset 0x18.
        // Compare current node with the end sentinel.
        if (current == *reinterpret_cast<void**>(static_cast<char*>(container) + 0x18)) {
            assert(!"Iterator is at end");
        }
        // Return pointer to the data at offset 8 from the current node.
        return static_cast<char*>(current) + 8;
    }
};