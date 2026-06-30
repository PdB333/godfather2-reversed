// FUNC_NAME: DataStream::processNumberEntry
// Function at 0x00631f10: Processes a stream of entries (type 3 or 4), handles a special "number" value.
// Likely part of the EARS packet serialization system. Writes a new type 3 entry with a scaled float.

__declspec(naked) void __thiscall DataStream::processNumberEntry(void) {
    // This is a reconstructed function; actual prologue/epilogue omitted.
    // Offsets:
    // +0x08: mWritePos (pointer to current write position in stream)
    // +0x0C: mReadPos  (pointer to current read position in stream)
}

// Decompiled logic:
undefined4 __thiscall DataStream::processNumberEntry(DataStream *this)
{
    int *pReadPos;         // piVar3: pointer to current read position (from +0x0C)
    int *pWritePos;        // puVar1: pointer to current write position (from +0x08)
    int iResult;           // iVar2: result of getScaledFloat()
    float fTemp;           // local_14: temporary float storage
    int iTemp;             // local_10: temporary int (type 3)
    float fScaled;         // local_c: float from getScaledFloat()

    // Start by reading the type and data at the read pointer
    pReadPos = *(int **)((int)this + 0x0C);  // +0x0C: mReadPos

    // Check if write position is past read position (stream exhausted?)
    if (*(int **)((int)this + 0x08) <= pReadPos) goto exit_zero;
    if (pReadPos == (int *)0x0) goto exit_zero;

    // Check the type tag at read position
    if (*pReadPos != 3) {
        if (*pReadPos != 4) goto exit_zero; // not type 3 or 4 -> use zero
        // Type 4: call a helper to get a scaled float
        iResult = getScaledFloat(&fTemp);   // FUN_00636850
        if (iResult == 0) goto exit_zero;
        // Set up a local "entry" with type 3 and the float from getScaledFloat
        iTemp = 3;
        fScaled = fTemp;
        pReadPos = &iTemp;  // point to local (stack) entry
    }

    // Read the float value following the type tag (now pReadPos[1])
    fTemp = (float)pReadPos[1];

    // Check if this float equals the special number value
    if (fTemp == kNumberSpecialValue) {   // DAT_00e2b05c
        // Special value: scan forward in stream until we find a valid entry (type 3 or type 4 with getScaledFloat success)
        while (true) {
            pReadPos = *(int **)((int)this + 0x0C);  // re-fetch read pointer (maybe updated?)
            // Check end of stream or null pointer
            if (*(int **)((int)this + 0x08) <= pReadPos) break;
            if (pReadPos == (int *)0x0) break;
            // Check for type 3 or type 4 with success
            if (*pReadPos == 3) break;
            if (*pReadPos == 4) {
                iResult = getScaledFloat(&iTemp);  // reuse local variable
                if (iResult != 0) break;
            }
            // If not valid, print debug message "number" and continue (loop does not advance? Perhaps the stream pointer is advanced elsewhere)
            debugPrintNumber(PTR_s_number_00e2a8a8);  // FUN_00627ac0
        }
        // After loop, fTemp retains the value from before (or possibly unchanged)
    }

    // Now write a new entry with type 3 and the (possibly scaled) float
    pWritePos = *(int **)((int)this + 0x08);  // +0x08: mWritePos
    fTemp = fTemp * kNumberMultiplier;        // DAT_00e445c8: scale factor
    *pWritePos = 3;                           // type 3
    pWritePos[1] = *(int *)&fTemp;            // write the float as integer
    *(int *)((int)this + 0x08) = (int)pWritePos + 8; // advance write pointer by 8 bytes
    return 1;

exit_zero:
    fTemp = 0.0f;
    // Falls through to write a zero entry (type 3 with value 0)
    // Note: this path also writes, but the write pointer might be used (pWritePos not yet set)
    // Actually the goto jumps to after the special value check, so the write block executes with fTemp=0.
    // The write block uses pWritePos which is set there, so it overwrites the current write pointer.
    pWritePos = *(int **)((int)this + 0x08);
    *pWritePos = 3;
    pWritePos[1] = 0;
    *(int *)((int)this + 0x08) = (int)pWritePos + 8;
    return 1;
}