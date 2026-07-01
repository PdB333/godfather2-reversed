// FUNC_NAME: PlayerActionController::updateActions

// Function 0x007e21c0: Player action controller update - processes input and triggers actions based on state
// Called from PlayerActionController::update (0x007e4b80)
// Uses action manager vtable to dispatch actions with IDs:
//   0x40000, 0x200000, 0x800, 0x100, 0x200, 0x400, 0x80

#include <cstdint>

// Forward declarations of helper functions (from other modules)
// These are likely static functions in the same translation unit or globals
extern int* getActionManager();
extern int* getInputState();
extern int* getButtonModifiers();
extern uint32_t getActionIdFromTable(void* tableBase, int offset, int index = 0);
extern bool canPerformTalkAction(void* entity, uint32_t actionId);
extern bool canPerformExtortAction(void* entity, uint32_t actionId);
extern bool canPerformShoveAction(void* entity, uint32_t actionId);
extern bool canPerformGenericAction(void* entity, uint32_t actionId);

// Global variable (likely a time threshold)
extern float g_actionTimeThreshold;

class PlayerActionController {
public:
    // Likely vtable for action manager: index 0 = startInput, index 1 = triggerAction
    struct ActionManagerVTable {
        void (*startInput)(uint32_t context);       // +0x00
        void (*triggerAction)(uint32_t action);     // +0x04
    };

    // Member offsets (relative to 'this')
    // +0x00: vtable pointer (not used here directly)
    // +0x30: m_animTimer (float)
    // +0x58: m_pEntity (Entity*)
    // Other fields unknown

    float m_animTimer;      // +0x30
    void* m_pEntity;        // +0x58 (pointer to some entity/character object)

    void updateActions();
};

void PlayerActionController::updateActions()
{
    void* entity = *(void**)((uint8_t*)this + 0x58);  // iVar1
    int* actionMgr = getActionManager();
    ActionManagerVTable* vtable = *(ActionManagerVTable**)actionMgr;

    // Begin input processing with context 0x240f80
    vtable->startInput(0x240f80);

    // Check current character state (offsets from entity)
    int state1 = *(int*)((uint8_t*)entity + 0xff0);
    int state2 = *(int*)((uint8_t*)entity + 0x1010);

    bool isIdleOrSpecial = (state1 == 0) || (state1 == 0x48);
    bool isInRange = (state2 > 0x2d) && (state2 < 0x3e); // 0x2e..0x3d

    if (isIdleOrSpecial || isInRange) {
        // First set of actions (when in idle or certain states)
        int* inputState = getInputState();
        int* buttonModifiers = getButtonModifiers();

        // Check for quick talk action (0x40000)
        if ((*(uint8_t*)((uint8_t*)inputState + 4) & 0x100) != 0) {
            if ((*(uint8_t*)((uint8_t*)buttonModifiers + 4) & 2) != 0) {
                uint32_t talkActionId = getActionIdFromTable(actionMgr, 0x0c);
                if (canPerformTalkAction(entity, talkActionId)) {
                    vtable->triggerAction(0x40000);
                }
            }
        }

        // Check for extort action (0x200000)
        if ((*(uint8_t*)((uint8_t*)inputState + 4) & 4) != 0) {
            if ((*(uint8_t*)((uint8_t*)buttonModifiers + 4) & 2) != 0) {
                // Check bit 9 of entity flags at +0x8e0 is clear
                if ((*(uint32_t*)((uint8_t*)entity + 0x8e0) >> 9 & 1) == 0) {
                    uint32_t extortActionId = getActionIdFromTable(actionMgr, 0x2c);
                    if (canPerformExtortAction(entity, extortActionId)) {
                        vtable->triggerAction(0x200000);
                    }
                }
            }
        }
    } else {
        // Second set of actions (when in non-idle states)
        int* inputState = getInputState();
        int* buttonModifiers = getButtonModifiers();

        // Check for shove action (0x800)
        if ((*(uint8_t*)((uint8_t*)inputState + 4) & 8) != 0) {
            if ((*(uint8_t*)((uint8_t*)buttonModifiers + 4) & 2) != 0) {
                uint32_t shoveActionId = getActionIdFromTable(actionMgr, 0x4c);
                if (canPerformShoveAction(entity, shoveActionId) && (g_actionTimeThreshold < *(float*)((uint8_t*)this + 0x30))) {
                    vtable->triggerAction(0x800);
                }
            }
        }

        // Check for three generic actions (0x100, 0x200, 0x400) under trigger 0x80
        if ((*(uint8_t*)((uint8_t*)inputState + 4) & 0x80) != 0) {
            if ((*(uint8_t*)((uint8_t*)buttonModifiers + 4) & 2) != 0) {
                // First generic (action 0x100)
                uint32_t actionId1 = getActionIdFromTable(actionMgr, 0x6c, 0);
                if (canPerformGenericAction(entity, actionId1) && (g_actionTimeThreshold < *(float*)((uint8_t*)this + 0x30))) {
                    vtable->triggerAction(0x100);
                }

                // Second generic (action 0x200)
                uint32_t actionId2 = getActionIdFromTable(actionMgr, 0x94, 1);
                if (canPerformGenericAction(entity, actionId2) && (g_actionTimeThreshold < *(float*)((uint8_t*)this + 0x30))) {
                    vtable->triggerAction(0x200);
                }

                // Third generic (action 0x400)
                uint32_t actionId3 = getActionIdFromTable(actionMgr, 0xbc, 2);
                if (canPerformGenericAction(entity, actionId3) && (g_actionTimeThreshold < *(float*)((uint8_t*)this + 0x30))) {
                    vtable->triggerAction(0x400);
                }
            }
        }

        // Check for auto-return action (0x80) based on entity flags
        if ((*(uint32_t*)((uint8_t*)entity + 0x8e8) >> 0x17 & 1) != 0) {
            vtable->triggerAction(0x80);
            return;
        }
    }
}