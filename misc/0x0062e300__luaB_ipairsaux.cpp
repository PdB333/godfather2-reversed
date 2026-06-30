// FUNC_NAME: luaB_ipairsaux
// Function Address: 0x0062e300
// Role: Lua iterator auxiliary function for ipairs. 
// Iterates over array-like tables by incrementing the previous key and fetching the value.
// Returns 2 if the next value exists (key and value pushed), 0 if not (no values pushed).

// Lua state offsets (custom EARS Lua implementation):
// +0x0: unknown
// +0x08: top of stack (TValue*)
// +0x0C: base of current function arguments (TValue*)
// Each TValue is 8 bytes: [4 bytes tag, 4 bytes value]
// Tags: 3 = number, 4 = string, 5 = table, -1 = nil? (custom)

// Helper functions (named based on typical Lua runtime roles):
// FUN_00636850: attempts to convert a string on the stack to a number (if possible).
// FUN_00627ac0: likely lua_getglobal (fetches a global table by name).
// FUN_00627360: likely lua_error (raises a runtime error).
// FUN_00638920: likely lua_getfield (retrieves a field from a table by string key). Called with "ipairs".
// FUN_00625e70: likely lua_settop / lua_pushvalue (adjusts stack).
// FUN_00637f10: likely lua_gettable / lua_rawgeti (fetches table[t] where t is a number key).

// Global constants:
// PTR_s_table_00e2a8b0: string "table" (global name).
// DAT_00e2b05c: sentinel value (0.0f).
// DAT_00e2b1a4: increment value (1.0f).

int __cdecl luaB_ipairsaux(lua_State* L)
{
    // base pointer to the first argument (the table is at base[0], previous key at base[1])
    TValue* args = *(TValue**)(L + 0x0C);
    TValue* prevKey = (TValue*)((int)args + 8); // args[1] — because each TValue is 8 bytes

    float currentIndex = 0.0f;

    // Check the type of the previous key (the one provided by the ipairs control variable)
    if ( (*(int*)args < *(int*)(L+8)) && (prevKey != nullptr) )
    {
        if (prevKey->tag == 3) // number
        {
            currentIndex = (float)prevKey->value;
            goto L_CheckTable;
        }
        else if (prevKey->tag == 4) // string
        {
            // Attempt to convert string to a number
            int converted = FUN_00636850(&L);
            if (converted != 0)
            {
                int local_8 = 3; // tag number
                int local_4 = (int)L;
                prevKey = (TValue*)&local_8;
                currentIndex = (float)prevKey->value;
            }
        }
    }
    prevKey = nullptr; // fallthrough

L_CheckTable:
    // Ensure the table (first argument) is present and of type 5 (table)
    TValue* tablePtr = *(TValue**)(L + 0x0c); // base[0]
    TValue* stackTop = *(TValue**)(L + 0x08);
    if ( (stackTop <= tablePtr) || (tablePtr == nullptr) || (tablePtr->tag != 5) )
    {
        FUN_00627ac0(PTR_s_table_00e2a8b0); // raise "table expected"
    }

    // Check for end condition: currentIndex equals sentinel and the next element is nil
    if ( (currentIndex == DAT_00e2b05c) &&
         ( (TValue*)((int)prevKey + 16) <= stackTop || prevKey == nullptr || prevKey->tag == -1) )
    {
        // End of iteration – push nil and return 3? Actually pushes final control values
        if ( *(uint*)(*(int*)(L + 0x10) + 0x20) <= *(uint*)(*(int*)(L + 0x10) + 0x24) )
        {
            FUN_00627360(); // potential error handler
        }
        TValue* newTop = *(TValue**)(L + 0x08);
        newTop->tag = 4;
        newTop->value = FUN_00638920(L, "ipairs", 6); // push global function "ipairs"
        *(int*)(L + 0x08) += 8;
        FUN_00625e70(); // adjust stack
        newTop = *(TValue**)(L + 0x08);
        TValue* current = *(TValue**)(L + 0x0C);
        newTop->tag = current->tag;
        newTop->value = current->value;
        *(int*)(L + 0x08) += 8;
        newTop = *(TValue**)(L + 0x08);
        newTop->tag = 3;
        newTop->value = 0;
        *(int*)(L + 0x08) += 8;
        return 3; // number of results
    }

    // Next iteration: increment index
    currentIndex += DAT_00e2b1a4; // add 1.0
    TValue* newTop = *(TValue**)(L + 0x08);
    newTop->tag = 3;
    newTop->value = (int)currentIndex;
    *(int*)(L + 0x08) += 8;

    // Fetch table[currentIndex]
    TValue* fetched = (TValue*)FUN_00637f10(); // pushes the value from table
    TValue* newTop2 = *(TValue**)(L + 0x08);
    newTop2->tag = fetched->tag;
    newTop2->value = fetched->value;
    *(int*)(L + 0x08) += 8;

    // Check if the fetched value is nil
    TValue* lastPushed = *(TValue**)(L + 0x08) - 1;
    if (lastPushed == nullptr)
        return 2; // keep pushing? Actually no, fallthrough
    return -((lastPushed->value != 0) & 2); // returns 2 if non-nil, 0 if nil
}