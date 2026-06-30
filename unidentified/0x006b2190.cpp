// FUN_006b2190: IntArray::contains
bool IntArray::contains(int value) const {
    // this+0xa8 : int* mArray   // dynamic array of ints
    // this+0xac : unsigned int mCount   // number of elements
    if (mCount != 0) {
        for (unsigned int i = 0; i < mCount; ++i) {
            if (mArray[i] == value) {
                return true;
            }
        }
    }
    return false;
}