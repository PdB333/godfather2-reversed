// FUNC_NAME: AICombatComponent::processStimulus
// Address: 0x005f1f80
// Handles an incoming stimulus for an AI combat component.
// param_1 is a pointer to a StimulusData structure.
// Returns 1 if stimulus was handled, 0 if null.
int __thiscall AICombatComponent::processStimulus(AICombatComponent* this, StimulusData* stimulus) {
    bool bCanAttack = false;    // bVar6
    bool bCanEvade = false;     // bVar5
    int ret = 1;

    if (stimulus == nullptr) {
        ret = 0;
    } else {
        // Evaluate current state and stimulus flags to determine reaction priority
        if (this != nullptr) {
            int state = this->state; // +0x68
            bool stimFlag40 = (*(uint8_t*)(*(int*)&stimulus[1] + 8) & 0x40) != 0; // stimulus->target->flags bit 6

            // bCanAttack: state 5 (idle?) or state 4 with no stimFlag40
            if (state == 5 || (state == 4 && !stimFlag40)) {
                bCanAttack = true;
            }
            // bCanEvade: state 2 (evade?) or state 4 with stimFlag40
            if (state == 2 || (state == 4 && stimFlag40)) {
                bCanEvade = true;
            }

            float stimulusDistance = stimulus->distance; // +0x08

            // Store current distance in component
            this->lastStimulusDistance = stimulusDistance; // +0x50

            if (bCanAttack) {
                return 1;
            }

            if (stimulusDistance > STIMULUS_DISTANCE_THRESHOLD) {
                if (bCanEvade) {
                    return 1;
                }

                // Try to find or create target
                AICombatComponent* target = nullptr;
                if (this == nullptr) {
                    target = findOrCreateTarget(stimulus->target, stimulusDistance); // FUN_005f1df0
                }
                if (target != nullptr) {
                    // Set target orientation flag based on stimulus direction
                    uint16_t direction = stimulus->direction; // +0x0C
                    uint8_t flag = (uint8_t)(((char)(direction >> 7)) * 2); // bit 1 of byte
                    target->orientationFlags = (target->orientationFlags & ~2) | flag; // +0x7b
                    setDirectionEffect(stimulus->effectType); // FUN_005f2150, effectType at +0x0F
                    return 1;
                }
            } else {
                // Distance below threshold: check other flags
                bool stimFlag20 = (*(uint8_t*)(*(int*)&stimulus[1] + 8) & 0x20) != 0;
                if (stimFlag20) {
                    triggerGlobalStimulusReaction(); // FUN_005e4cf0
                    return 1;
                }

                if (this != nullptr && bCanEvade) {
                    int currentState = this->state; // +0x68
                    setCombatState(1); // FUN_005f2230(1) - transition to state 1?
                    if (currentState != 4) {
                        this->state = 3; // Set state to 3 (patrol?)
                    }
                    return 1;
                }
            }
        }
        // Default: return 1 if stimulus was processed
        ret = 1;
    }
    return ret;
}