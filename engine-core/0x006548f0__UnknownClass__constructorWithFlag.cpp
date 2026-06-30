// FUNC_NAME: UnknownClass::constructorWithFlag
undefined4 __thiscall UnknownClass::constructorWithFlag(byte flag)
{
    // Call base class constructor or initializer
    baseClassConstructor(); // FUN_0065e330
    
    // If flag bit 0 is set, call registration function (e.g., add to manager list)
    if (flag & 1) {
        registerToManager(this); // FUN_009c8eb0(this)
    }
    
    return this;
}