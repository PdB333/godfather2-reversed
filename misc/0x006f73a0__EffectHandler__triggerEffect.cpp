// FUNC_NAME: EffectHandler::triggerEffect
// Address: 0x006f73a0
// This function appears to validate and trigger an effect on a target.
// The object at 'this' has state at +0x2c, a 128-bit ID at +4, a hook pointer at +0x24, and a flag at +0x30.
// The magic constants represent an "invalid" or "null" ID pattern used by the engine.

#include <cstdint>

struct Guid128 {
    uint32_t data[4];
};

static const Guid128 kInvalidGuid1 = { 0xBADBB9BA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911 };
static const Guid128 kNullGuid = { 0, 0, 0, 0 };

// Forward declarations of internal functions (assumed from other functions)
void* getDataFromGuid(const Guid128* guid);   // FUN_006f4680
void* resolveTargetFromHandle(uint32_t handle); // FUN_006f4cd0
void* createHook();                            // FUN_006f0780
void initAction(void* actionData);             // FUN_006f0c20
bool applyEffect(void* target, void* actionData, EffectHandler* self, 
                 uint32_t param2, uint32_t param4, uint32_t param5, float magnitude); // FUN_006f15b0

class EffectHandler {
public:
    uint32_t m_state;          // +0x2c
    Guid128 m_effectId;        // +0x04 (16 bytes)
    void* m_actionHook;        // +0x24
    uint8_t m_extraFlag;       // +0x30

    bool triggerEffect(uint32_t param2, uint32_t param3, uint32_t param4, uint32_t param5,
                       uint8_t param6, char param7)
    {
        // Check state restrictions
        switch (m_state) {
        case 1:
            if (param7 == '\0') {
                return false; // Must have immediate flag set in state 1
            }
            break;
        case 2:
        case 3:
            return false; // State 2 and 3 always reject
        }

        // Validate the effect ID: must not be the special "invalid" pattern
        if (m_effectId.data[0] == kInvalidGuid1.data[0] && 
            m_effectId.data[1] == kInvalidGuid1.data[1] &&
            m_effectId.data[2] == kInvalidGuid1.data[2] && 
            m_effectId.data[3] == kInvalidGuid1.data[3]) {
            return false;
        }

        // Must not be all zero
        if (m_effectId.data[0] == 0 && m_effectId.data[1] == 0 &&
            m_effectId.data[2] == 0 && m_effectId.data[3] == 0) {
            return false;
        }

        // Resolve action data from the effect ID
        void* actionData = getDataFromGuid(&m_effectId);
        if (actionData == nullptr) {
            return false;
        }

        // Resolve the target object from the handle (param3)
        void* target = resolveTargetFromHandle(param3);
        if (target == nullptr) {
            return false;
        }

        // Check target's action count (or some counter)
        if (*reinterpret_cast<int*>(*reinterpret_cast<int*>(static_cast<char*>(target) + 0x18) + 4) < 1) {
            return false;
        }

        // Allocate a hook if not already present
        if (m_actionHook == nullptr) {
            m_actionHook = createHook();
        }
        if (m_actionHook == nullptr) {
            return false;
        }

        // Prepare the action
        initAction(actionData);

        // Apply the effect with a magnitude of 1.0f
        if (!applyEffect(target, actionData, this, param2, param4, param5, 1.0f)) {
            return false;
        }

        // Store the extra flag
        m_extraFlag = param6;
        return true;
    }
};