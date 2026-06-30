// FUNC_NAME: UnknownClass::Constructor (0x00761ab0)

// Constructor for a class with vtable at 0x00d654d0.
// Takes 4 parameters and stores them in fields at offsets 0x10, 0x14, 0x18, 0x1C.
// Offset 0x4 is a pointer that may be freed if non-null.

class UnknownClass {
public:
    UnknownClass(int param2, int param3, int param4, int param5) : m_vtable(0x00d654d0) {
        m_ptr = 0;          // +0x04
        field_0x08 = 0;     // +0x08
        field_0x0C = 0;     // +0x0C
        field_0x10 = param2; // +0x10
        if (m_ptr != 0) {
            FUN_004daf90(m_ptr); // Free previously stored pointer
            m_ptr = 0;
        }
        field_0x0C = 0;     // +0x0C (redundant set)
        field_0x18 = param3; // +0x18
        field_0x14 = param4; // +0x14
        field_0x1C = param5; // +0x1C
    }

private:
    void *m_vtable;         // +0x00
    int *m_ptr;             // +0x04
    int field_0x08;         // +0x08
    int field_0x0C;         // +0x0C
    int field_0x10;         // +0x10
    int field_0x14;         // +0x14
    int field_0x18;         // +0x18
    int field_0x1C;         // +0x1C
};