// FUNC_NAME: NodePool::acquireNode
// Function at 0x00456460 - Acquires a pre-allocated node from an internal pool, initializes it, and returns it.
// Uses __thiscall with 'this' in EAX (unusual, but present in some EA EARS code).
// A second context pointer is passed in EDI, used to set a success flag at offset +0x4c.
// Node structure:
//   +0x00: vtable pointer (set to 0x00e36674)
//   +0x04: next pointer (cleared)
//   +0x08: self-relative offset (adjusted if non-zero)
// Pool offsets:
//   +0x14: free head pointer (source of node)
//   +0x1c: becomes the acquired node (tail or current pointer)

#include <cstdint>

class Node {
public:
    void** vtable;              // +0x00
    Node* next;                 // +0x04
    int32_t relativeAdjust;     // +0x08 (self-relative offset, adjusted in-place)
};

class NodePool {
public:
    Node* freeHead;             // +0x14
    Node* allocatedTail;        // +0x1c
    // ... other fields

    // Acquire a node from the free list, initialize it, and return pointer.
    // context: pointer to an object that receives a status byte at +0x4c.
    // Returns nullptr if no node available.
    Node* acquireNode(void* context) {
        Node* node = this->freeHead;          // read +0x14
        this->allocatedTail = node;           // store +0x1c

        if (node != nullptr) {
            // Set vtable pointer
            node->vtable = reinterpret_cast<void**>(0x00e36674);
            node->next = nullptr;

            // Adjust self-relative offset if present (common EA EARS technique)
            if (node->relativeAdjust != 0) {
                node->relativeAdjust = reinterpret_cast<int32_t>(node) + node->relativeAdjust;
            }

            // Internal initialization call
            FUN_005e35e0();

            // Mark success on context object
            *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(context) + 0x4c) = 1;
        } else {
            // Even when no node, set flag (likely indicates "done" or "all processed")
            *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(context) + 0x4c) = 1;
        }

        return node;
    }
};