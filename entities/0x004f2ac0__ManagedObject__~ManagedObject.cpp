// FUNC_NAME: ManagedObject::~ManagedObject
void* __thiscall ManagedObject::~ManagedObject(ManagedObject* this, byte deleteFlag)
{
    // Set vtable pointer (likely to base class vtable)
    this->vtable = &PTR_FUN_00e37110;

    // Check if there is a resource pointer at offset 0x10
    int* resourcePtr = this->field_0x10;
    if (resourcePtr != 0)
    {
        // Get the global list head at DAT_01206880 + 0x14
        int** listHead = (int**)(DAT_01206880 + 0x14);
        // Write a sentinel/label to the current list position
        *(void**)*listHead = &PTR_LAB_01123be8;
        // Advance the list head pointer
        (*listHead)++;
        // Store the resource pointer in the list
        *(int*)*listHead = (int)resourcePtr;
        // Advance again
        (*listHead)++;
        // Clear the resource fields
        this->field_0x10 = 0;
        this->field_0x14 = 0;
    }

    // If delete flag is set, deallocate the object
    if ((deleteFlag & 1) != 0)
    {
        FUN_009c8eb0(this); // operator delete
    }

    return this;
}