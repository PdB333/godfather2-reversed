// FUNC_NAME: dispatchCallbackAction
void __thiscall dispatchCallbackAction(void* this, int* outActionId, uint callbackArg)
{
    int actionId = -1;
    // +0x18: pointer to some state/context object
    if (*(int*)((int)this + 0x18) != 0) {
        actionId = FUN_00650f30(); // retrieve current action identifier
    }
    uint savedArg = callbackArg;
    bool canDispatch = FUN_0064bb50(actionId != -1); // check if action is valid
    if (canDispatch) {
        *outActionId = actionId;
        FUN_0064b810(10, outActionId); // register action ID (10 = register action type?)
        // +0x14: pointer to a vtable-based object; call its 3rd virtual function (offset 8)
        (*(void(__thiscall**)(void*, uint))(**(int**)((int)this + 0x14) + 8))(*(void**)((int)this + 0x14), savedArg);
        // Update state flags after dispatch: apply bitmask to field at +0x30 of the context object
        FUN_0064bb50(*(uint*)(*(int*)((int)this + 0x18) + 0x30) >> 1 & 0xffffff01);
    }
}