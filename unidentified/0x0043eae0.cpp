// FUN_0043eae0: ResourceManager::shutdown
// Address: 0x0043eae0
// Role: Releases sub-resources and calls virtual cleanup functions. Called during shutdown sequence.

#include <cstddef>

class ResourceManager {
public:
    void* vtable;               // +0x00
    class ChildObject* m_childObject; // +0x10 (in_EAX[4])
    void* m_subResource2;       // +0x14 (in_EAX[5])
    void* m_subResource1;       // +0x18 (in_EAX[6])

    // Vtable indices (each entry 4 bytes):
    // [0] - unknown
    // [1] - releaseSubResource1(ptr, constant)  (offset +4)
    // [3] - unknown (offset +12)
};

class ChildObject {
public:
    void* vtable;               // +0x00
    // Vtable:
    // [1] - releaseSubResource2(ptr, constant)
    // [3] - finalize() (offset +12)
};

// External functions (likely memory cleanup)
void FUN_0043ec10(void);   // preShutdown
void FUN_0043ee30(void);   // postShutdown

void __thiscall ResourceManager::shutdown(void) {
    typedef void (__thiscall *VFunc1)(void* self, void* ptr, int constant);
    typedef void (__thiscall *VFuncChildFinalize)(void* self);

    FUN_0043ec10();

    // Call second virtual function of this object with m_subResource1 and 0xc
    VFunc1 vfuncThis = (VFunc1)(*(int*)(*(int*)this + 4));
    vfuncThis(this, this->m_subResource1, 0xc);
    this->m_subResource1 = 0;

    if (this->m_subResource2 != 0) {
        // Call second virtual function of child object with m_subResource2 and 0
        VFunc1 vfuncChild = (VFunc1)(*(int*)(*(int*)this->m_childObject + 4));
        vfuncChild(this->m_childObject, this->m_subResource2, 0);
        this->m_subResource2 = 0;
    }

    // Call fourth virtual function of child object (finalize)
    VFuncChildFinalize vfuncFinalize = (VFuncChildFinalize)(*(int*)(*(int*)this->m_childObject + 12));
    vfuncFinalize(this->m_childObject);

    FUN_0043ee30();
}