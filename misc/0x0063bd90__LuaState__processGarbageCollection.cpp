// FUNC_NAME: LuaState::processGarbageCollection
// Address: 0x0063bd90
// This function appears to process garbage collection for a custom Lua binding (tolua).
// It manipulates a stack-like structure within the Lua state, converting and copying values
// based on type info stored alongside each stack entry.

int LuaState::processGarbageCollection(int param_1) // param_1 is 'this' (LuaState*)
{
    int* stackPtr;       // pointer to current position in stack (at this+0xC)
    int* stackTop;       // pointer to top of stack (at this+0x8)
    int* convertedType;  // temporary for type conversion results
    int value;           // saved value from stack (uVar1)
    int* srcPtr;         // pointer to source data on stack
    int* dstPtr;         // pointer to destination (replacement) data

    // Get stack base pointer (this+0xC is likely a "current stack frame" or "stack base")
    stackPtr = *(int**)(param_1 + 0xC);
    // Check if stackPtr < stackTop and non-null
    if (stackPtr < *(int**)(param_1 + 8) && stackPtr != (int*)0x0) {
        // Examine the type stored at the stack entry (*stackPtr)
        if (*stackPtr == 2) {
            // Type 2: string (or similar) – source is directly at stackPtr[1]
            srcPtr = (int*)(stackPtr[1]);
        }
        else if (*stackPtr == 7) {
            // Type 7: userdata – source is offset by 0x10 from stackPtr[1]
            srcPtr = (int*)(stackPtr[1] + 0x10);
        }
        else {
            srcPtr = (int*)0x0; // unknown type, no source
        }
    }
    else {
        srcPtr = (int*)0x0;
    }

    // Save the value at the source pointer (if any)
    value = *srcPtr;  // uVar1

    // Call the tolua_gc hook (probably registers the object for GC)
    FUN_00625ca0(param_1, "tolua_gc");

    // Now work with the stack top (this+0x8 points to the top)
    stackTop = (int*)*(int*)(param_1 + 8);
    // Check the type at the top of stack (stackTop[-2] because each entry is 2 ints: type + value)
    if (*(int*)(stackTop - 8) == 3) {
        // Type 3: float? Check if float identity fails (NaN? Or different check)
        if ((float)(int)*(float*)(stackTop - 4) != *(float*)(stackTop - 4)) {
            goto L_type_fallback;
        }
        // Normal float – get conversion function for type 3
        dstPtr = (int*)FUN_00637f10(); // maybe "to_float" converter
    }
    else if (*(int*)(stackTop - 8) == 4) {
        // Type 4: integer – get conversion function
        dstPtr = (int*)FUN_00637f90(); // maybe "to_int" converter
    }
    else {
L_type_fallback:
        // Fallback: generic conversion
        dstPtr = (int*)FUN_00637ea0(); // maybe "to_generic" converter
    }
    // Store the conversion descriptor at the stack entry (overwrites type and value)
    *(int*)(stackTop - 8) = *dstPtr;      // new type
    *(int*)(stackTop - 4) = dstPtr[1];    // new value reference

    // Now push a new entry onto the stack: type=2, value=uVar1
    // The stack pointer (this+0x8) is incremented by 8 (one entry)
    dstPtr = *(int**)(param_1 + 8);
    *dstPtr = 2;        // type 2 (string? or object?)
    dstPtr[1] = value;  // the previously saved value
    *(int*)(param_1 + 8) = *(int*)(param_1 + 8) + 8; // advance stack top

    // Now examine the new stack top (which is the entry just pushed)
    stackTop = (int*)*(int*)(param_1 + 8); // same as after increment
    // Check type at stackTop[-2] (the original entry we replaced earlier? Wait, careful with indexing)
    // Actually after push, stackTop points to the new free slot; we need to look at the entry we just pushed (at stackTop-2)?
    // The code does: iVar2 = *(int*)(param_1+8); then iVar3 = *(int*)(iVar2 + -8); 
    // So iVar2 = new stack top pointer, iVar3 = type of the entry we just pushed (stackTop[-2])
    if (*(int*)(stackTop - 8) == 3) {
        if ((float)(int)*(float*)(stackTop - 4) == *(float*)(stackTop - 4)) {
            // Also float identity check? Different condition? Actually seeing if float == int conversion matches.
            convertedType = (int*)FUN_00637f10();
            goto L_got_converter;
        }
    }
    else if (*(int*)(stackTop - 8) == 4) {
        convertedType = (int*)FUN_00637f90();
        goto L_got_converter;
    }

    // Fallback
    convertedType = (int*)FUN_00637ea0();
L_got_converter:
    // Apply conversion to the pushed entry (overwrites its type/value again)
    *(int*)(stackTop - 8) = *convertedType;
    *(int*)(stackTop - 4) = convertedType[1];

    // Now peek at the previous entry (the one we modified earlier) from stack top
    dstPtr = *(int**)(param_1 + 8); // current stack top pointer (after push)
    // Check if the entry at offset -2 from that (i.e., the entry we modified earlier) has type 6
    if ((dstPtr - 2 != (int*)0x0) && (dstPtr[-2] == 6)) {
        // Type 6: Probably a table or object that needs additional processing
        srcPtr = *(int**)(param_1 + 0xC); // stack base
        // Copy two ints from stack base to current stack top (overwrite pushed entry)
        *dstPtr = *srcPtr;
        dstPtr[1] = srcPtr[1];
        *(int*)(param_1 + 8) = *(int*)(param_1 + 8) + 8; // advance stack top again

        // Call a function to handle the structure (maybe to perform a table assignment)
        FUN_006362d0(param_1, *(int*)(param_1 + 8) + -0x10, 0);

        // Push another entry: type=2, value=uVar1
        dstPtr = *(int**)(param_1 + 8);
        *dstPtr = 2;
        dstPtr[1] = value;
        *(int*)(param_1 + 8) = *(int*)(param_1 + 8) + 8;

        // Push a zero (type 0, value 0)
        **(int**)(param_1 + 8) = 0;
        *(int*)(param_1 + 8) = *(int*)(param_1 + 8) + 8;

        // Get the stack top after the additional pushes
        stackTop = (int*)*(int*)(param_1 + 8);
        // Call a conversion on something from earlier stack entries
        dstPtr = (int*)FUN_00638020(param_1, *(int*)(stackTop - 0x14));
        *dstPtr = *(int*)(stackTop - 8);
        dstPtr[1] = *(int*)(stackTop - 4);

        // Rewind stack by 0x10 (two entries) twice? Actually (stack -= 0x10) then (stack -= 0x10) => total -0x20
        *(int*)(param_1 + 8) = *(int*)(param_1 + 8) - 0x10;
        *(int*)(param_1 + 8) = *(int*)(param_1 + 8) - 0x10;
        return 0;
    }

    // If not type 6, just rewind stack by 0x10 (one entry? Actually two ints = 8 bytes, but 0x10 = 16 bytes = two entries)
    *(int*)(param_1 + 8) = *(int*)(param_1 + 8) - 0x10;
    return 0;
}