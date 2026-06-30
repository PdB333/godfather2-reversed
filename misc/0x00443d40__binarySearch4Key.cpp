// FUNC_NAME: binarySearch4Key
int __fastcall binarySearch4Key(int* pArrayDesc, uint* pKey) {
    int count = pArrayDesc[1];
    int low = -1;
    int high = count;

    // Binary search on sorted array of 20-byte (0x14) records
    // Each record contains a 16-byte key (4 uint32) as the first four fields
    while (true) {
        int mid = (low + high) >> 1;
        uint* record = (uint*)(pArrayDesc[0] + mid * 0x14);

        // Lexicographic comparison of 4 uint32 keys
        if (*record < *pKey) {
            low = mid;
        } else if (*record > *pKey) {
            high = mid;
        } else {
            // First uint32 equal; compare remaining three
            if (record[1] < pKey[1]) {
                low = mid;
            } else if (record[1] > pKey[1]) {
                high = mid;
            } else {
                if (record[2] < pKey[2]) {
                    low = mid;
                } else if (record[2] > pKey[2]) {
                    high = mid;
                } else {
                    if (record[3] < pKey[3]) {
                        low = mid;
                    } else if (record[3] > pKey[3]) {
                        high = mid;
                    } else {
                        // All four equal – exact match found
                        return mid;
                    }
                }
            }
        }

        // Convergence check: when low and high become adjacent, loop ends
        if (low + 1 == high) {
            // Check if the element at 'high' (if within bounds) matches the key
            if (high < count) {
                uint* candidate = (uint*)(pArrayDesc[0] + high * 0x14);
                if (*candidate == *pKey &&
                    candidate[1] == pKey[1] &&
                    candidate[2] == pKey[2] &&
                    candidate[3] == pKey[3]) {
                    return high;
                }
            }
            return -1;
        }
    }
}