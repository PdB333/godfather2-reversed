//FUNC_NAME: lua_readUpvalues
void __thiscall lua_readUpvalues(uint upvalueCount, int* L, int closure)
{
    int* allocatedArray;
    uint allocSize;
    int newArray;
    int i;
    undefined4 value;
    undefined1 isZero;

    // Check Lua stack state (likely a stack guard)
    FUN_00641940();

    isZero = upvalueCount == 0;
    if ((int)upvalueCount < 0) {
        // Error: bad integer in function name
        FUN_00633920(*L, "bad integer in %s", L[4]);
    }

    // Validate upvalue count matches expected (stored at closure+0x44 as byte)
    if ((!(bool)isZero) && (upvalueCount != *(byte*)(closure + 0x44))) {
        FUN_00633920(*L, "bad nupvalues in %s: read %d; expected %d",
                     L[4], upvalueCount, (uint)*(byte*)(closure + 0x44));
    }

    int state = *L;
    allocSize = upvalueCount * 4;
    if (allocSize != 0) {
        if (allocSize > 0xfffffffc) {
            FUN_00633920(state, "memory allocation error: block too big");
        }
        newArray = (*DAT_012059dc)(0, allocSize); // custom allocator
        if (newArray != 0) {
            if (state != 0) {
                int* totalAlloc = (int*)(*(int*)(state + 0x10) + 0x24);
                *totalAlloc = *totalAlloc + allocSize;
            }
            goto LAB_00641e57;
        }
        if (state != 0) {
            FUN_00635a80(); // memory error handler
            return;
        }
    }
    newArray = 0;

LAB_00641e57:
    i = 0;
    *(int*)(closure + 0x1c) = newArray; // upvalue array pointer
    *(uint*)(closure + 0x24) = upvalueCount; // upvalue count
    if (0 < (int)upvalueCount) {
        do {
            value = FUN_00641a50(L); // read next value from Lua stack
            *(undefined4*)(*(int*)(closure + 0x1c) + i * 4) = value;
            i = i + 1;
        } while (i < (int)upvalueCount);
    }
    return;
}