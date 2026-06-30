// FUNC_NAME: SomeClass::delegateToSubObject
// Calls a function on the sub-object at offset +0x9c from 'this'
// The inner function at 0x006b45e0 takes (subObject*, arg1, arg2)
void __thiscall SomeClass::delegateToSubObject(int arg1, int arg2) {
    // Sub-object is at this + 0x9c (likely a component or state machine)
    void* subObject = (void*)((char*)this + 0x9c);
    // Delegate to sub-object function (defined at 0x006b45e0)
    // Using a function pointer to avoid defining the sub-object's type
    typedef void (*SubObjectFunc)(void*, int, int);
    ((SubObjectFunc)0x006b45e0)(subObject, arg1, arg2);
}