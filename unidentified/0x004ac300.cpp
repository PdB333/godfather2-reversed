// FUN_004ac300: ActionRequest::executeAction
// This method processes an action request. param_2 = actionID, param_4 = overrideFlag, param_6, param_7 are stored.
// It checks if the current action state allows this new action; if not, returns 0, else calls virtual methods on the character.

class CharacterActionState {
public:
    // +0x0 vtable (if polymorphic)
    uint32_t flags;              // +0x10 (tested with 0x2000003)
    int32_t actionID;           // +0x18 (compared with param_2)
    float someTimeThreshold;    // +0x24 (compared with global float DAT_00e2b1a4)
    bool active;                // +0x30 (char, non-zero = active)
    void* animationData;        // +0x70 (assert non-null, then check via FUN_00573440())
    int32_t storedParam6;       // +0x130 (stores param_6 if m_actionState != 0)
};

class Character {
public:
    // vtable at +0x0
    // +0x48: CharacterLink link member (used for back-referencing, see ActionRequest)
    CharacterActionState* m_actionState; // +0x218
    int32_t m_field294;                 // +0x294 (stores param_7)

    virtual int32_t executeAction(int32_t actionID, uint32_t param3, uint32_t param5) = 0;  // vtable+0x14c
    virtual void postAction() = 0;                                                           // vtable+0x168
};

// Helper: get Character from a pointer to its link member (offset 0x48)
inline Character* getCharacterFromLink(CharacterLink* link) {
    return reinterpret_cast<Character*>(reinterpret_cast<uint8_t*>(link) - 0x48);
}

// The ActionRequest class has a pointer to a Character's link at offset +0x48
class ActionRequest {
public:
    // +0x0 vtable (unused here)
    CharacterLink* m_pCharacterLink; // +0x48 (points to Character::link, so Character = m_pCharacterLink - 0x48)
    // other members not used in this function

    // method at 0x004ac300
    // parameters: param_2 = actionID, param_3 = ?, param_4 = overrideFlag, param_5 = ?, param_6 = ?, param_7 = ?
    // returns 0 on failure, otherwise the result of Character::executeAction
    undefined1 executeAction(int32_t actionID, uint32_t param3, bool overrideFlag, uint32_t param5, uint32_t param6, uint32_t param7);
};

undefined1 ActionRequest::executeAction(int32_t actionID, uint32_t param3, bool overrideFlag, uint32_t param5, uint32_t param6, uint32_t param7) {
    bool shouldExecute = false;
    Character* character = getCharacterFromLink(m_pCharacterLink);

    if (!overrideFlag) {
        CharacterActionState* actionState = character->m_actionState;

        if (actionState == nullptr || !actionState->active) {
            // Action state inactive or null – check for possible action directly on character vtable?
            actionState = character->m_actionState;
            if (actionState != nullptr &&
                actionState->actionID == actionID &&
                actionState->animationData != nullptr &&
                (*(uint8_t*)((uint8_t*)actionState->animationData + 0x30) != 0) &&
                FUN_00573440() != '\0') {
                // fall through to skip execution
                shouldExecute = false; // remains false, meaning reject
            } else {
                shouldExecute = true; // allow execution
            }
        } else {
            // Action state is active – check flags and time threshold
            if (actionState == nullptr ||
                ((actionState->flags & 0x2000003) == 0 &&
                 DAT_00e2b1a4 < actionState->someTimeThreshold)) {
                // skip  (shouldExecute remains false → reject)
                shouldExecute = false;
            } else {
                // additional deep checks
                if (actionState != nullptr &&
                    actionState->actionID == actionID &&
                    actionState->animationData != nullptr &&
                    (*(uint8_t*)((uint8_t*)actionState->animationData + 0x30) != 0) &&
                    FUN_00573440() != '\0') {
                    // skip (reject)
                    shouldExecute = false;
                } else {
                    shouldExecute = true;
                }
            }
        }
    } else {
        // overrideFlag is true – execute regardless
        shouldExecute = true;
    }

    // Store param6 and param7 regardless
    if (character->m_actionState != nullptr) {
        character->m_actionState->storedParam6 = param6;
    }
    character->m_field294 = param7;

    if (!shouldExecute) {
        return 0;
    }

    // Execute the action via virtual calls
    undefined1 result = character->executeAction(actionID, param3, param5);
    character->postAction();
    return result;
}