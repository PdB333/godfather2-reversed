// FUNC_NAME: SomeClass::swapAndForward
// Function address: 0x008258c0
// Role: Wrapper that swaps the order of two parameters before forwarding to the actual implementation.
// This likely exists due to a calling convention mismatch or a design pattern where the underlying
// function expects arguments in a specific order.

class SomeClass {
public:
    // __thiscall: this pointer is the first implicit parameter
    void* __thiscall swapAndForward(void* value2, void* value3) {
        // Forward to inner function with swapped arguments
        FUN_00825800(this, value3, value2);  // Underlying implementation takes (this, value3, value2)
        return this; // Return this pointer for chaining
    }
};