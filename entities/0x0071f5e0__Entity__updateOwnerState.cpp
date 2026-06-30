// FUNC_NAME: Entity::updateOwnerState
void __fastcall Entity::updateOwnerState(Entity* this)
{
    // +0x4: pointer to a component embedded in an owner object at offset 0x48
    EntityComponent* componentPtr = *(EntityComponent**)((int)this + 4);
    if (componentPtr != nullptr && componentPtr != (EntityComponent*)0x48)
    {
        // Owner object is at componentPtr - 0x48 (the component is an embedded member)
        Entity* owner = (Entity*)((int)componentPtr - 0x48);
        // Check bit 25 at owner+0x1f58 (e.g., alive flag)
        if ((*(uint32*)((int)owner + 0x1f58) >> 0x19 & 1) == 0)
        {
            *(uint32*)((int)this + 0x20) |= 0x20; // Set flag bit 5 at +0x20
        }
    }
    // Clear flag bit 3 at +0x20
    *(uint32*)((int)this + 0x20) &= 0xfffffff7;

    if (componentPtr != nullptr && componentPtr != (EntityComponent*)0x48)
    {
        Entity* owner = (Entity*)((int)componentPtr - 0x48);
        if ((*(uint32*)((int)owner + 0x1f58) >> 0x19 & 1) == 0)
        {
            // Set owner's timestamp at +0x854 to a global value
            *(uint32*)((int)owner + 0x854) = DAT_00e544d8;
        }
    }
    // Update own timestamp at +0xC with a global value
    *(uint32*)((int)this + 0xC) = _DAT_00d5780c;

    if (componentPtr != nullptr)
    {
        // Mark component's byte at +0x9d8 as 1 (dirty flag)
        *(uint8*)((int)componentPtr + 0x9d8) = 1;
        *(uint32*)((int)this + 0x20) &= 0xfffffffb; // Clear flag bit 2
        return;
    }
    // Fallback: set global byte at 0x0a20 to 1
    uRam00000a20 = 1;
    *(uint32*)((int)this + 0x20) &= 0xfffffffb; // Clear flag bit 2
}