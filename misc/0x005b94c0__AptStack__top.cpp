// FUNC_NAME: AptStack::top
// Function address: 0x005b94c0
// Returns the top element of the stack without removing it.
// Asserts that the stack is not empty (nElements - nPos > 0).

struct AptStack {
    int mCount;       // +0x00: number of elements currently in stack
    int mElements[1]; // +0x04: start of element array (actual size varies)
};

int __thiscall AptStack::top() {
    // Assertion: stack must not be empty
    if (mCount <= 0) {
        // Debug assertion from _AptStack.h line 47:
        // "nElements - nPos > 0"
        // In debug builds, this triggers a breakpoint or error message.
        // The full assertion code (FS segment, debug output, etc.) is omitted.
    }
    // Return the top element (index mCount, since mElements[0] is the first element)
    return mElements[mCount];
}