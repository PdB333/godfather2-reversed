// FUNC_NAME: invokeVirtualThenGlobal
void __thiscall invokeVirtualThenGlobal(int* thisPtr)
{
    // Call virtual member function at vtable offset 0x44
    (*(void (__thiscall**)(int*))(*(int*)thisPtr + 0x44))(thisPtr);

    // Call a global/static function at 0x00594420
    FUN_00594420();
}