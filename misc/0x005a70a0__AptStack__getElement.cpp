// FUNC_NAME: AptStack::getElement
// Address: 0x005a70a0
// This function implements a stack element accessor with bounds checking.
// It asserts that the requested position is within the stack's element count.
// The stack stores elements as a contiguous array after a header containing the count.
// Elements are indexed from the top: position 0 is the top-most element.

int AptStack::getElement(int nPos) {
    // Debug assertion: ensure nPos is within valid range (nElements - nPos > 0)
    // If the global debug flag (DAT_01128fa5) is non-zero, the assertion is active.
    // In production builds, this check is typically removed.
    if (m_nElements != nPos && m_nElements - nPos >= 0) {
        // Condition passes, proceed to return element
    } else {
        // Assertion failed! Trigger breakpoint and potential debug handler.
        // The original code uses thread-local storage and function pointers for assert handling.
        // Here we replace with a simple assert for clarity.
        // (Original: __debugbreak() if assertion triggers)
        // (Release build: this block is omitted)
        __debugbreak(); // or assert(0)
    }
    // Access element: data is stored as an int array immediately after the header.
    // The header at offset 0 holds m_nElements (count).
    // Elements occupy indices 1 through m_nElements (inclusive).
    // The requested position nPos (0 = top) maps to index m_nElements - nPos.
    return *(reinterpret_cast<int*>(this) + m_nElements - nPos);
}