// FUNC_NAME: AptStack::push
// Function address: 0x005b18b0
// Role: Push an element onto a fixed-size stack (capacity 32), with debug assertion and message type filtering.

#include <cstdint>

// Forward declarations (assumed external globals)
extern uint32_t* g_globalPointer;  // DAT_0119cbbc
extern void processMessage(uint32_t* element); // FUN_0059c230

class AptStack {
public:
    int32_t count;       // +0x00: number of elements currently in stack
    uint32_t* elements[32]; // +0x04: array of 32-element pointers

    void push(uint32_t* element) {
        // Assert: count < capacity (0x20)
        if (this->count >= 32) {
            // Debug assertion: "nElements < _nSize" from apt/_AptStack.h line 28
            // (assertion handling omitted for clarity)
            return;
        }

        this->elements[this->count] = element;
        this->count++;

        // Post-push filtering: skip if element is the global pointer or certain types
        if (element == g_globalPointer) {
            return;
        }

        uint32_t msgType = *element & 0x7FFF;
        bool bit15 = (*element >> 15) & 1;

        // Condition: (type != 0x19) && (bit15 != 0 || (type != 0xB && type != 0x18 && type != 0x17))
        if (msgType != 0x19 && (bit15 != 0 || (msgType != 0xB && msgType != 0x18 && msgType != 0x17))) {
            processMessage(element);
        }
    }
};