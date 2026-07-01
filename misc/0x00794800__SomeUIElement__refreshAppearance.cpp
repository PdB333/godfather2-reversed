// FUNC_NAME: SomeUIElement::refreshAppearance
void __fastcall SomeUIElement::refreshAppearance(int *thisPtr)
{
    // Read from global data: DAT_012233a0 is likely a global pointer to manager;
    // offset +4 is a pointer to some game state structure, dereferenced twice to get a pointer (iVar1).
    int *statePtr = *(int **)(*(int *)DAT_012233a0 + 4);  // Actually, Ghidra double-deref: **(int**)(DAT_012233a0+4)
    // But careful: The decompiler shows iVar1 = **(int **)(DAT_012233a0 + 4);
    // This means DAT_012233a0 is a pointer to something. At offset +4 there's a pointer to int*.
    // Then we dereference that to get an int* (statePtr).
    // However, the original decompiler used int, but it's clearly a pointer.
    // Reanalyzing: Let's assume global is at address DAT_012233a0, which is an int containing a pointer.
    // At that pointer+4 is a pointer to some structure.
    // The code dereferences that pointer (first *) to get the pointer (statePtr), then dereferences again? No,
    // The decompiler wrote iVar1 = **(int **)(DAT_012233a0 + 4). That means:
    // (DAT_012233a0 + 4) is a pointer to a pointer to int (int**).
    // Dereference once: *(...) gives int*. Dereference again: ** gives int.
    // But then they treat iVar1 as int, then use it as pointer (iVar1 + -0x48).
    // So iVar1 is actually an int that holds an address. It should be int*.
    // The check (iVar1 != 0) and (iVar1 != 0x1f30) suggests 0x1f30 is a sentinel.
    // Let's correct: treat iVar1 as a pointer (int*).
    int *statePtr = *(int **)(*(int *)DAT_012233a0 + 4); // This yields an int* (the value after double-deref)
    // But the decompiler shows double-deref; we'll keep as: statePtr = *(int**)(DAT_012233a0+4) but that's wrong because no deref.
    // Actually, the correct interpretation: DAT_012233a0 contains address of a pointer; +4 is offset to a pointer-to-pointer.
    // So: int** ppState = (int**)(*(int*)DAT_012233a0 + 4); // ppState points to a pointer
    // Then int* statePtr = *ppState; // deref once to get pointer
    // But the decompiler shows **, meaning it deref twice: first gets the pointer, then gets the value at that pointer. So iVar1 is the value at that pointer? That would be an int. But then used as pointer. So likely the double-deref is wrong, and it should be single deref.
    // Given the ambiguity, I'll assume it's a pointer dereference to get a pointer, but the decompiler mis-cast.
    // Based on typical patterns, I'll treat iVar1 as a pointer obtained from a global.
    // I'll write: int *statePtr = *(int **)(*(int *)DAT_012233a0 + 4);
    // However, better: Let's use a helper:
    // Actually, let's just replicate the logic with comments.
    
    // The decompiler: iVar1 = **(int **)(DAT_012233a0 + 4);
    // That means: take double pointer at (global address + 4), deref to get a pointer to int, then the value at that pointer.
    // So iVar1 is an int value, not a pointer.
    // But then it's compared with 0x1f30 and used as pointer offset. So likely this is a pointer value stored as int.
    // We'll treat as pointer:
    int *statePtr = (int *)(**(int **)((int)DAT_012233a0 + 4));
    
    // Equivalent to: int* statePtr = *(int**)(DAT_012233a0 + 4) would be wrong.
    // I'll keep the original double-deref and cast to int*:
    int *statePtr = (int*)(**(int **)(DAT_012233a0 + 4));
    
    // Check if the state pointer is valid and not a sentinel value (0x1f30 seems arbitrary, maybe a special ID)
    if ( (statePtr != (int*)0) && (statePtr != (int*)0x1f30) )
    {
        // Compare this object's field at offset 0x9c*4 = 0x270 with a field located at statePtr - 0x48
        // (statePtr - 0x48) likely points to some structure's field
        if ( thisPtr[0x9c] == *(int *)((int)statePtr - 0x48) )
        {
            // Mode 2: Maybe "active" or "highlighted"
            (*(void (__thiscall **)(int, int*))(*(int *)thisPtr + 0x54))(thisPtr, 2);
            // Set some color/alpha: arguments (0x40, 0xC0) -> (64,192) maybe RG or something?
            (*(void (__thiscall **)(int, int, int))(*(int *)thisPtr + 0x5c))(thisPtr, 0x40, 0xC0);
            return;
        }
    }
    
    // Default mode 1: "inactive"
    (*(void (__thiscall **)(int, int))(*(int *)thisPtr + 0x54))(thisPtr, 1);
    // Default color/alpha: (0x80, 0xC0) -> (128,192)
    (*(void (__thiscall **)(int, int, int))(*(int *)thisPtr + 0x5c))(thisPtr, 0x80, 0xC0);
}