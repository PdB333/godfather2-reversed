// FUNC_NAME: ResourceArray::clear
void __thiscall ResourceArray::clear(void)
{
    int iVar1;
    int iVar2;
    int *slotPtr;
    int count;

    // Count of elements in the array
    count = this->count - 1;
    if (-1 < count) {
        // Offset to the last element (each element is 0x4C = 76 bytes)
        iVar2 = count * 0x4c;
        do {
            // Get pointer to the element at the current offset
            slotPtr = (int *)(this->buffer + iVar2);

            // Destroy slot at +0x30 (fourth object slot)
            // The object pointer is at +0x30, its destructor is at +0x3C
            iVar1 = *(int *)((int)this->buffer + 0x30 + iVar2);
            if (iVar1 != 0) {
                (*(void (__thiscall **)(int))slotPtr[0xf])(iVar1);
            }

            // Destroy slot at +0x20 (third object slot)
            // Object pointer at +0x20, destructor at +0x2C
            if (slotPtr[8] != 0) {
                (*(void (__thiscall **)(int))slotPtr[0xb])(slotPtr[8]);
            }

            // Destroy slot at +0x10 (second object slot)
            // Object pointer at +0x10, destructor at +0x1C
            if (slotPtr[4] != 0) {
                (*(void (__thiscall **)(int))slotPtr[7])(slotPtr[4]);
            }

            // Destroy slot at +0x00 (first object slot)
            // Object pointer at +0x00, destructor at +0x0C
            if (*slotPtr != 0) {
                (*(void (__thiscall **)(int))slotPtr[3])(*slotPtr);
            }

            count--;
            iVar2 -= 0x4c;
        } while (-1 < count);
    }

    // Reset count, deallocate the buffer, and clear pointers
    this->count = 0;
    deallocateBuffer(this->buffer);
    this->buffer = 0;
    this->field_8 = 0;

    return;
}