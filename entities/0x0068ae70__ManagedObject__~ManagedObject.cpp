// FUNC_NAME: ManagedObject::~ManagedObject

// Destructor for a class with two deletable managed objects.
// Object layout:
//   +0x00: vtable pointer (set to base vtable on cleanup)
//   +0x08: m_pObjectA (first managed object)
//   +0x14: m_pDeleterA (function pointer to destroy m_pObjectA)
//   +0x18: m_pObjectB (second managed object)
//   +0x24: m_pDeleterB (function pointer to destroy m_pObjectB)
// The flag byte (deleteFlag) controls whether the memory itself is deallocated.

class ManagedObject {
public:
    // Deleters are function pointers taking void*
    typedef void (*DeleterFunc)(void*);

    // Reconstructed destructor (__thiscall)
    void* __thiscall destructor(unsigned char deleteFlag) {
        // Delete second object if present
        if (m_pObjectB != nullptr) {
            m_pDeleterB(m_pObjectB);
        }
        // Delete first object if present
        if (m_pObjectA != nullptr) {
            m_pDeleterA(m_pObjectA);
        }
        // Set vtable to a base class vtable (no-op destructor) to avoid double deletion
        this->vtablePtr = &s_baseVtable; // PTR_LAB_00d576d4
        // If bit 0 of deleteFlag is set, deallocate the object itself
        if (deleteFlag & 1) {
            deallocateThis(this); // calls FUN_009c8eb0
        }
        return this;
    }

private:
    // Vtable pointer (not explicitly declared in class, but at offset 0)
    void* vtablePtr; // +0x00

    // Managed object pointers and their associated deleters
    void* m_pObjectA;       // +0x08
    DeleterFunc m_pDeleterA; // +0x14
    void* m_pObjectB;       // +0x18
    DeleterFunc m_pDeleterB; // +0x24

    // Static base vtable (assigned after cleanup)
    static void* s_baseVtable; // address 0x00d576d4

    // Deallocation function (custom free at 0x009c8eb0)
    static void deallocateThis(void* ptr);
};