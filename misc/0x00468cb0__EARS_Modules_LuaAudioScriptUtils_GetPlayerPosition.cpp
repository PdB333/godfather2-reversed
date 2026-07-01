// Xbox PDB: EARS::Modules::LuaAudioScriptUtils::GetPlayerPosition
// FUNC_NAME: ScriptContext::registerPositionScriptAPI
void ScriptContext::registerPositionScriptAPI(void* scriptCtx)
{
    // +0x08: stack pointer (int*)
    // +0x40: method table pointer
    int* stackPtr = *(int**)((char*)scriptCtx + 0x08);
    void* methodTable = *(void**)((char*)scriptCtx + 0x40);

    // Register "RegisterScriptName"
    RegisterScriptName(scriptCtx, "RegisterScriptName");
    *stackPtr = 0; // push 0 onto stack (8-byte slot)
    stackPtr += 2; // advance by 8 bytes
    *(int**)((char*)scriptCtx + 0x08) = stackPtr;
    SetupNativeMethod(methodTable, (int)(stackPtr - 4), (int)(stackPtr - 2));

    // Register "GetPositionValues"
    RegisterScriptName(scriptCtx, "GetPositionValues");
    *(int**)((char*)scriptCtx + 0x08) = stackPtr; // restore
    *stackPtr = 0;
    stackPtr += 2;
    *(int**)((char*)scriptCtx + 0x08) = stackPtr;
    SetupNativeMethod(methodTable, (int)(stackPtr - 4), (int)(stackPtr - 2));

    // Register "SetPositionValues"
    RegisterScriptName(scriptCtx, "SetPositionValues");
    *(int**)((char*)scriptCtx + 0x08) = stackPtr;
    *stackPtr = 0;
    stackPtr += 2;
    *(int**)((char*)scriptCtx + 0x08) = stackPtr;
    SetupNativeMethod(methodTable, (int)(stackPtr - 4), (int)(stackPtr - 2));

    // Register "GetPlayerPosition"
    RegisterScriptName(scriptCtx, "GetPlayerPosition");
    *(int**)((char*)scriptCtx + 0x08) = stackPtr;
    *stackPtr = 0;
    stackPtr += 2;
    *(int**)((char*)scriptCtx + 0x08) = stackPtr;
    SetupNativeMethod(methodTable, (int)(stackPtr - 4), (int)(stackPtr - 2));

    // Register "TEMP_POS"
    RegisterScriptName(scriptCtx, "TEMP_POS");
    *(int**)((char*)scriptCtx + 0x08) = stackPtr;
    *stackPtr = 0;
    stackPtr += 2;
    *(int**)((char*)scriptCtx + 0x08) = stackPtr;
    SetupNativeMethod(methodTable, (int)(stackPtr - 4), (int)(stackPtr - 2));

    // Register "CreatePosition"
    RegisterScriptName(scriptCtx, "CreatePosition");
    *(int**)((char*)scriptCtx + 0x08) = stackPtr;
    *stackPtr = 0;
    stackPtr += 2;
    *(int**)((char*)scriptCtx + 0x08) = stackPtr;
    SetupNativeMethod(methodTable, (int)(stackPtr - 4), (int)(stackPtr - 2));

    // Register "GetPlatform"
    RegisterScriptName(scriptCtx, "GetPlatform");
    *(int**)((char*)scriptCtx + 0x08) = stackPtr;
    *stackPtr = 0;
    stackPtr += 2;
    *(int**)((char*)scriptCtx + 0x08) = stackPtr;
    SetupNativeMethod(methodTable, (int)(stackPtr - 4), (int)(stackPtr - 2));
}