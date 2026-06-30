// FUNC_NAME: Iterator::getCurrentField

#include <cassert>

class Iterator {
public:
    // Iterator structure:
    // +0x00: pointer to container (int*)
    // +0x04: pointer to current element (int*)
    
    // Container structure (at *containerPtr):
    // +0x00: data pointer (unused here)
    // +0x04: end pointer (one past last element)
    
    int* containerPtr;  // +0x00
    int* currentPtr;    // +0x04

    // Returns pointer to field at offset 0x0C within the current element.
    // Asserts that container is non-null and iterator is not past end.
    int* getCurrentField() {
        // Check container exists
        if (containerPtr == nullptr) {
            reportAssert(); // assertion failure
        }
        // Check we haven't reached the end
        if (currentPtr == reinterpret_cast<int*>(containerPtr[1])) {
            reportAssert(); // assertion failure
        }
        // Return pointer to offset 0x0C in the current element
        return currentPtr + 0x0C; // Equivalent to (int*)((char*)currentPtr + 0x0C)
    }
};