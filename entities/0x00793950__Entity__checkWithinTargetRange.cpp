// FUNC_NAME: Entity::checkWithinTargetRange
// Address: 0x00793950
// Checks if this entity is within a certain range of the target returned by FUN_00471610.
// Uses scaling factor param_2 (scale) multiplied with field at +0xCD to get radius.
// Also checks bit5 of field at +0xAF and virtual function at vtable+0x158.

#include <cstdint>

struct Vector3 {
    float x, y, z;
};

class Entity {
public:
    // vtable+0x48: GetPosition
    virtual void getPosition(Vector3* out) = 0;
    // vtable+0x158: Check condition (returns char, 0 means condition met)
    virtual char checkCondition() = 0;

    // +0xAF: flags (uint32)
    // +0xCD: radius multiplier (float)

    // param_2: scaling factor for radius
    bool checkWithinTargetRange(float scale) {
        // Check that bit5 of flags is clear and checkCondition returns 0
        uint32_t flags = *(uint32_t*)((uint8_t*)this + 0xAF);
        if (((~(flags >> 5) & 1) != 0) && (checkCondition() == 0)) {
            Vector3 localPos;
            getPosition(&localPos);

            // Get target object from FUN_00471610 (likely returns pointer to some entity)
            int targetObj = FUN_00471610();
            // Target position: x at +0x30, y at +0x34, z at +0x38 (assumed)
            float targetX = *(float*)(targetObj + 0x30);
            float targetY = *(float*)(targetObj + 0x34);
            float targetZ = *(float*)(targetObj + 0x38);

            float dx = localPos.x - targetX;
            float dy = localPos.y - targetY;
            float dz = localPos.z - targetZ;

            float radius = *(float*)((uint8_t*)this + 0xCD) * scale;
            return (dx*dx + dy*dy + dz*dz) < (radius * radius);
        }
        return false;
    }
};