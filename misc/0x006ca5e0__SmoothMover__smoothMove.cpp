// FUNC_NAME: SmoothMover::smoothMove
// Function address: 0x006ca5e0
// Role: Performs a smooth linear interpolation between two positions, clamped by a physics sweep test.
//       Returns the final interpolation factor used (range 0..1).

#include <cstdint>

// Forward declarations for the called functions (no body provided)
void FUN_009f1820(float* vec, int mode);  // Likely setLength(vec, 1) or normalize
bool FUN_009e7fd0(int physicsHandle, float* targetPos, void** something, int param); // Physics sweep / raycast

class SmoothMover {
public:
    // Offsets from this pointer:
    // +0x84 : Physics collision handle (int32)
    // +0x88 : Smoothing speed (float) – used as a factor to limit interpolation
    // Global variables:
    //   _DAT_00d5780c -> float g_maxStepSize (max distance per frame)
    //   _DAT_01223394 -> global flag structure at offset +0x54: g_usePhysicsCheck
    //   _DAT_00d5ef84 -> float g_unusedZero (0.0)
    //   _DAT_00e445dc -> float g_defaultSmoothFactor
    //   PTR_LAB_00d5f038 -> const char* g_debugLabel (e.g., "SmoothMove")

    float __thiscall smoothMove(const float* fromPos, const float* toPos, float* outPos);
};

float SmoothMover::smoothMove(const float* fromPos, const float* toPos, float* outPos)
{
    float fVar1;               // Final interpolation factor
    float local_80[4];         // Temp from vector (local copy)
    float local_70[4];         // Temp to vector (local copy)
    void* local_50;            // Temporary pointer (likely debug string)
    float local_4c;            // Equivalent to g_defaultSmoothFactor
    char local_48;             // Result flag from physics check (non-zero if collision)
    float local_24;            // Derived from physics sweep result
    struct {
        uint32 field_0x00;     // +0x00 (from offset 0x88 of this)
        uint32 field_0x04;     // +0x04 (0)
        uint32 field_0x08;     // +0x08 (0)
    } local_struct;            // Padding used by sweep function

    float g_maxStepSize = *(float*)0x00d5780c;              // Global: maximum allowed step distance
    bool  g_usePhysicsCheck = *(char*)(*(int*)0x01223394 + 0x54) != 0; // Global: enable physics sweep
    float g_defaultSmoothFactor = *(float*)0x00e445dc;      // Global: default smoothing fraction
    float g_unusedZero = *(float*)0x00d5ef84;               // Global: constant 0.0

    fVar1 = g_maxStepSize;

    if (!g_usePhysicsCheck) {
        // Copy fromPos
        local_80[0] = fromPos[0];
        local_80[1] = fromPos[1];
        local_80[2] = fromPos[2];
        local_80[3] = 0.0f; // w component

        // Normalize the "from" vector?  (second arg 0 might mean "set length to 1")
        FUN_009f1820(local_80, 0);

        // Copy toPos and prepare local struct for sweep
        local_70[0] = toPos[0];
        local_70[1] = toPos[1];
        local_70[2] = toPos[2];
        local_70[3] = 0.0f;

        // Build the struct from member data
        local_struct.field_0x00 = *(unsigned int*)((char*)this + 0x88); // Smoothing speed / factor
        local_struct.field_0x04 = 0;
        local_struct.field_0x08 = 0;

        // Unused local variables (likely part of a larger struct)
        // local_64 = 0; local_60 = g_unusedZero; local_5c = g_unusedZero;

        // Set the debug string pointer
        local_50 = (void**)&PTR_LAB_00d5f038;

        // Initialize local flag and smoothing factor from globals
        local_48 = '\0';
        local_24 = g_defaultSmoothFactor;
        local_4c  = g_defaultSmoothFactor;

        // Perform physics sweep: check if movement from local_80 to local_70 is valid.
        // Parameters:
        //   First: ((int*)(this+0x84))[4]  (physics handle offset by 0x10 bytes? possibly a physics shape)
        //   Second: pointer to local_70 (target position)
        //   Third: pointer to local_50 (debug label)
        //   Fourth: 0 (unused)
        // Returns true if collision detected, false otherwise.
        bool collision = FUN_009e7fd0(
            *(int*)((char*)this + 0x84) + 0x10, // Physics shape object
            &local_70,                           // Target position
            &local_50,                           // Unused output?
            0                                     // Flags
        );

        // If collision was detected, adjust interpolation factor
        if (local_48 != '\0') {
            if (0.0f < local_24) {
                fVar1 = local_24;
                if (g_maxStepSize <= local_24) {
                    fVar1 = g_maxStepSize;
                }
            }
            else {
                fVar1 = 0.0f;
            }
        }
    }

    // Final linear interpolation using the determined factor
    outPos[0] = (toPos[0] - fromPos[0]) * fVar1 + fromPos[0];
    outPos[1] = (toPos[1] - fromPos[1]) * fVar1 + fromPos[1];
    outPos[2] = (toPos[2] - fromPos[2]) * fVar1 + fromPos[2];

    return (float)fVar1;
}