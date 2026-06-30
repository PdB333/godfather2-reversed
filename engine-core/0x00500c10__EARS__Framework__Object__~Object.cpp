// FUNC_NAME: EARS::Framework::Object::~Object
// Function address: 0x00500c10
// Role: Destructor for a base object in the EARS framework. Releases resources and removes from global free list.

void __fastcall EARS::Framework::Object::~Object(Object* this)
{
    // Set vtable to first derived class vtable (likely for proper destruction order)
    this->vtable = &PTR_FUN_00e37d00;

    // If a resource at offset 0x44 is allocated, release it
    if (this->field_0x44 != 0) {
        FUN_004eba30(1); // Release resource (e.g., sound, animation)
    }

    // Set vtable to base class vtable
    this->vtable = &PTR_FUN_00e37110;

    // If a pointer at offset 0x10 is non-null, add it to the global free list
    if (this->field_0x10 != 0) {
        // Global memory manager at DAT_01206880, free list pointer at offset 0x14
        int** freeListPtr = (int**)(DAT_01206880 + 0x14);

        // Write sentinel to current free list head
        **freeListPtr = &PTR_LAB_01123be8;
        (*freeListPtr)++; // Advance to next slot

        // Store the pointer from field_0x10 into the free list
        **freeListPtr = this->field_0x10;
        (*freeListPtr)++; // Advance again

        // Clear the fields
        this->field_0x10 = 0;
        this->field_0x14 = 0;
    }
}