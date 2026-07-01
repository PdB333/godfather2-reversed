// FUNC_NAME: SomeClass::updateSomething
void __fastcall SomeClass::updateSomething(int thisPtr)
{
    // Call FUN_008934e0 with the value at this+0x54 and pointer to this+0x74
    FUN_008934e0(*(int*)(thisPtr + 0x54), thisPtr + 0x74);
    
    // Call FUN_00895000 with pointer to this+0x50 and value at this+0x54
    FUN_00895000(thisPtr + 0x50, *(int*)(thisPtr + 0x54));
    
    return;
}