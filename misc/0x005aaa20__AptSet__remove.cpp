// FUNC_NAME: AptSet::remove
bool __thiscall AptSet::remove(int this, int element)
{
    // Assert that the number of elements is within the maximum size (64)
    if (*(int*)this > 63) {
        // Debug assertion failure: "nElements < _nSize"
        // This is a typical EA debug assert with file/line info
        char* expr = "nElements < _nSize";
        char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptSet.h";
        int line = 0x3b; // 59
        int flags = 2;
        // The assertion handler is called via FS segment (thread-local storage)
        // If the assertion fails, it may break into debugger
        // (simplified: we just return false in release, but here we mimic the debug behavior)
        // In the original code, it calls a debug function and possibly triggers a breakpoint
        // For reconstruction, we'll just return false to indicate failure
        return false;
    }

    int count = *(int*)this;               // +0x00: number of elements
    int* elements = (int*)(this + 4);      // +0x04: array of element pointers (size 64)

    int i = 0;
    while (i < count) {
        if (elements[i] == element) {
            // Found the element at index i
            if (i > 63) {
                return false; // Safety check (should not happen)
            }
            // Decrement the count
            (*(int*)this)--;
            // Call destructor on the element (via a vtable or function pointer table)
            // The destructor is looked up from a global table at DAT_0103aee0, indexed by (element & 0x7fff)
            // This suggests elements are handles or pointers with a type tag in the low bits
            int typeIndex = (*(uint*)element) & 0x7fff;
            void (*destructor)(void*) = *(void (**)(void*))(DAT_0103aee0 + typeIndex * 4);
            destructor((void*)element);
            // Clear the slot
            elements[i] = 0;
            return true;
        }
        i++;
    }
    return false; // Element not found
}