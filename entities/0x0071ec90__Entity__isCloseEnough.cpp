// FUNC_NAME: Entity::isCloseEnough
// Address: 0x0071ec90
// Role: Check if a target distance (param_2 + global epsilon) is less than the object's range (0x40 - 0x4c).
// The object has two float fields: +0x40 (likely position or radius), +0x4c (likely another position or offset).
// Global float at 0x00e44598 is a proximity fudge factor.

// Global float for range adjustment
extern float g_proximityEpsilon; // 0x00e44598

class Entity {
public:
    // Returns 1 if the given distance (param_2) plus the global epsilon is within the object's range.
    // The range is computed as (field_0x40 - field_0x4c).
    // +0x40: float (e.g., max range or position)
    // +0x4c: float (e.g., min range or offset)
    int __thiscall isCloseEnough(float targetDistance) {
        // Example: if (targetDistance + g_proximityEpsilon < maxRange - minRange)
        if (targetDistance + g_proximityEpsilon < *(float*)(this + 0x40) - *(float*)(this + 0x4c)) {
            return 1;
        }
        return 0;
    }
};