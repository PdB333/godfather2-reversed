// FUNC_NAME: DynamicArray<DataElement>::addElement(const DataElement&)
void __thiscall DynamicArray::addElement(int* thisPtr, int* elementPtr)
{
    int* dataPtr = (int*)thisPtr[0]; // +0x00: pointer to allocated data
    int& sizeRef = thisPtr[1];       // +0x04: current number of elements
    int& capacityRef = thisPtr[2];   // +0x08: allocated capacity

    if (sizeRef == capacityRef)
    {
        int newCapacity;
        if (capacityRef == 0)
        {
            newCapacity = 1;
        }
        else
        {
            newCapacity = capacityRef * 2;
        }
        reserve(newCapacity); // FUN_008c2080: reallocate to new capacity
    }

    // Compute destination pointer for the new element at index sizeRef
    DataElement* dest = (DataElement*)(dataPtr + sizeRef * 0x1c); // size of DataElement is 28 bytes (0x1c)
    sizeRef++;

    if (dest != nullptr)
    {
        // Initialize sub-object at offset +16 (12 bytes) to zero
        dest->subObject.field0 = 0; // +0x10
        dest->subObject.field1 = 0; // +0x14
        dest->subObject.field2 = 0; // +0x18

        // Copy first three dwords (offsets 0,4,8)
        dest->field0 = elementPtr->field0; // +0x00
        dest->field1 = elementPtr->field1; // +0x04
        dest->field2 = elementPtr->field2; // +0x08

        // Copy sub-object using its copy constructor (FUN_00792320)
        copySubObject(&dest->subObject, &elementPtr->subObject); // param_2+4 -> offset 16

        // Copy byte at offset 12
        dest->flags = elementPtr->flags; // +0x0C (byte)
    }
}