// FUNC_NAME: ResourcePairContainer::releaseAll
void __thiscall ResourcePairContainer::releaseAll(void)
{
    // Structure layout (offsets relative to 'this' in ESI):
    // +0x00: m_pManagerA (pointer to base object with vtable)
    // +0x04: m_pResourceB (pointer to resource)
    // +0x08: m_pManagerB (pointer to base object with vtable)
    // +0x0C: m_pResourceA (pointer to resource)

    // Release resource A via ManagerB, then call ReleaseComplete on ManagerB
    if (this->m_pResourceA != 0) {
        (*(code **)(*(int *)this->m_pManagerB + 4))(this->m_pResourceA, 0);  // ManagerB->ReleaseResource(resourceA, 0)
        this->m_pResourceA = 0;
    }
    (*(code **)(*(int *)this->m_pManagerB + 0xC))();  // ManagerB->OnReleaseComplete()

    // Release resource B via ManagerA, then call ReleaseComplete on ManagerA
    if (this->m_pResourceB != 0) {
        (*(code **)(*(int *)this->m_pManagerA + 4))(this->m_pResourceB, 0);  // ManagerA->ReleaseResource(resourceB, 0)
        this->m_pResourceB = 0;
    }
    (*(code **)(*(int *)this->m_pManagerA + 0xC))();  // ManagerA->OnReleaseComplete()

    // Note: Indirect jump at 0x004cee76 is a tail call to ManagerA->OnReleaseComplete return value? 
    // Ghidra treats it as call; ignored as it just returns.
    return;
}