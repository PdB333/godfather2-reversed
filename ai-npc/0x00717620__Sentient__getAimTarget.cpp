// FUNC_NAME: Sentient::getAimTarget
// Address: 0x00717620
// Role: Determines aim target position and optionally distance. Returns true if a valid target exists.
// Uses member field at +0x338 (likely m_targetType enum). If 0 -> no target, if 0x48 (72) -> fallback to stored target.

#include <cstdint>

// Forward declares for unknown functions (assumed globals or free functions)
bool __stdcall FUN_007ff880(); // Maybe check if system is ready
int __thiscall FUN_00471610(); // Likely returns a pointer to some global state (e.g., SimulationManager)
bool __thiscall FUN_00874e60(void* param, void* outPosition, float* outSomething); // Raycast or line test
float __thiscall FUN_0046fd30(const float* vec); // Vector length (2 or 3 components)
float __stdcall FUN_00733f60(); // Get some value (maybe time or random)
float __stdcall FUN_00733fc0(); // Get some value (maybe time or random)

// Helper: output parameter resembles a 3-component vector stored in undefined8 + one undefined4
struct Vec3 { float x, y, z; };

bool __thiscall Sentient::getAimTarget(Vec3* outPosition, float* outDistance, float* outParam4)
{
    int targetType = *(int*)((uint8_t*)this + 0x338); // e.g., m_targetType

    if (targetType == 0)
        return false;

    if (targetType != 0x48) // Not a specific target type (e.g., not a stored target)
    {
        // Attempt to compute target from environment
        if (FUN_007ff880() != 0)
        {
            int iVar2 = FUN_00471610();
            iVar2 += 0x30; // Probably offset to some sub-object

            void* param = (void*)iVar2;
            bool hit = FUN_00874e60(param, outPosition, outParam4);

            if (outDistance != nullptr)
            {
                float len = FUN_0046fd30((float*)outPosition);
                *outDistance = len;
            }

            if (hit)
                return true;
        }

        // Fallback: use stored default values
        if (outParam4 != nullptr)
        {
            float val = FUN_00733f60(); // e.g., squared distance or angle
            *outParam4 = val * val;
        }
        if (outDistance != nullptr)
        {
            float val = FUN_00733fc0(); // e.g., some scalar
            *outDistance = val;
        }

        // Copy from stored target at global offset
        int base = FUN_00471610();
        uint8_t* src = (uint8_t*)(base + 0x30);
        // Assuming outPosition is 12 bytes (Vec3)
        outPosition->x = *(float*)(src + 0);
        outPosition->y = *(float*)(src + 4);
        outPosition->z = *(float*)(src + 8);
        // Also copy the fourth float if needed (param_2+1 is undefined4)
        // The original code writes *(undefined4*)(param_2+1) which would be offset 8 in 16-byte structure
        // But since outPosition is Vec3 (12 bytes), we ignore the extra word for clarity.
        return true;
    }

    return false;
}