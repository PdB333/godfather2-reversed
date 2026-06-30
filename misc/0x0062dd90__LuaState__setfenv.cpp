// FUNC_NAME: LuaState::setfenv
// 0x0062dd90: Implementation of Lua's setfenv (set function environment).
// Expects stack: arg1 = function (type 5), arg2 = new environment (table or function).

int LuaState::setfenv(lua_State* L) {
    // +0x0C: base stack pointer (StkId base)
    int* base = *(int**)((char*)L + 0x0C);
    // +0x08: top stack pointer (StkId top)
    int* top = *(int**)((char*)L + 0x08);  

    // Check that stack[2] is a function (type 5)
    int* secondSlot = base + 2; // offset 8 bytes = 2 int slots
    if (top <= secondSlot || secondSlot == nullptr || *secondSlot != 5) {
        // Error: first argument must be a function
        FUN_00627ac0(PTR_s_table_00e2a8b0);  // "bad argument #1 to 'setfenv'"
    }

    // Additional stack validation
    FUN_0062dbc0();  // likely luaD_checkstack or lua_lock

    // Check if the function's environment is protected
    int isProtected = FUN_0062dc80(L);
    if (isProtected != 0) {
        FUN_00627bd0("`setfenv' cannot change a protected environment");
    }

    // Pop two values from top (4 bytes each? actual TValue size may be 8)
    top = (int*)((char*)top - 0x10);  // -16 bytes
    // Copy values from base+8 and base+0xC into the new top position
    int* src = base;
    int* dst = top;
    *dst = *(int*)((char*)src + 8);   // copy base[1]
    *(dst + 1) = *(int*)((char*)src + 0xC); // copy base[2]
    top = (int*)((char*)top + 8);   // +8, effectively one slot

    // Re-evaluate base pointer after stack manipulation
    int* currentArg = *(int**)((char*)L + 0x0C);  // base
    // Condition: base < top, base not null, and base[0] is table (3) or function (4) with extra check
    if (currentArg < top && currentArg != nullptr) {
        if (*currentArg == 3 || 
            (*currentArg == 4 && 
             (FUN_00636850((undefined1 (*) [8])auStack_c) != 0))) { 
            float value = (float)FUN_006259b0(L, 1); // index 1 = first argument
            if (value == 0.0f) {
                // Set environment from the two values at current top-2
                *(int*)((char*)L + 0x40) = *(int*)((char*)top - 8);
                *(int*)((char*)L + 0x44) = *(int*)((char*)top - 4);
                top = (int*)((char*)top - 8); // pop
                return 0;
            }
        }
    }

    // Additional error handling
    int errorCheck = FUN_00626180();
    if (errorCheck != 0) {
        return 0;
    }

    // Fallback error
    FUN_00627bd0("`setfenv' cannot change environment of given function");
    // Force debug break (software interrupt 3)
    void (*breakFunc)() = (void(*)())swi(3);
    return breakFunc();
}