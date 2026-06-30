//FUNC_NAME: BricknMortarRes::~BricknMortarRes
void __fastcall BricknMortarRes::~BricknMortarRes(undefined4 *this)
{
    undefined4 *pPair;
    int i;

    // Set initial vtable pointers (multiple inheritance or interface)
    this[0] = &PTR_FUN_00d5e1dc;   // +0x00: primary vtable
    this[1] = &PTR_LAB_00d5e1cc;   // +0x04: secondary vtable
    this[4] = &PTR_LAB_00d5e1c0;   // +0x10: another vtable
    this[6] = &PTR_LAB_00d5e1b0;   // +0x18: yet another vtable

    // Unregister hash and resource type
    FUN_004639e0(0x32b7d466);      // unregisterHash
    FUN_0049c7f0("BricknMortarRes"); // unregisterResourceType

    // Destroy global singleton objects (likely static members or global instances)
    FUN_00408310(&DAT_0112a620);
    FUN_00408310(&DAT_0112a5e0);
    FUN_00408310(&DAT_0112a600);
    FUN_00408310(&DAT_0112a650);
    FUN_00408310(&DAT_0112a660);
    FUN_00408310(&DAT_0112a628);
    FUN_00408310(&DAT_0112a5b4);
    FUN_00408310(&DAT_0112a5f0);
    FUN_00408310(&DAT_0112a5e8);
    FUN_00408310(&DAT_0112a5d8);
    FUN_00408310(&DAT_0112a610);
    FUN_00408310(&DAT_0112a648);
    FUN_00408310(&DAT_0112a640);
    FUN_00408310(&DAT_0112a5a4);
    FUN_00408310(&DAT_0112a5c4);
    FUN_004086d0(&DAT_0112a5bc);   // different destructor for this type
    FUN_00408310(&DAT_0112a5bc);
    FUN_004086d0(&DAT_0112a5ac);
    FUN_00408310(&DAT_0112a5ac);
    FUN_00408310(&DAT_0112a5cc);
    FUN_00408310(&DAT_0112a618);
    FUN_00408310(&DAT_0112a630);
    FUN_00408310(&DAT_0112a594);
    FUN_00408310(&DAT_0112a638);
    FUN_00408310(&DAT_0112a608);
    FUN_00408310(&DAT_0112a59c);
    FUN_00408310(&DAT_0112a5f8);
    FUN_00408310(&DAT_0112a658);

    // Destroy array of 10 object/function pointer pairs at offset +0x108 (0x42*4)
    i = 9;
    pPair = this + 0x42;           // points to start of pair array
    do {
        if (pPair[-4] != 0) {      // object pointer at offset -4 from pair base
            (*(code *)pPair[-1])(pPair[-4]); // call destructor function at offset -1
        }
        i--;
        pPair -= 4;                // move to previous pair (each pair is 4 words? Actually decrement by 4 elements = 16 bytes)
    } while (i >= 0);

    // Release additional member objects if non-null
    if (this[0xd] != 0) {          // +0x34
        FUN_009c8f10(this[0xd]);   // releaseObject
    }
    if (this[0x10] != 0) {         // +0x40
        FUN_009c8f10(this[0x10]);
    }
    if (this[7] != 0) {            // +0x1C
        FUN_009c8f10(this[7]);
    }

    // Update vtable pointer for one interface
    this[6] = &PTR_LAB_00e30fe0;   // +0x18: final vtable

    // Final cleanup
    FUN_0049c640();                // cleanupResourceManager
    FUN_004083d0();                // destroyGlobalState

    // Set primary vtable to base class (or final vtable)
    this[0] = &PTR_LAB_00d5dfd8;

    // Clear global singleton pointer
    DAT_0112a558 = 0;
}