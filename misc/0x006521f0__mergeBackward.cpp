// FUNC_NAME: mergeBackward
// Address: 0x006521f0
// Merges two sorted ranges [firstStart, firstEnd) and [firstEnd, secondEnd) into a single sorted range
// into the memory region ending at destEnd (i.e., the merged output occupies [destEnd - totalSize, destEnd)).
// Returns a pointer to the start of the merged output.
// The comparator is a less-than function: comp(a, b) returns true if a should precede b in the final order.
// Note: This function is designed for arrays of 4-byte elements (e.g., 32-bit pointers or ints).
// The algorithm works by comparing elements from the end of each range and placing the largest at the current output position.

typedef bool (*LessThanFunc)(const void* a, const void* b);

void* __thiscall mergeBackward(void* destEnd, void* firstStart, void* firstEnd, void* secondEnd, LessThanFunc comp) {
    void* currentOutput = destEnd;
    void* currentSecond = secondEnd;
    void* currentFirstEnd = firstEnd;

    while (firstStart != currentOutput) {
        if (currentFirstEnd == currentSecond) {
            // first range exhausted, copy remaining second range
            int count = (int)destEnd - (int)firstStart >> 2;   // number of 4-byte elements
            void* target = (char*)currentOutput - (count * 4);
            memmove_s(target, count * 4, firstStart, count * 4);
            return target;
        }

        // compare elements from the end of each range
        void* secondElement = (char*)currentSecond - 4;
        void* firstElement = (char*)currentOutput - 4;
        bool less = comp(secondElement, firstElement);

        currentOutput = (char*)currentOutput - 4;
        if (!less) {
            // second element >= first element, take second
            *(int*)currentOutput = *(int*)secondElement;
            currentSecond = secondElement;   // consume from second range
        } else {
            // second element < first element, take first
            *(int*)currentOutput = *(int*)firstElement;
            destEnd = firstElement;          // consume from first range
            // currentSecond unchanged (second element stays for next compare)
        }
    }

    // first range fully consumed, copy any remaining second range
    int count = (int)currentSecond - (int)currentFirstEnd >> 2;
    void* target = (char*)currentOutput - (count * 4);
    memmove_s(target, count * 4, currentFirstEnd, count * 4);
    return target;
}