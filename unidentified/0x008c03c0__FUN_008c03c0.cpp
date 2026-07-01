// FUNC_NAME: UnknownClass::UnknownClass (constructor at 0x008c03c0)
// Role: Initializes an object of UnknownClass, sets vtable pointer and zeroes fields.
// Calls a cleanup function (FUN_009c8f10) on a null pointer (likely safe).

class UnknownClass {
public:
    // Vtable pointer at offset 0x00
    void* m_vtable;
    // Field at offset 0x04
    int m_field1;
    // Field at offset 0x08
    int m_field2;
    // Byte field at offset 0x0C (3rd word, low byte)
    char m_field3;
    // Field at offset 0x10 (4th word)
    void* m_field4; // pointer to something
    // Field at offset 0x14 (5th word)
    int m_field5;
    // Field at offset 0x18 (6th word)
    int m_field6;

    // Constructor
    __thiscall UnknownClass() {
        // Load global vtable pointer (DAT_00e44758)
        m_vtable = (void*)0x00e44758; // placeholder, actual global
        m_field1 = 0;
        m_field2 = 0;
        m_field3 = 0;
        m_field4 = 0;
        m_field5 = 0;
        m_field6 = 0;

        // Call cleanup function with null pointer (safe)
        // FUN_009c8f10 is likely a release/destructor that checks for null
        FUN_009c8f10(m_field4); // m_field4 is 0

        // Redundant zeroing (maybe for safety)
        m_field4 = 0;
        m_field6 = 0;
    }
};