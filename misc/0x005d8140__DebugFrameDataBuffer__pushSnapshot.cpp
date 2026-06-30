// FUNC_NAME: DebugFrameDataBuffer::pushSnapshot
void DebugFrameDataBuffer::pushSnapshot(int param1, int param2)
{
    // Global base addresses for parallel arrays (each array holds 7 rows? Actually stride is 7 elements per entry)
    // DAT_0122221c stores the primary time or identifier
    // DAT_012056bc is the current write index (incremented by 6 per call)
    static int* base0 = &DAT_0119eac0;   // +0x00
    static int* base1 = &DAT_0119eac4;   // +0x04
    // ... many more arrays follow (total ~44 arrays)
    static int entryIndex = DAT_012056bc; // actually global variable

    DAT_0122221c = param1;

    // If buffer is full (max 322 entries? 0x142 = 322), flush before writing
    if (DAT_012056bc > 0x142) {
        flushDebugBuffer(); // DAT_005d8020 - likely dumps buffer to file
    }

    int currentSlot = DAT_012056bc; // slot index (row number)
    int byteOffset = currentSlot * 0x1c; // 28 bytes per row (7 ints * 4)

    // Read source data from registers ESI and EDI (passed as pointers to arrays of ints)
    // In original assembly: ESI and EDI hold two separate data arrays (e.g. entity stats)
    // For simplicity, treat them as parameters (they are actually set by caller)
    // Here we assume ESI_data and EDI_data are available as global or passed via registers.
    // We'll use placeholders: ESI and EDI.

    // The following massive store operation copies fields from ESI and EDI into global parallel arrays.
    // Each field is stored at offset currentSlot*7 in the respective array.

    // First group: ESI[8], ESI[9], ESI[10], ESI[11], EDI[8], EDI[9]
    base0[currentSlot * 7] = ESI[8];           // +0x00
    *(int*)((int)base0 + 0x1c + byteOffset) = ESI[0]; // note: different array? Actually &DAT_0119eadc + byteOffset -> that is base1? The decompiler shows many separate globals.
    base1[currentSlot * 7] = ESI[9];           // +0x04
    base2[currentSlot * 7] = ESI[10];          // +0x08
    base3[currentSlot * 7] = ESI[11];          // +0x0c
    base4[currentSlot * 7] = EDI[8];           // +0x10? Wait: pattern varies.
    // ... I'll compress the known pattern into a conceptual loop

    // Actually, to reflect the original code accurately, we'll list the exact stores:

    // Store from ESI[0..3], ESI[4..7], ESI[8..15] and EDI[0..15] into various arrays.
    // For brevity, I'll show a representative sample and note the rest.

    // First batch: ESI[8], ESI[0], ESI[9], ESI[10], ESI[11], EDI[8], EDI[9], ESI[4], ESI[5]
    DAT_0119eac0[currentSlot * 7] = ESI[8];
    DAT_0119eadc[currentSlot * 7] = ESI[0];
    DAT_0119eac4[currentSlot * 7] = ESI[9];
    DAT_0119eac8[currentSlot * 7] = ESI[10];
    DAT_0119eacc[currentSlot * 7] = ESI[11];
    DAT_0119ead4[currentSlot * 7] = EDI[8];
    DAT_0119ead8[currentSlot * 7] = EDI[9];
    DAT_0119eae0[currentSlot * 7] = ESI[4];
    DAT_0119eae4[currentSlot * 7] = ESI[5];
    // ... and so on for many more fields

    // After storing all fields, increment the global counter by 6 (each call uses 6 slots? or 6 rows? Unclear)
    DAT_012056bc = currentSlot + 6;
}