// FUN_00442d90: PropertyMap::setValue
void PropertyMap::setValue(uint32 key, int32 value)
{
    // Look up the storage location for the given key
    // +0x0: key identifier (hash or ID)
    // +0x4: stored value
    int32 *slot = (int32 *)PropertyMap::findSlot(&key);
    
    if (slot != nullptr)
    {
        *slot = value; // Overwrite value in slot
    }
}