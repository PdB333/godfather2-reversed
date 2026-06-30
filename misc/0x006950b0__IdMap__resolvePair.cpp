// FUNC_NAME: IdMap::resolvePair
// Address: 0x006950b0
// Role: Retrieves a pair (this pointer and a hash/ID) based on a key, using a cached value at +0x4.
// If the key's hash differs from the cached hash and a bucket lookup succeeds, returns the new hash;
// otherwise returns the cached hash.

void __thiscall IdMap::resolvePair(int *this, int *outPair, int key)
{
    int hashResult;
    int bucketIndex;
    int thisCopy;
    int cachedHash;

    hashResult = FUN_00694950(key); // Compute hash from key
    if (this == 0) {
        FUN_00b97aea(); // Null pointer assertion/error
    }
    thisCopy = (int)this;
    if (hashResult != this[1]) { // Compare with cached hash at +0x4
        bucketIndex = FUN_004d4b20(hashResult + 0xc); // Lookup in bucket array
        if (bucketIndex >= 0) {
            // Use the new hash result
            outPair[0] = thisCopy;
            outPair[1] = hashResult;
            return;
        }
    }
    // Fallback: use cached hash
    cachedHash = this[1];
    outPair[0] = (int)this;
    outPair[1] = cachedHash;
    return;
}