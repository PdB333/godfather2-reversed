// FUNC_NAME: SlotArray::removeAtIndex
void __thiscall SlotArray::removeAtIndex(int index)
{
    int *lastElement;
    int *targetElement;
    int value;

    // If the element to remove is not the last one, swap with the last element.
    if (index != this->count - 1) {
        // Pointer to the last element in the array
        lastElement = (int *)(this->pBuffer + (this->count - 1) * 2); // each element is 2 ints (8 bytes)
        // Pointer to the element to remove
        targetElement = (int *)(this->pBuffer + index * 2);
        if (targetElement != lastElement) {
            value = *lastElement; // value of last element (object pointer)
            if (*targetElement != value) {
                // Release the old object if present
                if (*targetElement != 0) {
                    releaseNode(targetElement); // FUN_004daf90(targetElement)
                }
                *targetElement = value;
                if (value != 0) {
                    // Update the linked list: the target element becomes the previous node for the object.
                    // The object at 'value' has a back-pointer at offset +0x04 to its containing slot.
                    targetElement[1] = *(int *)(value + 4); // store previous object's back-pointer?
                    *(int **)(value + 4) = targetElement;   // object now points to this slot
                }
            }
        }
    }
    // Decrement the count
    this->count--;

    // If the new last element (now at index = count) has a non-null object, release it.
    // This handles the case where the removed element was the last one.
    if (*(int *)(this->pBuffer + this->count * 2) != 0) {
        releaseNode(); // likely releaseNode((int*)(this->pBuffer + this->count*2))
    }
}