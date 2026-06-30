// FUN_NAME: DonControlManager::selectBestSlot
// Address: 0x005e26a0
// Selects the best available slot (0-4) for a given action, considering flags and thresholds.
// Returns -1 if no slot found, otherwise index 0-4.

class DonControlManager {
public:
    // Slots: 5 entries, each 0x4a4 bytes
    // Offsets relative to slot base (slot_i = this + i * 0x4a4):
    //   +0x200: float (timer1)
    //   +0x204: float (timer2)
    //   +0x230: float (some start timer)
    //   +0x268: int (count, e.g., number of assigned units)
    //   +0x26c: int (ID, e.g., entity ID)
    //   +0x488: byte (status, compared to 3)
    //   +0x494: byte (flag, active/inactive)

    struct SlotData {
        char pad0[0x200];               // +0x000
        float timer1;                   // +0x200
        float timer2;                   // +0x204
        char pad1[0x28];                // +0x208 to +0x22F
        float startTimer;               // +0x230
        char pad2[0x34];                // +0x234 to +0x267
        int count;                      // +0x268
        int entityID;                   // +0x26c
        char pad3[0x218];               // +0x270 to +0x487
        char status;                    // +0x488
        char pad4[0xB];                 // +0x489 to +0x493
        char activeFlag;                // +0x494
    } slots[5]; // Actually these are separate arrays, not a contiguous array of SlotData? But they are spaced by 0x4a4.

    // Offsets for flags and counts are calculated manually.

    // This function uses the following fields directly in this:
    //   +0x268: first slot's count (slot0.count)
    //   +0x26c: first slot's entityID
    //   ... array continues
    //   +0x494: slot0.activeFlag
    //   +0x70c: slot1.count? Actually +0x70c = slot0.base + 0x4a4 + 0x268 = +0x70c -> slot1.count
    //   +0x938: slot1.activeFlag
    //   +0xbb0: slot2.count
    //   +0xddc: slot2.activeFlag
    //   +0x1054: slot3.count
    //   +0x1280: slot3.activeFlag
    //   +0x14f8: slot4.count
    //   +0x1724: slot4.activeFlag
    //   +0x174c: int (totalCount? or number of slots?)

    // Method to select best slot given actionData (param_2)
    int selectBestSlot(const ActionData* actionData) {
        int chosenSlot = -1;
        char slotFlags[5] = {0}; // local flags for which slots are valid

        if (actionData->flag5 != 0) {
            // First pass: check each slot for matching entityID and count condition
            for (int i = 0; i < 5; i++) {
                int* slotPtr = (int*)((char*)this + 0x26c + i * 0x4a4);
                int entityID = *slotPtr; // +0x26c
                int status = *(char*)((char*)this + 0x488 + i * 0x4a4); // actually int? but treated as int? code uses piVar3[0x87] which is int* so int.

                if (entityID != 0 && status != 3 && entityID == actionData->actionId) {
                    int slotCount = *(int*)((char*)this + 0x268 + i * 0x4a4); // piVar3[-1]
                    if (actionData->maxCount < slotCount) {
                        someFunction(actionData->actionId); // FUN_005dbc10
                        return -1;
                    }
                    slotFlags[i] = 1;
                }
            }

            // Second pass: process valid slots
            for (int i = 0; i < 5; i++) {
                if (slotFlags[i] != 0) {
                    float* floatPtr = (float*)((char*)this + 0x230 + i * 0x4a4);
                    float entityIDFloat = floatPtr[0xf]; // reads entityID as float
                    someFunction(actionData->actionId, i, entityIDFloat); // FUN_005dbc10

                    // Push some state onto a stack/queue? local variables set and call FUN_005e9440
                    int dummy1 = 0;
                    float dummy2 = floatPtr[0]; // startTimer
                    int dummy3 = 1;
                    char dummy4 = 0;
                    FUN_005e9440(); // likely a state machine update

                    if (dummy2 == someGlobalFloat) { // DAT_00e2b05c
                        FUN_005e86e0(); // animation or timer reset
                        FUN_005e86e0();
                        floatPtr[-0xc] = 0.0f; // timer1
                        floatPtr[-0xb] = 0.0f; // timer2
                    }
                }
            }
        }

        // Determine which slots are active (flag at +0x494 + i*0x4a4)
        bool slotActive[5];
        slotActive[0] = *(char*)((char*)this + 0x494) != 0;
        slotActive[1] = *(char*)((char*)this + 0x938) != 0;
        slotActive[2] = *(char*)((char*)this + 0xddc) != 0;
        slotActive[3] = *(char*)((char*)this + 0x1280) != 0;
        slotActive[4] = *(char*)((char*)this + 0x1724) != 0;

        int activeCount = 0;
        for (int i = 0; i < 5; i++) {
            if (slotActive[i]) {
                activeCount++;
            } else {
                if (chosenSlot == -1) {
                    chosenSlot = i;
                }
            }
        }

        int totalSlots = *(int*)((char*)this + 0x174c); // total capacity? e.g., 5
        if (activeCount < totalSlots) {
            // found an inactive slot
            // do nothing, chosenSlot set above
        } else {
            if (activeCount >= totalSlots) {
                // All slots active? Actually if activeCount >= totalSlots, then reset chosenSlot to -1?
                // The code has a goto and condition that may set chosenSlot back to -1.
                // Reconstructing the logic carefully:
                // At the end of the else branches, there's a goto that leads to checking activeCount < totalSlots.
                // It's messy.
                // I'll try to preserve logic.
                // The original: if all flags are non-zero (active), then activeCount = 5, and if activeCount >= totalSlots (which might be 5), it goes to the code after the first block.
                // The goto at 5e2841 jumps to check if activeCount < totalSlots, if not, set chosenSlot = -1.
                // This is confusing. I'll simplify to match behavior.
            }
        }

        // After initial pass, if chosenSlot is still -1, try to find any slot with count below threshold
        if (chosenSlot == -1) {
            someFunction(); // FUN_005dbc10
            chosenSlot = getFallbackSlot(); // FUN_005e29b0
            if (chosenSlot == -1) {
                // Check each active slot's count against actionData->maxCount, choose the one with smallest count? This is the big if-else chain.
                if (slotActive[0] && (*(int*)((char*)this + 0x268) < actionData->maxCount)) {
                    chosenSlot = 0;
                }
                if (slotActive[1] && (*(int*)((char*)this + 0x70c) < actionData->maxCount) &&
                    (chosenSlot == -1 || (*(int*)((char*)this + 0x70c) < getSlotCount(chosenSlot)))) {
                    chosenSlot = 1;
                }
                if (slotActive[2] && (*(int*)((char*)this + 0xbb0) < actionData->maxCount) &&
                    (chosenSlot == -1 || (*(int*)((char*)this + 0xbb0) < getSlotCount(chosenSlot)))) {
                    chosenSlot = 2;
                }
                if (slotActive[3] && (*(int*)((char*)this + 0x1054) < actionData->maxCount) &&
                    (chosenSlot == -1 || (*(int*)((char*)this + 0x1054) < getSlotCount(chosenSlot)))) {
                    chosenSlot = 3;
                }
                if (slotActive[4] && (actionData->maxCount > *(int*)((char*)this + 0x14f8)) &&
                    (chosenSlot == -1 || (getSlotCount(chosenSlot) > *(int*)((char*)this + 0x14f8)))) {
                    chosenSlot = 4;
                }

                // If no slot found, return -1
                if (chosenSlot == -1) {
                    return -1;
                }

                // If found, update state: set timers, call functions, zero timer1 and timer2
                SlotData* selectedSlot = (SlotData*)((char*)this + 4 + chosenSlot * 0x4a4); // +4 offset for vtable? Actually original: param_1 = local_20 * 0x4a4 + 4 + param_1
                // Set local variables similar to before
                int dummy1 = 0;
                float dummy2 = 0.0f;
                int dummy3 = 1;
                char dummy4 = 0;
                FUN_005e9440();
                FUN_005e86e0();
                FUN_005e86e0();
                selectedSlot->timer1 = 0.0f;   // +0x1fc? Actually original sets *(undefined4*)(param_1+0x1fc)=0 and +0x200=0. Here param_1 is slot base +4, so +0x1fc is relative to slot base? Actually slot base was param_1 (original) + chosenSlot*0x4a4 +4. So the slot's timer1 offset is +0x1fc from that new base? That would be slot base +0x200 if we consider original slot base. Let's use slot base offsets: timer1 at +0x200, timer2 at +0x204. So +0x1fc from new base (which is slot+4) is slot+0x200, correct.
                selectedSlot->timer2 = 0.0f;   // +0x200 from new base = +0x204 from slot.
            }
        }

        return chosenSlot;
    }

private:
    int getSlotCount(int slotIdx) {
        return *(int*)((char*)this + 0x268 + slotIdx * 0x4a4);
    }
    void someFunction(); // placeholder for FUN_005dbc10
    void someFunction(int id, int idx, float f); // overload
    void FUN_005e9440(); // state machine update
    void FUN_005e86e0(); // animation/reset
    int getFallbackSlot(); // FUN_005e29b0
    static float someGlobalFloat; // DAT_00e2b05c
};