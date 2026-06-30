// FUNC_NAME: FamilyManager::initializeComponentTables
void __fastcall FamilyManager::initializeComponentTables(int this)
{
    // Call base class initialization (likely SimManager::init)
    FUN_00537150();

    // --- Initialize family slots (6 families) at offset +0x12C0 ---
    uint i = 0;
    undefined4* pFamilySlots = (undefined4*)(this + 0x12C0);  // 6 family object slots
    do {
        *pFamilySlots = FUN_0060a380();  // create default family object (probably Family::create)
        i++;
        pFamilySlots++;
    } while (i < 6);

    // --- Initialize crew member slots (24 crew, 4 per family) at offset +0x12D8 ---
    undefined4* pCrewSlots = (undefined4*)(this + 0x12D8);  // 24 crew object slots
    i = 0;
    do {
        *pCrewSlots = FUN_0060a380();  // create default crew member (MadeMan or NPC)
        i++;
        pCrewSlots++;
    } while (i < 0x18);  // 0x18 = 24

    // --- Initialize property/building slots (32 buildings) at offset +0x1338 ---
    undefined4* pPropertySlots = (undefined4*)(this + 0x1338);  // 32 property objects
    i = 0;
    do {
        // Use global table of type descriptors to create each property type
        *pPropertySlots = FUN_0060a2e0(*(undefined4*)((int)&PTR_PTR_01128200 + i));
        i += 4;  // step through global pointer table (0x80/4 = 32 entries)
        pPropertySlots++;
    } while (i < 0x80);

    // --- Build cross-reference table A: 24 families/groups x 12 entries each (offset +0xE38) ---
    // Associates family objects with crew data from a static table
    undefined4* pCrossTableA = (undefined4*)(this + 0xE38);
    int dataOffsetA = (int)&PTR_DAT_010bdfc0 - this;  // base of static crew data per family
    int outerCountA = 0x18;  // 24 groups
    pFamilySlots = (undefined4*)(this + 0x12C0);  // reset to first family
    do {
        int innerCountA = 0xC;  // 12 entries per group
        do {
            *pCrossTableA = FUN_0060a580(*pFamilySlots, *(undefined4*)(dataOffsetA + (int)pCrossTableA));
            pCrossTableA++;
            innerCountA--;
        } while (innerCountA != 0);
        pFamilySlots++;  // next family
        dataOffsetA -= 0x30;  // move to previous family's data block
        outerCountA--;
    } while (outerCountA != 0);

    // --- Build cross-reference table B: 6 families x 11 entries each (offset +0xD30) ---
    // Another association, possibly family->family stats
    undefined4* pCrossTableB = (undefined4*)(this + 0xD30);
    int dataOffsetB = (int)&PTR_DAT_010be054 - this;
    int outerCountB = 6;
    pFamilySlots = (undefined4*)(this + 0x12C0);
    do {
        int innerCountB = 0xB;  // 11 entries
        do {
            *pCrossTableB = FUN_0060a580(*pFamilySlots, *(undefined4*)(dataOffsetB + (int)pCrossTableB));
            pCrossTableB++;
            innerCountB--;
        } while (innerCountB != 0);
        pFamilySlots++;
        dataOffsetB -= 0x2C;
        outerCountB--;
    } while (outerCountB != 0);

    // --- Build cross-reference table C: 32 buildings x 11 entries each (offset +0x7A4) ---
    undefined4* pCrossTableC = (undefined4*)(this + 0x7A4);
    int dataOffsetC = (int)&PTR_DAT_010be684 - this;
    int outerCountC = 0x20;  // 32
    pPropertySlots = (undefined4*)(this + 0x1338);
    do {
        int innerCountC = 0xB;
        do {
            *pCrossTableC = FUN_0060a580(*pPropertySlots, *(undefined4*)((int)pCrossTableC + dataOffsetC));
            pCrossTableC++;
            innerCountC--;
        } while (innerCountC != 0);
        pPropertySlots++;
        dataOffsetC -= 0x2C;
        outerCountC--;
    } while (outerCountC != 0);

    // --- Process 8 "control" objects (e.g., DonControl) with virtual call table (offset +0xA4) ---
    int* pVtableArray = (int*)(this + 0xA4);  // array of vtable pointers (8 * 0x2E *4 size)
    undefined4* pControlTargets = (undefined4*)(this + 0x664);  // 40 entries (8 x 5)
    undefined4* pControlObjects = (undefined4*)(this + 0x1378);  // 16 entries (8 x 2)
    int dataOffsetD = (int)&PTR_DAT_010be7f0 - this;
    int outerCountD = 8;
    do {
        int innerCountD = 5;
        undefined4* pDest = pControlTargets;
        do {
            *pDest = FUN_0060a580(*pControlObjects, *(undefined4*)(dataOffsetD + (int)pDest));
            pDest++;
            innerCountD--;
        } while (innerCountD != 0);

        // Call the second virtual function (vtable[1]) on the control object
        // Typically a destructor, release, or attach method
        (**(code**)(*pVtableArray + 4))(*pControlObjects);

        // Advance to next control group
        pControlTargets += 10;        // each group is 10 ints (40 bytes)
        pControlObjects += 2;         // each control object is 2 ints (8 bytes?)
        dataOffsetD -= 0x28;          // next data block for this control
        pVtableArray += 0x2E;         // next vtable entry (0x2E * 4 = 0xB8 bytes stride)
        outerCountD--;
    } while (outerCountD != 0);
}