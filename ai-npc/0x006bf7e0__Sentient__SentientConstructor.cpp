// FUNC_NAME: Sentient::SentientConstructor
void __fastcall Sentient::SentientConstructor(Sentient* this) {
    // Set virtual function table pointers for multiple base classes
    this->vtable = (void*)&PTR_FUN_00d5ecb0;       // +0x00: Primary vtable
    this->field_0x3C = &PTR_LAB_00d5eca0;           // +0x3C: Second vtable (e.g., IActionableTarget)
    this->field_0x48 = &PTR_LAB_00d5ec9c;           // +0x48: Third vtable
    this->field_0x50 = &PTR_LAB_00d5ec98;           // +0x50: Fourth vtable
    this->field_0x54 = &PTR_LAB_00d5ec38;           // +0x54: Fifth vtable
    this->field_0x58 = &PTR_LAB_00d5ebd0;           // +0x58: Sixth vtable

    // Initialize a sub-object at offset 0x180 (m_pSubObject)
    if (this->m_pSubObject != nullptr) {
        int result = this->m_pSubObject->Initialize(); // FUN_006b07e0
        if (result != 0) {
            this->PostInitialize(); // FUN_006ae600
        }
    }

    // Register this instance with the object manager (or set debug name)
    GameObject::RegisterWithManager(); // FUN_0046ea20
}