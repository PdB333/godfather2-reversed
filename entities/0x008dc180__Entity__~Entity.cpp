// FUNC_NAME: Entity::~Entity
void __fastcall Entity::~Entity(Entity *this)
{
    int *pWeakRef;

    // Set up vtable pointers (constructor-like? but this is destructor, so maybe vtable already set)
    this->m_pVTable = &PTR_FUN_00d7e240; // +0x00
    this->m_pVTable2 = &PTR_LAB_00d7e230; // +0x3C (offset 0x0F)
    this->m_pVTable3 = &PTR_LAB_00d7e22c; // +0x48 (0x12)
    this->m_pVTable4 = &PTR_LAB_00d7e228; // +0x50 (0x14)
    this->m_pVTable5 = &PTR_LAB_00d7e1c8; // +0x54 (0x15)
    this->m_pVTable6 = &PTR_LAB_00d7e160; // +0x58 (0x16)

    // Clean up a sub-object pointer at offset +0x190 (param_1[100])
    if (this->m_pSubObject != nullptr) // +0x190
    {
        FUN_004df600(); // Release or decrement reference count?
        FUN_004df600(); // Double release? Possibly two references
        // Call a virtual function on the object pointed by m_pVTable6 with argument 0x10
        (**(void (__thiscall **)(int, int))(this->m_pVTable6 + 0x28))(this->m_pVTable6, 0x10);
        this->m_pSubObject = nullptr; // +0x190
        this->m_field_0x1AC = 0; // +0x1AC (param_1[0x6b])
    }

    // Destroy sub-object at offset +0x194 (param_1+0x65)
    FUN_004086d0(&this->m_subObj1); // Destructor call
    FUN_00408310(&this->m_subObj1); // Deallocation or final cleanup

    // Destroy another sub-object at offset +0x19C (param_1+0x67)
    FUN_004086d0(&this->m_subObj2);
    FUN_00408310(&this->m_subObj2);

    // Clean up pointer at offset +0x1A4 (param_1+0x69)
    pWeakRef = &this->m_pWeakRef; // +0x1A4
    if (*pWeakRef != 0)
    {
        FUN_00408310(pWeakRef); // Free or release
        *pWeakRef = 0;
    }

    // Clear weak references: these set offset+8 to zero (probably weak pointer targets)
    if (this->m_pWeakTarget1 != nullptr) // +0x204 (0x81*4)
    {
        *(int *)(this->m_pWeakTarget1 + 8) = 0; // Clear weak pointer backlink
        this->m_pWeakTarget1 = nullptr;
    }
    if (this->m_pWeakTarget2 != nullptr) // +0x1F0 (0x7C*4)
    {
        *(int *)(this->m_pWeakTarget2 + 8) = 0;
        this->m_pWeakTarget2 = nullptr;
    }
    if (this->m_pWeakTarget3 != nullptr) // +0x1DC (0x77*4)
    {
        *(int *)(this->m_pWeakTarget3 + 8) = 0;
        this->m_pWeakTarget3 = nullptr;
    }

    // Final debug/cleanup call
    FUN_008d8620();
}