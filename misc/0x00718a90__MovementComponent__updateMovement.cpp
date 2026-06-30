// FUNC_NAME: MovementComponent::updateMovement
bool __thiscall MovementComponent::updateMovement(MovementComponent* this, MovementParams* params)
{
    bool result = false;
    int entityHandle; // entity handle from params
    int currentTime; // time
    float deltaTime; // computed time delta
    bool entityValid;
    int simTime;
    int local_8; // varies
    int var_4; // unused
    int overrideHandle;
    int playerPtr;
    float clampedTime;
    float timeValue;

    // Check if params has a valid entity reference (+0x8 points to entity handle)
    if ((params->entityPtr != 0) && (entityHandle = *(int*)(params->entityPtr) - 0x48, entityHandle != 0)) {
        // Get global simulation time
        simTime = FUN_0071c120();
        // Check if entity handle is valid
        entityValid = FUN_00713bb0(entityHandle);
        if (entityValid != 0) {
            this->flags = this->flags | 1; // set bit 0 (e.g., moving flag)
        }

        var_4 = 0;
        local_8 = entityHandle;
        // Possibly retrieve a global override (e.g., for debugging)
        if ((simTime != 0) && (overrideHandle = FUN_007ff880(), overrideHandle != 0)) {
            local_8 = overrideHandle;
        }

        // Get current time from time manager
        uVar3 = FUN_0077dd80();
        timeValue = (float)FUN_00712ef0(uVar3); // convert to float (seconds?)
        clampedTime = timeValue;

        // Retrieve player or controller instance to check max time cap
        playerPtr = FUN_007175b0();
        if ((playerPtr != 0) && (clampedTime < *(float*)(playerPtr + 0x34c))) {
            // Clamp to minimum time threshold from player's component
            clampedTime = *(float*)(playerPtr + 0x34c) + DAT_00d5779c;
        }

        // Call a virtual method from behavior vtable at this+0x1bc, offset 0x18 (likely "canStartMovement")
        // Signature: bool (int handle, int zero, float time, int zero)
        bool canStart = (**(code** (*(int*)(this + 0x1bc) + 0x18))(local_8, 0, clampedTime, 0);
        if (canStart != 0) {
            // Start movement on the entity with given time
            FUN_0071c720(*(int*)(this + 0x18), entityHandle, clampedTime);
            // Reset some movement state
            FUN_0071c170(*(int*)(this + 0x18), 0);
            // Get a factor from the behavior (offset 0x30, e.g., getMovementSpeed)
            float factor = (float)(**(code** (*(int*)(this + 0x1bc) + 0x30))();
            // Apply movement with time and factor
            FUN_0071c870(clampedTime, factor);

            // Additional condition for player-controlled or special actions
            // Check params->stateFlags bit 1 not set, global unaff_ESI (likely global player entity), and if player controlled
            if ((((*(params->stateFlags >> 1) & 1) == 0) && (globalPlayerEntity != 0)) &&
                (*(int*)(this + 0x18) != 0) && (FUN_0043b870(DAT_0113105c) != 0)) {
                int currentAction = FUN_009b2900();
                int desiredAction = FUN_00716c30();
                if (currentAction == desiredAction) {
                    // Set movement flag
                    FUN_0071bfd0(clampedTime);
                    params->stateFlags = params->stateFlags | 2; // set bit 1
                }
            }

            // Further state machine update based on params->stateFlags bit 0
            if ((params->stateFlags & 1) == 0) {
                params->stateFlags &= 0xfffd; // clear bit 1
                result = true;
            } else {
                params->stateFlags |= 2; // set bit 1
                result = true;
            }
        }

        // Cleanup: clear movement flag
        FUN_0071c360(clampedTime);
        this->flags &= 0xfffffffe; // clear bit 0
    }

    return result;
}