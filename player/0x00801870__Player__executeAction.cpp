// FUNC_NAME: Player::executeAction
void __thiscall Player::executeAction(int this, int actionParam)
{
    int dataPtr = *(int *)(this + 0x840); // +0x840: pointer to player state/component
    int value = 0;
    if (dataPtr != 0) {
        value = *(int *)(dataPtr + 0xe4); // +0xe4: some ID (e.g., weapon, dialog, marker type)
    }
    int result = FUN_006a7c60(actionParam, value, 0); // create/retrieve object with given parameters
    FUN_004717c0(result, 0); // activate/display the object
    return;
}