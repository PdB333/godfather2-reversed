//FUNC_NAME: Player::updateAbilityCooldown
void __fastcall Player::updateAbilityCooldown(Player* this)
{
    // Check if the "cooldown active" flag (bit 0x15) is set and the timer hasn't expired yet
    if (((*(uint32_t*)((uintptr_t)this + 0x1b94) >> 0x15) & 1) != 0 &&
        (*(float*)((uintptr_t)this + 0x5f8) + gFrameDeltaTime < gCooldownThreshold))
    {
        // Clear the cooldown active flag
        *(uint32_t*)((uintptr_t)this + 0x1b94) &= 0xFFDFFFFF;

        // Decrement the remaining uses count if non-zero
        if (*(int32_t*)((uintptr_t)this + 0x5fc) != 0)
        {
            *(int32_t*)((uintptr_t)this + 0x5fc) -= 1;
        }

        // If no uses left, clear the "ability enabled" flags (bits 0x13 and 0x14)
        if (*(int32_t*)((uintptr_t)this + 0x5fc) == 0)
        {
            *(uint32_t*)((uintptr_t)this + 0x1b94) &= 0xFFF9FFFF;
        }
        else
        {
            // Otherwise, set the ability enabled flags (bits 0x13 and 0x14)
            *(uint32_t*)((uintptr_t)this + 0x1b94) |= 0x60000;
        }
    }
}