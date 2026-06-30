// FUNC_NAME: EventQueue::pushEvent

#include <cstdint>

// Forward declarations of global functions and variables
typedef uint32_t (__cdecl *ValidateFunc)(uint32_t slotIndex);
extern ValidateFunc g_validateFunc;         // DAT_01163cd0

// Global manager structure pointer
struct GlobalManager;
extern GlobalManager* g_globalManager;      // DAT_012053e0

// Allocator and queue insertion functions
uint32_t* __cdecl allocateNode();           // FUN_004abf10
void __cdecl insertNode(uint32_t** pNode);  // FUN_00434f50

// Structure for a node in the event queue
struct EventNode {
    uint32_t field0;   // +0x00
    uint32_t field4;   // +0x04
    uint32_t field8;   // +0x08
    uint32_t fieldC;   // +0x0C
};

class EventQueue {
public:
    uint32_t m_maxSize;  // offset +0x00
    // ... other members

    // Returns true if the event was successfully enqueued
    bool pushEvent(uint32_t slotIndex, uint32_t data1, uint32_t data2, uint32_t data3, uint32_t data4) {
        // slotIndex corresponds to param_5, data1=param_2, data2=param_3, data3=param_4, data4=param_6
        if (slotIndex >= m_maxSize)
            return false;

        // Optional validation callback
        if (g_validateFunc != nullptr) {
            uint32_t validatedSize = g_validateFunc(slotIndex);
            if (m_maxSize <= validatedSize)
                return true;  // Already within limits? Or special success?
        }

        // Check if the global manager allows insertion
        if (*(reinterpret_cast<int32_t*>(reinterpret_cast<uintptr_t>(g_globalManager) + 0x14)) != 0) {
            uint32_t* pNode = allocateNode();   // Allocate a new node
            if (pNode == nullptr)
                return false;   // Allocation failed (unchecked in original)

            // Fill node fields (order as observed)
            pNode[0] = data2;        // param_3 -> field0
            pNode[1] = data3;        // param_4 -> field4
            pNode[2] = data4;        // param_6 -> field8
            pNode[3] = data1;        // param_2 -> fieldC

            insertNode(&pNode);      // Enqueue the node (takes pointer to pointer)
            return true;
        }

        return false;
    }
};