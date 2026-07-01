// FUNC_NAME: EventManager::processEvent
void __thiscall EventManager::processEvent(int thisPtr, int eventID, undefined4 param3, undefined4 param4, undefined4 param5)
{
    uint index = 0;
    if (*(uint *)(thisPtr + 0x1a8) != 0) {
        int **eventPtrArray = *(int ***)(thisPtr + 0x1a4);
        while (*(int *)(*eventPtrArray + 8) != eventID) {
            index++;
            eventPtrArray++;
            if (*(uint *)(thisPtr + 0x1a8) <= index) {
                return;
            }
        }
        if ((-1 < (int)index) && (*(int *)((*(int **)(thisPtr + 0x1a4))[index] + 4) != 7)) {
            // Event state is not 7 (likely "completed" or "inactive")
            FUN_008c80d0(param4);
            FUN_008c8a20(param3, param5);
        }
    }
    return;
}