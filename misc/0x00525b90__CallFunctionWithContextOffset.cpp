// FUNC_NAME: CallFunctionWithContextOffset
void __fastcall CallFunctionWithContextOffset(int context, int actionIndex, int param3, int param4, int param5, char param6)
{
    int statePtr;
    // context is passed via EAX by the caller (offset +0x54 selects sub-object)
    if (context == 0) {
        statePtr = 0;
    } else {
        statePtr = context + 0x54; // point to internal state component at +0x54
    }
    // call the actual processing function with rearranged arguments
    FUN_00525970(param3, param4, statePtr, param5, param6, actionIndex);
}