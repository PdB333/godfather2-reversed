// FUNC_NAME: PlayerActionable::canPerformAction (0x007d8610)
// Checks various conditions (global time threshold, bit flags, game state) before allowing an action flagged by 0x2000000.

int __fastcall PlayerActionable::canPerformAction(PlayerActionable* this)
{
    uint flags;
    char isValid;
    int result;

    // Allocate temporary object (likely a state check)
    void* tempObj = FUN_00798f50(0x2c);
    isValid = FUN_0079e970(tempObj);
    if ((((isValid != '\0') && (g_globalTimeThreshold < *(float*)(this + 0x30))) &&
        (flags = *(uint*)(*(int*)(this + 0x58) + 0x24a0), (flags >> 0xb & 1) == 0)) &&
       ((((flags >> 0xd & 1) == 0 && (isValid = FUN_007f7c50(), isValid == '\0')) &&
        (result = FUN_007ab340(), result != 0)))) {
        isValid = FUN_007ab420(0x2000000);
        if (isValid != '\0') {
            return 1;
        }
    }
    return 0;
}