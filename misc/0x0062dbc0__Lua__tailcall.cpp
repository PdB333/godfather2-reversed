// FUNC_NAME: Lua::tailcall
void Lua::tailcall() {
    int *currentFuncPtr = *(int**)(this + 0xC);  // +0xC: pointer to current function or value on stack
    int *stackTop = *(int**)(this + 0x8);         // +0x8: stack top pointer (next free slot)
    int level = (int)DAT_00e2b1a4;                // global constant, possibly current call level
    int *tmp;

    // Check if there is room on the stack (stackTop > currentFuncPtr)
    if (currentFuncPtr < stackTop) {
        // If current function type is 6 (Lua function), push it onto the call stack
        if ((currentFuncPtr != nullptr) && (*currentFuncPtr == 6)) {
            *stackTop = *currentFuncPtr;          // copy type
            *(stackTop + 1) = *(currentFuncPtr + 1); // copy value
            *(int*)(this + 0x8) += 8;            // increment stack top by one TValue (8 bytes)
            return;
        }

        // Otherwise, if current function is non-nil and positive (valid object?), call some evaluation
        if ((currentFuncPtr < stackTop) && (currentFuncPtr != nullptr) && (*currentFuncPtr > 0)) {
            float someFloat = luaV_execute();     // FUN_00628080 - likely luaV_execute
            level = (int)someFloat;               // use returned float as new level
        }
    }

    // If level (call depth) becomes negative, handle error
    if (level < 0) {
        luaD_throw();                            // FUN_00627a20 - error/throw
    }

    // Check if we can push more frames (stack space)
    int spaceAvailable = lua_checkstack();        // FUN_00632b70
    if (spaceAvailable == 0) {
        luaD_throw();                            // error
    }

    // Perform the tail call itself (setup new call frame)
    luaD_call();                                 // FUN_00632fb0

    // After call, check the previously pushed function (now at stackTop-1)
    currentFuncPtr = (int*)(*(int*)(this + 0x8) - 8);
    if ((currentFuncPtr != nullptr) && (*currentFuncPtr == 0)) {
        // Nil function at the call point - should not happen for tail call
        luaG_runerror("no function environment for tail call at level %d", (int)level);
        // Trigger breakpoint or crash
        code *handler = (code*)swi(3);
        (*handler)();
    }
}