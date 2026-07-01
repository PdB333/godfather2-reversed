// Xbox PDB: EARS::Framework::Lua::LuaScript::RunScript
// FUNC_NAME: EventHandler::tryInvokeCallback
void __thiscall EventHandler::tryInvokeCallback(void* callbackObj) {
    // +0x8: pointer to data structure (maybe to an array or vtable)
    // +0x1C: offset or size used to compute a difference
    int* dataPtr = *(int**)(this + 8);           // dereference field at +8
    int baseValue = (int)dataPtr - 8;             // subtract 8 to get base pointer
    int diff = baseValue - *(int*)(this + 0x1C);  // difference to field at +0x1C

    int buffer[2];
    buffer[0] = baseValue;
    buffer[1] = -1; // 0xFFFFFFFF sentinel

    if (!globalCheckFunction()) { // FUN_00629280 – maybe check if engine is active
        if (comparisonFunction(&LAB_006261e0, buffer, diff) == 0) { // FUN_00636570
            if (callbackObj != nullptr) {
                // Call virtual function at index 0 (VTBL + 0)
                (**(void (__thiscall**)(void*))callbackObj)(callbackObj);
            }
        }
    }
    cleanupFunction(); // FUN_006255e0 – possibly release temporary resources
}