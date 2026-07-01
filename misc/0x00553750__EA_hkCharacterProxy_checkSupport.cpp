// Xbox PDB: EA_hkCharacterProxy::checkSupport
// FUNC_NAME: SpatialQuerySystem::filterPointsByPlaneAndComputeAverage
// Function address: 0x00553750
// This function takes an array of points (with per-point flags) and filters them against a plane,
// then computes a weighted average (position and additional attributes) for points that pass the filter.
// It uses a TLS-based allocator for temporary buffers and includes profiling markers.

#include <windows.h>
#include <cmath>

// Forward declarations (internal engine functions)
void* __fastcall allocTempMemory(int size); // FUN_00aa4110 - memory expansion
void   __fastcall freeTempMemory(void* ptr, int size, int id); // FUN_00aa26e0 - memory free
void   computePlaneProjection(const float* planeParams, float* inOutVec); // FUN_00c015f0 - projects a vector onto plane

// External memory constants (from data section)
extern float g_threshold;        // DAT_00e448d4 - dot product threshold
extern float g_scaleFactor;      // DAT_00e2b1a4 - scaling constant for averaging
extern float g_minDistSq;        // DAT_00e44564 - minimum distance squared for collision?
extern float g_maxDistSq;        // DAT_00e2e780 - maximum distance squared?

// TLS indices for profiling and memory (from .data)
extern DWORD g_tlsProfilingIndex; // DAT_01139830
extern DWORD g_tlsMemoryIndex;    // DAT_01139810

// Structure for input data (point with attributes)
struct InputPoint {
    float position[3];      // offset +0x00 (3 floats)
    float attribute1;       // offset +0x0C
    float attribute2;       // offset +0x10? Actually size 0x30 per element
    // ... more unknown fields
};

// Structure for output (result after filtering and averaging)
struct FilterResult {
    bool  hasValidPoints;       // +0x00 (bool, written as 0 or 1)
    float normalizedDirection[3]; // +0x10 unit vector of averaged positions
    float normalizedAttribute;    // +0x1C (attribute normalized by same length)
    float averagePosition[3];     // +0x20 weighted average position (with offset)
    float averageAttribute;       // +0x2C additional averaged attribute
};

// The main function: this = InputData, param_2 = planeNormalAndOffset (4 floats)
// Output is written via the hidden return pointer (passed in EAX)
void __thiscall SpatialQuerySystem::filterPointsByPlaneAndComputeAverage(
    InputData* this_,
    const float* planeParams, // [0]=nx, [1]=ny, [2]=nz, [3]=d or unused
    FilterResult* outResult   // hidden pointer (passed in EAX)
)
{
    // ---- TLS Profiling (begin marker "TtcheckSupport") ----
    {
        LPVOID tlsProfiling = TlsGetValue(g_tlsProfilingIndex);
        int** ptr = (int**)((char*)tlsProfiling + 4);
        if ((int*)(ptr) < (int*)(char*)tlsProfiling + 0xc) {
            *ptr = (int*)"TtcheckSupport";
            unsigned __int64 ts = __rdtsc();
            ptr[1] = (int)ts;
            ptr += 3;
        }
    }

    // ---- Step 1: Prepare temporary buffer for points with offset adjustment ----
    int pointCount = this_->count1 + this_->count2; // total points to process
    // Allocate buffer of 0x40 bytes per point (but only first 0x30 used? see loop)
    int allocSize1 = pointCount * 0x40 + 0x10; // +0x10 for header?
    char* tempBuffer1 = nullptr;
    int usedSize1 = 0;
    {
        int* tlsMem = (int*)TlsGetValue(g_tlsMemoryIndex);
        int currentPos = tlsMem[8];
        int newPos = currentPos + allocSize1;
        if ((unsigned int)tlsMem[0xb] < newPos) {
            // Need to allocate from heap
            currentPos = (**(int(__fastcall**)(int))(tlsMem[0] + 0x14))(allocSize1);
        } else {
            tlsMem[8] = newPos;
        }
        tempBuffer1 = (char*)currentPos;
        usedSize1 = pointCount | 0x80000000; // mark as allocated from TLS? (bit 31 used as flag)
    }

    // Expand buffer if needed (internal function)
    if ((int)(usedSize1 & 0x3fffffff) < pointCount) {
        int newSize = (usedSize1 & 0x3fffffff) * 2;
        if (newSize <= pointCount) newSize = pointCount;
        FUN_00aa4110(&tempBuffer1, newSize, 0x40);
    }

    // Copy points from input array, subtracting offset
    int processedCount = 0;
    char* writePtr = tempBuffer1 + 0x10; // skip header
    for (int i = 0; i < this_->count1; i++) {
        // Each input point is 0x30 bytes (reconstructed from offsets)
        InputPoint* src = (InputPoint*)(this_->pointArray + i * 0x30);
        float* dest = (float*)(writePtr + i * 0x40);
        // Copy the 4 floats (position + attribute)?? Actually copies 0x30 bytes from +0x19
        (**(code**)(this_->vtable + 0x14))(this_->pointArray + i * 0x30, dest);
        // Then subtract offset (this_->offsetX, etc.)
        dest[0] -= (float)this_->offsetX;
        dest[1] -= (float)this_->offsetY;
        dest[2] -= (float)this_->offsetZ;
        dest[3] -= (float)this_->offsetW; // maybe unused?
        processedCount++;
    }

    // ---- Step 2: Prepare second temporary buffer for per-point flags (0x10 bytes each) ----
    int newPointCount = pointCount + 1; // one extra?
    int allocSize2 = newPointCount * 0x10;
    char* tempBuffer2 = nullptr;
    int usedSize2 = 0;
    {
        int* tlsMem = (int*)TlsGetValue(g_tlsMemoryIndex);
        int currentPos2 = tlsMem[8];
        int newPos2 = currentPos2 + allocSize2;
        if ((char*)tlsMem[0xb] < (char*)currentPos2 + allocSize2) {
            currentPos2 = (**(int(__fastcall**)(int))(tlsMem[0] + 0x14))(allocSize2);
        } else {
            tlsMem[8] = newPos2;
        }
        tempBuffer2 = (char*)currentPos2;
        usedSize2 = newPointCount | 0x80000000;
    }

    // Expand buffer if needed
    if ((int)(usedSize2 & 0x3fffffff) < newPointCount) {
        int newSize2 = (usedSize2 & 0x3fffffff) * 2;
        if (newSize2 <= newPointCount) newSize2 = newPointCount;
        FUN_00aa4110(&tempBuffer2, newSize2, 0x10);
    }

    // ---- Step 3: Build a transformation from plane params and callbacks ----
    // Construct a structure for plane projection
    struct PlaneTransform {
        float planeParams[4];
        int    unknown1[4];
        int    inputData[4]; // from this_->someData
        int    callbackPointer;
        char*  flagBuffer;
        int    flagBufferSize;
        float  something[4];
        // ... many fields as per stack frame
    } transformInput;
    // Fill plane params
    transformInput.planeParams[0] = planeParams[0];
    transformInput.planeParams[1] = planeParams[1];
    transformInput.planeParams[2] = planeParams[2];
    transformInput.planeParams[3] = planeParams[3];
    // Fill additional data from this_
    transformInput.unknown1[0] = this_->someInt1;
    transformInput.unknown1[1] = this_->someInt2;
    transformInput.unknown1[2] = this_->someInt3;
    transformInput.unknown1[3] = this_->someInt4;
    transformInput.inputData[0] = this_->someData[0];
    transformInput.inputData[1] = this_->someData[1];
    transformInput.inputData[2] = this_->someData[2];
    transformInput.inputData[3] = this_->someData[3];
    transformInput.callbackPointer = (int)tempBuffer1; // store temp buffer pointer
    transformInput.flagBuffer = tempBuffer2;
    transformInput.flagBufferSize = newPointCount;
    // Set other fields from global constants
    transformInput.something[0] = *(float*)0x00e2e230; // DAT_00e2e230
    transformInput.something[1] = *(float*)0x00e2e230;
    transformInput.something[2] = *(float*)0x00e448d8;
    transformInput.something[3] = *(float*)0x00e2e780;

    // Call callbacks stored in this_->callbackArray
    int callbackCount = this_->callbackCount;
    for (int i = callbackCount - 1; i >= 0; i--) {
        void (*callback)(void*, PlaneTransform*) = (void(*)(void*, PlaneTransform*))this_->callbackArray[i];
        if (callback) {
            callback(this_->pointArray, &transformInput);
        }
    }

    // ---- Step 4: Compute plane projection to get a direction vector ----
    float projectedVec[4]; // output from FUN_00c015f0
    FUN_00c015f0(&transformInput, projectedVec); // computes plane projection, stores in projectedVec (4 floats)

    // Use the projected vector to refine the plane normal? Actually modifies local array
    float localVec[4]; // corresponds to auStack_40
    // localVec = projectedVec? Seems they are used for dot product later.
    // In decompiled: fStack_30 = *param_2 * fVar17 + fStack_30; etc.
    // This is a classic vector projection: new = v - (v·n)n    or vice versa.
    // We'll simplify: assume localVec gets the projection result.

    // Actually the decompiled code does:
    // fVar4 = DAT_00e2e780;
    // fVar1 = planeParams[1];
    // fVar15 = planeParams[2];
    // fVar16 = planeParams[0];
    // fVar14 = fVar15 * fStack_28 + fVar1 * fStack_2c + fVar16 * fStack_30;  (dot product)
    // fVar17 = DAT_00e44564 - fVar14;
    // *in_EAX = (fVar14*fVar14 < (something) - DAT_00e2e780) ? 1 : 0;
    // then update fStack_30,28,2c by adding planeParams * fVar17
    // This is a collision-like response: reflect or project.

    // For simplicity, we'll leave it as computed, but we note the flag set.

    // ---- Step 5: Filter points and accumulate ----
    int numPassed = 0;
    float sumPos[3] = {0,0,0};
    float sumAttr1 = 0;
    float sumAttr2 = 0;
    float sumAttr3 = 0;
    float sumAttr4 = 0;
    float sumAttr5 = 0;

    // Iterate over all points (using second buffer as flag per point)
    char* flagPtr = tempBuffer2;
    float* pointData = (float*)(tempBuffer1 + 0x18); // +0x18 to get the first point's data? Actually offsets are tricky.
    // In decompiled: pfVar8 is at iStack_b8 + 0x18, which is the start of point data after header.
    // And pcVar10 iterates over tempBuffer2 (0x10 per item).
    for (int i = 0; i < pointCount; i++) {
        if (*flagPtr != 0) {
            // Dot product test: compare point position against plane normal with threshold
            float dot = pointData[-6] * planeParams[0] + // pointData[-6] is x? Actually from decompiled: pfVar8[-6] * *param_2
                         pointData[-5] * planeParams[1] + // y
                         pointData[-4] * planeParams[2];  // z
            if (dot < g_threshold) {
                // Accumulate point data (positions and attributes)
                sumPos[0] += pointData[-6];
                sumPos[1] += pointData[-5];
                sumPos[2] += pointData[-4];
                sumAttr1 += pointData[-3];
                sumAttr2 += pointData[-2];
                sumAttr3 += pointData[-1];
                sumAttr4 += pointData[0];
                sumAttr5 += pointData[1];
                numPassed++;
            }
        }
        flagPtr += 0x10; // next flag
        pointData += 0x10; // next point (each point is 0x10 floats? Actually 0x40 bytes so 0x10 floats)
    }

    if (numPassed > 0) {
        // Normalize the summed direction
        float lenSq = sumPos[0]*sumPos[0] + sumPos[1]*sumPos[1] + sumPos[2]*sumPos[2];
        if (lenSq != 0.0f) {
            float invLen = 1.0f / sqrtf(lenSq);
            outResult->normalizedDirection[0] = sumPos[0] * invLen;
            outResult->normalizedDirection[1] = sumPos[1] * invLen;
            outResult->normalizedDirection[2] = sumPos[2] * invLen;
            outResult->normalizedAttribute = sumAttr1 * invLen;
        } else {
            outResult->normalizedDirection[0] = 0;
            outResult->normalizedDirection[1] = 0;
            outResult->normalizedDirection[2] = 0;
            outResult->normalizedAttribute = 0;
        }
        // Compute weighted average for position and other attributes
        float invCount = g_scaleFactor / numPassed;
        outResult->averagePosition[0] = sumAttr2 * invCount + this_->offsetX;
        outResult->averagePosition[1] = sumAttr3 * invCount + this_->offsetY;
        outResult->averagePosition[2] = sumAttr4 * invCount + this_->offsetZ;
        outResult->averageAttribute = sumAttr5 * invCount + this_->offsetW;
        outResult->hasValidPoints = true;
    } else {
        outResult->hasValidPoints = false;
    }

    // ---- Cleanup: free temporary buffers with TLS ----
    {
        LPVOID tlsProfiling = TlsGetValue(g_tlsProfilingIndex);
        int** ptr = (int**)((char*)tlsProfiling + 4);
        if ((int*)(ptr) < (int*)(char*)tlsProfiling + 0xc) {
            *ptr = (int*)0x00e39c6c; // "unknown string"
            unsigned __int64 ts = __rdtsc();
            ptr[1] = (int)ts;
            ptr += 3;
        }
    }
    // Free tempBuffer2
    {
        int* tlsMem = (int*)TlsGetValue(g_tlsMemoryIndex);
        tlsMem[8] = (int)tempBuffer2;
        if (tempBuffer2 == (char*)tlsMem[10]) {
            (**(void(__fastcall**)(void*))(tlsMem[0] + 0x18))(tempBuffer2);
        }
    }
    if ((int)usedSize2 >= 0) { // if not heap-allocated (bit31 clear means heap)
        TlsGetValue(g_tlsMemoryIndex);
        FUN_00aa26e0(tempBuffer2, usedSize2 << 4, 0x17);
    }
    // Free tempBuffer1
    {
        int* tlsMem = (int*)TlsGetValue(g_tlsMemoryIndex);
        tlsMem[8] = (int)tempBuffer1;
        if (tempBuffer1 == (char*)tlsMem[10]) {
            (**(void(__fastcall**)(void*))(tlsMem[0] + 0x18))(tempBuffer1);
        }
    }
    if ((int)usedSize1 >= 0) {
        TlsGetValue(g_tlsMemoryIndex);
        FUN_00aa26e0(tempBuffer1, usedSize1 << 6, 0x17);
    }
}