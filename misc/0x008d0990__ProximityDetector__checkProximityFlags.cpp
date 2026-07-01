// FUNC_NAME: ProximityDetector::checkProximityFlags
// Function at 0x008d0990 checks distance between two 3D positions and sets flags based on proximity thresholds.
// Returns the output byte pointer with flags set.
// Class fields:
//   +0x70 float outerRadius (if distance >= outer, set bit 0)
//   +0x74 float innerRadius (if distance <= inner, set bit 1)
//   +0x88 int mode (selects source position: if 0 or 0x48, use local offset +0x64; else use global camera/player? via FUN_00471610)
//   +0x64 Vector3? (3 floats: x,y,z at +0x64, +0x68, +0x6C) - only used in certain modes

#include <cstdint>

// Forward declaration for the global function returning a pointer to some object with a position at +0x30 (Vector3) and maybe something at +0x38/0x3C? Actually it's 3 floats at +0x30, +0x34, +0x38.
struct GlobalObject; // dummy
GlobalObject* __fastcall getGlobalObject(); // FUN_00471610

// Class representing a proximity check object
class ProximityDetector {
public:
    uint8_t* checkProximityFlags(uint8_t* outFlags); // __thiscall

private:
    // Unknown data, offsets known:
    // 0x70: float outerRadius
    // 0x74: float innerRadius
    // 0x88: int mode (0, 0x48, or other)
    // 0x64: Vector3 localPosition (3 floats)
};

uint8_t* ProximityDetector::checkProximityFlags(uint8_t* outFlags)
{
    // Get global status pointer (likely a game instance)
    int* globalPtr = *(int**)(0x012233a0 + 4); // DAT_012233a0 + 4
    int someStatus = (globalPtr != nullptr) ? *globalPtr : 0;

    *outFlags = 0;

    // Check if global is valid and not in a special state (0x1f30)
    if (someStatus != 0 && someStatus != 0x1f30)
    {
        // Get source position pointer from global object (likely camera or player)
        GlobalObject* sourceObj = getGlobalObject(); // FUN_00471610()
        // Extract source vector components
        // Note: The original code loads 8 bytes as uint64 and splits into two floats,
        // then loads a third float from offset +0x38. This corresponds to Vector3 at +0x30.
        float srcX = *(float*)((uint8_t*)sourceObj + 0x30);
        float srcY = *(float*)((uint8_t*)sourceObj + 0x34);
        float srcZ = *(float*)((uint8_t*)sourceObj + 0x38);

        // Choose target position based on mode
        float targetX, targetY, targetZ;
        int mode = *(int*)((uint8_t*)this + 0x88);
        if (mode == 0 || mode == 0x48)
        {
            // Use local position stored in this object at offset 100 (0x64)
            targetX = *(float*)((uint8_t*)this + 0x64);
            targetY = *(float*)((uint8_t*)this + 0x68);
            targetZ = *(float*)((uint8_t*)this + 0x6C);
        }
        else
        {
            // Use the same source position (gets pointer from global object again)
            // In original code, both else-if and else do the same thing:
            // load again from sourceObj (the same).
            GlobalObject* obj = getGlobalObject();
            targetX = *(float*)((uint8_t*)obj + 0x30);
            targetY = *(float*)((uint8_t*)obj + 0x34);
            targetZ = *(float*)((uint8_t*)obj + 0x38);
        }

        // Compute squared distance
        float dx = srcX - targetX;
        float dy = srcY - targetY;
        float dz = srcZ - targetZ;
        float distSq = dx*dx + dy*dy + dz*dz;

        // Check against thresholds
        float outerSq = *(float*)((uint8_t*)this + 0x70); // outerRadius^2? Actually original compares against the square directly? Wait original stores float at +0x70, and comparison is <= fVar4 (distSq). So +0x70 is squared outer radius.
        if (outerSq <= distSq)
        {
            *outFlags |= 1; // bit 0: distance >= outer
        }

        float innerSq = *(float*)((uint8_t*)this + 0x74);
        if (distSq <= innerSq)
        {
            *outFlags |= 2; // bit 1: distance <= inner
            return outFlags; // early return? original returns after setting bit 1? Actually it has return param_2; after setting bit 1, but not after bit 0 only. The original returns param_2 unconditionally at end if condition not met, but if bit 1 set, it returns early. That matches: if inner condition met, no need to continue? But the original code: after setting bit 1, it does "return param_2;" so it returns. The bit 0 is not set if inner condition met? Wait, the code sets bit 0 first, then checks inner. If inner condition true, it sets bit 1 and returns immediately, so bit 0 may have been set earlier. That is correct: both bits can be set, but if inner condition true, it returns after setting bit 1, but bit 0 may have been set. So the early return only stops further checks.
        }
    }

    return outFlags;
}