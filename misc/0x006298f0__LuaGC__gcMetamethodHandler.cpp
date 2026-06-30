// FUNC_NAME: LuaGC::gcMetamethodHandler

// Reconstructed tolua++ garbage collection metamethod for The Godfather 2 (EA EARS engine)
// 0x006298f0
// Handles __gc for userdata objects, reclaiming associated game entity references

int __cdecl LuaGC_gcMetamethodHandler(LuaState* L) {
    // LuaState structure offsets:
    // +0x08: top (pointer to current stack top, a TValue*)
    // +0x0C: current (pointer to currently evaluated TValue, probably argument)
    // +0x10: extra state (maybe registry or metatable)
    // +0x20, +0x24: some internal counters (e.g., allocated objects)

    TValue* current = *(TValue**)(L + 0x0C);   // current TValue being garbage-collected
    bool success = false;

    // Ensure the current pointer is valid and within the stack bounds
    if (current < *(TValue**)(L + 0x08) && current != nullptr) {
        int type = current->type;
        if (type == 2 || type == 7) { // Light userdata (2) or full userdata (7)
            void* objectPtr;
            if (type == 2) {
                objectPtr = (void*)current->value; // lightuserdata holds pointer directly
            } else if (type == 7) {
                // Full userdata: the value is a pointer to the userdata block; +0x10 is the actual object pointer
                objectPtr = *(void**)((char*)current->value + 0x10);
            } else {
                objectPtr = nullptr;
            }

            // Retrieve the userdata's contained pointer and clear internal reference
            int objectID = *(int*)objectPtr;
            *(int*)(*(int*)(L + 0x10) + 0x20) = 0; // Clear some allocation counter

            if (*(uint*)(*(int*)(L + 0x10) + 0x20) <= *(uint*)(*(int*)(L + 0x10) + 0x24)) {
                // This condition likely checks for memory boundary; call emergency handler if needed
                FUN_00627360(); // Possibly a panic/abort function
            }

            // Call the actual tolua++ garbage collection routine (named "tolua_gc")
            FUN_00625ca0(L, "tolua_gc"); // pushes the string "tolua_gc" and calls it
            FUN_00625e70(); // Stack stability check

            // Replace the current TValue with a light userdata pointing to the freed object ID
            TValue* top = *(TValue**)(L + 0x08);
            top->type = 2;          // light userdata
            top->value = objectID;  // the game object ID (or pointer)
            *(TValue**)(L + 0x08) = top + 1; // increment stack top

            FUN_00625e70(); // Another stability check

            // If the previous stack slot (just below new top) is a function (type 6), 
            // then we need to push an additional light userdata for the return value, 
            // and then adjust the stack to form a call/return pair.
            top = *(TValue**)(L + 0x08);
            if ((top - 2) != nullptr && (top - 2)->type == 6) {
                // Push another light userdata (type 2) with the same objectID
                top->type = 2;
                top->value = objectID;
                *(TValue**)(L + 0x08) = top + 1;

                // Push a nil (type 0) as placeholder
                top = *(TValue**)(L + 0x08);
                top->type = 0;
                top->value = 0;
                *(TValue**)(L + 0x08) = top + 1;

                // Call some function to rearrange the stack for the pending function call
                // FUN_00638020 takes the Lua state and an offset (likely the number of arguments)
                int newTop = *(int*)(L + 0x08);
                TValue* result = (TValue*)FUN_00638020(L, *(undefined4*)(newTop - 0x1C));
                result->type = *(undefined4*)(newTop - 8);
                result->value = *(undefined4*)(newTop - 4);
                *(int*)(L + 0x08) = newTop - 0x10; // revert stack to hide the call setup
                success = true;
            }
        }
    }

    // Push boolean result (success) onto the stack
    TValue* top = *(TValue**)(L + 0x08);
    top->type = 1;      // boolean
    top->value = (uint)success;
    *(TValue**)(L + 0x08) = top + 1;

    return 1; // Number of return values (one boolean)
}