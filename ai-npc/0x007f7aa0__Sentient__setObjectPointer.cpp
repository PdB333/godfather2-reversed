// FUNC_NAME: Sentient::setObjectPointer
void __thiscall Sentient::setObjectPointer(void *newPointer)
{
    // +0x8A0: pointer to some reference-counted object (e.g., AI component, attachment)
    if (this->m_pObject != NULL) {
        // Call vtable function at offset 4 (index 1) – likely virtual Release() with a flag
        this->m_pObject = (void*)((int (__thiscall*)(void*, int))(*((int**)this->m_pObject) + 1))(this->m_pObject, 1);
    } else {
        this->m_pObject = newPointer;
    }
}