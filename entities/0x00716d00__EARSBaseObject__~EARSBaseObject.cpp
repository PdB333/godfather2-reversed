// FUNC_NAME: EARSBaseObject::~EARSBaseObject
// Address: 0x00716d00
// Role: Destructor (with optional memory deallocation). Cleans up a child subobject, sets base vtable, and frees memory if flag set.

class EARSBaseObject {
public:
    // Vtable pointer (first member at offset 0x00)
    void *vfptr;

    // Pointer to child subobject (at offset 0x10, param_1[4])
    void *m_pChild;  // +0x10
    // ... (other members)
};

// Forward declarations for external functions:
// Release and nullify a pointer (FUN_004daf90)
void safeRelease(void **pp);  // Expected: calls destructor and sets *pp = nullptr

// Custom operator delete (FUN_009c8eb0)
void operator delete(void *p);

// Destructor
EARSBaseObject * __thiscall EARSBaseObject::~EARSBaseObject(byte freeFlags) {
    // Set vtable to current class vtable (likely derived type)
    this->vfptr = (void*)0x00d61adc; // PTR_FUN_00d61adc

    // Release child subobject if it exists
    if (this->m_pChild != nullptr) {
        // Pass address of child pointer so it can be nulled after destruction
        safeRelease(&this->m_pChild); // FUN_004daf90(param_1+4)
    }

    // Set vtable to base class vtable (cleanup done)
    this->vfptr = (void*)0x00d61acc; // PTR_LAB_00d61acc

    // Optionally deallocate memory (if freeFlags bit 0 is set)
    if (freeFlags & 1) {
        operator delete(this); // FUN_009c8eb0
    }

    return this;
}