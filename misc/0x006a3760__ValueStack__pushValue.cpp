// FUNC_NAME: ValueStack::pushValue
#include <cstddef>

class ValueStack {
public:
    // Offset +0x48: number of elements in the stack
    int count;

    // Offset +0x5c: fixed-size buffer for 32-bit values (capacity unknown, but assumed sufficient)
    int buffer[]; // Actually defined as int buffer[?]; size determined by class allocation

    /**
     * Pushes a 32-bit value onto the stack.
     * @param value The value to store (treated as a raw 32-bit integer).
     */
    void __thiscall pushValue(int value) {
        // Store value at current count index in buffer
        buffer[count] = value;
        // Increment the count
        count++;
    }
};