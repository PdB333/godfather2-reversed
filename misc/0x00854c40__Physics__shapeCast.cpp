// FUNC_NAME: Physics::shapeCast

#include <cstdint>

// Forward declarations for internal functions
void InternalCastShape(uint32_t* outResult, int32_t collWorld, float* inputArray, int32_t maxHits, int32_t filter, uint32_t* outExtended);
void* __cdecl operator new(size_t size, size_t alignment, const char* file, int line); // approximated
void ShapeCastResult_ctor(void* thisPtr);

// Global sentinel value used to mark invalid/initialized fields
extern int32_t g_sentinelValue; // _DAT_00d5780c

// Vtable address for ShapeCastResult class
extern void* g_ShapeCastResultVtable; // PTR_LAB_00d75130

// Size of ShapeCastResult (0x40 bytes)
struct ShapeCastResult {
    void* vtable;                // +0x00
    int32_t field_04;            // +0x04 (unused/zero)
    int32_t field_08;            // +0x08
    int32_t field_0C;            // +0x0C
    // The following fields are filled from parameters
    float hitPointX;             // +0x10 (from param_2 first word)
    float hitPointY;             // +0x14 (from param_2 second word)
    float hitPointZ;             // +0x18 (from param_2 third word)
    int32_t sentinel1;           // +0x1C (always g_sentinelValue)
    float hitNormalX;            // +0x20 (from param_6 first word)
    float hitNormalY;            // +0x24 (from param_6 second word)
    float hitNormalZ;            // +0x28 (from param_6 third word)
    int32_t sentinel2;           // +0x2C (always g_sentinelValue)
    int32_t sentinel3;           // +0x30 (always g_sentinelValue)
    int32_t sentinel4;           // +0x34 (always g_sentinelValue)
    int32_t sentinel5;           // +0x38 (always g_sentinelValue)
    int32_t sentinel6;           // +0x3C (always g_sentinelValue)
};

// Main function: performs a shape cast (ray/volume sweep)
void Physics::shapeCast(
    int32_t collisionWorld,      // param_1: context/handle to collision world
    uint64_t param2[2],          // param_2: pointer to two 8-byte values (e.g., start point + direction)
    uint64_t param3[2],          // param_3: additional geometry data
    uint64_t param4[2],          // param_4: additional geometry data
    uint64_t param5[2],          // param_5: additional geometry data
    int32_t param6[3]            // param_6: additional parameters (e.g., filter info)
) {
    uint32_t outResult[3];       // local_a8: used to return status and pointer
    int32_t dummy = 0;           // local_a8[1] initializer

    // Extract 32-bit words from the 64-bit parameters
    // param3: low and high parts of first eight bytes, then next eight bytes low part
    uint64_t uVar3 = param3[0];
    int32_t p3_low = *(int32_t*)&param3[1]; // low word of second eight bytes (offset 8)
    uint64_t uVar4 = param4[0];
    int32_t p4_low = *(int32_t*)&param4[1]; // low word of second eight bytes (offset 8)
    int32_t p5_low = *(int32_t*)&param5[1]; // low word of second eight bytes (offset 8)
    uint64_t uVar5 = param5[0];
    uint64_t uVar6 = param2[0];
    int32_t p2_low = *(int32_t*)&param2[1]; // low word of second eight bytes (offset 8)

    // Build a 16-word array (local_50..local_14) by combining extracted components
    // This array is passed to the low-level cast function
    float local_50, local_4c, local_48, local_44;
    float local_40, local_3c, local_38, local_34;
    float local_30, local_2c, local_28, local_24;
    float local_20, local_1c, local_18, local_14;

    local_50 = *(float*)&uVar4;              // low word of param4[0]
    local_4c = *((float*)&uVar4 + 1);       // high word of param4[0]
    local_48 = *(float*)&p4_low;            // low word of param4[1] (actually p4_low is a 32-bit value)
    local_44 = 0.0f;
    local_40 = *(float*)&uVar5;              // low word of param5[0]
    local_3c = *((float*)&uVar5 + 1);       // high word of param5[0]
    local_38 = *(float*)&p5_low;            // low word of param5[1]
    local_34 = 0.0f;
    local_30 = *(float*)&uVar6;              // low word of param2[0]
    local_2c = *((float*)&uVar6 + 1);       // high word of param2[0]
    local_28 = *(float*)&p2_low;            // low word of param2[1]
    local_24 = 0.0f;
    local_20 = *(float*)&uVar3;              // low word of param3[0]
    local_1c = *((float*)&uVar3 + 1);       // high word of param3[0]
    local_18 = *(float*)&p3_low;            // low word of param3[1]
    local_14 = *(float*)&g_sentinelValue;   // always sentinel value

    // Additional fields
    outResult[1] = 0;                        // clear second word
    // Actually store original 64-bit values for later use (but they are not used further)
    // (The code reassigns local_90 etc. but they are overwritten, not needed)
    // We skip the redundant re-extraction.

    // Perform the low-level collision cast
    InternalCastShape(outResult, collisionWorld, &local_50, 0x1ff, 0, &outResult[1]);

    if (outResult[0] != 0) {
        // Allocate a ShapeCastResult object (size 0x40, alignment 0x10)
        ShapeCastResult* result = (ShapeCastResult*)operator new(0x40, 0x10, __FILE__, __LINE__);
        outResult[2] = g_sentinelValue; // set sentinel at index 2 (not used?)

        if (result != nullptr) {
            // Initialize the result object (simplified: call constructor)
            result->vtable = &g_ShapeCastResultVtable;
            result->field_04 = 0;
            result->field_08 = 0;
            result->field_0C = 0;
            // Fill hit point from param_2 (first three 32-bit words)
            result->hitPointX = *(float*)&param2[0];           // first word of first 8-byte
            result->hitPointY = *((float*)&param2[0] + 1);     // second word of first 8-byte
            result->hitPointZ = *(float*)&param2[1];           // first word of second 8-byte
            result->sentinel1 = g_sentinelValue;

            // Fill hit normal from param_6 (three 32-bit values)
            result->hitNormalX = *(float*)&param6[0];
            result->hitNormalY = *(float*)&param6[1];
            result->hitNormalZ = *(float*)&param6[2];
            result->sentinel2 = g_sentinelValue;

            // Fill remaining sentinels
            result->sentinel3 = g_sentinelValue;
            result->sentinel4 = g_sentinelValue;
            result->sentinel5 = g_sentinelValue;
            result->sentinel6 = g_sentinelValue;

            // Call the initialization/constructor function on the result
            ShapeCastResult_ctor(result);
        }

        if (outResult[0] != 0) {
            // Clear a field in the output structure (possibly a linked list or reference)
            *(int32_t*)(outResult[0] + 8) = 0;
        }
    }
    return;
}