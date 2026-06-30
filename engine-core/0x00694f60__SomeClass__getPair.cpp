// FUNC_NAME: SomeClass::getPair
void __thiscall SomeClass::getPair(int this, int* outPair, int key)
{
    int hash = computeHash(key);  // FUN_006948e0
    int storedHash = *(int*)(this + 4);  // +0x04: current hash/version

    if (this == 0) {
        assertionFailure();  // FUN_00b97aea
    }

    int local_10 = this;
    int local_c = hash;
    int local_8;
    int local_4;

    if (hash != storedHash) {
        int result = isHashValid(hash + 0xc);  // FUN_004d4b20
        if (result >= 0) {
            // Use computed hash as second element
            outPair[0] = local_10;  // this
            outPair[1] = local_c;   // hash
            return;
        }
    }

    // Fallback: use stored hash from object
    local_4 = *(int*)(this + 4);  // +0x04
    local_8 = this;
    outPair[0] = local_8;  // this
    outPair[1] = local_4;  // storedHash
}