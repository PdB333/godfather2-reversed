// FUNC_NAME: Player::setAbilityFlag
bool Player::setAbilityFlag(uint flagMask)
{
    // Check if the player object is active (flag at this+0x1744)
    if (*(bool*)(this + 0x1744))
    {
        // Get the ability manager from a global/static function
        void* abilityMgr = getAbilityManager();
        if (abilityMgr)
        {
            // OR the mask into the flags field at offset 0x250 of the manager
            *(uint*)((uint)abilityMgr + 0x250) |= flagMask;
            return true;
        }
    }
    return false;
}