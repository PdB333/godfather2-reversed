// FUNC_NAME: AptStack::top
// Function at 0x005b1b90: Returns the top element of the stack without popping.
// Debug assertion macro from _AptStack.h (line 47): "nElements - nPos > 0"

class AptStack {
public:
    int top() {
        // Check that the stack is not empty (nCount > 0)
        if (nCount > 0) {
            // Return the top element (elements are stored starting at index 1 in the raw array)
            return elements[nCount - 1];
        }
        // Assertion failure: trigger debug break if enabled
        // In release builds, this would be undefined behavior / a crash
        // The assertion macro uses the file, line, and condition string
        // Here we simulate with a breakpoint and exit
        #ifdef _DEBUG
            // Debug assertion handler (implementation omitted for brevity)
            // Typically calls __debugbreak() or similar
            __debugbreak();
        #endif
        return 0; // Never reached in debug builds; included for release
    }

private:
    int nCount;      // +0x00: number of elements, also index of top element in raw array
    int elements[1]; // +0x04: array of elements (actual capacity determined by context)
};