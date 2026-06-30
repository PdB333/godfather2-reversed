// FUNC_NAME: Entity::initComponents
void __thiscall Entity::initComponents(int thisPtr, undefined4 param2, undefined4 param3, undefined4 param4, undefined4 param5)
{
    // Call initialization function with param2, param3, param5
    FUN_006042a0(param2, param3, param5);
    
    // Initialize component at offset +0xB4 (e.g., a sub-object or pointer)
    FUN_004d4300(thisPtr + 0xB4);
    
    // Set up something using param5, a global constant, and param4
    FUN_004d4b00(param5, &DAT_00e4086c, param4);
    
    // Initialize component at offset +0xC4
    FUN_004d4300(thisPtr + 0xC4);
}