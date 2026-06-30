// FUNC_NAME: ActionManager::createAction

void __thiscall ActionManager::createAction(void *this, int *templateObj, undefined4 param3, undefined4 param4, undefined4 param5)
{
    char canStart;
    undefined4 typeID;
    int *newAction;

    FUN_00568080(templateObj, param3, param4, param5);
    if (templateObj != nullptr) {
        typeID = (*(code **)(*templateObj + 8))();  // vtable+8: likely getActionTypeID

        if (*(int **)((int)this + 0xc) != nullptr) {
            canStart = (**(code **)(**(int **)((int)this + 0xc) + 0x8c))();  // vtable+0x8c: isContextReady?
            if ((canStart != '\0') && (*(int *)((int)this + 0x36c) == 0)) {
                newAction = (int *)FUN_009c8e50(0x6c);  // allocate 108 bytes
                if (newAction != nullptr) {
                    typeID = FUN_004538b0(*(undefined4 *)((int)this + 0x374), typeID);
                    *(undefined4 *)((int)this + 0x36c) = typeID;  // store new action pointer at +0x36C
                    return;
                }
                *(int *)((int)this + 0x36c) = 0;
            }
        }
    }
    return;
}