// FUNC_NAME: Entity::processMessage
void __thiscall Entity::processMessage(void *this, undefined4 *inputData, undefined4 someId)
{
    int *ptrField;
    bool isActive;
    undefined4 localStack[4]; // uninitialized, but used for copy
    
    FUN_00470b80(inputData, someId);
    ptrField = *(int **)((int)this + 0x2E8); // offset 0xba*4
    isActive = (**(code **)(*(int *)this + 0x19c))(); // virtual check
    if (!isActive) {
        if (ptrField != 0) {
            localStack[0] = *inputData;
            localStack[1] = inputData[1];
            localStack[2] = inputData[2];
            localStack[3] = DAT_00e2b1a4; // global constant
            FUN_00aa36a0(localStack, someId);
            FUN_009f4c70(/* possibly output buffer */);
        }
    } else {
        FUN_0055db00(someId);
    }
    (**(code **)(*(int *)this + 600))(); // virtual post-update
    return;
}