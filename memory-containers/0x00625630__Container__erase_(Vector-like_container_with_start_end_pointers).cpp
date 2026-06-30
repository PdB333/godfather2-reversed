// FUNC_NAME: Container::erase (Vector-like container with start/end pointers)
// Address: 0x00625630
// Removes element at 1-based index from dynamic array of 8-byte elements.
// Container layout: +0x08 = end pointer (pointer to one past last element)
//                   +0x0C = start pointer (pointer to first element)
void __thiscall Container::erase(int index) {
    int elementAddr;
    int* src; // pointer to current element being shifted

    if (index < 1) {
        // Invalid index – default to removing first element via separate path
        elementAddr = FUN_00625430(); // likely pop_front() or shift operation
    } else {
        // Calculate address of element to remove: start + (index-1)*8
        elementAddr = *(int*)(this + 0x0C) + -8 + index * 8;
    }

    // src points to the element after the one being removed
    src = (int*)(elementAddr + 8);

    // Shift all subsequent elements down by one position (each element = 8 bytes)
    while (src < *(int**)(this + 0x08)) {
        src[-2] = src[0];  // copy first dword
        src[-1] = src[1];  // copy second dword
        src += 2;          // advance by 2 ints (8 bytes)
    }

    // Decrement end pointer by element size (8 bytes)
    *(int*)(this + 0x08) = *(int*)(this + 0x08) - 8;
}