// FUNC_NAME: Family::Family

class Family {
public:
    // +0x00: vtable pointer
    // +0x3C: some vtable pointer
    // +0x48: another vtable pointer
    // +0x50: int field
    // +0x54: short field
    // +0x56: short field
    // +0x58..+0x7C: 10 dword array (arrayFamilySlots[10])
    // Base class (likely Entity) at +0x04..+0x38 (set by base constructor)

    void* vtable;            // +0x00
    // base class fields (offset 0x04..0x38)
    void* unknownPtr1;       // +0x3C
    void* unknownPtr2;       // +0x48
    int   unknownInt;        // +0x50
    short unknownShort1;     // +0x54
    short unknownShort2;     // +0x56
    int   arrayFamilySlots[10]; // +0x58
};

// Global symbols (from Ghidra labels)
extern void* g_familyVTable;          // PTR_FUN_00d7d464
extern void* g_familySubVTable1;      // PTR_LAB_00d7d454
extern void* g_familySubVTable2;      // PTR_LAB_00d7d450
extern int g_defaultValueA;           // DAT_00d5ef50
extern int g_defaultValueB;           // _DAT_00d5c458
extern int g_defaultValueC;           // _DAT_00d5780c

Family::Family(int param) {
    // Call base class constructor (likely Entity or Sentient)
    // FUN_0046c590
    this->vtable = &g_familyVTable;
    this->unknownPtr1 = &g_familySubVTable1;  // at +0x3C
    this->unknownPtr2 = &g_familySubVTable2;  // at +0x48
    this->unknownInt = 0;                     // at +0x50
    this->unknownShort1 = 0;                  // at +0x54
    this->unknownShort2 = 0;                  // at +0x56

    // Initialise family member slots (10 entries)
    this->arrayFamilySlots[0] = g_defaultValueA;   // from DAT_00d5ef50
    this->arrayFamilySlots[1] = g_defaultValueB;   // from _DAT_00d5c458
    this->arrayFamilySlots[2] = g_defaultValueB;
    this->arrayFamilySlots[3] = g_defaultValueB;
    this->arrayFamilySlots[4] = g_defaultValueB;
    this->arrayFamilySlots[5] = g_defaultValueB;
    this->arrayFamilySlots[6] = g_defaultValueB;
    this->arrayFamilySlots[7] = g_defaultValueC;   // from _DAT_00d5780c
    this->arrayFamilySlots[8] = g_defaultValueB;
    this->arrayFamilySlots[9] = g_defaultValueC;
}