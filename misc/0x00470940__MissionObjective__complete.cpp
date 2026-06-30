// FUNC_NAME: MissionObjective::complete

void __thiscall MissionObjective::complete(int thisPtr, char forceComplete)
{
    undefined4 completionData;
    int *globalBufferPtr;
    int *pBufferWritePos;
    undefined4 *localBuffer;
    undefined4 localData;

    // Check if completion is pending (bit0 at +0x15f) or forced
    if ((((*(byte *)(thisPtr + 0x15f) & 1) != 0) || (forceComplete != '\0')) &&
        // Clear a bit (bit8) in flags at +0x15e to mark completion
        (*(ushort *)(thisPtr + 0x15e) = *(ushort *)(thisPtr + 0x15e) & 0xfeff,
         *(int *)(thisPtr + 0x130) != 0) && (*(int *)(thisPtr + 0x164) != 0))
    {
        completionData = *(undefined4 *)(thisPtr + 0x150); // +0x150: some data (e.g., delay/ID)

        // Access global buffer at DAT_01206880 (likely a log/command queue)
        globalBufferPtr = (int *)(DAT_01206880 + 0x14);
        // Write vtable pointer of a command structure (PTR_LAB_0110babc) into the buffer
        **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_0110babc;
        *globalBufferPtr = *globalBufferPtr + 4; // Advance write position by 4 bytes
        // Write the object pointer (thisPtr + 0x54) as first argument
        *(int *)*globalBufferPtr = thisPtr + 0x54;
        int tempWritePos = *globalBufferPtr;
        // Write the completion data as second argument
        *(undefined4 *)(tempWritePos + 4) = completionData;
        // Advance write position by 8 bytes total (vtable ptr + two arguments)
        *globalBufferPtr = tempWritePos + 8;

        // If the pointer at +0x130 is still valid, call a helper to process the queued command
        if (*(int *)(thisPtr + 0x130) != 0)
        {
            localData = *(undefined4 *)(thisPtr + 0x150);
            localBuffer = &PTR_LAB_00e32aac;
            // Queue the completion event (FUN_004a4bd0 likely handles buffer flush)
            FUN_004a4bd0(&localBuffer);
        }
    }
    return;
}