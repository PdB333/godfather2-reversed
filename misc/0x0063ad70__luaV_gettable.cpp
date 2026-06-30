// FUNC_NAME: luaV_gettable
// Function at 0x0063ad70: Handles Lua table access with __index metamethod
// State structure: lua_State* (param_1)
// Offsets: +0x08 = stack top pointer, +0x0C = stack base, +0x10 = registry or global table?
// TValue: 8 bytes: [type (4 bytes), value (4 bytes)]
// Opcodes: 3=number, 4=string? 5=string, 6=function, 7=table? (EA custom)

int luaV_gettable(lua_State *L) {
    TValue *top;
    TValue *base;
    TValue *entry;
    int type;
    TValue *t;
    int extra;

    // Push constant string (likely "__index" or "__newindex"?)
    lua_pushstring(L, &DAT_00e416ec);

    // Get current top of stack
    top = (TValue *)L->stackTop;   // +0x08
    entry = top - 1;               // point to the value just before top (the one we are accessing?)
    type = entry->type;            // +0 (offset -8 from top)
    if (type == 3) {
        // Number type - check if integer conversion needed
        if ((float)(int)entry->value.f != entry->value.f) goto LAB_0063adc6;
        // Convert to integer
        t = (TValue *)luaV_tointeger(L);
    }
    else if (type == 4) {
        // String type?
        t = (TValue *)luaV_tostring(L);
    }
    else {
LAB_0063adc6:
        // Default conversion
        t = (TValue *)luaV_toany(L);
    }

    // Overwrite the entry's type and value with the converted result
    entry->type = t->type;
    entry->value = t->value;

    // Now examine the item below the entry (if any)
    base = (TValue *)L->stackBase; // +0x0C? Actually it's L->stackBase (maybe +0x0C)
    top = (TValue *)L->stackTop;
    if ((base != NULL) && (base->type == 5)) {  // 5 = string key
        // Read key from the string's internal data
        int keyOffset = *(int *)(base[1].value.ptr + 8); // base[1] is the value part of the string TValue
        *(int *)(&top->type) = 5;      // Set new entry type to string
        *(int *)(&top->value) = keyOffset; // Set value to the key
        L->stackTop = (int *)((char *)L->stackTop + 8); // advance top

        lua_pushstring(L, "__index");
        luaV_pushvalue(L, 0); // copy top? (maybe duplicates)

        // Copy two TValues from base to top?
        // (This likely copies the key and value from the string or table)
        top = (TValue *)L->stackTop;
        TValue *src = (TValue *)L->stackBase;
        top[0] = src[0];
        top[1] = src[1];
        L->stackTop = (int *)((char *)L->stackTop + 16); // advance 2 TValues

        // Now check the opcode just before the new top (the "__index" string?)
        TValue *newEntry = top - 2; // point to the first copied TValue
        if (newEntry->type == 6) {  // 6 = function
            // Call the __index function with appropriate arguments
            luaV_call(L, newEntry, 1); // FUN_006362d0?
            return 1;
        }
        if (newEntry->type == 5) { // 5 = table
            // Look up in that table with the key
            TValue *result = luaV_gettable(L, newEntry); // recursive?
            // This call seems to be FUN_00633cb0
            // Actually it's luaV_gettable again?
            // For now, we assume it returns a TValue.
            L->stackTop = (int *)((char *)L->stackTop - 8); // pop one?
            *(int *)((char *)L->stackTop - 8) = result->type;
            *(int *)((char *)L->stackTop - 4) = result->value;
            return 1;
        }
    }

    // Fallback: push nil
    **(int **)(L->stackTop) = 0;   // type = nil
    L->stackTop = (int *)((char *)L->stackTop + 8);
    return 1;
}