// FUN_00411220: CharacterController::executeBehaviorAction
void __thiscall CharacterController::executeBehaviorAction(void)
{
    // param_1 is the 'this' pointer
    // +0x4EC: array of behavior function table pointers (size 4 per entry)
    // +0x565: current behavior index (byte)
    uint index = *(byte *)(this + 0x565);
    // Get the appropriate behavior table pointer
    int *behaviorTable = *(int **)(this + 0x4EC + index * 4);
    // +0x18: offset to a function pointer within the behavior table (e.g., execute)
    // Call with arguments (4, 0) — possibly action type and parameter
    (**(code **)(behaviorTable + 0x18))(4, 0);
}