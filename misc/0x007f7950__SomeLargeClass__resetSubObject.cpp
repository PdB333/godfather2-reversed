// FUNC_NAME: SomeLargeClass::resetSubObject
void __thiscall SomeLargeClass::resetSubObject(int this) {
    // Clear field at offset 0x838 (likely a flag or pointer)
    *(int*)(this + 0x838) = 0;

    // Get sub-object at offset 0x828 and call its method (returns something)
    int subObj = *(int*)(this + 0x828);
    // Call method on sub-object (likely reset or initialize)
    int result = FUN_00540cc0(subObj);
    // Call another method on the returned object
    FUN_0054e940(result);
}