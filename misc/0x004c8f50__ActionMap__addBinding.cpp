// FUNC_NAME: ActionMap::addBinding

int __fastcall ActionMap::addBinding(int key1, int key2) {
    int index = 0;
    int *entryPtr = this + 5; // Start at first entry's key2 field (offset +5 ints)

    // Search for duplicate key pair (key1, key2)
    while (entryPtr[-1] != key1 || *entryPtr != key2) {
        index++;
        entryPtr += 5;
        if (index > 31) {
            goto findEmpty;
        }
    }

    // Duplicate found – do not add
    if (index != -1) {
        return 0;
    }

findEmpty:
    index = 0;
    entryPtr = this + 4; // Start at first entry's key1 field (offset +4 ints)

    do {
        if (*entryPtr == 0) {
            if (index == -1) {
                return 0;
            }
            // Insert new binding
            (*this)++; // Increment count at offset 0
            this[index * 5 + 4] = key1;
            this[index * 5 + 5] = key2;
            this[index * 5 + 6] = DAT_01205224; // Some global value
            ActionMap::notifyTableChanged(this);
            return 1;
        }
        index++;
        entryPtr += 5;
    } while (index < 32);

    return 0; // No empty slot
}