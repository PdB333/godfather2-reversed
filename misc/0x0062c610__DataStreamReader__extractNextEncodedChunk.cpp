// FUNC_NAME: DataStreamReader::extractNextEncodedChunk

#include <cstdint>
#include <cmath>

// Forward declarations of helper functions (callees)
int   DataStreamReader__resolveIndirection(int thisPtr);               // FUN_00633990
void  DataStreamReader__signalOverflow();                             // FUN_00627360
bool  DataStreamReader__tryGetExtendedSize(int thisPtr);              // FUN_00636850
uint32_t DataStreamReader__scanForChunk(uint32_t* startPos, uint32_t targetOffset, uint32_t endPos); // FUN_0062bd60
uint32_t DataStreamReader__advanceStream(uint32_t foundOffset, uint32_t targetOffset);                // FUN_0062c1b0

// --------------------------------------------------------------------------
// Reads the next variable‑length chunk from the internal stream.
// Assumes the stream header (at param_1+0xC) has fields:
//   -4         : int32   totalLength? (size of the header + data)
//   +0x00 .. +0x06 : data? (not used directly)
//   +0x07      : uint8   version / flags
//   +0x10      : int32   type1 (0, 4, or other)
//   +0x14      : int32   ptrOrOffset1
//   +0x18      : int32   type2
//   +0x1C      : int32   ptrOrOffset2
//   +0x20 (>=3): int64   extendedHeader (first word = sub‑type, second = float)
// --------------------------------------------------------------------------
uint32_t DataStreamReader::extractNextEncodedChunk(int thisPtr)
{
    // ----- read the three fields from the header -----

    // Field 1: baseChunkSize (local_124)
    int headerBase = *(int*)(*(int*)(thisPtr + 0xC) - 4); // pointer to start of header
    int field1 = 0;
    if (*(char*)(headerBase + 7) != '\0' && *(int*)(headerBase + 0x10) != 0) {
        if (*(int*)(headerBase + 0x10) == 4) {
            field1 = *(int*)(headerBase + 0x14) + 0x10;
        } else {
            int resolved = DataStreamReader__resolveIndirection(thisPtr);
            if (resolved != 0) {
                field1 = *(int*)(headerBase + 0x14) + 0x10;
            }
            // overflow check after the indirect call
            if (*(uint32_t*)(*(int*)(thisPtr + 0x10) + 0x20) <= *(uint32_t*)(*(int*)(thisPtr + 0x10) + 0x24)) {
                DataStreamReader__signalOverflow();
            }
        }
    }

    // Field 2: baseOffset (local_128)
    int field2 = 0;
    if (*(char*)(headerBase + 7) != '\0' && *(int*)(headerBase + 0x10) != 0) {
        if (*(int*)(headerBase + 0x10) == 4) {
            field2 = *(int*)(*(int*)(headerBase + 0x14) + 0xC);
        } else {
            int resolved2 = DataStreamReader__resolveIndirection(thisPtr);
            if (resolved2 != 0) {
                field2 = *(int*)(*(int*)(headerBase + 0x14) + 0xC);
            }
        }
    }

    // Field 3: startOffset (iVar7)
    int field3 = 0;
    if (1 < *(byte*)(headerBase + 7) && *(int*)(headerBase + 0x18) != 0) {
        if (*(int*)(headerBase + 0x18) == 4) {
            field3 = *(int*)(headerBase + 0x1C) + 0x10;
        } else {
            int resolved3 = DataStreamReader__resolveIndirection(thisPtr);
            if (resolved3 != 0) {
                field3 = *(int*)(headerBase + 0x1C) + 0x10;
            }
            // overflow check again
            if (*(uint32_t*)(*(int*)(thisPtr + 0x10) + 0x20) <= *(uint32_t*)(*(int*)(thisPtr + 0x10) + 0x24)) {
                DataStreamReader__signalOverflow();
            }
        }
    }

    // ----- read extended size (if version >= 3) -----
    float extendedSize = 0.0f;
    longlong* pExt = nullptr;
    if (*(byte*)(headerBase + 7) < 3) {
        pExt = nullptr;
    } else {
        pExt = (longlong*)(headerBase + 0x20);
    }
    if (pExt != nullptr) {
        if ((int)*pExt == 3) {
            // direct float size
            extendedSize = *(float*)((int*)pExt + 1);
        } else if ((int)*pExt == 4) {
            // need to resolve via another function
            int tmp = DataStreamReader__tryGetExtendedSize(&field2); // may modify field2? but we use local copy
            if (tmp != 0) {
                extendedSize = *(float*)((int)&extendedSize); // actually reads from a local temp? see note below
                // The decompiler shows: local_128 = CONCAT22((short)((uint)fVar9 >> 0x10),in_FPUControlWord);
                // and then local_120 = (longlong)ROUND(fVar9); 
                // That's a float‑to‑int conversion. The value comes from the header at pExt+4.
                // We'll assume extendedSize was already set earlier? Actually the code reads fVar9 from plVar2+4.
                // I'll handle it straightforwardly:
                extendedSize = *(float*)((int)pExt + 4); // same as the direct case? The decompiler might be misleading.
            }
        }
    }

    // ----- set up search bounds -----
    int searchStart = field1;                  // local_118
    int searchEnd   = field2 + field1;         // local_114
    uint32_t target = field1 + (uint32_t)(extendedSize + 0.5f); // rounded to nearest int

    // ----- iterate from target offset to searchEnd -----
    for (uint32_t cur = target; cur <= searchEnd; ++cur) {
        uint32_t found = DataStreamReader__scanForChunk(
            (uint32_t*)&searchStart, cur, field3); // field3 is the "end" or "max" parameter?
        if (found != 0) {
            int delta = found - field1;
            if (found == cur) {
                delta += 1; // adjust when found exactly at target
            }

            // Write a marker into the output buffer (at this+0x8)
            uint32_t* writePtr = *(uint32_t**)(thisPtr + 8);
            writePtr[0] = 3;                            // type marker
            writePtr[1] = *(uint32_t*)&delta;           // delta as float
            *(int*)(thisPtr + 8) += 8;                  // advance write pointer

            // Copy the just‑written marker to the extended header area,
            // then discard it from the output buffer (effectively moving it).
            int curWritePos = *(int*)(thisPtr + 8);
            int hdrBase = *(int*)(*(int*)(thisPtr + 0xC) - 4);
            uint32_t* dest = nullptr;
            if (*(byte*)(hdrBase + 7) >= 3) {
                dest = (uint32_t*)(hdrBase + 0x20);
            }
            if (dest) {
                dest[0] = *(uint32_t*)(curWritePos - 8);
                dest[1] = *(uint32_t*)(curWritePos - 4);
            }
            *(int*)(thisPtr + 8) -= 8; // undo the write (data moved to header)

            // Advance the stream and return the new position
            return DataStreamReader__advanceStream(cur, found);
        }
    }

    return 0; // chunk not found
}