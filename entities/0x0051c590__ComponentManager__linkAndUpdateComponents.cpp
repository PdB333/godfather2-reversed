// FUNC_NAME: ComponentManager::linkAndUpdateComponents
int ComponentManager::linkAndUpdateComponents(void)
{
    int *pComponentSlot;
    uint uFlags;
    undefined4 *pSubObjData;
    bool bHasDataUpdate;
    bool bIsProcessing;
    int iSlotIndex;
    int iGlobalTypeCount;
    int *pGlobalTypeEntry;
    float *pMinValue;
    float fDefaultMin;
    int localCounter;

    // Clear bit 0x20000000 (bit 29) of object flags at +0x14
    *(uint *)(this + 0x14) = *(uint *)(this + 0x14) & 0xdfffffff;

    bHasDataUpdate = false;
    bIsProcessing = false;
    localCounter = 0;

    if (*(char *)(this + 0x1c) == '\0') {
        // No components, skip to flag check
        goto CHECK_SKIP_COND;
    }

    // Loop over component slots array (starting at this+0x30, stride 36 bytes)
    pComponentSlot = (int *)(this + 0x30);
    iGlobalTypeCount = DAT_011946b4; // Number of registered component types
    do {
        // Compute pointer to sub-object (offset stored in slot + this base)
        int *pSubObj = (int *)(*pComponentSlot + this);
        iSlotIndex = 0;

        if (iGlobalTypeCount < 1) {
            // No types registered -> clear slot
            SET_NULL_SLOT:
            *pComponentSlot = 0;
        } else {
            // Search global type table for matching sub-object type
            do {
                pGlobalTypeEntry = (int *)(&DAT_011946b8)[iSlotIndex];
                if (pGlobalTypeEntry != (int *)0x0) {
                    if (pGlobalTypeEntry[2] == *pSubObj) {      // Compare type ID
                        if (pGlobalTypeEntry[4] == pSubObj[1]) { // Compare subtype ID
                            // Match found: link slot to sub-object and store global type pointer
                            *pComponentSlot = (int)pSubObj;               // Slot now points to sub-object
                            *pSubObj = (int)pGlobalTypeEntry;             // Sub-object stores global type pointer
                            // Call initialization function (vtable+0x14) on sub-object's data area (offset 12)
                            (**(code **)(*pGlobalTypeEntry + 0x14))(pSubObj + 3);

                            uFlags = pSubObj[2]; // Flags from sub-object
                            if ((pComponentSlot[2] & 0x10U) != 0) {
                                bHasDataUpdate = true;
                            }
                            if (((uFlags & 1) != 0) && ((!bHasDataUpdate || ((pComponentSlot[2] & 0x20U) == 0)))) {
                                bIsProcessing = true;
                            }
                            if ((uFlags & 4) != 0) {
                                *(uint *)(this + 0x14) = *(uint *)(this + 0x14) | 0x40000000;
                            }
                            if ((uFlags & 0x10) != 0) {
                                pComponentSlot[2] = pComponentSlot[2] | 0x100;
                            }
                            iGlobalTypeCount = DAT_011946b4; // Reload count (may have changed)
                            if ((pComponentSlot[2] & 0x100U) != 0) {
                                *(uint *)(this + 0x14) = *(uint *)(this + 0x14) | 4;
                            }
                        } else {
                            *pComponentSlot = 0; // Type mismatch -> clear slot
                        }
                        goto NEXT_SLOT;
                    }
                }
                iSlotIndex++;
            } while (iSlotIndex < iGlobalTypeCount);
            // No match found -> clear slot
            *pComponentSlot = 0;
        }

        NEXT_SLOT:
        localCounter++;
        pComponentSlot += 9; // Move to next slot (sizeof(Slot)=36 = 9*int)
    } while (localCounter < (int)(uint)*(byte *)(this + 0x1c));

    // If not processing or threshold > 0, skip setting bit
    if ((!bIsProcessing) || (0.0 < *(float *)(this + 0x18))) {
        goto CHECK_SKIP_COND;
    }
    // Set bit 0x20000000 (bit 29) of object flags
    *(uint *)(this + 0x14) = *(uint *)(this + 0x14) | 0x20000000;

CHECK_SKIP_COND:
    // Compute minimum float value across all component slots
    iSlotIndex = 0;
    *(undefined4 *)(this + 0x28) = DAT_00e2b1a4; // Default min value
    if (*(char *)(this + 0x1c) != '\0') {
        pMinValue = (float *)(this + 0x48); // First slot's minValue field (offset +0x18 from slot start)
        do {
            pSubObjData = (undefined4 *)pMinValue[-6]; // Access slot's sub-object offset (at +0x00 from slot)
            if (pSubObjData != (undefined4 *)0x0) {
                fDefaultMin = *(float *)(this + 0x28);
                if (*pMinValue <= *(float *)(this + 0x28)) {
                    fDefaultMin = *pMinValue;
                }
                *(float *)(this + 0x28) = fDefaultMin;
                // Call update function (vtable+0x2c) on the sub-object
                (**(code **)(*(int *)*pSubObjData + 0x2c))();
            }
            iSlotIndex++;
            pMinValue += 9; // Move to next slot
        } while (iSlotIndex < (int)(uint)*(byte *)(this + 0x1c));
    }
    return 1;
}