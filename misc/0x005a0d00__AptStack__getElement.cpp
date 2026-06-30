// FUNC_NAME: AptStack::getElement
int __thiscall AptStack::getElement(int index) {
    // this is passed in EDI, but Ghidra doesn't show that directly.
    // The stack object has a size field at offset 0, and elements stored from offset 4 (or similar).
    // The assert ensures index is within valid range: nElements - nPos > 0, i.e., index < size.
    int size = *(int*)this;
    // Check: if size != index && size - index >= 0, we are within bounds; else assert.
    if (size != index && (size - index) >= 0) {
        goto valid_access;
    }
    // Debug assertion failed: "nElements - nPos > 0"
    // source file: "c:\packages001_pc\apt\0.19.optimized\source\apt\_AptStack.h", line 47
    EA_DEBUG_ASSERT_EXPRESSION("nElements - nPos > 0", "_AptStack.h", 47, 2);
    // The actual assert function uses thread-local storage to call a debug handler.
    // If not already suppressed, it triggers a breakpoint.
    // (Simplified: we just return the value anyway if assert is ignored.)

valid_access:
    // Return the element at index from the top? Note: accessing array[size - index].
    // This suggests elements are stored in reverse order, or index is a distance from top.
    return ((int*)this)[size - index];
}