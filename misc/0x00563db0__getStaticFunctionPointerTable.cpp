// FUNC_NAME: getStaticFunctionPointerTable
// Address: 0x00563db0
// Identifies role: Returns the address of a static function pointer table (likely a vtable or callback table)
void** getStaticFunctionPointerTable(void)
{
    // Returns a reference to a static pointer stored in data section at 0x00e3a4b4
    return &PTR_FUN_00e3a4b4;
}