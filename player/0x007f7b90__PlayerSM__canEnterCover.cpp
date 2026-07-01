// FUNC_NAME: PlayerSM::canEnterCover
bool __fastcall PlayerSM::canEnterCover(int thisPtr)
{
    // +0x1028: bool - some flag (e.g., isAlive, isActive)
    // +0x1018: uint8 - state enum (0x02 = some specific state like "on foot")
    // +0x8e4: uint32 - bitfield of flags (bit 2 = cover-related flag)
    // +0x1010: int32 - current action/weapon type enum
    
    bool result = false;
    if ((*(char*)(thisPtr + 0x1028) != '\0') &&          // is alive/active
        (*(char*)(thisPtr + 0x1018) == '\x02') &&        // in appropriate state (on foot)
        ((*(uint32_t*)(thisPtr + 0x8e4) >> 2 & 1) != 0 || // has cover ability flag
         (((int iVar1 = *(int*)(thisPtr + 0x1010);       // current weapon/action
           iVar1 == 0x2c || iVar1 == 0x2d) ||            // weapon types that allow cover
          iVar1 == 0x2e))))                              // another weapon type
    {
        result = true;
    }
    return result;
}