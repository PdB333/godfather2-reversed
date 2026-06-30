// FUNC_NAME: GodfatherGameManager::destroy

void __fastcall GodfatherGameManager::destroy(GodfatherGameManager* this)
{
    // Set vtable to derived class vtable (for cleanup)
    this->vtable = (void*)&PTR_FUN_00d5fd04;                // +0x00: derived vtable
    this->field_4 = (int)&PTR_LAB_00d5fcf4;                 // +0x04: secondary vtable or data

    // Call a virtual function on m_pSubObject1 (offset 0x14)
    // Through its vtable at offset 0xc (e.g., destroy or release)
    ((void (__thiscall*)(void*))this->m_pSubObject1->vtable[3])(this->m_pSubObject1);

    // Release m_pSubObject2 (offset 0x18) via m_pInterface (offset 0x28)
    // vtable+4 is likely a release or delete method taking a flag
    ((void (__thiscall*)(void*, int))this->m_pInterface->vtable[1])(this->m_pInterface, this->m_pSubObject2, 0);

    // Conditionally release m_pSubObject3 (offset 0x24) if non-null
    if (this->m_pSubObject3) {
        ((void (__thiscall*)(void*, int))this->m_pInterface->vtable[1])(this->m_pInterface, this->m_pSubObject3, 0);
    }

    // Finalize m_pInterface via vtable+0xc (e.g., final cleanup)
    ((void (__thiscall*)(void*))this->m_pInterface->vtable[3])(this->m_pInterface);

    // Global cleanup (likely operator delete or freeing memory)
    FUN_004083d0();

    // Set vtable back to base class vtable (for base destructor handling)
    this->vtable = (void*)&PTR_LAB_00d5fcb8;                // +0x00: base vtable

    // Mark the global instance as deinitialized
    DAT_011298cc = 0;
}