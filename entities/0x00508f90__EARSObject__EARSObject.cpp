// FUNC_NAME: EARSObject::EARSObject
//
// Function: 0x00508f90
// Role: Constructor for a base EARS engine object. Initializes vtable pointer,
//       default fields, and sets initial flags (bit0 and bit1) and a handle to -1.
//
// The vtable pointer references PTR_FUN_00e380b0, which is the class vtable.

class EARSObject {
public:
    void* m_vtable;      // +0x00
    int   m_field4;      // +0x04 (unknown/unused initially)
    int   m_flags;       // +0x08 (bit0, bit1 set to 1)
    int   m_fieldC;      // +0x0C
    int   m_field10;     // +0x10
    int   m_field14;     // +0x14
    int   m_field18;     // +0x18
    int   m_handle;      // +0x1C (initialized to -1)
    // ... further fields up to offset 0xA0
    int   m_fieldA0;     // +0xA0

    EARSObject() {
        m_vtable = &PTR_FUN_00e380b0; // set vtable
        m_field4 = 0;
        m_flags = 0;
        m_fieldC = 0;
        m_field10 = 0;
        m_field14 = 0;
        m_field18 = 0;
        m_handle = 0xFFFFFFFF; // -1 (invalid handle)
        m_fieldA0 = 0;

        m_flags |= 3; // set bits 0 and 1 (e.g., object active and visible?)
    }
};