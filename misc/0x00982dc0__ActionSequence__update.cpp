// FUNC_NAME: ActionSequence::update
bool __fastcall ActionSequence::update(void)
{
    // +0x6c: currentActionIndex (index into action array)
    // +0x7c: bActionsCompleted (flag indicating all actions done)
    // +0x4c: pActionArray (array of pointers to action objects)
    if (*(int *)((char *)this + 0x6c) != 0 && *(int *)((char *)this + 0x7c) == 0)
    {
        int actionIndex = *(int *)((char *)this + 0x6c);
        void *pAction = *(void **)((char *)this + 0x4c + actionIndex * 4);
        if (pAction != nullptr && *(void **)((char *)pAction + 0x18) != nullptr)
        {
            // Action object fields:
            // +0x10: actionData (some parameter)
            // +0x18: pfnUpdate (callback, returns bool)
            bool result = (*(bool (__thiscall **)(void *, int))((char *)pAction + 0x18))(pAction, *(int *)((char *)pAction + 0x10));
            if (!result)
            {
                // Log or handle error with handle -2 (0xFFFFFFFE)
                FUN_00982c00(-2, 0);
            }
        }
    }
    return *(int *)((char *)this + 0x6c) == 0;
}