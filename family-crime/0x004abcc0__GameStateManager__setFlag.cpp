// FUNC_NAME: GameStateManager::setFlag
// Address: 0x004abcc0
// This function activates a flag (bitwise OR) and triggers a callback if a condition is met.
// Observations:
//   +0x3c: uint32 m_flags (bitfield of active flags)
//   +0x1c: TriggerObject* m_pTriggerObject (nullable pointer, expected to have its own state)
// The condition checks if the trigger object exists and its byte at offset 0x44 is zero.
//   +0x44: bool m_bTriggered (or similar completion flag, 0 = not yet triggered)
// If condition holds, a global/static callback is invoked (0x004abd20).

// Forward declaration of the external callback function.
extern void onFlagSetCallback();

// Class representing a trigger object that may be associated with the flag manager.
class TriggerObject {
public:
    // Offset +0x44: if zero, the trigger hasn't fired yet.
    char m_bTriggered; // bool (stored as char)
    // ... other fields ...
};

// Class managing a set of game state flags.
class GameStateManager {
public:
    uint32_t m_flags;               // +0x3c bitfield of enabled flags
    TriggerObject* m_pTriggerObject; // +0x1c pointer to associated trigger (nullable)

    // Sets a specific flag and possibly triggers the callback.
    // @param flagBit: the bit to OR into m_flags.
    void setFlag(uint32_t flagBit) {
        m_flags |= flagBit;
        // If a trigger object exists and hasn't been triggered yet, call the callback.
        if (m_pTriggerObject != nullptr && m_pTriggerObject->m_bTriggered == 0) {
            onFlagSetCallback();
        }
    }
};