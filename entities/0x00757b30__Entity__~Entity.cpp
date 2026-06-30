// FUNC_NAME: Entity::~Entity

void __thiscall Entity::~Entity(Entity* this)
{
    // Vtable pointers: base class and interface tables
    this->vtable = &PTR_00d64f34;          // +0x00: primary vtable
    this->vtable2 = &PTR_00d64f30;         // +0x50: secondary vtable (offset 0x50)
    this->m_pInterface = &PTR_00d64f28;    // +0xF4: interface subobject vtable

    // Cleanup sub-object at offset 0x108
    if (this->m_pSubObject1 != nullptr) {
        FUN_005f7860(this->m_pSubObject1);  // destruct sub-object
        this->m_pSubObject1 = nullptr;
    }

    // Cleanup sub-object at offset 0x10C (interface object)
    void* pSubObj2 = this->m_pSubObject2; // +0x10C
    if (pSubObj2 != nullptr) {
        // Call a virtual function on sub-object2 (likely release(1))
        (*(void (**)(void*, int))(*static_cast<int**>(pSubObj2)))(pSubObj2, 1);
        if (pSubObj2 != nullptr) {
            FUN_004daf90(&pSubObj2);       // deallocate memory
            this->m_pSubObject2 = nullptr;
        }
    }

    // Check flag bit 0x200000 at offset 0xA8
    if ((this->flags & 0x00200000) != 0) {
        FUN_007ee320(&this->m_pInterface);  // release interface subobject
        this->flags &= 0xFFDFFFFF;          // clear the flag
    }

    // Clean up additional members at offsets 0x124 and 0x118
    if (this->m_pField_0x124 != nullptr) {
        FUN_004daf90(this + 0x124);        // deallocate
    }
    if (this->m_pField_0x118 != nullptr) {
        FUN_004daf90(this + 0x118);        // deallocate
    }

    // Final cleanup of sub-object2 if still alive
    if (this->m_pSubObject2 != nullptr) {
        FUN_004daf90(&this->m_pSubObject2);
    }

    // Switch interface vtable to a different table
    this->m_pInterface = &PTR_00d61acc;

    // Call base destructor
    FUN_0075cc50();
}