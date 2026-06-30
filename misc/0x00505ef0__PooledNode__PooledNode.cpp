// FUNC_NAME: PooledNode::PooledNode
// Address: 0x00505ef0
// Role: Initializes a pooled node with provided data and pushes it to the front of a global linked list.
//       The function is called with `this` in ESI, 4 stack parameters (int a, int b, int c, int d),
//       and two float parameters in XMM0 and XMM1. The node structure (24 bytes) has fields:
//       +0x00: next pointer (head of old list)
//       +0x04: float from XMM0 (parameter a_float)
//       +0x08: int a (param1)
//       +0x0C: int b (param2)
//       +0x10: int c (param3)
//       +0x14: clamped float (min(XMM1, g_maxValue))
//       +0x18: int d (param4)
//       The global list head is obtained via a call to 0x00505c90, which returns a pointer to a
//       ListHead structure containing: +0x00: pointer to first node, +0x0C: node count.
//       After copying old head to new node's next, the node count is incremented and the head
//       pointer is updated to point to the new node.

#include <cstdint>

// Global constant for clamping the second float parameter
static const float g_maxValue = *(float*)0x00e446d8; // Pulled from ROM: likely a predefined maximum

// Forward declaration of the list head structure
struct ListHead;

// Function to retrieve the global list head structure (defined at 0x00505c90)
ListHead* getGlobalListHead(uint32_t someGlobalPtr); // DAT_0120550c is passed

// List head structure (offset 0x0C contains count, offset 0x00 contains head pointer)
struct ListHead {
    PooledNode* head; // +0x00
    // ... other fields, but only offset 0x0C known: uint32_t count
    uint32_t count; // +0x0C (offset 12)
};

// Node structure (24 bytes)
class PooledNode {
public:
    PooledNode* next;    // +0x00
    float        field4; // +0x04 (from XMM0)
    int32_t      field8; // +0x08 (param1)
    int32_t      fieldC; // +0x0C (param2)
    int32_t      field10;// +0x10 (param3)
    float        field14; // +0x14 (min of XMM1 and g_maxValue)
    int32_t      field18; // +0x18 (param4)

    // Constructor: initializes the node and inserts it at the front of the global list.
    // Note: The actual calling convention passes `this` in ESI, while other params are on stack
    // and in XMM registers. This C++ signature represents that.
    void __thiscall construct(float value1, int32_t a, int32_t b, int32_t c, int32_t d, float value2) {
        // Retrieve the global list head structure
        ListHead* listHead = getGlobalListHead(0x0120550c); // global pointer

        // Store the first parameter (from XMM0) into field +0x04
        this->field4 = value1;

        // Store the stack parameters into the corresponding fields
        this->field8 = a;   // param1 -> +0x08
        this->fieldC = b;   // param2 -> +0x0C
        this->field10 = c;  // param3 -> +0x10
        this->field18 = d;  // param4 -> +0x18

        // Clamp the second float parameter (from XMM1) against the global maximum
        float clampedValue = (value2 <= g_maxValue) ? value2 : g_maxValue;
        this->field14 = clampedValue;

        // Insert node at front of the linked list:
        // - Copy current head pointer into this node's next field
        this->next = listHead->head;

        // - Increment the node count (at offset 0x0C in list head)
        listHead->count++;

        // - Update the list head to point to this new node
        listHead->head = this;
    }
};