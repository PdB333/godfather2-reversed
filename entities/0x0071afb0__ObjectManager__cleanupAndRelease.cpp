// FUNC_NAME: ObjectManager::cleanupAndRelease
void __fastcall ObjectManager::cleanupAndRelease(ObjectManager* thisPtr)
{
    // thisPtr+0x1: count of elements in array
    int index = thisPtr->elementCount - 1;
    if (index >= 0)
    {
        // Each element is 12 bytes. Offset from start of array.
        int offset = index * 12;
        do
        {
            // Check if the first field of the element (likely a pointer or marker) is non-zero.
            if (*(int*)((char*)thisPtr->elements + offset) != 0)
            {
                // Destroy the element at this offset (FUN_004daf90 is likely element destructor)
                destroyElement((char*)thisPtr->elements + offset);
            }
            index--;
            offset -= 12;
        } while (index >= 0);
    }

    // Call virtual function at vtable+4 on element array handle with argument 0.
    // (This might release the memory of the array itself.)
    VirtualDeleter* deleter = thisPtr->deleter; // thisPtr+0x10: pointer to a helper/manager with vtable
    deleter->vtable->release(thisPtr->elements, 0); // vtable offset 4

    // If there is a secondary pointer (thisPtr+0xC), release it similarly.
    if (thisPtr->secondaryObject != nullptr)
    {
        deleter->vtable->release(thisPtr->secondaryObject, 0);
    }

    // Finally, call the virtual function at vtable+0xC on the deleter (likely final cleanup)
    deleter->vtable->finalize();
}