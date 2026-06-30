// FUNC_NAME: DynamicArray::pushBack
void DynamicArray::pushBack(void* element)
{
    // FUN_00654620 is likely reallocateIfNeeded or growCapacity
    FUN_00654620();
    
    // Increment array size
    *arraySize = *arraySize + 1;
    
    // Calculate address of new element slot
    // elementSize = 0x14 (20 bytes)
    // baseAddress = this + 8 (offset +2 for int*)
    // newSlot = baseAddress + (size - 1) * elementSize
    undefined8* newSlot = (undefined8*)(elementData + (-0x14 + *arraySize * 0x14));
    
    if (newSlot != (undefined8*)0x0) {
        // Copy element data (2 * 8 bytes + 4 bytes = 20 bytes total)
        *newSlot = *element;
        newSlot[1] = element[1];
        *(undefined4*)(newSlot + 2) = *(undefined4*)(element + 2);
    }
}