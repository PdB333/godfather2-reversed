// FUNC_NAME: HUDObject::updateVisibility
void HUDObject::updateVisibility(void)
{
    float value;
    int *pWriteHead; // pointer to current write position in display list buffer
    char *dataPtr;   // pointer to some data at this+0x54

    // Get the current value: either via a custom getter or from a member
    if (g_pGetValueFunc == nullptr) {
        value = *(float *)(this + 0x270); // health/progress
    } else {
        value = (float)*g_pGetValueFunc();
    }

    // Check against threshold (likely 0.0f)
    if (value <= kDisplayThreshold) {
        // Value is below threshold -> remove from display list if registered
        if ((*(uint8_t *)(this + 0x184) & 0x40) != 0) {
            pWriteHead = (int *)(g_pDisplayManager + 0x14);
            **(uint32_t **)pWriteHead = s_vtableRemove; // vtable for removal
            *pWriteHead = *pWriteHead + 4;
            *(int *)*pWriteHead = this;
            *pWriteHead = *pWriteHead + 4;
            // Clear registration flag
            *(uint32_t *)(this + 0x184) = *(uint32_t *)(this + 0x184) & 0xFFFFFFBF;
        }
        return;
    }

    // Value is above threshold
    if ((*(uint8_t *)(this + 0x184) & 0x40) == 0) {
        // Not yet registered -> add to display list with initial vtable
        pWriteHead = (int *)(g_pDisplayManager + 0x14);
        **(uint32_t **)pWriteHead = s_vtableAdd;
        *pWriteHead = *pWriteHead + 4;
        *(int *)*pWriteHead = this;
        *pWriteHead = *pWriteHead + 4;
        dataPtr = (char *)(this + 0x54); // some data block
        *(int *)*pWriteHead = dataPtr;
        *pWriteHead = *pWriteHead + 4;    // advance past data pointer
        // Write the current value at offset 4 in the next slot (TODO: verify layout)
        int *nextSlot = pWriteHead;       // captured after dataPtr write
        *(float *)((int)nextSlot + 4) = value;
        *pWriteHead = (int)nextSlot + 8; // advance by 8, accounting for the float write
        // Set registration flag
        *(uint32_t *)(this + 0x184) = *(uint32_t *)(this + 0x184) | 0x40;
        if ((*(uint8_t *)(this + 0x184) & 0x40) == 0) {
            return; // shouldn't happen
        }
    }

    // In all cases when visible, push an update entry with a different vtable
    pWriteHead = (int *)(g_pDisplayManager + 0x14);
    **(uint32_t **)pWriteHead = s_vtableUpdate;
    *pWriteHead = *pWriteHead + 4;
    *(int *)*pWriteHead = this;
    *pWriteHead = *pWriteHead + 4;
    dataPtr = (char *)(this + 0x54);
    *(int *)*pWriteHead = dataPtr;
    *pWriteHead = *pWriteHead + 4;
    return;
}