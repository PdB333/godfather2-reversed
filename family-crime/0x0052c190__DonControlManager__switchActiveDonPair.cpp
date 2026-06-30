// FUNC_NAME: DonControlManager::switchActiveDonPair

// Function at 0x0052c190
// Activates two don family slots sequentially, swapping global active family pointers
// Uses a static array of 20 family slots (each 8 bytes: key + flags)
// Allocates and initializes a small block of data (possible gadget/presentation)

/* Known globals (addresses from debug symbols):
   g_ActiveDonPairCurrent = DAT_011f38f0 (int*) - current active family ID/ptr
   g_ActiveDonPairPrevious = DAT_011f38f4 (int*) - previous active family ID
   g_FamilySlotKeys = DAT_01218e50 (int[20]) - keys for each slot
   g_FamilySlotFlags = DAT_01218e54 (int[20]) - flags for each slot
   g_DonGadgetParams1 = DAT_00e2eff4 (int)
   g_DonGadgetParams2 = DAT_00e2b1a4 (int)
*/

void __thiscall DonControlManager::switchActiveDonPair(
    int param1,   // first family handle (compared to 'this' maybe? or pointer)
    int param2,   // second family handle
    int param3,   // initially passed, overwritten with 'this' if condition
    undefined4 param4,   // unused
    char param5)  // flag to call finalization at end
{
    int oldCurrent;
    int oldPrevious;

    // Heuristic: if param1 and param2 are not equal to 'this' (in_EAX), then set param3 = this
    // This suggests param1 and param2 are object pointers, and param3 is a local that gets set to this.
    if ((param1 != in_EAX) && (param2 != in_EAX)) {
        param3 = in_EAX; // assume in_EAX is 'this' pointer
    }

    // --- Activate first family (param3) ---
    uint i = 0;
    do {
        if (g_FamilySlotKeys[i * 2] == param3) {
            if (i < 20) { // 0x14
                g_FamilySlotFlags[i * 2] &= 0xfffffffc; // clear bottom 2 bits (e.g. remove "selected" flag)
            }
            break;
        }
        i++;
    } while (i < 20);

    // Save current global active pair and set new active pair to param3
    oldPrevious = g_ActiveDonPairPrevious; // DAT_011f38f4
    oldCurrent = g_ActiveDonPairCurrent;   // DAT_011f38f0
    g_ActiveDonPairPrevious = 0;
    g_ActiveDonPairCurrent = param3;

    // Internal state transitions (likely input/UI/camera capture)
    FUN_00609340(0, oldCurrent, oldPrevious);  // maybe updateInputState(0,...)
    FUN_00609810(1);   // capture controller 1?
    FUN_0053d470(0);   // setFamilyActive(0)
    FUN_0053d590();    // update UI?
    FUN_0053d310();    // refresh family display

    // Allocate 4 bytes? Actually the following writes suggest it's larger.
    // Possibly the allocation function takes (tag, size, ..., ...) and size is misinterpreted.
    // The written block is 8*4 = 32 bytes.
    int* pGadget = (int*)FUN_0060cd00(0xd, 4, 0, 1, 0); // tag 0xd, size 4, alignment 0, pool 1, flags 0
    if (pGadget != nullptr) {
        // Fill gadget structure from globals
        pGadget[0] = g_DonGadgetParams1;
        pGadget[1] = oldCurrent;   // note: oldCurrent is the previous g_ActiveDonPairCurrent
        pGadget[2] = oldPrevious;
        pGadget[3] = oldCurrent;
        pGadget[4] = oldPrevious;
        pGadget[5] = oldPrevious;
        pGadget[6] = oldCurrent;
        pGadget[7] = oldPrevious;
        FUN_0060cde0();  // initialize the gadget?
    }

    FUN_00612e00();      // finalize UI transition
    FUN_00609890(1);     // release controller?

    // --- Activate second family (param2) ---
    i = 0;
    do {
        if (g_FamilySlotKeys[i * 2] == param2) {
            if (i < 20) {
                g_FamilySlotFlags[i * 2] &= 0xfffffffc; // clear same flags
            }
            break;
        }
        i++;
    } while (i < 20);

    oldCurrent = g_ActiveDonPairCurrent;   // re-read (note: was set to param3 above)
    oldPrevious = g_ActiveDonPairPrevious; // set to 0 above, now 0
    g_ActiveDonPairCurrent = param2;       // set new active to param2
    g_ActiveDonPairPrevious = 0;

    FUN_00609340(0, oldCurrent, oldPrevious); // update with old values (oldCurrent was param3)
    FUN_00609810(1);
    FUN_0053d470(1);   // setFamilyActive(1) - note argument 1 (maybe index)
    FUN_0053d590();
    FUN_0053d310();

    pGadget = (int*)FUN_0060cd00(0xd, 4, 0, 1, 0);
    if (pGadget != nullptr) {
        *pGadget = g_DonGadgetParams1;
        pGadget[1] = oldCurrent;
        pGadget[2] = oldPrevious;
        pGadget[3] = oldCurrent;
        pGadget[4] = oldPrevious;
        pGadget[5] = oldPrevious;
        pGadget[6] = oldCurrent;
        pGadget[7] = oldPrevious;
        FUN_0060cde0();
    }

    FUN_00612e00();

    if (param5 != '\0') {
        FUN_00609890(1); // final release if flag set
    }
    return;
}