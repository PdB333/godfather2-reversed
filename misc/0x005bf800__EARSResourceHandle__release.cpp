// FUNC_NAME: EARSResourceHandle::release
struct EARSResourceHandle {
    int* m_pResource; // +0x00
    int m_field4;     // +0x04
    int m_field8;     // +0x08
};

void __fastcall EARSResourceHandle::release(EARSResourceHandle* this)
{
    this->m_field8 = 0;
    this->m_field4 = 0;
    if (this->m_pResource != 0) {
        // Call release method on the resource via global vtable pointer at DAT_012234ec+4
        int* vtable = *(int**)(*(int*)(DAT_012234ec + 4) + 4);
        ((void (__fastcall*)(int*, int))vtable)(this->m_pResource, 0);
    }
    this->m_pResource = 0;
}