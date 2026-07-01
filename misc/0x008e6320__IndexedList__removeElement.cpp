//FUNC_NAME: IndexedList::removeElement
// Function address: 0x008e6320
// Role: Removes an element from a dynamic array by value or index, swapping with last element.
// Fields: +0x20 pointer to array of ints (elements), +0x24 count of elements.

void __thiscall IndexedList::removeElement(int value, uint index)
{
    uint i;
    int *pElement;

    // If index is 0xFFFFFFFF, search for the value in the array
    if (index == 0xffffffff) {
        i = 0;
        index = 0xffffffff;
        if (this->count != 0) {
            pElement = this->elements;
            do {
                index = i;
                if (*pElement == value) break;
                i = i + 1;
                pElement = pElement + 1;
                index = 0xffffffff;
            } while (i < this->count);
        }
    }

    // If the found index is not the last element, swap with the last element
    if (index != this->count - 1U) {
        this->elements[index] = this->elements[this->count - 1];
    }

    // Decrement count
    this->count = this->count - 1;

    // Notify or perform cleanup after removal
    this->onElementRemoved();
}