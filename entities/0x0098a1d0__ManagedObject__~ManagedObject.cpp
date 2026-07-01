// FUNC_NAME: ManagedObject::~ManagedObject
// Destructor for an object that owns two subobjects with custom deleters stored as function pointers.
// +0x00: vtable pointer (PTR_FUN_00d916a8)
// +0x04: first owned object pointer (deleted by function at +0x10)
// +0x10: deleter function pointer for first owned object
// +0x18: second owned object pointer (deleted by function at +0x24)
// +0x24: deleter function pointer for second owned object
// param_2 bit 0 controls whether to also free the memory of this object.

namespace EARS {
namespace Framework {

class ManagedObject {
public:
    // +0x00 vtable pointer (set to PTR_FUN_00d916a8)
    
    virtual ~ManagedObject() = 0; // placeholder for vtable
    
    void* m_pFirstOwned;       // +0x04
    void* m_pFirstDeleter;     // +0x10 (function pointer)
    void* m_pSecondOwned;      // +0x18
    void* m_pSecondDeleter;    // +0x24 (function pointer)
    
    // Destructor implementation at 0x0098a1d0
    void* __thiscall destructor(byte destroyMemory) {
        // Set vtable pointer (though it should already be set by base class destructor)
        this->vtable = &PTR_FUN_00d916a8;
        
        // Delete the second owned object using its stored deleter
        if (this->m_pSecondOwned != 0) {
            ((deleterFunc)(this->m_pSecondDeleter))(this->m_pSecondOwned);
        }
        
        // Delete the first owned object using its stored deleter
        if (this->m_pFirstOwned != 0) {
            ((deleterFunc)(this->m_pFirstDeleter))(this->m_pFirstOwned);
        }
        
        // Optionally deallocate the memory for this object
        if ((destroyMemory & 1) != 0) {
            FUN_009c8eb0(this);
        }
        
        return this;
    }
};

} // namespace Framework
} // namespace EARS

// Note: FUN_009c8eb0 is a memory deallocation function (likely custom operator delete).
// The function pointer types are assumed to be void (*deleterFunc)(void*).