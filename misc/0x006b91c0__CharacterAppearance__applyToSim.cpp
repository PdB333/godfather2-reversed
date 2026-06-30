// FUNC_NAME: CharacterAppearance::applyToSim
void __thiscall CharacterAppearance::applyToSim(int this, int *updateType) {
    int *entity;
    int appearanceData;
    int temp;
    int *appearanceComponent;
    int *newValue;

    // Check if the update type matches the primary appearance slot (offset 0x14)
    if (*updateType == *(int *)(this + 0x14)) {
        // Get the entity to apply to (likely the current simulation object)
        entity = getEntity();
        if (entity != 0) {
            // If secondary appearance data exists, clear it
            if (*(int *)(this + 0x1c) != 0) {
                clearSecondaryAppearance(entity);
            }
            // Cancel any active animation timers (IDs stored at +0x54 and +0x58)
            if (*(int *)(this + 0x54) >= 0) {
                cancelAnimationTimer(*(int *)(this + 0x54));
            }
            if (*(int *)(this + 0x58) >= 0) {
                cancelAnimationTimer(*(int *)(this + 0x58));
            }
            // Get the appearance component from the entity (offset 0xd4)
            appearanceComponent = *(int **)(entity + 0xd4);
            if (appearanceComponent != 0) {
                // Apply mesh/skin slot 0 (offset 0x26c)
                if (*(int *)(this + 0x38) != 0) {
                    newValue = (int *)(appearanceComponent + 0x26c);
                    if (*newValue != 0) {
                        deleteSmartPtr(newValue);
                    }
                    assignSmartPtr(newValue, *(int *)(this + 0x38));
                }
                // Apply mesh/skin slot 1 (offset 0x274)
                if (*(int *)(this + 0x3c) != 0) {
                    newValue = (int *)(appearanceComponent + 0x274);
                    if (*newValue != 0) {
                        deleteSmartPtr(newValue);
                    }
                    assignSmartPtr(newValue, *(int *)(this + 0x3c));
                }
                // Apply mesh/skin slot 2 (offset 0x1dc)
                if (*(int *)(this + 0x40) != 0) {
                    newValue = (int *)(appearanceComponent + 0x1dc);
                    if (*newValue != 0) {
                        deleteSmartPtr(newValue);
                    }
                    assignSmartPtr(newValue, *(int *)(this + 0x40));
                }
                // Apply mesh/skin slot 3 (offset 0x29c)
                if (*(int *)(this + 0x44) != 0) {
                    newValue = (int *)(appearanceComponent + 0x29c);
                    if (*newValue != 0) {
                        deleteSmartPtr(newValue);
                    }
                    assignSmartPtr(newValue, *(int *)(this + 0x44));
                }
                // Apply additional appearance data (offset 0x1d8)
                if (*(int *)(this + 0x48) != 0) {
                    *(int *)(appearanceComponent + 0x1d8) = *(int *)(this + 0x48);
                }
            }
            // Finalize the appearance update on the entity
            finalizeAppearance(entity);
            return;
        }
    }
    // Otherwise, check if update type matches secondary appearance slot (offset 0x1c) and if there is stored data at +0x5c
    else if ((*updateType == *(int *)(this + 0x1c)) && (*(int *)(this + 0x5c) != 0)) {
        entity = getEntity();
        if (entity != 0) {
            // Get the stored appearance data block (array of 5 ints)
            int *storedData = *(int **)(this + 0x5c);
            // Clear the old animation timers from the stored data (indices 7 and 8)
            cancelAnimationTimer(storedData[7]);
            cancelAnimationTimer(storedData[8]);
            // Get the appearance component
            appearanceComponent = *(int **)(entity + 0xd4);
            if (appearanceComponent != 0) {
                // Apply mesh/skin slot 0 from stored data (index 0)
                if (*(int *)(appearanceComponent + 0x26c) != 0) {
                    deleteSmartPtr(appearanceComponent + 0x26c);
                }
                assignSmartPtr(appearanceComponent + 0x26c, storedData[0]);
                // Slot 1 (index 1)
                appearanceComponent = (int *)((char *)appearanceComponent + 0x274);
                if (*appearanceComponent != 0) {
                    deleteSmartPtr(appearanceComponent);
                }
                assignSmartPtr(appearanceComponent, storedData[1]);
                // Slot 2 (index 2)
                int *slot2 = (int *)((char *)appearanceComponent - 0x98); // 0x274 - 0x1dc = 0x98, but careful: let's recalc
                // Actually simpler to recompute from original pointer:
                // slot2 offset 0x1dc from appearanceComponent base
                if (*(int *)((int)appearanceComponent - 0x98) != 0) {
                    deleteSmartPtr((int *)((int)appearanceComponent - 0x98));
                }
                assignSmartPtr((int *)((int)appearanceComponent - 0x98), storedData[2]);
                // Slot 3 (index 3, offset 0x29c)
                // offset from slot1: 0x29c - 0x274 = 0x28
                if (*(int *)((int)appearanceComponent + 0x28) != 0) {
                    deleteSmartPtr((int *)((int)appearanceComponent + 0x28));
                }
                assignSmartPtr((int *)((int)appearanceComponent + 0x28), storedData[3]);
                // Additional data (index 4, offset 0x1d8)
                // offset from base appearanceComponent: 0x1d8 - 0x26c = -0x94? This is messy.
                // Original code uses: *(undefined4 *)(iVar2 + 0x1d8) = puVar4[4];
                // So it directly assigns to iVar2+0x1d8, where iVar2 is appearanceComponent (base at +0xd4)
                // Let's re-derive from original decompiled: 
                // iVar2 = *(int *)(iVar6 + 0xd4) -> pointer to appearance component
                // then *(undefined4 *)(iVar2 + 0x1d8) = puVar4[4];
                // So we need to add 0x1d8 to the base.
                int *appearanceBase = *(int **)(entity + 0xd4);
                *(int *)(appearanceBase + 0x1d8) = storedData[4];
            }
            // Finalize the appearance with a different method (maybe notify or commit)
            finalizeAppearanceWithNotify(entity);
        }
        // Delete the temporary stored data block
        if (*(int *)(this + 0x5c) != 0) {
            freeMemory(*(int *)(this + 0x5c));
            *(int *)(this + 0x5c) = 0;
        }
    }
    return;
}