// FUNC_NAME: EARSObject::constructor

// Function address: 0x00449760 - EARSObject constructor (singleton registration)
// Sets up vtable pointers for multiple inheritance (offsets +0x00 and +0x04)
// Initializes member fields at offsets +0x08 and +0x0C
// Stores 'this' in global pointer (DAT_01223438)
// Optionally registers with two external lists (DAT_012069c4, DAT_012069b4)

void* __thiscall EARSObject::constructor(EARSObject* this)
{
    // Pointer to the base subobject (offset +0x04)
    uint32_t* baseVtablePtr = reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(this) + 4);

    // Store singleton reference globally
    g_EARSObjectSingleton = this;  // DAT_01223438

    // Temporary base vtable assignment (likely from base constructor call)
    *baseVtablePtr = reinterpret_cast<uint32_t>(&PTR_FUN_00e2f19c);

    // Member initialization
    this->field_08 = 1;  // +0x08: reference count / active flag
    this->field_0C = 0;  // +0x0C: unknown

    // Set derived class vtable at offset +0x00
    this->vtable = reinterpret_cast<uint32_t>(&PTR_FUN_00e311e0);

    // Overwrite base vtable at offset +0x04 with final correct pointer
    *baseVtablePtr = reinterpret_cast<uint32_t>(&PTR_LAB_00e311e4);

    // Register with external lists if they exist
    if (g_listA != 0)  // DAT_012069c4
    {
        FUN_00407e60(baseVtablePtr, &g_listA);
    }
    if (g_listB != 0)  // DAT_012069b4
    {
        FUN_00407e60(baseVtablePtr, &g_listB);
    }

    return this;
}