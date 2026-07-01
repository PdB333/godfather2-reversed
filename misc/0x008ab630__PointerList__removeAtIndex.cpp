// FUNC_NAME: PointerList::removeAtIndex
void __thiscall PointerList::removeAtIndex(int* thisPointer, int index)
{
    int* data = (int*)*thisPointer;      // array of elements (each 8 bytes: [objectPtr, nextPtr])
    int count = thisPointer[1];           // current element count
    int* lastElement;
    int* targetElement;
    int objectPtr;

    // Only need to swap if the element to remove is not the last one.
    if (index != count - 1) {
        lastElement = (int*)((int)data + (count - 1) * 8); // pointer to last element
        targetElement = (int*)((int)data + index * 8);      // pointer to element at index

        if (targetElement != lastElement) {
            objectPtr = *lastElement; // save the object pointer of the last element

            // If the target element's object is different from the last's object,
            // release the target's old object and copy the last's object into target.
            if (*targetElement != objectPtr) {
                if (*targetElement != 0) {
                    releaseElement(targetElement); // call to FUN_004daf90
                }
                *targetElement = objectPtr;
                if (objectPtr != 0) {
                    // Update the intrusive linked list: copy the next pointer from the
                    // object and set the object's back pointer to point to this element.
                    targetElement[1] = *(int*)(objectPtr + 4);
                    *(int**)(objectPtr + 4) = targetElement;
                }
            }
        }
    }

    // Decrease the count, effectively removing the element (now at the end after swap).
    thisPointer[1] = count - 1;

    // After decrement, the element at the new last position (index = count-1 before removal)
    // may still have a non‑zero object pointer. If so, release it.
    // Note: The decompiled output shows a call to FUN_004daf90 with no arguments.
    // This is likely a decompilation error; we assume it should release the element
    // at (data + count * 8) after decrement.
    if (*(int*)((int)data + (thisPointer[1]) * 8) != 0) {
        releaseElement((int*)((int)data + (thisPointer[1]) * 8));
    }
}