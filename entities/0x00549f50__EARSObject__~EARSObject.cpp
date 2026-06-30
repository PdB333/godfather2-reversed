// FUNC_NAME: EARSObject::~EARSObject
// Address: 0x00549f50
// Destructor for an EARS reference-counted object. Releases an inner ref-counted object (offset +0xC0) and optionally frees memory.

class EARSObject {
public:
    // Vtable pointer (offset +0x00)
    void* vtable;

    // Pointer to an inner reference-counted object, stored at offset +0xC0 (param_1[0x30])
    // The inner object has a vtable at +0x00, a strong ref count at +0x04 (short),
    // and an internal ref count at +0x06 (short).
    void* m_pInnerObject;

    // Destructor with deletion flag.
    // param_2: bit0 set indicates memory should be freed.
    __thiscall ~EARSObject(unsigned char deletionFlag) {
        // Set vtable to base class vtable for correct destruction order.
        this->vtable = &PTR_FUN_00e39bc8;

        // Release reference to inner object if it exists.
        if (this->m_pInnerObject != nullptr) {
            // Check if the inner object's strong reference count is non-zero.
            short* innerRefCount = reinterpret_cast<short*>(this->m_pInnerObject) + 1; // offset +0x04
            short* innerInternalCount = reinterpret_cast<short*>(reinterpret_cast<char*>(this->m_pInnerObject) + 6); // offset +0x06

            if (*innerRefCount != 0) {
                // Decrement internal ref count and possibly destroy inner object.
                (*innerInternalCount)--;
                if (*innerInternalCount == 0) {
                    // Call virtual destructor of inner object (first vtable entry) with deletion flag = 1.
                    void (**vfunc)(int) = *reinterpret_cast<void (***)(int)>(this->m_pInnerObject);
                    (*vfunc)(1);
                }
            }
            this->m_pInnerObject = nullptr;
        }

        // Free memory if requested.
        if (deletionFlag & 1) {
            FUN_009c8eb0(this); // likely operator delete
        }
    }
};