// FUNC_NAME: binarySearchCompoundKey
// Function address: 0x004cbdc0
// Purpose: Binary search for a compound key (4 uint fields) in a sorted array of struct pointers.
// Fields compared: struct[offset+4], [offset+8], [offset+0xc], [offset+0x10]
// Returns index if found, -1 otherwise.

typedef struct {
    uint32_t field0;      // +0x00 (unused in comparison)
    uint32_t key1;        // +0x04
    uint32_t key2;        // +0x08
    uint32_t key3;        // +0x0C
    uint32_t key4;        // +0x10
} CompoundKeySearchStruct;

typedef struct {
    uint32_t k1;
    uint32_t k2;
    uint32_t k3;
    uint32_t k4;
} CompoundKey;

int binarySearchCompoundKey(const CompoundKey* key, CompoundKeySearchStruct** sortedArray, int count)
{
    if (count <= 0) {
        return -1;
    }

    int low = -1;
    int high = count;

    while (low + 1 < high) {
        int mid = (low + high) / 2;
        CompoundKeySearchStruct* entry = sortedArray[mid];

        // Lexicographic comparison (key1, key2, key3, key4)
        if (key->k1 <= entry->key1) {
            if (entry->key1 <= key->k1) {
                if (entry->key2 < key->k2) {
                    // entry smaller -> continue left? Actually we go to next step but note the condition.
                    // Original code: if (entry->key2 < key->k2) goto LAB_004cbe31 (which updates low=mid, high unchanged? No, low=mid only if key is <= entry? Wait need to trace carefully.
                    // The decompiled logic: if key1 <= entry->key1, then check if entry->key1 <= key1 (so equal). Then compare key2: if entry->key2 < key->k2, jump to update low? Actually LAB_004cbe31 is after the inner if, and it updates iVar4 = iVar5 (which is mid) if the condition is false? Let's re-express.
                    // Better to restructure: The original uses nested ifs with gotos. Equivalent logic:
                    if (key->k1 < entry->key1) {
                        high = mid;
                    } else if (key->k1 > entry->key1) {
                        low = mid;
                    } else {
                        // key1 equal
                        if (key->k2 < entry->key2) {
                            high = mid;
                        } else if (key->k2 > entry->key2) {
                            low = mid;
                        } else {
                            // key2 equal
                            if (key->k3 < entry->key3) {
                                high = mid;
                            } else if (key->k3 > entry->key3) {
                                low = mid;
                            } else {
                                // key3 equal
                                if (key->k4 < entry->key4) {
                                    high = mid;
                                } else if (key->k4 > entry->key4) {
                                    low = mid;
                                } else {
                                    // exact match found during search? The loop continues; later checks for exact match after loop.
                                    // In this path we don't update low/high? Actually the original code sets iVar5 = iVar4 (which is low) and iVar6 = iVar3 (which is mid) when all keys are <=, so it sets high = mid. That's consistent with "if all keys <=, then search left half".
                                    // So if all keys are <= (i.e., key <= entry), set high = mid. Otherwise (if any key >), set low = mid.
                                    // So easier: treat it as regular binary search with comparison function.
                                    // We'll implement clean comparison:
                                    // if key < entry -> high = mid; else if key > entry -> low = mid; else match -> but we don't return early; we continue.
                                }
                            }
                        }
                    }
                    // Because the original code only updates low/high after the if block, we need to restructure.
```

Given the complexity, I'll rewrite the loop with a clear comparison:

```cpp
int low = -1;
int high = count;
while (low + 1 < high) {
    int mid = (low + high) / 2;
    CompoundKeySearchStruct* entry = sortedArray[mid];
    bool smaller = false;
    bool larger = false;
    if (key->k1 < entry->key1) {
        smaller = true;
    } else if (key->k1 > entry->key1) {
        larger = true;
    } else {
        if (key->k2 < entry->key2) {
            smaller = true;
        } else if (key->k2 > entry->key2) {
            larger = true;
        } else {
            if (key->k3 < entry->key3) {
                smaller = true;
            } else if (key->k3 > entry->key3) {
                larger = true;
            } else {
                if (key->k4 < entry->key4) {
                    smaller = true;
                } else if (key->k4 > entry->key4) {
                    larger = true;
                } else {
                    // exact equal; left as is (no change)
                }
            }
        }
    }
    if (smaller) {
        high = mid;
    } else if (larger) {
        low = mid;
    } else {
        // equal: we need to set high = mid to continue searching leftmost? Original code sets high = mid when all keys <=.
        // Actually original: if (uVar1 <= entry->key1) then check further; if all <=, sets iVar6 = mid (high) and iVar4 = iVar5 (low unchanged). So yes, set high = mid.
        high = mid;
    }
}
// After loop, check if high is valid and exact match
if (high < count) {
    CompoundKeySearchStruct* candidate = sortedArray[high];
    if (candidate->key1 == key->k1 &&
        candidate->key2 == key->k2 &&
        candidate->key3 == key->k3 &&
        candidate->key4 == key->k4) {
        return high;
    }
}
return -1;
```

However, the original code's loop condition is that low+1 < high. The initial low=-1, high=count. The loop buys the standard binary search pattern. My rewritten version matches the original behavior.

Let's produce final code with meaningful names. Use 'key' for param_1, 'array' for param_2, 'count' for param_3.

Final output as requested.// FUNC_NAME: binarySearchCompoundKey
// Function address: 0x004cbdc0
// Purpose: Binary search for a compound key (4 uint fields) in a sorted array of struct pointers.
// Fields compared: struct[offset+4], [offset+8], [offset+0xc], [offset+0x10]
// Returns index if found, -1 otherwise.

typedef struct {
    uint32_t padding;   // +0x00 (unused)
    uint32_t key1;      // +0x04
    uint32_t key2;      // +0x08
    uint32_t key3;      // +0x0C
    uint32_t key4;      // +0x10
} CompoundKeySearchStruct;

typedef struct {
    uint32_t k1;
    uint32_t k2;
    uint32_t k3;
    uint32_t k4;
} CompoundKey;

int binarySearchCompoundKey(const CompoundKey* key, CompoundKeySearchStruct** sortedArray, int count) {
    if (count <= 0) {
        return -1;
    }

    int low = -1;
    int high = count;

    while (low + 1 < high) {
        int mid = (low + high) / 2;
        CompoundKeySearchStruct* entry = sortedArray[mid];

        bool smaller = false;
        bool larger = false;

        // Lexicographic comparison of the four key fields
        if (key->k1 < entry->key1) {
            smaller = true;
        } else if (key->k1 > entry->key1) {
            larger = true;
        } else {
            if (key->k2 < entry->key2) {
                smaller = true;
            } else if (key->k2 > entry->key2) {
                larger = true;
            } else {
                if (key->k3 < entry->key3) {
                    smaller = true;
                } else if (key->k3 > entry->key3) {
                    larger = true;
                } else {
                    if (key->k4 < entry->key4) {
                        smaller = true;
                    } else if (key->k4 > entry->key4) {
                        larger = true;
                    }
                    // If all keys equal, keep smaller/larger false, treat as match (search left half)
                }
            }
        }

        if (smaller) {
            high = mid;
        } else if (larger) {
            low = mid;
        } else {
            // All keys <= entry -> move high to mid (left half)
            high = mid;
        }
    }

    // Check if high is valid and exactly matches the key
    if (high < count) {
        CompoundKeySearchStruct* candidate = sortedArray[high];
        if (candidate->key1 == key->k1 &&
            candidate->key2 == key->k2 &&
            candidate->key3 == key->k3 &&
            candidate->key4 == key->k4) {
            return high;
        }
    }

    return -1;
}