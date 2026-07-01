// FUNC_NAME: PlayerSM::tryBeginBlock

bool __thiscall PlayerSM::tryBeginBlock(int this, int attackData)
{
    // +0x50: pointer to character data (e.g., player character)
    int characterData = *(int *)(this + 0x50);
    // +0x5c: pointer to state machine context (e.g., PlayerSM internals)
    int stateMachine = *(int *)(this + 0x5c);

    // Attempt to get a block state object from character data
    int *blockStatePtr = nullptr;
    if (characterData != 0) {
        // +0x70 in character data: pointer to some inner state
        int innerPtr = *(int *)(characterData + 0x70);
        int *ptr = (int *)(innerPtr - 0x48); // adjust to base of block state object
        // +0xc9: flag byte, check bit 0 (1 << 0)
        if (ptr != nullptr && (*(byte *)(characterData + 0xc9) & 1) != 0) {
            blockStatePtr = ptr;
        }
    }

    // +0xb74 in state machine: flag indicating if currently in an action (e.g., attacking)
    // If not in another action and either:
    //   - block state exists and its vtable function (offset 0x1b0) returns a value >= threshold (block cooldown still active)
    //   - dodge is not possible and local cooldown timer (+0x98) is below another threshold
    if (*(int *)(stateMachine + 0xb74) == 0 &&
        ((blockStatePtr != nullptr &&
          ((*(float (__thiscall **)(int *))*blockStatePtr)(blockStatePtr) >= DAT_00d75860)) ||
         (FUN_0086e440(0, 0) == false && *(float *)(this + 0x98) < DAT_00d75f64)))
    {
        // Set block attempt timer at +0x94 and indicate block cannot start
        *(int *)(this + 0x94) = DAT_00d5ccf8;
        return false;
    }

    // Otherwise, attempt to initiate blocking using the incoming attack data
    bool result = FUN_0086dff0(attackData);
    return result;
}