// FUNC_NAME: LuaEngine::callLuaFunction

uint LuaEngine::callLuaFunction(uint param_1) {
    int iVar1;
    int iVar2;
    undefined4 *puVar3;
    int *piVar4;
    char *functionName = (char *)EDI;
    int local_10[3];
    
    iVar1 = globalLuaState[6];                          // +0x18 offset? Maybe stack count
    piVar4 = globalLuaState;                             // pointer to Lua interpreter block
    
    if (*functionName != '\0') {
        debugPrint(iVar1, "CallLuaFunction");            // log entry
        puVar3 = (undefined4 *)allocateStack(iVar1, 
                                             iVar1 + 0x40,
                                             *(int *)(iVar1 + 8) + -8,
                                             0);
        iVar2 = *(int *)(iVar1 + 8);
        *(undefined4 *)(iVar2 + -8) = *puVar3;           // push value onto stack
        *(undefined4 *)(iVar2 + -4) = puVar3[1];
        piVar4 = (int *)(*(int *)(iVar1 + 8) + -8);
        if ((piVar4 != (int *)0x0) && (*piVar4 == 6)) {  // check if function type is 6 (LUA_TFUNCTION?)
            debugPrint(iVar1);                           // log something
            debugPrint(iVar1, param_1);                  // log the argument
            local_10[0] = *(int *)(iVar1 + 8) + -0x18;
            local_10[1] = 0;
            piVar4 = (int *)findFunction(&funcLabel, 
                                         local_10, 
                                         local_10[0] - *(int *)(iVar1 + 0x1c));
            if (piVar4 == (int *)0x0) {
                return 1;
            }
        }
    }
    return (uint)piVar4 & 0xffffff00;
}