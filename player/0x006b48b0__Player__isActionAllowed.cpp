// FUNC_NAME: Player::isActionAllowed
bool __thiscall Player::isActionAllowed()
{
    int iTarget; // eax? Actually iVar1 is target pointer
    int iCharacterData;

    iTarget = *(int *)(this + 0x16c); // +0x16c: m_pTarget or m_pConstraint

    // Check: not dead/stunned (0x120000), not in a specific state (0x1), has character data
    if ( ( (*(uint *)(this + 0x34) & 0x120000) == 0 ) &&
         ( (*(byte *)(this + 0x34) & 1) == 0 ) &&
         ( *(int *)(this + 0x40) != 0 ) )
    {
        iCharacterData = FUN_008c74d0( *(int *)(this + 0x40) ); // get character component
        if ( (iCharacterData != 0) &&
             ( ( (*(uint *)(iCharacterData + 0x84) >> 5) & 1 ) == 0 ) && // bit5 must be clear (e.g., not attacking)
             ( iTarget == 0 ) ) // no active target
        {
            // Return whether certain flags are set (e.g., in cover, vehicle? bits 0x50004)
            return (*(uint *)(this + 0x34) & 0x50004) != 0;
        }
    }
    return true;
}