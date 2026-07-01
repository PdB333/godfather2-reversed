// FUNC_NAME: Entity::updateWithGuard

// Function address: 0x009019f0
// Role: Conditional update wrapper with profiling markers (0xCC for event ID).
//       Checks if the entity is valid via IsEntityValid(); if so, calls the main update function.
//       Otherwise returns 1 (likely success in no-op case).

#include <cstdint>

// Forward declarations of internal functions (represented by known addresses)
void ProfileBegin(uint32_t eventId);    // FUN_005403e0
void ProfileEnd(uint32_t eventId);      // FUN_00540410
char IsEntityValid(Entity* entity);     // FUN_00903e60
byte EntityUpdateCore(Entity* entity, uint32_t param2, uint32_t param3); // FUN_004c2200

class Entity {
public:
    // +0x00 ... typical vtable pointer or fields
    // ... other members omitted

    // __thiscall method
    byte updateWithGuard(uint32_t param2, uint32_t param3);
};

byte Entity::updateWithGuard(uint32_t param2, uint32_t param3) {
    ProfileBegin(0xCC);  // start profiling event 0xCC

    byte returnVal = 1;  // default: return success (non-zero)
    char isValid = IsEntityValid(this);
    if (isValid != 0) {
        returnVal = EntityUpdateCore(this, param2, param3);
    }

    ProfileEnd(0xCC);    // end profiling event 0xCC
    return returnVal;
}