// FUNC_NAME: IsObjectValid (generic object state check via global vtable)
bool IsObjectValid(void* object)
{
    // Call virtual function at vtable offset 0x34 on the object
    // The vtable is stored in a global pointer (DAT_01223510)
    // This is likely an interface or base class vtable
    char result = (*(code**)(*(int*)DAT_01223510 + 0x34))(object);
    return result != '\0';
}