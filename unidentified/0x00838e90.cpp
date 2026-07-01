// FUN_NAME: handleEventOrError
void __fastcall handleEventOrError(int thisPtr)
{
    int result = 0;          // local_10
    int someParam = 0;       // local_c
    int unused = 0;          // local_8
    void __fastcall (*callback)(int) = nullptr; // local_4

    int flag = *(int *)(thisPtr + 0x8c); // +0x8c: some flag/state
    int errorCode = (-(uint)(flag != 0) & 0xdd771a01) + 0x3af3f06f;
    FUN_00603330(errorCode, &result);
    FUN_004d44b0(10);
    FUN_004d43f0(result, 0, someParam);
    if (result != 0) {
        callback(result); // WARNING: callback is null, this will crash
    }
}