// FUNC_NAME: Node::Node(void *, int)
// Function address: 0x00956680
// Role: Constructor for a linked list node, inserts the node into a list owned by an object at offset 0x48.
//       The node has a vtable, priority field (0xff), and doubly-linked list pointers at offsets 0x10 and 0x14.

// Assumed structure layout (offsets from this pointer):
// +0x00: void* vtable
// +0x04: int m_someInt            (initialized to 0)
// +0x08: uint8_t m_byteFlag       (initialized to 0)
// +0x0C: int m_priority           (initialized to 0xFF)
// +0x10: int* m_pPrev             (pointer to previous node/list head's m_pPrev field)
// +0x14: int* m_pNext             (pointer to next node's m_pPrev field)
// +0x18: uint8_t m_anotherByte    (initialized to 0)
// +0x1C: int m_dummy              (initialized to 0)
//
// Note: The list uses a variant of a doubly-linked list where "next" pointers actually point to the "m_pPrev" field
// of the following node. A head node at the owner's offset 0x48 has the same layout.

#include <cstdint>

class Node {
public:
    Node(void* ownerOrParent, int param)
    {
        // Initialize vtable pointer
        *reinterpret_cast<int*>(this) = reinterpret_cast<int>(&PTR_FUN_00d8c120);

        // Clear fields
        m_someInt = 0;
        m_byteFlag = 0;
        m_priority = 0xFF;
        m_pPrev = nullptr;
        m_pNext = nullptr;
        m_anotherByte = 0;
        m_dummy = 0;

        // Determine the list head location in the owner object.
        // If ownerOrParent is non-null, the head is at offset 0x48 from that pointer.
        void* listHead;
        if (ownerOrParent == nullptr) {
            listHead = nullptr;
        } else {
            listHead = reinterpret_cast<char*>(ownerOrParent) + 0x48;
        }

        // If a list head exists, insert this node immediately after the head.
        if (m_pPrev != listHead) {
            // If already attached to another list, detach first.
            if (m_pPrev != nullptr) {
                detach(&m_pPrev);
            }
            m_pPrev = reinterpret_cast<int*>(listHead);
            if (listHead != nullptr) {
                // m_pNext points to the node after the head (i.e., head->m_pNext)
                m_pNext = *reinterpret_cast<int**>(reinterpret_cast<int*>(listHead) + 1);
                // Update the head's next pointer to point to this node's m_pPrev field.
                *(reinterpret_cast<int**>(listHead) + 1) = &m_pPrev;
            }
        }
    }

private:
    // fields (as per offsets)
    // Note: Actual layout may differ; these are placeholder names.
    int m_dummyVtable;       // +0x00
    int m_someInt;           // +0x04
    uint8_t m_byteFlag;      // +0x08
    int m_priority;          // +0x0C
    int* m_pPrev;            // +0x10
    int* m_pNext;            // +0x14
    uint8_t m_anotherByte;   // +0x18
    int m_dummy;             // +0x1C

    // Helper: detach node from current list (corresponds to FUN_004daf90)
    void detach(int** nodePrevField);
};