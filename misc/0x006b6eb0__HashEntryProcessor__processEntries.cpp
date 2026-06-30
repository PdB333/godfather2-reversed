// FUNC_NAME: HashEntryProcessor::processEntries

class HashEntryProcessor {
public:
    // Structure: [0] count, then array of 5-int entries
    // Entry layout: int field0, field1, field2, field3, field4
    void __thiscall processEntries() {
        int count = *(int*)this - 1;  // +0x00: number of entries
        if (count < 0) return;

        int* entryPtr = (int*)this + count * 5 + 3;  // points to field3 of last entry
        do {
            uint field3 = entryPtr[0];   // entry[3]
            uint field1 = entryPtr[-2];  // entry[1]
            uint field2 = entryPtr[-1];  // entry[2]
            uint field4 = entryPtr[1];   // entry[4]

            // Compute hash: (((field1 * 33 + field2) * 33 + field3) * 33 + field4)
            long long hash = __allmul((long long)field1 * 0x21 + (long long)field2, 0x21, 0);
            hash = __allmul(hash + (long long)field3, 0x21, 0);
            int finalHash = (int)(hash + (long long)field4);

            // Call debug/log function with level 2, hash, and two 1s
            FUN_00814550(2, finalHash, 1, 1);

            count--;
            entryPtr -= 5;  // move to previous entry
        } while (count >= 0);
    }
};