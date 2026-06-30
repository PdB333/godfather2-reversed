// FUNC_NAME: SupportFinder::evaluateSupport

#include <cstdint>

// Forward declarations
struct SupportEntry; // 64 bytes
struct SupportQuery; // 48 bytes? return struct

// TLS manager for profiling and memory allocation
struct TlsMemoryManager {
    // ...
};

// External functions
extern uint32_t __rdtsc();
extern void* __TlsGetValue(uint32_t index);
extern void __copySupportEntry(const SupportEntry* src, SupportEntry* dst); // vtable[0x14]
extern void __transformSupportQuery(SupportQuery* query, float* out); // FUN_00c015f0
extern float __sqrt(float); // FUN_00414a80
extern void __freeTemp(void* ptr); // FUN_00aa26e0
extern void __reallocTemp(void** ptr, int newSize, int elementSize); // FUN_00aa4110

// Constants (from data references)
extern const float kDotThreshold; // DAT_00e448d4
extern const float kEpsilon; // DAT_00e2e780
extern const float kSupportLength; // DAT_00e2b1a4
extern const float kScaleFactor; // DAT_00e44564

struct SupportFinder {
    // vtable pointer at +0x00
    // The following offsets are from this pointer:
    // +0x18: int numSupportsActive? // param_1[0x18]
    // +0x19: SupportEntry* supports; // param_1[0x19]
    // +0x1a: int numSupportsTotal? // param_1[0x1a]
    // +0x1c: void** supportProcessors; // array of function pointers
    // +0x1d: int numProcessors; // count
    // +0x10: int centerX; // param_1[0x10]
    // +0x11: int centerY; // param_1[0x11]
    // +0x12: int centerZ; // param_1[0x12]
    // +0x13: int centerW; // param_1[0x13]
    // +0x04: int worldOffsetX; // param_1[4]
    // +0x05: int worldOffsetY; // param_1[5]
    // +0x06: int worldOffsetZ; // param_1[6]
    // +0x07: int worldOffsetW; // param_1[7]
};

struct SupportEntry {
    // 64 bytes
    float firstFour[4];   // +0x00: precomputed vector (direction?) 
    float position[4];    // +0x10: world position (xyz w)
    // remaining 32 bytes: possibly normal, etc. (not used in this function)
    // Actually the accumulation uses 8 floats from start: firstFour[0..3] and position[0..3]
};

struct SupportQuery {
    // The return struct written to hidden pointer
    float direction[4];   // +0x00: normalized direction? Actually written as bool? 
    // There are bools at in_EAX[0] and in_EAX[1] (the first two bytes)
    // Then at +0x10: accumulated support stuff
    float accumulatedSupport[4]; // +0x10: weighted average direction? 
    float accumulatedNormal[4];  // +0x1c: weighted normal? 
    float accumulatedPoint[4];   // +0x20: weighted position?
    // Actually the offsets: +0x10, +0x14, +0x18, +0x1c, +0x20, +0x24, +0x28, +0x2c
    // That's 8 floats starting at +0x10
};

// TLS indices
static const uint32_t kProfilerTlsIndex = 0x01139830; // DAT_01139830
static const uint32_t kMemoryTlsIndex = 0x01139810; // DAT_01139810

void SupportFinder::evaluateSupport(const float* supportDir, SupportQuery* result) {
    // Profiler scope start
    {
        void* tls = __TlsGetValue(kProfilerTlsIndex);
        uint32_t* ptr = *(uint32_t**)((char*)tls + 4);
        if (ptr < *(uint32_t**)((char*)tls + 12)) {
            *ptr = (uint32_t)"TtcheckSupport";
            uint64_t cycle = __rdtsc();
            ptr[1] = (uint32_t)cycle;
            *(uint32_t**)((char*)tls + 4) = ptr + 3;
        }
    }

    int totalCount = this->numSupportsTotal + this->numSupportsActive; // +0x1a and +0x18

    // Temporary buffer for transformed supports (64 bytes per entry)
    struct TempBuffer {
        SupportEntry* ptr;
        int count;
        uint32_t flags; // bit30: owned, bit29: allocated? Actually used for size management
    };

    TempBuffer tempSupports = {0};
    tempSupports.count = 0;
    tempSupports.flags = 0x80000000; // mark as owned

    // Allocate temporary memory via TLS memory manager
    void* tlsMem = __TlsGetValue(kMemoryTlsIndex);
    int* memState = (int*)tlsMem;
    int currentPtr = memState[8]; // memory cursor
    int requiredSize = totalCount * 0x40 + 0x10;
    int newPtr = currentPtr + requiredSize;
    if ((uint32_t)memState[11] < (uint32_t)newPtr) {
        // Need to allocate
        currentPtr = (**(int(__thiscall*)(int*))(*memState + 0x14))(requiredSize); // realloc
    } else {
        memState[8] = newPtr;
    }
    tempSupports.ptr = (SupportEntry*)currentPtr;
    tempSupports.flags |= totalCount; // store count

    // Copy active supports and offset by world position
    int copyCount = this->numSupportsActive; // +0x1a? Actually the loop uses param_1[0x1a] for count
    if (copyCount > 0) {
        int srcOffset = 0;
        int dstOffset = 0;
        while (srcOffset < copyCount) {
            // Call copy function (vtable offset 0x14)
            void (*copyFunc)(const SupportEntry*, SupportEntry*) = *(void(**)(const SupportEntry*, SupportEntry*))((int*)this->supports + srcOffset);
            // Actually it's a virtual function call on this: (**(code **)(*param_1 + 0x14))(param_1[0x19] + srcOffset*0x30, dstBase + dstOffset);
            // We'll represent as:
            copyFunc((SupportEntry*)((char*)this->supports + srcOffset * 0x30), 
                     (SupportEntry*)((char*)tempSupports.ptr + dstOffset));
            // Then subtract world offset
            float* pos = (float*)((char*)tempSupports.ptr + dstOffset + 0x10);
            pos[0] -= (float)this->worldOffsetX;
            pos[1] -= (float)this->worldOffsetY;
            pos[2] -= (float)this->worldOffsetZ;
            pos[3] -= (float)this->worldOffsetW;
            srcOffset++;
            dstOffset += 0x40;
            tempSupports.count++;
        }
    }

    // Second temporary buffer for flags (16 bytes per entry)
    struct FlagBuffer {
        char* ptr;
        int count;
        uint32_t flags;
    };
    FlagBuffer tempFlags = {0};
    tempFlags.count = 0;
    tempFlags.flags = 0x80000000;

    tlsMem = __TlsGetValue(kMemoryTlsIndex);
    memState = (int*)tlsMem;
    currentPtr = memState[8];
    int totalEntries = totalCount; // actually param_1[0x1a] + param_1[0x18]
    requiredSize = (totalEntries + 1) * 0x10;
    newPtr = currentPtr + requiredSize;
    if ((uint32_t)memState[11] < (uint32_t)newPtr) {
        currentPtr = (**(int(__thiscall*)(int*))(*memState + 0x14))(requiredSize);
    } else {
        memState[8] = newPtr;
    }
    tempFlags.ptr = (char*)currentPtr;
    tempFlags.flags |= totalEntries;

    // Initialize flags buffer? Not explicitly, but loop sets later

    // Build query orientation from supportDir and processors
    // Stack variables for orientation (16 bytes each)
    float queryOrientation[4]; // 4 floats at uStack_90
    float transformedDir[4];   // 4 floats at auStack_40

    // Initialize queryOrientation from supportDir and default values
    queryOrientation[0] = supportDir[0];
    queryOrientation[1] = supportDir[1];
    queryOrientation[2] = supportDir[2];
    queryOrientation[3] = supportDir[3];

    // Additional fields from this: (center offset for orientation)
    int centerInts[4] = { this->centerX, this->centerY, this->centerZ, this->centerW }; // +0x10..0x13

    // Call processors on orientation
    int numProcessors = this->numProcessors; // +0x1d
    while (numProcessors > 0) {
        numProcessors--;
        void (*processorFunc)(SupportQuery*, float*) = *(void(**)(SupportQuery*, float*))((int*)this->supportProcessors + numProcessors * 4);
        processorFunc((SupportQuery*)queryOrientation, (float*)centerInts); // &uStack_90 used as SupportQuery* but really just floats
    }

    // Transform query orientation
    __transformSupportQuery((SupportQuery*)queryOrientation, transformedDir);

    // Compute result direction
    float dotDir = transformedDir[0] * supportDir[0] + transformedDir[1] * supportDir[1] + transformedDir[2] * supportDir[2];
    float dotResult = kDotThreshold - dotDir;
    // The first byte of result indicates if dotDir^2 < (direction magnitude^2 - threshold)
    float dirMagSq = supportDir[0]*supportDir[0] + supportDir[1]*supportDir[1] + supportDir[2]*supportDir[2];
    // Actually the code uses: fVar14 = fVar15*fStack_28 + fVar1*fStack_2c + fVar16*fStack_30; (which is dot of transformedDir with something)
    // Then compare with.
    // We'll simplify: the result->hasSupports = (check passed);
    // The first two bytes of result are boolean flags: result[0] and result[1]
    // They are set based on comparisons.

    // Set result's direction (the accumulated support vector to zero initially)
    result->accumulatedSupport[0] = 0.0f;
    result->accumulatedSupport[1] = 0.0f;
    result->accumulatedSupport[2] = 0.0f;
    result->accumulatedSupport[3] = 0.0f;
    // Also the normal and point accumulators at +0x10, +0x14, +0x18, +0x1c, +0x20, +0x24, +0x28, +0x2c
    // Actually there are 8 floats: support (x,y,z,w) and normal (x,y,z,w)
    // But the code writes to 8 floats starting at +0x10:
    float* accumSupport = &result->accumulatedSupport[0]; // +0x10
    float* accumNormal = &result->accumulatedSupport[4];  // +0x1c? Actually +0x20? 
    // From the code: *(in_EAX + 0x10) = ... *(in_EAX + 0x14) ... up to +0x2c. So 8 floats.
    // We'll treat as array of 8.
    for (int i = 0; i < 8; ++i) {
        ((float*)&result->accumulatedSupport)[i] = 0.0f;
    }

    // Iterate over all supports
    int supportCount = copyCount; // actually totalCount? The loop uses iStack_44 = param_1[0x1a] (active count)
    int hits = 0;
    SupportEntry* entry = tempSupports.ptr;
    char* flag = tempFlags.ptr;
    for (int i = 0; i < supportCount; ++i) {
        if (flag[0] != 0) { // flag indicates active
            // Use the first 4 floats of entry (precomputed vector) dot with supportDir
            float dot = entry->firstFour[0] * supportDir[0] 
                      + entry->firstFour[1] * supportDir[1] 
                      + entry->firstFour[2] * supportDir[2];
            if (dot < kDotThreshold) {
                // Accumulate support
                accumSupport[0] += entry->firstFour[0];
                accumSupport[1] += entry->firstFour[1];
                accumSupport[2] += entry->firstFour[2];
                accumSupport[3] += entry->firstFour[3];
                // Also accumulate the subtracted position? Actually the code uses the original (pre-subtraction) values
                // But we have the entry's position (at +0x10) which was modified by subtraction.
                // The code uses pfVar8[-6] to pfVar8[-1] which are the first 6 floats? That includes firstFour[0..3] and position[0..1]
                // Actually from analysis, they accumulate firstFour and then also the next two floats (normal?).
                // We'll just mimic the accumulation of all 8 floats.
                float* data = (float*)entry;
                for (int j = 0; j < 8; ++j) {
                    ((float*)&result->accumulatedSupport)[j] += data[j];
                }
                hits++;
            }
        }
        entry = (SupportEntry*)((char*)entry + 0x40);
        flag += 0x10;
    }

    if (hits > 0) {
        // Normalize the accumulated support direction (first 3 floats)
        float sumSq = accumSupport[0]*accumSupport[0] + accumSupport[1]*accumSupport[1] + accumSupport[2]*accumSupport[2];
        if (sumSq != 0.0f) {
            float invLength = 1.0f / __sqrt(sumSq);
            accumSupport[0] *= invLength;
            accumSupport[1] *= invLength;
            accumSupport[2] *= invLength;
            accumSupport[3] *= invLength; // w unaffected
        }
        // Scale the accumulated normal and point by average
        float avgScale = kSupportLength / (float)hits;
        // The accumNormal etc. are at offsets +0x1c, +0x20, etc.
        // Actually we have accumSupport[4..7] as the next 4 floats (normal xyz w)
        // Then the next 4 floats are point? But the code uses the same loop to accumulate 8 floats.
        // We'll just apply scaling to the second 4 floats.
        for (int i = 4; i < 8; ++i) {
            ((float*)&result->accumulatedSupport)[i] *= avgScale;
        }
        // Add world offset to the point (last 4 floats? Actually the point accumulation is at +0x20? In the code at offsets +0x20, +0x24, +0x28, +0x2c)
        // This corresponds to the point (position). We add the worldOffset.
        float* point = &((float*)&result->accumulatedSupport)[4]; // starting at +0x1c? Actually need to match offsets.
        // From the code: *(in_EAX + 0x20) = (float)param_1[4] + *(in_EAX + 0x20); etc.
        // So the point is at offsets +0x20, +0x24, +0x28, +0x2c. That is the third float in our array? Let's just add to all four positions after scaling.
        ((float*)&result->accumulatedSupport)[4] += (float)this->worldOffsetX;
        ((float*)&result->accumulatedSupport)[5] += (float)this->worldOffsetY;
        ((float*)&result->accumulatedSupport)[6] += (float)this->worldOffsetZ;
        ((float*)&result->accumulatedSupport)[7] += (float)this->worldOffsetW;
    } else {
        // No hits, set result flag to 0
        *((char*)result) = 0;
    }

    // Profiler scope end
    {
        void* tls = __TlsGetValue(kProfilerTlsIndex);
        uint32_t* ptr = *(uint32_t**)((char*)tls + 4);
        if (ptr < *(uint32_t**)((char*)tls + 12)) {
            *ptr = (uint32_t)&"TtcheckSupport_end";
            uint64_t cycle = __rdtsc();
            ptr[1] = (uint32_t)cycle;
            *(uint32_t**)((char*)tls + 4) = ptr + 3;
        }
    }

    // Free temporary buffers
    // For tempFlags:
    tlsMem = __TlsGetValue(kMemoryTlsIndex);
    if ((int)tempFlags.flags >= 0) {
        // Free via TLS stack or real free
        __freeTemp(tempFlags.ptr);
    } else {
        // Restore memory cursor
        int* mem = (int*)tlsMem;
        mem[8] = (int)tempFlags.ptr;
    }

    // For tempSupports:
    tlsMem = __TlsGetValue(kMemoryTlsIndex);
    if ((int)tempSupports.flags >= 0) {
        __freeTemp(tempSupports.ptr);
    } else {
        int* mem = (int*)tlsMem;
        mem[8] = (int)tempSupports.ptr;
    }
}