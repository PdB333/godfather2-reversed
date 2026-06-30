// FUNC_NAME: SimManager::processSlotByIndex
// Address: 0x0053b4f0
// Role: Retrieves an object from a global array (size 0x3c each) by index (stored in a global byte) and calls a processing function if the object exists.

void __thiscall SimManager::processSlotByIndex(int param_2)
{
    // Global pointer to array of objects (size 0x3c each) - +0x00 base
    int* objectArray = (int*)0x011254b8;
    // Global byte serving as index into the array - +0x00
    unsigned int index = *(unsigned char*)0x01125389;
    // Compute pointer to the object at the given index
    int* targetObject = (int*)((int)objectArray + index * 0x3c);
    
    if (targetObject != (int*)0) {
        // Call function with global context (0x011252ec), the object pointer, and the second parameter
        FUN_0060add0(*(int*)0x011252ec, (int)targetObject, param_2);
    }
    return;
}