// FUNC_NAME: GenericDoublyLinkedList::removeNode

#include <cstdint>

// +0x00: next pointer
// +0x04: prev pointer
struct ListNode {
    ListNode* next;
    ListNode* prev;
};

// +0x00: head pointer
// +0x04: tail pointer
// +0x08: unknown (2 bytes, possibly padding or flags)
// +0x0A: count (2 bytes)
struct ListHead {
    ListNode* head;   // +0x00
    ListNode* tail;   // +0x04
    uint16_t unknown; // +0x08
    uint16_t count;   // +0x0A
};

// __fastcall: first argument (list) in ECX, second (node) in EDX
// in_EAX appears to be a residual value from the caller, used to construct the return.
// This function removes a node from a doubly linked list with separate head/tail pointers.
// The removal logic is unusual for both head and tail cases; it may assume a circular list
// or use a specific discipline (e.g., the list behaves as a free-list or ring buffer).
uint __fastcall removeNode(ListHead* list, ListNode* node)
{
    // value is initialized from in_EAX (e.g., a previous node's pointer) and masked to keep high 24 bits.
    uint value = 0; // placeholder: in_EAX & 0xFFFFFF00
    uint result = value;

    // Empty list
    if (list->count == 0)
        return result;

    // --- Case: node is the tail ---
    if (node == list->tail)
    {
        uint nextVal = (uint)node->next;
        if (nextVal != 0)
        {
            // Tail has a successor (e.g., list is circular or contains sentinel)
            list->tail = (ListNode*)nextVal;        // new tail = node->next
            node->next->prev = nullptr;             // break back-link from new tail
            list->count--;
            return 1 | (nextVal >> 8);              // success with high bits from new tail address
        }
    }
    else
    {
        // --- Case: node is not tail ---
        if (node != list->head)
        {
            // Normal removal of a middle node
            node->next->prev = node->prev;
            node->prev->next = node->next;
            list->count--;
            // Return 1 in low byte and high bits from the previous node's address
            return 1 | ((uint)node->prev >> 8);
        }

        // --- Case: node is head ---
        if (node->prev != 0)
        {
            // Head has a predecessor (e.g., list is circular)
            uint prevVal = (uint)node->prev;
            list->head = (ListNode*)prevVal;        // new head = node->prev
            node->prev->next = nullptr;             // clear forward link from new head
            list->count--;
            return 1 | (prevVal >> 8);
        }
    }

    // --- Last node removal (or head removal with no predecessor / tail removal with no successor) ---
    list->count--;
    list->head = nullptr;
    list->tail = nullptr;
    return 1 | (result >> 8);  // low byte 1, high bytes from the original value
}