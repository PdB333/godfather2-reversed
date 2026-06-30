// FUNC_NAME: ManagerClass::destroy
void __fastcall ManagerClass::destroy(ManagerClass* this)
{
    int i;
    int j;
    int offset;

    // Set vtable pointers for this object (likely base class vtables)
    this->vtable = &PTR_FUN_00d5d724;          // +0x00: primary vtable
    this->vtable2 = &PTR_LAB_00d5d714;         // +0x3C: secondary vtable
    this->vtable3 = &PTR_LAB_00d5d710;         // +0x48: tertiary vtable

    // Global reference counting or initialization
    FUN_004086d0(&DAT_0112a534);
    FUN_00408310(&DAT_0112a534);
    FUN_004086d0(&DAT_0112db74);

    // Destroy each element in the array
    if (this->elementCount > 0)                // +0x54: number of elements
    {
        offset = 0;
        i = 0;
        do
        {
            // Each element is 0x30 bytes; get pointer at offset 0x10 within element
            int* subObj = *(int**)(this->elementArray + 0x10 + offset); // +0x58: pointer to array
            if (subObj != 0)
            {
                FUN_005e6820(subObj, 0, 0);   // Destroy sub-object part 1
                FUN_006a5690(subObj, 0, 0);   // Destroy sub-object part 2
                FUN_005e6660(subObj);         // Destroy sub-object part 3
            }
            i++;
            offset += 0x30;                   // Advance to next element
        } while (i < this->elementCount);
    }

    // Reset vtable pointers for each element (to base class vtable)
    int count2 = this->someOtherCount - 1;     // +0x5C: another count (maybe last index)
    if (count2 >= 0)
    {
        offset = count2 * 0x30;
        do
        {
            // Set vtable at offset 0x24 within each element to base vtable
            *(void***)(this->elementArray + 0x24 + offset) = &PTR_LAB_00e2f0c0;
            count2--;
            offset -= 0x30;
        } while (count2 >= 0);
    }

    // Free the array memory
    if (this->elementArray != 0)
    {
        FUN_009c8f10(this->elementArray);      // operator delete
    }

    // Global cleanup
    FUN_0046c640();
}