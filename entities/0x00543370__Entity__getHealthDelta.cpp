// FUNC_NAME: Entity::getHealthDelta
// Address: 0x00543370
// Calls a virtual function at vtable offset 0x1fc (index 127) and subtracts from member at offset 0x2BC (0xaf*4).
// Possibly returns health remaining (max health - current health) or similar.
int __fastcall Entity::getHealthDelta(int *thisPtr)
{
    // Virtual function at vtable index 127 (offset 0x1fc)
    int (*getSomeValue)(int *) = (int (*)(int *))(*(int *)(*(int *)thisPtr + 0x1fc));
    
    // Member at offset 0x2BC (this[0xaf])
    return thisPtr[0xaf] - getSomeValue(thisPtr);
}