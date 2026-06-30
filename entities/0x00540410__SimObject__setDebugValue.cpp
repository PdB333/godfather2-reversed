// FUNC_NAME: SimObject::setDebugValue
void __thiscall SimObject::setDebugValue(int this, int value)
{
    // +0x28: isActive flag (bool)
    if (*(char *)(this + 0x28) != '\0') {
        FUN_00ab51e0(1); // Some debug utility call (likely logging or counter)
        g_globalDebugValue = value; // Global debug target variable at 0x103b274
    }
}