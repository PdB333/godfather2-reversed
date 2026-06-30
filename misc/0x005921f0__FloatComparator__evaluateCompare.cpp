// FUNC_NAME: FloatComparator::evaluateCompare
// Function at 0x005921f0: Compares two float values obtained from value sources.
// First source is indirectly via pointer to char*, second source directly via char*.
// If the value of the second source is greater than the first, stores this pointer
// in outArray[3] and returns 1. Otherwise returns 0.
typedef void (*__stdcall FloatFunc)(void* userData, int index, float* outFloat);

extern int DAT_01205574;           // max index for table
extern FloatFunc* DAT_01205570;   // array of function pointers (size = 0xc per entry)

// Structure at offset +8 of this object, contains two value source pointers
struct ValueSourceData {
    char** ppFirstData;   // +0x00: pointer to char* (indirect source)
    char*  pSecondData;   // +0x04: direct char* source
};

// This: this pointer (unknown class, but has +8 pointing to ValueSourceData)
// outArray: output array of void* (index 3 receives this if condition true)
int __thiscall FloatComparator::evaluateCompare(int this, void** outArray)
{
    ValueSourceData* pSources = *(ValueSourceData**) (this + 8);
    char* pFirstChar = **(pSources->ppFirstData);  // indirect: deref twice to get char*
    float firstVal;
    if (*pFirstChar == '\n') {
        // Newline indicates use table lookup
        int index = *(short*)(pFirstChar + 2);   // short after newline
        if ((index >= 0) && (index < DAT_01205574)) {
            FloatFunc func = *(FloatFunc*)(DAT_01205570 + 4 + index * 0xc);
            if (func != 0) {
                func(*outArray, index, &firstVal); // note: *outArray is first parameter?
            }
        }
    } else {
        // Otherwise read float from offset +4 of the char data
        firstVal = *(float*)(pFirstChar + 4);
    }

    char* pSecondChar = pSources->pSecondData;  // direct char* source
    float secondVal;
    if (*pSecondChar == '\n') {
        int index = *(short*)(pSecondChar + 2);
        if ((index >= 0) && (index < DAT_01205574)) {
            FloatFunc func = *(FloatFunc*)(DAT_01205570 + 4 + index * 0xc);
            if (func != 0) {
                func(*outArray, index, &secondVal);
            }
        }
    } else {
        secondVal = *(float*)(pSecondChar + 4);
    }

    if (secondVal <= firstVal) {
        return 0;
    }
    outArray[3] = (void*)this;  // store this pointer in output slot 3
    return 1;
}