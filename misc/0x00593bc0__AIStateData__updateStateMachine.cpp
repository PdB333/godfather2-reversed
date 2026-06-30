// FUNC_NAME: AIStateData::updateStateMachine
// Address: 0x00593bc0
// Role: Updates AI state machine for a character and resets navigation target if invalid.

// Reconstructed C++ for state machine update function.
// Uses custom calling convention with this in ESI and entity pointer in EDI.
// Fields and constants based on observed offsets and global data.

#include <cstdint>

// Forward declarations
class Entity;

// Global constant from address 0x00e2b1a4 (likely invalid/uninitialized target vector component)
static const int32_t INVALID_TARGET_COMPONENT = DAT_00e2b1a4; // (value unknown, placeholder)

// Structure resembling a 2D target or bounding box with two fields set to invalid constant
struct TargetResetData {
    int32_t field_0;  // +0x00 (unused, set to 0)
    int32_t field_4;  // +0x04 (unused, set to 0)
    int32_t field_8;  // +0x08 (unused, set to 0)
    int32_t field_C;  // +0x0C (set to INVALID_TARGET_COMPONENT)
    int32_t field_10; // +0x10 (unused, set to 0)
    int32_t field_14; // +0x14 (unused, set to 0)
    int32_t field_18; // +0x18 (unused, set to 0)
    int32_t field_1C; // +0x1C (set to INVALID_TARGET_COMPONENT)
};

// State data block pointed to by AIStateData+4
struct StateBlock {
    uint8_t  controlByte;   // +0x04: determines which state offset to use (0-9 or 10+)
    uint8_t  pad[0x1C];    // padding to reach 0x20
    uint32_t stateLow;     // +0x20: used if controlByte < 10
    uint32_t stateHigh;    // +0x28: used if controlByte >= 10
};

// Main state machine data class
class AIStateData {
public:
    // +0x04: pointer to state block
    StateBlock* pStateBlock;

    // Update state machine for the given entity
    uint8_t update(Entity* pEntity);
};

// Entity class with fields accessed in this function
class Entity {
public:
    uint8_t  typeFlag;      // +0x04: determines used offsets (0-9 or 10+)
    int32_t  targetLow;     // +0x0C: target value if typeFlag < 10
    int32_t  targetIndexLow; // +0x10: index if typeFlag < 10
    // padding to +0x20
    int32_t  targetHigh;    // +0x20: target value if typeFlag >= 10
    int32_t  targetIndexHigh; // +0x24: index if typeFlag >= 10
};

// Forward declarations of state handler functions (unknown actual names)
extern uint8_t stateHandler_Idle();    // FUN_00580230
extern uint8_t stateHandler_Patrol();  // FUN_0057e300
extern uint8_t stateHandler_Combat();  // FUN_0057a900
extern uint8_t stateHandler_Flee();    // FUN_0057cfe0

// Function to reset navigation target (unknown name)
extern void resetNavigationTarget(TargetResetData* pResetData, int32_t targetValue);

// Implementation
uint8_t AIStateData::update(Entity* pEntity) {
    uint8_t result = 0;

    // Retrieve state block
    StateBlock* block = pStateBlock;
    if (!block) return result;

    // Determine which state value to use based on control byte
    uint32_t stateValue;
    if (block->controlByte < 10) {
        stateValue = block->stateLow;
    } else {
        stateValue = block->stateHigh;
    }

    // Mask to lower 28 bits (0x0FFFFFFF)
    stateValue &= 0x0FFFFFFF;

    // Dispatch to appropriate state handler
    switch (stateValue) {
        case 0:
            result = stateHandler_Idle();
            break;
        case 1:
            result = stateHandler_Patrol();
            break;
        case 3:
            result = stateHandler_Combat();
            break;
        case 4:
            result = stateHandler_Flee();
            break;
        // default: result remains 0
    }

    // Second part: check entity's target index and reset if valid
    uint8_t entityFlag = pEntity->typeFlag;
    int32_t targetIndex;
    if (entityFlag < 10) {
        targetIndex = pEntity->targetIndexLow;
    } else {
        targetIndex = pEntity->targetIndexHigh;
    }

    if (targetIndex >= 0) {
        // Build reset data structure with two fields set to invalid constant
        TargetResetData resetData = {};
        resetData.field_C = INVALID_TARGET_COMPONENT;   // +0x0C
        resetData.field_1C = INVALID_TARGET_COMPONENT; // +0x1C

        // Get the target value to pass to reset function
        int32_t targetValue;
        if (entityFlag < 10) {
            targetValue = pEntity->targetLow;   // +0x0C
        } else {
            targetValue = pEntity->targetHigh;  // +0x20
        }

        // Call reset function
        resetNavigationTarget(&resetData, targetValue);
    }

    return result;
}