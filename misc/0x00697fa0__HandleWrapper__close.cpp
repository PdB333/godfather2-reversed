// FUNC_NAME: HandleWrapper::close
int __fastcall HandleWrapper::close(int this)
{
    BOOL BVar1;
    BVar1 = CloseHandle(*(HANDLE *)(this + 0x18));
    if (BVar1 == 0) {
        return 2; // CloseHandle failed
    }
    *(HANDLE *)(this + 0x18) = (HANDLE)0xffffffff; // Invalidate handle
    return 8; // Success
}