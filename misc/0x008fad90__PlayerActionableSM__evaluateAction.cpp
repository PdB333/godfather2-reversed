// FUNC_NAME: PlayerActionableSM::evaluateAction
void __fastcall PlayerActionableSM::evaluateAction(void *this)
{
    char isValid;
    int action;

    // Check if action state is 0 or 0x48 (idle/ready states)
    if (((*(int *)((int)this + 0x43c) == 0) || (*(int *)((int)this + 0x43c) == 0x48)) ||
        // If state is not idle, check if target at +0x430 is valid
        (isValid = FUN_008f78b0(*(uint *)((int)this + 0x430)), isValid == '\0'))
    {
        // Get an action object by combining controller (+0x178) and target (+0x430)
        action = FUN_008fa220(*(uint *)((int)this + 0x178), *(uint *)((int)this + 0x430));
        if (action != 0) {
            // Execute the action
            FUN_008fa2b0(action);
        }
    }
    return;
}