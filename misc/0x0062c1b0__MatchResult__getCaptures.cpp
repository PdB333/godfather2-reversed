// FUNC_NAME: MatchResult::getCaptures
#include <cstdint>

// Structure representing a capture result entry in the output buffer
struct CaptureEntry {
    int32_t type;       // 0: unused, 3: empty/length, 4: substring index
    union {
        float length;   // for type 3: number of characters captured (float)
        int32_t index;  // for type 4: index into string buffer or some ID
    } data;
};

// Structure holding a pointer to the dynamic capture output buffer
struct CaptureBuffer {
    int32_t* sizeCapacity; // pointer to capacity (offset +0x10+0x20?) and used (offset +0x10+0x24)
    CaptureEntry* entries; // current write pointer (offset +8)
    int32_t maxEntries;    // capacity in entries? (derived from sizes)
};

// Main context: the match result object
// Offsets relative to thisPtr:
// +0x00: int32_t matchStart    // start offset in the input string
// +0x04: int32_t *something    // not used in this function directly
// +0x08: int32_t *dictionary?  // used as a buffer pointer? (unclear)
// +0x0C: int32_t captureCount  // number of capture groups
// +0x10: CaptureBuffer* captureBuffer // pointer to dynamic buffer for results
// After that: array of capture ranges (start, end) for each group? The code accesses thisPtr[4] as base of pairs?

int32_t MatchResult::getCaptures(int32_t param_1, int32_t param_2) {
    int32_t stackDepthCheck = FUN_006254f0(); // likely checks recursion limit
    if (stackDepthCheck == 0) {
        FUN_00627bd0("stack overflow (%s)", "too many captures");
    }

    // If there are no capture groups (count == 0) and we have a valid substring,
    // treat the entire match as a single capture
    if ((thisPtr[3] == 0) && (param_1 != 0)) {
        FUN_00625c60(param_1, param_2 - param_1); // copy the full matched substring
        return 1;
    }

    int32_t processedCount = 0;
    if (thisPtr[3] > 0) {
        int32_t* capturePair = thisPtr + 4; // start of capture range pairs (start, end)
        do {
            int32_t captureEnd = capturePair[1]; // second element of pair

            if (captureEnd == -1) {
                // Unfinished capture reference (internal error)
                FUN_00627bd0("unfinished capture");
                // Software interrupt? In original code: swi(3); then call through function pointer
                // We'll skip emulation; assume unreachable
                // For reconstruction: raise exception or return error
                return -1; // fallback
            }

            if (captureEnd == -2) {
                // Empty capture: produce a "length" entry (type 3)
                int32_t captureStart = capturePair[0];
                int32_t baseOffset = thisPtr[0]; // presumably matchStart or something
                int32_t unknownPtr = thisPtr[2]; // pointer to CaptureBuffer structure?
                CaptureEntry* entry = *(CaptureEntry**)(unknownPtr + 8); // current write pointer
                entry->type = 3;
                entry->data.length = (float)((captureStart - baseOffset) + 1); // length in characters
                // Advance write pointer
                *(int32_t*)(unknownPtr + 8) = *(int32_t*)(unknownPtr + 8) + sizeof(CaptureEntry);
            } else {
                // Normal capture: produce a substring index entry (type 4)
                int32_t unknownPtr = thisPtr[2];
                int32_t captureStart = capturePair[0];
                // Check if the output buffer has room; if not, resize
                if (*(uint32_t*)(*(int32_t*)(unknownPtr + 0x10) + 0x20) <= 
                    *(uint32_t*)(*(int32_t*)(unknownPtr + 0x10) + 0x24)) {
                    FUN_00627360(); // resize buffer
                }
                CaptureEntry* entry = *(CaptureEntry**)(unknownPtr + 8);
                entry->type = 4;
                // FUN_00638920 returns some ID/index for this capture range
                uint32_t captureIndex = FUN_00638920(unknownPtr, captureStart, captureEnd);
                entry->data.index = captureIndex;
                *(int32_t*)(unknownPtr + 8) = *(int32_t*)(unknownPtr + 8) + sizeof(CaptureEntry);
            }

            processedCount++;
            capturePair += 2; // advance to next pair
        } while (processedCount < thisPtr[3]);
    }

    return thisPtr[3]; // return number of captures processed
}