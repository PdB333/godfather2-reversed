// FUNC_NAME: UnknownClass::setThreeValues
void __thiscall UnknownClass::setThreeValues(int this, int unused2, int param3, int unused4, int param5, int param6)
{
    // +0x70: some flag or member
    // +0x74, +0x78, +0x7c: three stored values from parameters
    FUN_0059b5e0(); // base constructor or global initialization
    *(char *)(this + 0x70) = 0; // clear flag
    *(int *)(this + 0x74) = param3; // first stored value
    *(int *)(this + 0x78) = param5; // second stored value
    *(int *)(this + 0x7c) = param6; // third stored value
}