// FUNC_NAME: ObjectArray::removeElement

void __thiscall ObjectArray::removeElement(int *this, int index)
{
    int *lastElement;
    int *targetElement;
    int *objectPtr;

    // Check if index is not the last element
    if (index != this[1] - 1) {
        // Get pointer to last element (base + (count-1)*8)
        lastElement = (int *)(*this + -8 + this[1] * 8);
        // Get pointer to target element (base + index*8)
        targetElement = (int *)(*this + index * 8);

        if (targetElement != lastElement) {
            // Move the last element's object pointer to the target slot
            objectPtr = (int *)*lastElement;
            if (*targetElement != (int)objectPtr) {
                // Release the existing object in the target slot, if any
                if (*targetElement != 0) {
                    releaseObject(targetElement);
                }
                *targetElement = (int)objectPtr;
                if (objectPtr != 0) {
                    // Adjust linked list pointers: 
                    // The array element's second field stores the object's original next pointer,
                    // and the object's next pointer (offset +0x4) now points back to the array element.
                    targetElement[1] = *(int *)((int)objectPtr + 4);
                    *(int **)((int)objectPtr + 4) = targetElement;
                }
            }
        }
    }

    // Decrement the count
    this[1] = this[1] - 1;

    // After removal, if the slot at the new tail (which now holds the moved element) is non-null,
    // call releaseObject on it (maybe to finalize the move?).
    if (*(int *)(*this + this[1] * 8) != 0) {
        releaseObject();
    }
}