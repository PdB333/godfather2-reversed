// FUNC_NAME: EntityManager::getFlagWithGeneration
uint EntityManager::getFlagWithGeneration(uint packedId) const
{
    // packedId: bits 0-4 = bit index in word, bits 5-12 = word index (max 256 words = 8192 flags)
    //          bits 13-31 = generation count (for object reuse validation)
    // return: (generation << 8) | (1 if flag is set, else 0)
    
    // Word array starts at +0x8E0 relative to this
    uint word = *(uint*)(this + 0x8E0 + ((packedId >> 5) * 4));
    bool flagSet = (word & (1 << (packedId & 0x1F))) != 0;
    return ((packedId >> 13) << 8) | (flagSet ? 1 : 0);
}