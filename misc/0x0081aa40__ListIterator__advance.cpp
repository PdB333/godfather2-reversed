// FUNC_NAME: ListIterator::advance
// Function at 0x0081aa40: Advances the iterator to the next node in a linked list.
// Structure layout (iterator):
//   +0x00: m_pList   (pointer to list control block)
//   +0x04: m_pCurrent (pointer to current node)
// List control block layout:
//   +0x18: m_pTail    (pointer to tail node)
// Node layout:
//   +0x00: m_pNext    (pointer to next node)

#include <cassert>

class ListIterator {
public:
    // Pointer to the list control block (contains head, tail, etc.)
    void* m_pList;          // +0x00

    // Pointer to the current node in iteration
    void* m_pCurrent;       // +0x04

    // Advance the iterator to the next node.
    // Returns pointer to this for chaining.
    ListIterator* advance() {
        // Assert that the list pointer is not null
        if (m_pList == nullptr) {
            assertionFailed();  // calls FUN_00b97aea (debug break/assertion)
        }

        // Assert that we are not at the tail (cannot advance past tail)
        if (m_pCurrent == *static_cast<void**>(static_cast<char*>(m_pList) + 0x18)) {
            assertionFailed();
        }

        // Move to next node: current node's next pointer is at offset 0x00
        m_pCurrent = *static_cast<void**>(m_pCurrent);

        return this;
    }

private:
    // Placeholder for the actual assertion/error handler at 0x00b97aea
    static void assertionFailed() {
        // In original binary: FUN_00b97aea (likely __debugbreak or error log)
    }
};

// Example usage (not part of original function):
// ListIterator it;
// it.advance();