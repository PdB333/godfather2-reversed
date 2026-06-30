// FUNC_NAME: SimManager::updateEntities
int SimManager::updateEntities(void) {
    int pTransformComponent = 0;

    // Check if the simulation is active (this+0x60 likely a bool flag)
    if (*(int*)(this + 0x60) != 0) {
        // Prepare default transform? Calls a setup function.
        FUN_0056fbb0();

        // Save current transform values (quaternion or position) from global?
        unsigned int saved0 = 0;
        unsigned int saved1 = 0;
        unsigned int saved2 = 0;
        unsigned int saved3 = DAT_00e2b1a4; // from a global constant

        // Get a transform component (likely from a singleton or context)
        pTransformComponent = FUN_00578ad0();
        if (pTransformComponent != 0) {
            saved0 = *(unsigned int*)(pTransformComponent + 0x10);
            saved1 = *(unsigned int*)(pTransformComponent + 0x14);
            saved2 = *(unsigned int*)(pTransformComponent + 0x18);
            saved3 = *(unsigned int*)(pTransformComponent + 0x1c);
            FUN_00414aa0(); // Likely a math function (e.g., cross product or rotation)
        }

        // Check bit 12 of flags (0x1000) - skip processing if set
        if ((*(unsigned int*)(this + 0x10) >> 0xc & 1) == 0) {
            // Iterate over a linked list of entities (next pointer at +0x124)
            int pNode = *(int*)(this + 0x124);
            while (pNode != 0) {
                if (pTransformComponent == 0) {
                    return 0;
                }

                // Check entity ID validity (-1 means invalid)
                if (*(int*)(pNode + 0x14) != -1) {
                    // If certain flags indicate idle/ready, clear action target?
                    if ((*(int*)(pNode + 0x11c) == 1) && (*(int*)(pNode + 0x110) == 1)) {
                        saved0 = 0; // Use saved0 as temporary store
                        *(unsigned int*)(pNode + 0x1c) = 0;
                    }

                    int pAnother = FUN_00578ad0(); // re-fetch (maybe singleton changes?)

                    // Check entity state (char at +0x30) and flags bits 0-1 and bit 28
                    if ((*(char*)(pNode + 0x30) == '\0') &&
                        ((*(unsigned int*)(pNode + 0x10) & 3) != 0) &&
                        ((*(unsigned int*)(pNode + 0x10) >> 0x1c & 1) != 0)) {
                        // Clear bit 28 (0x10000000) and call a reset function
                        *(unsigned int*)(pNode + 0x10) &= 0xefffffff;
                        FUN_00572580(); // likely reset internal state
                    }

                    // If both transforms are valid, and other condition met
                    if ((pAnother != 0) && (*(int*)(pAnother + 0x38) != 0) &&
                        (*(int*)(pTransformComponent + 0x38) != 0) &&
                        (FUN_00571db0() != 0) &&
                        (*(char*)(pNode + 0x120) == '\0') &&
                        (*(int*)(pNode + 0x60) != 0)) {

                        int pNext = *(int*)(pNode + 0x60); // another component pointer
                        // Determine which action to take based on sub-type
                        if ((*(char*)(pNext + 1) == '\0') ||
                            ((**(byte**)(pNext + 0xc) & 0x3f) != 0xe)) {
                            if (*(int*)(pNode + 0x110) == 0) {
                                pTransformComponent = FUN_00583460(pAnother); // action type A
                            } else {
                                pTransformComponent = FUN_00583610(saved0); // action type B using saved0
                            }
                        } else {
                            pTransformComponent = FUN_00582f90(0); // action type C with null
                        }
                        FUN_0056fb60(); // post-action cleanup
                    }
                }
                pNode = *(int*)(pNode + 0x124); // move to next node
            }
        }

        // Restore original transform component state
        if (pTransformComponent != 0) {
            *(unsigned int*)(pTransformComponent + 0x10) = saved0;
            *(unsigned int*)(pTransformComponent + 0x14) = saved1;
            *(unsigned int*)(pTransformComponent + 0x18) = saved2;
            *(unsigned int*)(pTransformComponent + 0x1c) = saved3;
            FUN_00414aa0(); // re-apply math operation
        }
    }
    return pTransformComponent; // returns pointer to the transform component (or 0)
}