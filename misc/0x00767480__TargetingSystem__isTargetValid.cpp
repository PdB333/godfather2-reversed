// FUNC_NAME: TargetingSystem::isTargetValid
// Address: 0x00767480
// Returns 1 if target is within valid detection range, considering a special flag and two distance thresholds.
// The function checks a bit in a game option (param_1+0x5c->0x8e0 bit 1). If that bit is not set, returns 0.
// Otherwise, evaluates target's flag at param_2+0x88 bit 0 and compares squared distance to two global constants.

#include <cstdint>

// Forward declaration of a function that returns a pointer to a structure with position data.
// The returned struct is assumed to have float x,y,z at offsets +0x30, +0x34, +0x38.
struct PositionData {
    float x; // +0x30
    float y; // +0x34
    float z; // +0x38
};

// Global distance thresholds (squared) used in the check.
extern float g_autoAimRangeSquared1; // DAT_00d65998
extern float g_autoAimRangeSquared2; // DAT_00d65994

// External function that returns a pointer to the player's (or camera's) position.
PositionData* getPlayerPosition(); // FUN_00471610

// Struct representing the target entity (partial view).
struct TargetEntity {
    float positionX; // +0x44
    float positionY; // +0x48
    float positionZ; // +0x4c
    uint8_t flags;   // +0x88 (bit0 used)
};

// Class containing the game options or state at param_1+0x5c.
// Offsets derived from the decompilation.
struct GameConfig {
    // ... other fields ...
    uint32_t unknownAt0x8e0; // +0x8e0 in some structure reachable from this+0x5c
};

// The this pointer (param_1) points to an object that contains a pointer to GameConfig.
struct TargetingSystem {
    GameConfig* config; // +0x5c
};

// The function implementation.
uint32_t __thiscall TargetingSystem::isTargetValid(TargetEntity* target) {
    // Get player position
    PositionData* playerPos = getPlayerPosition();

    // Calculate delta from player to target
    float deltaX = playerPos->x - target->positionX;
    float deltaY = playerPos->y - target->positionY;
    float deltaZ = playerPos->z - target->positionZ;

    // Squared distance
    float distanceSquared = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

    // Check the game option bit (bit 1 of the flag at config->unknownAt0x8e0)
    uint32_t optionFlag = config->unknownAt0x8e0;
    if ((optionFlag >> 1 & 1) == 0) {
        // Option disabled: always return false
        return 0;
    }

    // Check target's own flag (bit 0 of target->flags)
    bool targetFlag = (target->flags & 1) != 0;

    // Determine result based on target flag and distance thresholds
    // The condition from the decompiled code:
    // if ( ((targetFlag == false) || (distanceSquared >= g_autoAimRangeSquared1)) && (distanceSquared >= g_autoAimRangeSquared2) )
    //     return 0;
    // else
    //     return 1;
    bool firstPart = (targetFlag == false) || (distanceSquared >= g_autoAimRangeSquared1);
    bool secondPart = distanceSquared >= g_autoAimRangeSquared2;

    if (firstPart && secondPart) {
        return 0;
    } else {
        return 1;
    }
}