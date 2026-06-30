// FUNC_NAME: PooledObject::~PooledObject
void __fastcall PooledObject::~PooledObject(int* this)
{
    int resource1 = this[6];  // +0x18: first resource pointer
    int resource2 = this[7];  // +0x1C: second resource pointer

    // Set vtable to initial destructor vtable
    *this = (int)&PTR_FUN_00e37798;

    if (resource1 != 0) {
        // Global memory manager at DAT_012068e8
        // Offset +0x14 holds a pointer to a free-list node pointer
        int* freeListPtr = *(int**)(DAT_012068e8 + 0x14);
        // Write sentinel marker to current free-list node
        **(int**)(DAT_012068e8 + 0x14) = (int)&PTR_LAB_01124ba8;
        *freeListPtr = *freeListPtr + 4;  // Advance to next slot
        *(int*)*freeListPtr = resource1;  // Store the resource pointer
        *freeListPtr = *freeListPtr + 4;  // Advance again
        this[6] = 0;  // Clear the field
    }

    if (resource2 != 0) {
        int* freeListPtr = *(int**)(DAT_012068e8 + 0x14);
        **(int**)(DAT_012068e8 + 0x14) = (int)&PTR_LAB_01124ba8;
        *freeListPtr = *freeListPtr + 4;
        *(int*)*freeListPtr = resource2;
        *freeListPtr = *freeListPtr + 4;
        this[7] = 0;
    }

    // Transition vtable to base class vtable (likely after deallocation)
    *this = (int)&PTR_LAB_00e37304;
    return;
}