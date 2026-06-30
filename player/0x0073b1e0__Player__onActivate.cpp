// FUNC_NAME: Player::onActivate
void __fastcall Player::onActivate(Player* this)
{
    // Check if already active (bit 4 of flags at +0x74)
    if (!(this->flags & 0x10))
    {
        // If there is an associated component/child object (at +0x5C)
        if (this->componentPtr != nullptr)
        {
            // Retrieve a system/manager from global singleton
            void* obj = GetManagerFromGlobal(g_someGlobal); // FUN_0043b870(DAT_0113105c)
            if (obj != nullptr)
            {
                // Clear bit 1 (0x0002) of a ushort flag at +0x78 in the returned object
                *(unsigned short*)((int)obj + 0x78) &= 0xFFFB; // bit 2 cleared (0x0004)
            }
        }
        // Mark as active
        this->flags |= 0x10;
    }
}