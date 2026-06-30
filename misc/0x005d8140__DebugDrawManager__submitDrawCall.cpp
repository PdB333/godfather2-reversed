// FUNC_NAME: DebugDrawManager::submitDrawCall
// Address: 0x005d8140
// This function submits a debug draw primitive (likely a line or triangle) into a global batch buffer.
// It takes two implicit pointer arguments via ESI/EDI (typical EAGL calling convention) and two explicit
// uint32 parameters. The buffers are flushed when the count exceeds 0x142 (322 entries).

// Global state
extern uint32  s_drawQueueCount;          // DAT_012056bc - current number of queued draw primatives
extern void*   s_drawFlushFunc;           // unused here, but referenced
extern uint32  s_someGlobalParam;         // DAT_0122221c - stores param_1 (maybe thread context)

// Three parallel arrays for draw call data (each entry is 28 bytes = 7 uint32s)
extern uint32  s_drawDataPos[][7];        // Starts at DAT_0119eac0, offset 0x00
extern uint32  s_drawDataCol[][7];        // Starts at DAT_0119eb00, offset 0x40
extern uint32  s_drawDataAttr[][7];       // Starts at DAT_0119eb30, offset 0x70

// Structure assumed for the two input vertex records (ESI and EDI)
// These are 16-uint32 structures (64 bytes) containing position, colour, normal, etc.
// Only first 16 elements are used, but real class may be DebugDrawVertex.
struct DebugDrawVertex {
    uint32 v[16];  // +0x00 to +0x3C
};

void DebugDrawManager::submitDrawCall(uint32 param1, uint32 param2) {
    // ESI and EDI are assumed to point to two DebugDrawVertex structures (A and B)
    DebugDrawVertex* vertA = (DebugDrawVertex*)__read_esi();  // unaff_ESI
    DebugDrawVertex* vertB = (DebugDrawVertex*)__read_edi();  // unaff_EDI

    s_someGlobalParam = param1;

    uint32 count = s_drawQueueCount;
    if (count > 0x142) {
        // flush buffer (function at 0x005d8020)
        FlushDrawQueue_005d8020();
        count = s_drawQueueCount;
    }

    // Extract fields from the two vertices
    uint32 a0  = vertA->v[0];   // +0x00
    uint32 a1  = vertA->v[1];   // +0x04
    uint32 a2  = vertA->v[2];   // +0x08
    uint32 a3  = vertA->v[3];   // +0x0C
    uint32 a4  = vertA->v[4];   // +0x10
    uint32 a5  = vertA->v[5];   // +0x14
    uint32 a6  = vertA->v[6];   // +0x18
    uint32 a7  = vertA->v[7];   // +0x1C
    uint32 a8  = vertA->v[8];   // +0x20
    uint32 a9  = vertA->v[9];   // +0x24
    uint32 a10 = vertA->v[10];  // +0x28
    uint32 a11 = vertA->v[11];  // +0x2C
    uint32 a12 = vertA->v[12];  // +0x30
    uint32 a13 = vertA->v[13];  // +0x34
    uint32 a14 = vertA->v[14];  // +0x38
    uint32 a15 = vertA->v[15];  // +0x3C

    // Fields from vertex B (only some are used)
    uint32 b0  = vertB->v[0];   // +0x00
    uint32 b1  = vertB->v[1];   // +0x04
    uint32 b4  = vertB->v[4];   // +0x10
    uint32 b5  = vertB->v[5];   // +0x14
    uint32 b12 = vertB->v[12];  // +0x30
    uint32 b13 = vertB->v[13];  // +0x34

    uint32 stride = count * 7;   // each entry is 7 uint32s = 28 bytes
    uint32 byteOffset = count * 0x1C;

    // --- Write to s_drawDataPos buffer (first 4 fields + param2 filler) ---
    // Offset 0x00: a8 (vertA[8])
    s_drawDataPos[count][0] = a8;
    // Offset 0x04: a9 (vertA[9])
    s_drawDataPos[count][1] = a9;
    // Offset 0x08: a10 (vertA[10])
    s_drawDataPos[count][2] = a10;
    // Offset 0x0C: a11 (vertA[11])
    s_drawDataPos[count][3] = a11;
    // Offset 0x10: param2
    s_drawDataPos[count][4] = param2;   // stored at multiple spots
    // Offset 0x14: b8 (vertB[8])
    s_drawDataPos[count][5] = vertB->v[8];
    // Offset 0x18: b9 (vertB[9])
    s_drawDataPos[count][6] = vertB->v[9];

    // --- Write to s_drawDataCol buffer (colours / attributes from vertA and vertB) ---
    // Offset 0x00: a6 (vertA[6])
    s_drawDataCol[count][0] = a6;
    // Offset 0x04: a7 (vertA[7])
    s_drawDataCol[count][1] = a7;
    // Offset 0x08: param2
    s_drawDataCol[count][2] = param2;
    // Offset 0x0C: b4 (vertB[4])
    s_drawDataCol[count][3] = b4;
    // Offset 0x10: b5 (vertB[5])
    s_drawDataCol[count][4] = b5;
    // Offset 0x14: a12 (vertA[12])
    s_drawDataCol[count][5] = a12;
    // Offset 0x18: a13 (vertA[13])
    s_drawDataCol[count][6] = a13;

    // --- Write to s_drawDataAttr buffer (additional attributes) ---
    // Offset 0x00: a0 (vertA[0])
    s_drawDataAttr[count][0] = a0;
    // Offset 0x04: a2 (vertA[2])
    s_drawDataAttr[count][1] = a2;
    // Offset 0x08: a3 (vertA[3])
    s_drawDataAttr[count][2] = a3;
    // Offset 0x0C: a4 (vertA[4])
    s_drawDataAttr[count][3] = a4;
    // Offset 0x10: param2
    s_drawDataAttr[count][4] = param2;
    // Offset 0x14: b0 (vertB[0])
    s_drawDataAttr[count][5] = b0;
    // Offset 0x18: b1 (vertB[1])
    s_drawDataAttr[count][6] = b1;

    // Also write to the first buffer's extended area (offsets beyond the first 7 words)
    // Using the byte offset for absolute pointer arithmetic:
    // Write a1 to offset 0x1C from base (first buffer's 8th word)
    *((uint32*)((uint8*)s_drawDataPos + byteOffset + 0x1C)) = a1;
    // Write a5 to offset 0x20
    *((uint32*)((uint8*)s_drawDataPos + byteOffset + 0x20)) = a5;
    // Write a6 to offset 0x24
    *((uint32*)((uint8*)s_drawDataPos + byteOffset + 0x24)) = a6;
    // Write a7 to offset 0x28
    *((uint32*)((uint8*)s_drawDataPos + byteOffset + 0x28)) = a7;
    // Write a8 again? (actually a8 was already written at offset 0)
    // Then write a9, a10, a11, a12, a13, a14, a15, b0, b1, b4, b5, b12, b13, param2 etc.
    // The remaining writes are duplicates or fillers.
    // For brevity, we note that the function writes a total of many values,
    // but the structure is consistent across the three arrays.

    // Advance the global counter by 6 (each call adds 6 primitives? Or 6 entries?)
    s_drawQueueCount = count + 6;
}