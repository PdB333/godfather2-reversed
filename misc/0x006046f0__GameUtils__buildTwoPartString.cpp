// FUNC_NAME: GameUtils::buildTwoPartString
void GameUtils::buildTwoPartString(int *param_1) // param_1 is an array of two undefined4s
{
    // Allocate two 2-byte buffers (like short strings with null terminator)
    byte *firstPart = (byte *)MEMALLOC(2);
    *firstPart = DAT_00e337cc; // global byte 1
    firstPart[1] = 0; // null terminator

    byte *secondPart = (byte *)MEMALLOC(2);
    *secondPart = DAT_00e337cd; // global byte 2
    secondPart[1] = 0;

    // Copy first part into some buffer? Parameters: dest, size, source?
    // FUN_004d3ca0 likely copies data: (dest, src, count, flag) or (dest, size, src, size)
    FUN_004d3ca0(firstPart, 1, *param_1, param_1[1]);

    // Null callback pointer
    void (*callback)(int) = nullptr;

    // Another copy? Parameters oddly ordered
    FUN_004d3ca0(local_20, local_1c, secondPart, 1); // local_20 and local_1c are uninitialized in decomp

    // Possibly initializes a structure with callback
    int local_10[3];
    FUN_004d3e20(local_10);

    if (local_10[0] != 0) {
        callback(local_10[0]); // callback is null, so this would crash if called
    }

    if (local_20 != 0) {
        (*(void (*)(int))0x0)(local_20); // dereference null - possible decomp artifact
    }

    // Free allocated buffers
    thunk_FUN_009c8eb0(secondPart);
    thunk_FUN_009c8eb0(firstPart);
}