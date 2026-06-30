// FUNC_NAME: Entity::getSetFlags
uint Entity::getSetFlags(uint mask)
{
    // local_4: output parameter for virtual call (unused but passed)
    int local_4 = 0;

    // Virtual call at vtable+0x10: checks if the given mask flags are set.
    // Returns char (bool).
    char result = (**(char (__thiscall **)(uint, int*))(*(int*)this + 0x10))(mask, &local_4);

    // Return mask if true, else 0.
    // -(uint)(result != 0) creates 0xFFFFFFFF if true, 0x0 if false.
    return -(uint)(result != 0) & mask;
}