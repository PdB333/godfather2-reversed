// FUNC_NAME: SomeClass::delegateToFunction
void __thiscall SomeClass::delegateToFunction(SomeClass* this, uint arg)
{
    // Passes the member at offset +0x20 (likely a pointer or handle) 
    // and the given argument to another function
    FUN_006052d0(*(uint*)((uint)this + 0x20), arg);
}