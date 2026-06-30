// FUNC_NAME: PointerArray::removeElement
// Address: 0x006e9760
// Removes a pointer from a dynamic array of void* elements.
// This is a member function of a class that stores an array of pointers (+0x18) and count (+0x1c).
// The function finds the element and shifts subsequent entries left, decrementing count.

void __thiscall PointerArray::removeElement(void* element) {
    int count = *(int*)(this + 0x1c);                // m_count
    void** array = *(void***)(this + 0x18);          // m_array
    int index = -1;

    // Search for the element
    for (int i = 0; i < count; ++i) {
        if (array[i] == element) {
            index = i;
            break;
        }
    }

    // If not found, do nothing
    if (index == -1) {
        return;
    }

    // Shift elements left to fill the gap
    for (int j = index; j < count - 1; ++j) {
        array[j] = array[j + 1];
    }

    // Decrement count
    *(int*)(this + 0x1c) = count - 1;
}