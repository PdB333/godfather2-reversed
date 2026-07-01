// FUNC_NAME: SmartPtrArray::removeSmartPtrWithTemporaryNode
void __thiscall SmartPtrArray::removeByPointer(SmartPtr* targetPtr) {
    // targetPtr is a smart pointer whose managed object we want to remove from this array.
    // To prevent the object from being destroyed during removal, we link targetPtr into
    // a temporary stack-based linked ring.
    SmartPtr* savedNext = targetPtr->next; // +0x04
    SmartPtr stackNode; // local_8
    stackNode.obj = targetPtr;             // local_8 points to smart pointer (circular)
    targetPtr->next = &stackNode;          // link targetPtr to stackNode

    SmartPtr** dataPtr = *(SmartPtr***)(this + 4); // pointer to array of SmartPtr pointers
    int count = *(int*)(this + 8);                 // number of elements

    SmartPtr* foundSmartPtr = nullptr;     // piVar1
    SmartPtr** current = dataPtr;          // piVar3
    SmartPtr** end = current + count;      // piVar4

    while (true) {
        if (current == end) goto cleanup_and_release; // not found

        SmartPtr* entry = *current;        // piVar1: pointer to a SmartPtr stored in the array
        if (entry != nullptr && entry->obj == targetPtr->obj) { // compare managed objects
            foundSmartPtr = entry;         // found the entry that owns the same managed object
            break;
        }
        current++;
    }

    if (foundSmartPtr != nullptr) {
        // Destroy the managed object if it's unique? Or just release the smart pointer?
        if (foundSmartPtr->obj != nullptr) {
            // Call destruct/release on the managed object (likely ref count decrement)
            releaseManagedObject(foundSmartPtr->obj); // FUN_004daf90
        }
        // Deallocate the SmartPtr object itself
        deallocateSmartPtr(foundSmartPtr); // FUN_009c8eb0
    }

    // Shift remaining elements after the removed slot
    int shiftCount = count - (current - dataPtr) - 1; // number of elements after removed
    if (shiftCount > 0) {
        SmartPtr** src = current + 1;
        SmartPtr** dst = current;
        do {
            *dst++ = *src++;
            shiftCount--;
        } while (shiftCount > 0);
    }

    // Decrement size
    *(int*)(this + 8) = count - 1;

cleanup_and_release:
    // Release the managed object if the target pointer was valid
    if (targetPtr->obj != nullptr) {
        // Call virtual release function (param_2->vtable[0] with arg 1)
        (**(void (__thiscall**)(int))targetPtr->obj)(1); // e.g., release with flag
    }
    // Release the temporary stack node if non-null
    if (stackNode.obj != nullptr) {
        releaseManagedObject(&stackNode); // FUN_004daf90 on stackNode
    }
}
```