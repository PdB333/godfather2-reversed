// FUNC_NAME: SomeClass::releaseSubObjects
void SomeClass::releaseSubObjects(void)
{
    // Call virtual function at vtable[0] with argument 0 (likely a shutdown/release method)
    (this->vtable[0])(0);

    // Release pointer at offset +0x28 (e.g., m_pSubObject1)
    if (this->field_0x28 != 0) {
        // Call memory manager's deallocation function (vtable[1]) with pointer and 0
        (g_memoryManagerVtable[1])(this->field_0x28, 0);
        this->field_0x28 = 0;
    }

    // Release pointer at offset +0x29 (e.g., m_pSubObject2)
    if (this->field_0x29 != 0) {
        (g_memoryManagerVtable[1])(this->field_0x29, 0);
        this->field_0x29 = 0;
    }

    // Release pointer at offset +0x4a (e.g., m_pSubObject3)
    if (this->field_0x4a != 0) {
        (g_memoryManagerVtable[1])(this->field_0x4a, 0);
        this->field_0x4a = 0;
    }

    // Release pointer at offset +0x2d (e.g., m_pSubObject4)
    if (this->field_0x2d != 0) {
        (g_memoryManagerVtable[1])(this->field_0x2d, 0);
        this->field_0x2d = 0;
    }
}