// FUN_0084b400: SomeManager::findElement
// Address: 0x0084b400
// Role: Iterates through an internal array (count at +0x10) calling a matching function with `key`.
// Returns the first non-zero result from the matching function, or 0 if none match.

int __thiscall SomeManager::findElement(int this, int key) {
    unsigned int i = 0;
    if (*(int*)(this + 0x10) != 0) {          // +0x10: number of elements
        do {
            int matchResult = FUN_0084afb0(key);  // matching function (may be static or member)
            if (matchResult != 0) {
                return matchResult;
            }
            i++;
        } while (i < *(unsigned int*)(this + 0x10));
    }
    return 0;
}