// Xbox PDB: EARS_Apt_UIVenueApt3d_UIVenueApt3d
// FUNC_NAME: UIVenueApt3d::VenueInfoPool::constructor

// Reconstructed constructor for VenueInfoPool (UI Venue Apartment 3D view data pool)
// Address: 0x00991bf0
// The function initializes a singleton instance stored at DAT_01130040.
// It sets up vtable pointers and initializes member fields.

class VenueInfoPool {
public:
    // Virtual function table pointer at offset 0x00
    // +0x00: vtable pointer (set to &PTR_FUN_00d91dcc)
    // +0x04: field1 (param_1[1]) - initialized to 0
    // +0x08: field2 (param_1[2]) - initialized to 0
    // +0x0C: field3 (param_1[3]) - initialized to 0
    // +0x10: field4 (param_1[4]) - initialized to 0
    // +0x14: field5 (param_1[5]) - initialized to 0
    // +0x18: pVtable2 (param_1[6]) - pointer to secondary vtable, later updated
    // +0x1C: pFunction (param_1[7]) - function pointer, later updated
    // +0x20: field8 (param_1[8]) - initialized to 1
    // +0x24: field9 (param_1[9]) - initialized to 0
    // +0x28: pFunction2 (param_1[10]) - pointer to another function table
    // +0x60: field0x18 (param_1[0x18]) - initialized to 0
    // +0x64: field0x19 (param_1[0x19]) - initialized to 0
    // +0x84: field0x21 (param_1[0x21]) - initialized to 0
    // +0x88: short field0x22 - initialized to 0
    // +0x8C: field0x23 (param_1[0x23]) - initialized to 0

    void __fastcall constructor() {
        // Initialize first block of fields to 0
        this->field3 = 0;       // offset 0x0C
        this->field1 = 0;       // offset 0x04
        this->field2 = 0;       // offset 0x08
        this->field4 = 0;       // offset 0x10
        this->field5 = 0;       // offset 0x14

        // Set primary vtable pointer later; first set secondary vtable and function pointers
        this->pVtable2 = &PTR_LAB_00d91db4;   // +0x18
        DAT_01130040 = this;                  // Store singleton global

        this->pFunction = &PTR_FUN_00e2f19c;  // +0x1C
        this->field8 = 1;                     // +0x20
        this->field9 = 0;                     // +0x24

        // Now set primary vtable pointer (offset 0)
        *(void**)this = &PTR_FUN_00d91dcc;

        // Override secondary vtable and function pointer with new values
        this->pVtable2 = &PTR_LAB_00d91dc8;    // +0x18
        this->pFunction = &PTR_LAB_00d91db8;   // +0x1C

        // Memory allocation/logging for the pool (debug tracking)
        // FUN_004de0b0(0x48, 0x20, "UIVenueApt3d::VenueInfoPool", 0, 4);
        // 0x48 is size? 0x20 alignment? Parameters unknown.
        FUN_004de0b0(0x48, 0x20, "UIVenueApt3d::VenueInfoPool", 0, 4);

        // Set another function pointer table at offset 0x28
        this->pFunction2 = &PTR_FUN_00d91dac;  // +0x28

        // Initialize more fields to 0
        this->field0x18 = 0;   // +0x60
        this->field0x19 = 0;   // +0x64

        // Call another initialization routine
        FUN_005c0a30();

        this->field0x21 = 0;          // +0x84
        *(short*)((int)this + 0x88) = 0;  // +0x88 (halfword)
        this->field0x23 = 0;          // +0x8C
    }

private:
    int field1;             // +0x04
    int field2;             // +0x08
    int field3;             // +0x0C
    int field4;             // +0x10
    int field5;             // +0x14
    void* pVtable2;         // +0x18
    void* pFunction;        // +0x1C
    int field8;             // +0x20
    int field9;             // +0x24
    void* pFunction2;       // +0x28
    // alignment/padding ?
    int field0x18;          // +0x60
    int field0x19;          // +0x64
    int field0x21;          // +0x84
    short field0x22;        // +0x88
    int field0x23;          // +0x8C
};

// Global singleton pointer
extern VenueInfoPool* DAT_01130040;