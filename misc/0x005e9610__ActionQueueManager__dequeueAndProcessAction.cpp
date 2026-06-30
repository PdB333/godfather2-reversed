// FUNC_NAME: ActionQueueManager::dequeueAndProcessAction
// Address: 0x005e9610
// This function retrieves the next queued action from a circular buffer of 4 slots,
// updates the current action state, and copies action data into the manager's fields.
// The queue slots are 0x78 bytes each, starting at offset +0x294.
// The element structure (QueueSlot) is:
//   +0x00: m_pObject (pointer to some game object)
//   +0x04 to +0x6C: m_data[27] (27 ints, copied to this+0x210)
//   +0x70: m_paramA (int)
//   +0x74: m_paramB (int)

void __thiscall ActionQueueManager::dequeueAndProcessAction(int thisPtr)
{
    int currentSlot;
    int wrappedIndex;
    int count;
    int *pSlot;
    int *pDest;

    if (*(int *)(thisPtr + 0x1fc) > 0)  // m_queueSize > 0
    {
        currentSlot = *(int *)(thisPtr + 0x200);  // m_currentSlot
        wrappedIndex = currentSlot + 1;
        pSlot = (int *)(thisPtr + 0x294 + currentSlot * 0x78);  // base of current slot
        *(int *)(thisPtr + 0x200) = wrappedIndex;
        if (wrappedIndex > 3)  // wrap around for 4-slot circular buffer
        {
            wrappedIndex = currentSlot - 3;
        }
        *(int *)(thisPtr + 0x200) = wrappedIndex;
        count = *(int *)(thisPtr + 0x1fc) - 1;
        *(int *)(thisPtr + 0x1fc) = count;

        // Release/clear the slot (function 0x005dbc10)
        releaseQueueSlot(count);

        // Set the object's +0x60 field to 0 and store as currentObject
        *(undefined4 *)(*pSlot + 0x60) = 0;
        *(int *)(thisPtr + 0x1b4) = *pSlot;  // m_currentObject

        // Copy global timestamp value to start/end fields
        *(undefined4 *)(thisPtr + 0x204) = *(undefined4 *)(DAT_01223518 + 8);
        *(undefined4 *)(thisPtr + 0x208) = *(undefined4 *)(DAT_01223518 + 8);

        // Initialize various action state fields
        *(undefined4 *)(thisPtr + 0x1d8) = 0;          // m_field_1d8
        *(undefined4 *)(thisPtr + 0x1dc) = *(undefined4 *)(*pSlot + 0x54);  // from object +0x54
        *(int *)(thisPtr + 0x20c) = pSlot[0x1c];       // slot.m_paramA (offset 0x70)
        *(undefined1 *)(thisPtr + 0x283) = 0;          // m_byte_283
        *(undefined1 *)(thisPtr + 0x284) = 0;          // m_byte_284
        *(int *)(thisPtr + 0x27c) = pSlot[0x1d];       // slot.m_paramB (offset 0x74)

        // Copy the 27 ints from slot (starting at offset 0x04) to this+0x210 (m_actionData)
        pDest = (int *)(thisPtr + 0x210);
        for (int i = 0x1b; i != 0; i--)  // copy 27 ints (108 bytes)
        {
            *pDest = *pSlot;
            pDest++;
            pSlot++;
        }

        // Reset some IDs to -1 (no selection)
        *(undefined4 *)(thisPtr + 0x1cc) = 0xffffffff;
        *(undefined4 *)(thisPtr + 0x1d0) = 0xffffffff;

        // Set flags
        *(undefined1 *)(thisPtr + 0x285) = 1;  // m_flag_285 (active?)
        *(undefined1 *)(thisPtr + 0x286) = 0;  // m_flag_286

        // Handle state transition (offset 0x480/0x484)
        *(undefined4 *)(thisPtr + 0x480) = *(undefined4 *)(thisPtr + 0x484);  // m_prevState = m_state
        if (*(int *)(thisPtr + 0x484) != 4)  // if not in state 4
        {
            *(undefined4 *)(thisPtr + 0x484) = 4;
            // Notify state change if function 0x005e8900 returns true
            if (notifyStateChange())  // FUN_005e8900
            {
                *(undefined4 *)(thisPtr + 0x480) = *(undefined4 *)(thisPtr + 0x484);  // update m_prevState
            }
        }
    }
}