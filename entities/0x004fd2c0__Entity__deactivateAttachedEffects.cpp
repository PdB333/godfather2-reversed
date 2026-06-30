// FUNC_NAME: Entity::deactivateAttachedEffects
void Entity::deactivateAttachedEffects()
{
    // +0x78: bitfield, set bit 0 to mark effects as deactivated
    *(uint32_t *)(this + 0x78) |= 1;

    // Handle first attached effect object at +0x80
    int32_t* effectObj1 = *(int32_t **)(this + 0x80);
    if (effectObj1 != nullptr)
    {
        // If the "valid" flag (bit 17) is not set, set it and trigger an engine update
        if ((*(uint32_t *)(effectObj1 + 0xC) & 0x20000) == 0) // +0x0C: flags
        {
            *(uint32_t *)(effectObj1 + 0xC) |= 0x20000;
            FUN_0051b120();  // likely gfxMarkDirty or requestUpdate
        }
        // Clear bit 18 (0x40000) – possibly "active" flag
        *(uint32_t *)(effectObj1 + 0xC) &= 0xFFFBFFFF;

        // Clear the embedded pointer at +0x08
        effectObj1 = *(int32_t **)(this + 0x80); // re-fetch after potentially modified
        uint32_t** ptrSlot = (uint32_t **)(effectObj1 + 8); // +0x08: pointer to sub-object
        if (*ptrSlot != nullptr)
        {
            **ptrSlot = 0;                // nullify target
            *(uint32_t *)(effectObj1 + 8) = 0; // clear the pointer itself
        }
    }

    // Handle second attached effect object at +0x84 (identical pattern)
    int32_t* effectObj2 = *(int32_t **)(this + 0x84);
    if (effectObj2 != nullptr)
    {
        if ((*(uint32_t *)(effectObj2 + 0xC) & 0x20000) == 0)
        {
            *(uint32_t *)(effectObj2 + 0xC) |= 0x20000;
            FUN_0051b120();
        }
        *(uint32_t *)(effectObj2 + 0xC) &= 0xFFFBFFFF;

        effectObj2 = *(int32_t **)(this + 0x84);
        uint32_t** ptrSlot = (uint32_t **)(effectObj2 + 8);
        if (*ptrSlot != nullptr)
        {
            **ptrSlot = 0;
            *(uint32_t *)(effectObj2 + 8) = 0;
        }
    }

    // +0x7C: some count or state, reset to 0
    *(uint32_t *)(this + 0x7C) = 0;
}