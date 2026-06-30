// FUNC_NAME: Entity::clearDeathState
// Address: 0x0051b210
// Role: Handles clearing of death-related flags (bits 18 and 19) and possibly sets a resurrection flag (bit 31)
//        if certain conditions are met, then triggers a death state processing function.

class Entity; // forward declaration (assumed)

void __thiscall Entity::clearDeathState()
{
    // Fetch current flags from offset +0xC
    uint32_t flags = *(uint32_t*)((uint8_t*)this + 0xC); // +0xC: state flags

    // Check if the "dying" flag (bit 18) is set
    if (flags & 0x40000)
    {
        // Clear bit 18
        *(uint32_t*)((uint8_t*)this + 0xC) = flags & 0xFFFBFFFF;

        // If the "dead" flag (bit 19) is also set, handle full death transition
        if (flags & 0x80000)
        {
            // Compute new flags with both bits 18 and 19 cleared
            uint32_t newFlags = flags & 0xFFF3FFFF;

            // Check if bit 0 (active or alive flag) AND the referenced object's flag bit 29 are set
            if ((flags & 1) != 0) // bit 0: some active/living state
            {
                // Retrieve pointer to another object (e.g., owner, parent, or related entity) from offset +0x10
                void* otherObj = *(void**)((uint8_t*)this + 0x10); // +0x10: pointer to related object
                if (otherObj)
                {
                    // Check flag bit 29 in the other object's state at offset +0x14
                    uint32_t otherFlags = *(uint32_t*)((uint8_t*)otherObj + 0x14); // +0x14: other object's flags
                    if (otherFlags & 0x20000000)
                    {
                        // Set bit 31: indicates "resurrected" or "reanimated" state
                        newFlags |= 0x80000000;
                    }
                }
            }

            // Update the flags field with the final value
            *(uint32_t*)((uint8_t*)this + 0xC) = newFlags;

            // Call the associated death state processor (FUN_0051b0b0)
            processDeathState();
        }
    }
}