// FUNC_NAME: Entity::isActive
bool __fastcall Entity::isActive(int thisPtr)
{
    // Check for a specific invalid pointer sentinel (-0x3C0 = -960 = 0xFFFFFC40)
    // and test flag at offset 0x490 (bit 27, value 0x8000000)
    if (thisPtr != -0x3C0 && (*(uint*)(thisPtr + 0x490) & 0x8000000) != 0)
    {
        return true;
    }
    return false;
}