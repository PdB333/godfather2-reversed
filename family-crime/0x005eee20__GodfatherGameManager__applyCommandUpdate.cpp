// FUNC_NAME: GodfatherGameManager::applyCommandUpdate
// Function address: 0x005eee20
// Role: Processes a command update (type 0x9c) from a data buffer, updating internal state fields if conditions are met.

typedef int bool32;

class GodfatherGameManager {
public:
    // Assumed class fields (offsets relative to this)
    // +0x580: m_isReady (int, non-zero means active)
    // +0x9088: m_updatePending (byte, set to 1 after successful update)
    // +0x908c: m_currentValue (float, the current stored value)
    // +0x9094: m_fieldData0 (int, derived from command data[1])
    // +0x9098: m_fieldData1 (int, derived from command data[2])
    // +0x909c: m_fieldData2 (int, derived from command data[3])
    // +0x90a0: m_fieldData3 (int, derived from command data[4])

    bool32 applyCommandUpdate(int *commandData, float newValue);
};

// External global: maximum allowed value for clamping
extern float g_maxCommandValue; // DAT_00e2b1a4

// Internal helper: checks if a forced update is required
extern bool32 isForcedUpdateMode(); // FUN_005e3aa0

// Internal helper: processes after data is updated
extern void onCommandDataUpdated(GodfatherGameManager *self); // FUN_005eef50

bool32 GodfatherGameManager::applyCommandUpdate(int *commandData, float newValue) {
    // Validate inputs and readiness
    if (commandData == nullptr) return 0;
    if (m_isReady == 0) return 0;

    // Clamp newValue to valid range [0.0, g_maxCommandValue]
    float clampedValue = 0.0f;
    if (newValue > 0.0f) {
        if (g_maxCommandValue <= newValue) {
            clampedValue = g_maxCommandValue;
        } else {
            clampedValue = newValue;
        }
    } else {
        clampedValue = 0.0f;
    }
    newValue = clampedValue; // use clamped value

    // Only process command type 0x9c
    if (commandData[0] != 0x9c) return 0;

    // Check if a forced update is needed; if not, early out when value unchanged
    if (!isForcedUpdateMode()) {
        if (newValue == m_currentValue) {
            return 0;
        }
    }

    // Update internal fields from command data (index 1..4)
    m_fieldData0 = commandData[1];
    m_fieldData1 = commandData[2];
    m_fieldData2 = commandData[3];
    m_fieldData3 = commandData[4];

    // Store the new value
    m_currentValue = newValue;

    // Trigger post-update processing
    onCommandDataUpdated(this);

    // Mark update as pending
    m_updatePending = 1;

    return 1;
}