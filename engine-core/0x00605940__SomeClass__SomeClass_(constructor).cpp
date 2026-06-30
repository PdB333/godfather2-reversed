// FUNC_NAME: SomeClass::SomeClass (constructor)
undefined4 __thiscall SomeClass::SomeClass(byte ownsMemoryFlag)
{
    // Call base class constructor (e.g., EARS::Framework::Object)
    BaseClass::BaseClass();
    // If the object was heap-allocated (owns its memory), perform additional setup
    // (e.g., register for automatic cleanup or set a dynamic allocation flag)
    if ((ownsMemoryFlag & 1) != 0) {
        FUN_009c8eb0(this);
    }
    return this;
}