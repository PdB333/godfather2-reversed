// FUNC_NAME: PlayerWallCoverSM::processInput
// Function at 0x007b0f00: Handles cover input transitions based on bit flags in player action flags.
// Sets state IDs and player flags for cover directions (left/right?).
int __fastcall PlayerWallCoverSM::processInput(PlayerWallCoverSM* thisPtr)
{
    // +0x58: pointer to player entity (e.g., PlayerComponent)
    int* playerEntity = *(int**)(thisPtr + 0x58);
    // +0xff0: some component array/table in player entity (e.g., component list)
    int* componentPtr = *(int**)(playerEntity + 0xff0);
    // componentPtr may be non-zero, then subtract 0x48 to get a component (e.g., CombatKnowledge, CoverHintNodeManager?)
    if (componentPtr != nullptr) {
        int* componentVtable = (int*)(componentPtr - 0x48); // actual component object with vtable at start
        if (componentVtable != nullptr) {
            int outAllowed = 0;
            // Virtual call via component vtable +0x10: method signature (hash 0x369ac561) returns bool, takes out param
            // Likely "isCoverTransitionAllowed" or similar.
            char allowedFlag = (**(code**)(*componentVtable + 0x10))(0x369ac561, &outAllowed);
            if (allowedFlag != 0) {
                // playerObj is likely stored in ESI register (unaff_ESI) – typically the player entity globally available.
                // Offset +0x24a4 in player entity: action/flags bitmask (e.g., currentInputFlags)
                uint flags = *(uint*)(playerEntity + 0x24a4);
                // Bit 1 (mask 0x2): Left cover input
                if ((flags >> 1 & 1) != 0) {
                    // Set state IDs for cover left transition
                    *(int*)(thisPtr + 0x78) = 0x59; // likely stateID for "CoverEnterLeft" or "TakeCoverLeft"
                    *(int*)(thisPtr + 0x7c) = 0x5a; // likely sub-state or animation ID
                    // Set player flag bit 0x8000000 (e.g., "inCoverLeft" or "coverButtonHeld")
                    *(uint*)(playerObj + 0x218c) |= 0x8000000;
                    return 1;
                }
                // Bit 2 (mask 0x4): Right cover input
                if ((flags >> 2 & 1) != 0) {
                    *(int*)(thisPtr + 0x78) = 0x53;
                    *(int*)(thisPtr + 0x7c) = 0x54;
                    *(uint*)(playerObj + 0x218c) |= 0x10000000; // e.g., "inCoverRight"
                    return 1;
                }
            }
        }
    }
    return 0;
}