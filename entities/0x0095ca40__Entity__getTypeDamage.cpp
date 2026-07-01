// FUNC_NAME: Entity::getTypeDamage
// Function address: 0x0095ca40
// Role: Returns a value based on the object's type ID (hash lookup). Used for weapon damage multipliers.
// Object has a uint32 type index at offset +0x8.
// Global table at DAT_011307f8 contains 8-byte entries (first 4 bytes are a CRC32 hash, second 4 bytes unused here).
// DAT_011307fc is the table size (number of entries).
// Known hashes: 0x3d26cff9, 0x45c2f636, 0x7116917a (likely CRC32 of weapon type names).

int __thiscall Entity::getTypeDamage(Entity* thisPtr)
{
    uint32_t typeIndex = *(uint32_t*)((uint8_t*)thisPtr + 0x8);
    
    if (typeIndex < DAT_011307fc)
    {
        int hash = *(int*)(DAT_011307f8 + typeIndex * 8);
        if (hash == 0x45c2f636)
        {
            return 3; // Weak weapon type
        }
        if (hash == 0x3d26cff9 || hash == 0x7116917a)
        {
            return 100; // Strong weapon type
        }
    }
    return 1; // Default
}