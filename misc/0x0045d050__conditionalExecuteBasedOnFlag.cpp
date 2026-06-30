// FUNC_NAME: conditionalExecuteBasedOnFlag
void __thiscall conditionalExecuteBasedOnFlag(void* this, void* paramTarget, int enableFlag)
{
    // If the flag is non-zero, call the internal handler with the target parameter
    if (enableFlag != 0) {
        callInternalHandler(paramTarget); // 0x0045e630
    }
}