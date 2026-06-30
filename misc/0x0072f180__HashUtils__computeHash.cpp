// FUNC_NAME: HashUtils::computeHash
uint HashUtils::computeHash(void* ptr)
{
    // Return default hash (0) for null pointers
    if (ptr == (void*)0x0) {
        return 0;
    }

    // Obtain a global seed value (likely from a timer or random source)
    uint seed = getGlobalSeed();

    // Compute and return the hash from the pointer and seed
    return hashPointer(ptr, seed);
}