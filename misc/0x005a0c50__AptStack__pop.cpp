// FUNC_NAME: AptStack::pop
// Address: 0x005a0c50
// Role: Pops the top element from an AptStack, with debug assertion and destruction via type table.

#include <cstdint>

// Global function table for element destruction (indexed by type ID, masked 0x7FFF)
extern void (*g_elementDestructors[])(void*);

// External flag for assertion control (DAT_01128f61)
extern bool g_aptAssertEnabled;

class AptStack {
public:
    // The stack buffer: first 4 bytes are size (int), then data elements follow.
    // 'this' points directly to the buffer (i.e., to the size field).
    int* m_buffer;   // Actually this is the address of the stack object, which is the start of the buffer

    void __thiscall pop() {
        // Assert that stack is not empty
        if (m_buffer[0] > 0) goto pop_ok;

        // Assertion failed: "size() > 0"
        // File: c:\packages001_pc\apt\0.19.optimized\source\apt\_AptStack.h, line 35
        if (g_aptAssertEnabled) {
            // Structured exception handling for assertion failure
            // (simplified: break on assertion)
            __debugbreak();
        }

pop_ok:
        // Get the top element: at index m_buffer[0] (since data starts at index 1)
        void* element = (void*)m_buffer[m_buffer[0]];
        // The element's first 4 bytes contain a type index (masked to 0x7FFF)
        uint32_t typeIndex = *(uint32_t*)element & 0x7FFF;
        // Call the appropriate destructor from the global table
        g_elementDestructors[typeIndex](element);
        // Decrease the size
        m_buffer[0]--;
    }
};

// Global assertion flag initialization
bool AptStack::g_aptAssertEnabled = false; // Actual value from DAT_01128f61