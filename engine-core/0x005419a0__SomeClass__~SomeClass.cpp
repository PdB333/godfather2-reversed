// FUNC_NAME: SomeClass::~SomeClass
// Function address: 0x005419a0
// Destructor for a class with multiple embedded sub-objects (vtables at offsets 0x3C, 0x48, 0x50, 0x54, 0x58)
// The destructor sets all virtual table pointers, releases embedded resources, then calls global cleanup.

void __fastcall SomeClass::~SomeClass(SomeClass *this)
{
    // Set vtables for the main object and embedded sub-objects
    this->vtable = &PTR_FUN_00e392a0;               // +0x00: main vtable
    this->embedded1_vtable = &PTR_LAB_00e393f8;     // +0x3C (0x0F*4)
    this->embedded2_vtable = &PTR_LAB_00e39408;     // +0x48 (0x12*4)
    this->embedded3_vtable = &PTR_LAB_00e3940c;     // +0x50 (0x14*4)
    this->embedded4_vtable = &PTR_LAB_00e39410;     // +0x54 (0x15*4)
    this->embedded5_vtable = &PTR_LAB_00e39470;     // +0x58 (0x16*4)

    // Release global resource (e.g., memory pool, manager)
    FUN_004086d0(&DAT_0120e93c);                    // Likely a static/global release function

    // Release dynamically allocated object at offset 0x260 (if present)
    if (this->m_pSubObject != 0)
    {
        FUN_009f01a0();                             // Some sub-release function
        // Call virtual function at index 2 (offset 8) of sub-object's vtable
        (*(void (**)(int))(this->m_pSubObject[0x64] + 8))(0); // +0x190: pointer to vtable? Actually param_1[100] at +0x190
    }

    // Release secondary pointer at offset 0x264 (if present)
    if (this->m_pSecondary != nullptr)
    {
        // Call virtual function at index 4 (offset 0x10) of the pointed object's vtable
        (*(void (**)(int))(*((int*)this->m_pSecondary) + 0x10 / 4 * 4))(1); // +0x10 offset
    }
    this->m_pSecondary = nullptr;                   // +0x264 reset

    // Final global cleanup calls
    FUN_00562030();                                 // e.g., shutdown manager
    FUN_0046ea20();                                 // e.g., release resources
}