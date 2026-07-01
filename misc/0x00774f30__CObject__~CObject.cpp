// FUNC_NAME: CObject::~CObject

// Destructor for a CObject that manages two contained objects at offsets 0x54 and 0x5C.
// The object at 0x5C may be part of a linked structure; if its pointer value is not 0 or 0x48
// and a flag bit (bit 5 of field at +0x64) is clear, it treats it as a handle to a subobject
// at handle - 0x48, then performs a virtual function call on that subobject (if a field at offset 0x12C is valid).
// Finally both contained pointers are freed via a custom deallocation function (FUN_004daf90),
// and a global cleanup function (FUN_004ac1e0) is invoked.
void __thiscall CObject::~CObject(CObject* this)
{
    // Set vtable pointer to base class vtable (destructor chain)
    this->vtable = &VTABLE_BASE;  // PTR_LAB_00d67f24

    int* subObjPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x5C); // +0x5C
    int subObjVal = *subObjPtr; // could be a pointer or handle
    int field_0x64 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x64); // +0x64

    // Bit 5 of field_0x64 must be clear
    if (subObjVal != 0 && subObjVal != 0x48 && ((field_0x64 >> 5) & 1) == 0)
    {
        int* pSubObj = (subObjVal == 0) ? 0 : reinterpret_cast<int*>(subObjVal - 0x48);

        if (pSubObj != 0)
        {
            // Check a field at offset 0x12C (300) from pSubObj
            int* field_0x12C = reinterpret_cast<int*>(reinterpret_cast<char*>(pSubObj) + 0x12C);
            if (*field_0x12C != 0 && *field_0x12C != 0x48)
            {
                // Virtual function call at index 7 (0x1C/4) from vtable at offset 0x128
                int** vtable = reinterpret_cast<int**>(reinterpret_cast<char*>(pSubObj) + 0x128);
                void (*virtualFunc)(int*) = reinterpret_cast<void (*)(int*)>((*vtable)[7]);
                virtualFunc(reinterpret_cast<int*>(pSubObj));
            }
        }
    }

    // Free the object at offset 0x5C
    if (*subObjPtr != 0)
    {
        FUN_004daf90(subObjPtr); // custom deallocator (likely operator delete or free)
    }

    // Free the object at offset 0x54
    int* subObj2Ptr = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x54); // +0x54
    if (*subObj2Ptr != 0)
    {
        FUN_004daf90(subObj2Ptr);
    }

    // Global cleanup
    FUN_004ac1e0();
}