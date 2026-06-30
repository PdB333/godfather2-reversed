// FUNC_NAME: TlsHeapObject::~TlsHeapObject
// Address: 0x004afb20
// Destructor for objects allocated from a per-thread heap via TLS index 0x1139810.
// The object layout: vtable ptr at +0x00, m_pData at +0x08, m_index at +0x10.
// If m_index >= 0, frees m_pData[m_index * 16] with size class 0x17 (23).
// After cleanup, vtable is set to the base class vtable (0x00dcf968).

class TlsHeapObject
{
public:
    void* m_vtable;      // +0x00
    void* m_pData;       // +0x08 (pointer to array of 16‑byte blocks)
    int   m_index;       // +0x10 (index into the array, -1 if not allocated)
};

void __thiscall TlsHeapObject::Destructor(TlsHeapObject* this)
{
    // Step 1: switch vtable to derived class vtable for correct virtual dispatch during destruction
    this->m_vtable = (void*)&g_derivedVtable;  // PTR_LAB_00e3572c

    int index = this->m_index;
    if (index >= 0)
    {
        // Retrieve the per‑thread heap pointer (TLS slot value)
        void* tlsHeap = TlsGetValue(g_tlsIndex);  // DAT_01139810, return value used by CPL_00aa26e0

        // Free the block: offset = index * 16 bytes, size class 0x17 (23)
        CPL_00aa26e0(this->m_pData, index * 16, 0x17);
    }

    // Step 2: set vtable to base class vtable (allows proper chaining of destructors)
    this->m_vtable = (void*)&g_baseVtable;  // PTR_LAB_00dcf968

    return;
}