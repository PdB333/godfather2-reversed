// FUNC_NAME: Entity::isActiveAndReady
bool __thiscall Entity::isActiveAndReady(Entity* thisPtr)
{
    byte flags = *(byte*)((int)thisPtr + 0x2C); // flags field at +0x2C (bit0=active, bit5=suspended, bit7=negative)
    if (((flags & 0x20) == 0) &&    // not suspended (bit5 clear)
        ((flags & 1) != 0) &&       // active (bit0 set)
        (-1 < (char)flags))         // sign bit clear (bit7 clear)
    {
        return true;
    }
    return false;
}