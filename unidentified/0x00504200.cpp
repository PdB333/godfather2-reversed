// FUN_00504200: UnknownClass::initWithSize80
// This function is a thin wrapper that calls FUN_004eba90 with a constant value of 0x50 (80).
// param1 is likely the 'this' pointer (implicit __thiscall), param2 is an additional argument.
// The constant 0x50 may represent a buffer size, limit, or enumeration value.
// The final parameter 1 could be a boolean flag (e.g., enable, overwrite).
void UnknownClass::initWithSize80(int param2)
{
    int local_4 = 0x50; // constant value 80
    FUN_004eba90(this, param2, &local_4, 1); // call to underlying function at 0x004eba90
}