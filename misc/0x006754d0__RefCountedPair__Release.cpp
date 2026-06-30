// FUNC_NAME: RefCountedPair::Release
// Reconstructed C++ for function at 0x006754d0
// Releases two reference-counted objects: a child pointer (m_pSecond) and the container (m_pFirst)
// The objects are stored in a container's array, with indices stored in negative-offset headers

struct Container; // Forward declaration

// Header for objects stored in the container
struct ObjectHeader {
    int index;       // Index in Container::array (offset -8 from object pointer)
    int allocSize;   // Allocation size (or padding, offset -4 from object pointer)
};

// Container holding an array of pointers and a reference count
struct Container {
    int refCount;       // +0x04
    void** array;       // +0x0C, pointer to dynamic array
};

// Class that holds two pointers to elements in the container
class RefCountedPair {
public:
    Container* m_pFirst;   // +0x00
    void* m_pSecond;       // +0x0C

    void __thiscall Release();
};

void __thiscall RefCountedPair::Release()
{
    if (this != nullptr)
    {
        // Release the second element (m_pSecond)
        if (this->m_pSecond != nullptr)
        {
            Container* container = this->m_pFirst;                      // iVar3
            ObjectHeader* secondHeader = reinterpret_cast<ObjectHeader*>(this->m_pSecond) - 1; // iVar2-8, index field
            container->array[secondHeader->index] = nullptr;           // Clear pointer in array
            container->refCount--;                                      // Decrement container references
            // Free the memory of the second object (allocation header at -0x10)
            void* secondAlloc = reinterpret_cast<uint8*>(this->m_pSecond) - 0x10;
            ((void(*)(void*))DAT_01206694)(secondAlloc);
        }

        // Release the container itself (m_pFirst)
        Container* container = this->m_pFirst;                          // iVar2
        ObjectHeader* thisHeader = reinterpret_cast<ObjectHeader*>(this) - 1; // this-8, index field
        container->array[thisHeader->index] = nullptr;                 // Clear pointer in array
        container->refCount--;                                          // Decrement container references
        // Free the memory of this pair object (allocation header at -4)
        void* thisAlloc = reinterpret_cast<uint8*>(this) - 4;
        ((void(*)(void*))DAT_01206694)(thisAlloc);
    }
}