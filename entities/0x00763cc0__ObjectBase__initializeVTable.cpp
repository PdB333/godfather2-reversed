// FUNC_NAME: ObjectBase::initializeVTable
void __thiscall ObjectBase::initializeVTable(int this, char* methodTable) // methodTable is treated as byte pointer (vtable entries, 8-byte each)
{
    // this +0x78 points to a sub-object (e.g., a component manager)
    int subObj = *(int*)(this + 0x78);
    if (*(int*)(subObj + 0x7c) != 0) // check first internal pointer
    {
        int ptr = *(int*)(subObj + 0x88); // second internal pointer
        if (ptr != 0)
        {
            // Free two pairs of resources (e.g., audio handles or memory)
            // FUN_005f5c20 likely is a release/delete function taking (pointer, size or adjustment)
            releaseObject(*(int*)(subObj + 0x7c), *(int*)(subObj + 0x84)); // +0x84 companion value
            releaseObject(ptr, *(int*)(subObj + 0x90)); // +0x90 companion value
        }
    }

    // Get two sets of handles (e.g., task IDs or array buffers)
    int handlesA[3]; // aiStack_24
    int handlesB[3]; // aiStack_18
    getHandles(*(int*)(this + 0xdc), handlesA, handlesB); // FUN_00752b60 at +0xdc

    // Clean up if any handles were obtained
    if (handlesA[0] != 0)
        deleteArray(handlesA); // FUN_004daf90
    if (handlesB[0] != 0)
        deleteArray(handlesB);

    // Install member function pointers (this, function) pairs into the method table.
    // Each pair is 8 bytes: low 32 bits = this pointer, high 32 bits = function address.
    // Offsets are byte offsets into the table.
    *(ulonglong*)(methodTable + 0x34) = CONCAT44(&LAB_00762af0, this);
    *(ulonglong*)(methodTable + 0x36) = (ulonglong)uStack_c << 0x20;            // uStack_c uninitialized in decompiler
    *(ulonglong*)(methodTable + 0x38) = CONCAT44(&LAB_007631a0, uStack_8);      // uStack_8 uninitialized
    *(ulonglong*)(methodTable + 0x3a) = CONCAT44(FUN_00763c30, this);           // likely a sibling function
    *(ulonglong*)(methodTable + 0x3c) = (ulonglong)uStack_c << 0x20;            // repeated for symmetry
    *(ulonglong*)(methodTable + 0x3e) = CONCAT44(&LAB_007631b0, uStack_8);      // another label
}