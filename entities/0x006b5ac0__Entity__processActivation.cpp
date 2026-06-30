// FUNC_NAME: Entity::processActivation
void __fastcall Entity::processActivation(Entity* this)
{
    int targetHandle;
    Entity* targetObj;

    // Check bit 0 of flags at +0x34
    if ((*(uint8_t*)((int)this + 0x34) & 1) != 0)
    {
        // Clear bit 0
        *(uint32_t*)((int)this + 0x34) &= 0xFFFFFFFE;
        // Redundant check after clearing
        if ((*(uint32_t*)((int)this + 0x34) & 1) == 0)
        {
            // If target handle at +0x40 is non-zero
            if (*(int*)((int)this + 0x40) != 0)
            {
                targetHandle = *(int*)((int)this + 0x40);
                targetObj = (Entity*)getEntityByHandle(targetHandle); // FUN_008c74d0
                if ((targetObj != nullptr) &&
                    // Check if bit 5 of target's flags at +0x84 is clear
                    ((~((uint8_t)(*(uint32_t*)((int)targetObj + 0x84) >> 5)) & 1) != 0))
                {
                    triggerAction(); // FUN_006b5170
                    return;
                }
            }
        }
    }
}