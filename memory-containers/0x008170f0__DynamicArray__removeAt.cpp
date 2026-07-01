// FUNC_NAME: DynamicArray::removeAt
void __thiscall DynamicArray::removeAt(int index) {
    // container structure: [0] = array pointer, [4] = element count
    // each element is 0x18 (24) bytes
    int count = this->count;  // param_1[1]

    if (index != count - 1) {
        // Element* at removed index
        Element* pRemoved = &this->data[index];   // puVar1
        // Element* at last index
        Element* pLast = &this->data[count - 1];  // puVar2

        // Copy first two 32-bit fields (offset 0 and 4) from last element to removed slot
        pRemoved->field0 = pLast->field0;
        pRemoved->field4 = pLast->field4;

        // Release the resource held by the last element's handle (offset 8)
        releaseResource(&pLast->handle);  // FUN_004d3e20(puVar2+2)
    }

    this->count--;  // param_1[1] = param_1[1] - 1

    // Now finalize the last element slot (now beyond new count)
    Element* pOldLast = &this->data[this->count];  // piVar3 = offset 8 of that element
    int handle = pOldLast->handle;  // piVar3[0] (offset 8)
    if (handle != 0) {
        // Call destructor function stored at offset 20 within the element
        pOldLast->destructor(handle);  // (*(code *)piVar3[3])(iVar4)
    }
}