// FUNC_NAME: initializeFromGlobalManager
void __fastcall initializeFromGlobalManager(void* thisObject)
{
    // Dereference global singleton at DAT_012233a0+4 to get a pointer
    // This pointer likely points to a large structure (e.g., GameManager)
    // Subtract offset 0x1f30 to get a sub-object (e.g., a component or manager)
    void* subObject = *(*((int**)(DAT_012233a0 + 4))) - 0x1f30;
    if ((subObject != 0) && (*((int**)DAT_012233a0 + 1) != 0))
    {
        // Call virtual function at vtable offset 0x2c4 (index 177) on this object
        // passing the subObject as an argument
        (**(void (__fastcall**)(void*, void*))(*(int*)thisObject + 0x2c4))(thisObject, subObject);
    }
}