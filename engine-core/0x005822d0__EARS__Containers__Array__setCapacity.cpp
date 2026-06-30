// FUNC_NAME: EARS::Containers::Array::setCapacity
// Function at 0x005822d0: Resizes internal buffer to new capacity, copying existing elements and freeing old buffer.
// Structure fields (offsets from this):
//   +0x00: m_pData (int*) – pointer to element array
//   +0x04: m_nCount (uint) – number of elements currently stored
//   +0x08: m_nCapacity (uint) – allocated capacity (in elements)
//   +0x0C: m_pAllocator (Allocator*) – custom allocator; if null uses g_defaultAllocator
//   +0x10: m_pVtable? Actually pointer to allocator vtable (Allocator object)
// Allocator vtable: offset 0 = Allocate, offset 4 = Free

extern int g_defaultAllocator; // DAT_01218a14

class Allocator {
public:
    virtual void* Allocate(size_t size, void* hint) = 0;
    virtual void Free(void* ptr) = 0;
};

void __thiscall Array::setCapacity(uint newCapacity)
{
    if (newCapacity > m_nCapacity) {
        Allocator* alloc = m_pAllocator;
        if (alloc == nullptr) {
            alloc = reinterpret_cast<Allocator*>(&g_defaultAllocator);
        }
        int* newData = static_cast<int*>(alloc->Allocate(newCapacity * sizeof(int), alloc));
        if (m_pData != nullptr) {
            uint i = 0;
            int* src = m_pData;
            while (i < m_nCount) {
                if (newData != nullptr) {
                    newData[i] = src[i];
                }
                ++i;
            }
            alloc->Free(m_pData);
        }
        m_pData = newData;
        m_nCapacity = newCapacity;
    }
}