// FUNC_NAME: forwardCallToTarget
// Address: 0x004657d0 - Thin wrapper forwarding to 0x00465700 with identical parameters
void __thiscall forwardCallToTarget(void* this, void* param)
{
    // Calls the underlying implementation at 0x00465700
    baseFunction(this, param);
    return;
}