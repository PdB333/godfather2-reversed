// FUNC_NAME: NPCCrewComponent::applyDamageToCrewMember
// Function address: 0x005e1fd0
// Reconstructed from Ghidra decompilation. See field offsets documented in comments.

// This function applies a damage multiplier (or sets health) of 50 to a crew member 
// matching the given ID, but only if the crew is in a certain active state (flag at +0x1744).
// It uses a vtable call on the NPC object associated with the crew slot.

#define MAX_CREW_MEMBERS 5
#define CREW_SLOT_SIZE 0x4A4 // 1196 bytes per slot

// Global vtable pointer for NPC objects (likely AICharacter or similar)
extern void** g_npcVTable; // DAT_01223510

// Forward declaration of a helper function called at the start
void someCheckOrInit(); // FUN_005dbc10

class NPCCrewComponent {
public:
    // Offsets:
    // +0x1744: byte - active flag (e.g., isInCombat)
    // +0x0490: array of crew slot data (each 0x4A4 bytes)
    // Slot offsets:
    //   +0x000: int32 crewMemberID (first field of slot)
    //   +0x1CC: NPC object pointer (e.g., AICharacter*)
    //   +0x20C: int32 someValue (set to 50 here)

    bool applyDamageToCrewMember(int memberID) {
        someCheckOrInit();

        if (*(char*)(this + 0x1744) == 0) {
            return false; // Crew not active, cannot apply
        }

        // Iterate over 5 crew slots
        for (int i = 0; i < MAX_CREW_MEMBERS; i++) {
            // Each slot begins at base + 0x490 + i * CREW_SLOT_SIZE
            int slotBase = (int)(this + 0x490) + i * CREW_SLOT_SIZE;
            int* slotIDPtr = (int*)slotBase; // first dword is crew member ID

            if (*slotIDPtr == memberID) {
                // Found matching slot, compute pointer to element start
                // Note: The decompiled code computes address as (i * CREW_SLOT_SIZE + 4 + this)
                // But our slotBase is this + 0x490 + i * CREW_SLOT_SIZE.
                // There's an offset difference of 0x48C, so the element "start" per the assembly 
                // is actually this + 4 + i * CREW_SLOT_SIZE.
                // This suggests the array base is not at +0x490 but at +0x4? 
                // However, the loop uses piVar3 = (int*)(this + 0x490) and increments by 0x129 (int-sized steps),
                // which matches our calculation. The mismatch in final address may indicate 
                // that the slot structure has a header or the slot index is recalculated.
                // We'll follow the decompiled logic exactly:
                int slotElement = (int)(this + 4) + i * CREW_SLOT_SIZE;

                // Set value at offset +0x20C to 50
                *(int*)(slotElement + 0x20C) = 50;

                // Call vtable method at +0x9C on the NPC pointer stored at offset +0x1CC
                // NPC object is pointed to by field at slotElement + 0x1CC
                void* npcObject = *(void**)(slotElement + 0x1CC);
                void** vtable = *(void***)g_npcVTable; // actually vtable from global
                // The call passes the NPC object as 'this' and 50 as the argument
                (*(void(__thiscall*)(void*, int))(*vtable + 0x9C))(npcObject, 50);

                return true;
            }
        }
        return false; // No matching crew member found
    }
};