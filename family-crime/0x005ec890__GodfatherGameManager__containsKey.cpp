// FUNC_NAME: GodfatherGameManager::containsKey
// Address: 0x005ec890
// Searches a pair array (key/value) for a given key. Returns 1 if found, 0 otherwise.
// Structure fields:
//   +0x81A0: pointer to array of key/value pairs (each 2 ints)
//   +0x81A4: number of pairs in the array

bool GodfatherGameManager::containsKey(int targetKey) {
    // Get count of pairs
    int pairCount = *(int*)((char*)this + 0x81A4);
    if (pairCount == 0) {
        return false;
    }

    // Pointer to start of pair array
    int* currentPair = *(int**)((char*)this + 0x81A0);
    for (int i = 0; i < pairCount; i++) {
        // Compare first element of pair (key) to target
        if (*currentPair == targetKey) {
            return true;
        }
        // Move to next pair (skip key and value)
        currentPair += 2;
    }
    return false;
}