// FUNC_NAME: SimObject::updateTimedAction
// Address: 0x0090a500
// Calls a time-based update on either a global object or null, if elapsed time exceeds threshold.

void __thiscall SimObject::updateTimedAction(void* thisObj, int useGlobalObj)
{
    float* piVar1;
    float elapsedTime;
    float interval;

    interval = *(float*)((char*)thisObj + 0x4); // +0x4: update interval or frequency
    FUN_008936b0(0x58ee812, interval, &elapsedTime); // Get time since last update? hash 0x58ee812 likely "UpdateTime"
    if (*(float*)0x00d577a0 < elapsedTime) { // global threshold (e.g., gMaxFrameDelta)
        if (useGlobalObj == 0) {
            piVar1 = (float*)0x0;
        }
        else {
            piVar1 = (float*)FUN_0043b870(*(int*)0x01131018); // Get global object (e.g., gGameManager)
        }
        (**(code**)(piVar1 + 0x10))(elapsedTime); // vtable+0x40: update(float timeDelta)
        (**(code**)(piVar1 + 0x0F))(thisObj); // vtable+0x3c: setTarget(void* object)
    }
    return;
}