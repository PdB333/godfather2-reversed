// FUNC_NAME: BaseClass::~BaseClass
// Address: 0x00567fc0
// Role: Scalar deleting destructor for a base class. Releases a resource via a stored function pointer, then sets vtable to purecall vtable to prevent double deletion. Optionally deallocates memory if param_2 (deletingFlag) is set.

// Note: This is a __thiscall member function.
// Object layout:
//   +0x00: vtable pointer (set to PTR___purecall_00e3a9d0 after release)
//   +0x04: m_pResource (pointer to resource to release)
//   +0x10: m_pReleaseFunc (function pointer to release the resource)

undefined4 * __thiscall BaseClass::~BaseClass(undefined4 *this, byte deletingFlag)
{
    // If the resource pointer is non-null, call its release function
    if (this[1] != 0) {
        (*(code *)this[4])(this[1]);  // Call release function on resource
    }
    
    // Set vtable to purecall vtable to prevent further virtual calls after destruction
    *this = &PTR___purecall_00e3a9d0;
    
    // If the deleting flag (bit 0) is set, deallocate the object's memory
    if ((deletingFlag & 1) != 0) {
        FUN_009c8eb0(this);  // Likely operator delete
    }
    
    return this;
}