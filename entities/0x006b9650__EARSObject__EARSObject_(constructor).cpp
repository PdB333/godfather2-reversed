// FUNC_NAME: EARSObject::EARSObject (constructor)
class EARSObject {
public:
    // Virtual table pointers (multiple inheritance)
    int* vtable; // +0x00 - Main vtable for this class
    int* vtable2; // +0x3C (offset 0xF * 4) - Secondary vtable
    int* vtable3; // +0x48 (offset 0x12 * 4) - Tertiary vtable

    // Sub-object at offset +0x64 (0x19 * 4)
    // Contains at least two fields initialized by FUN_004086d0 and FUN_00408310
    // Likely a list or queue structure (e.g., EventQueue or MessageList)
    struct SubObject {
        // Members initialized by FUN_004086d0
        int field_0;
        int field_4;
        // etc.
    } m_subObject;

    // Constructor
    // param_2: flags (bit 0 indicates whether to deallocate on error)
    __thiscall EARSObject(byte flags) {
        // Set virtual tables
        vtable = (int*)&g_vtable1; // PTR_FUN_00d5e618
        vtable2 = (int*)&g_vtable2; // PTR_LAB_00d5e608
        vtable3 = (int*)&g_vtable3; // PTR_LAB_00d5e604

        // Initialize sub-object at offset 0x64
        FUN_004086d0(&m_subObject);
        FUN_00408310(&m_subObject);

        // Global initialization (likely static state)
        FUN_0046c640();

        // If flag bit 0 set, call deallocation function on this object
        // (this function may act as cleanup in error case or for placement new)
        if (flags & 1) {
            FUN_0043b960(this, 0x74); // size = 0x74 bytes
        }
    }
};