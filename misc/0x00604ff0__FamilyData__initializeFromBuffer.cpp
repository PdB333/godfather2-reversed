// FUNC_NAME: FamilyData::initializeFromBuffer
struct FamilyDataRecord {
    void* mOwner;           // +0x00
    char mName1[32];        // +0x04
    char mName2[32];        // +0x24
    char mName3[32];        // +0x44
    char mName4[32];        // +0x64
    char mName5[32];        // +0x84
    int padding;            // +0xA4? (unused)
    void* mArrayA;          // +0xAC (index 0x2B)
    void* mArrayB;          // +0xB0 (index 0x2C)
};

// External helpers
extern char* __stdcall FUN_00605690(void* ptr, int* param);
extern int __stdcall FUN_00605df0();
extern void* __cdecl FUN_009c8e80(size_t size); // malloc
extern void __stdcall FUN_00605e30(void* param); // some init
extern void __cdecl FUN_009c8f10(void* ptr); // free
extern int __stdcall FUN_006052d0(FamilyDataRecord* record, int value);
extern void __stdcall FUN_00605340(int a, int b, int c);
extern int __stdcall FUN_006054b0(FamilyDataRecord* record, int value);
extern void __stdcall FUN_00605520(int a, int b);

FamilyDataRecord* __thiscall FamilyData::initializeFromBuffer(void* thisPtr, FamilyDataRecord* outRecord) {
    int* vtable; // this->vtable
    char* strPtr;
    unsigned int count;
    long version;
    unsigned int numElements;
    int allocSizes[3];
    void* memBlock;
    int* arrayPtr;
    int i;
    int strLen;
    void* unaff_ESI; // preserved from caller, likely another this or global

    // Initialize output record
    outRecord->mOwner = thisPtr;
    // Clear all string fields (first byte at each offset)
    *(char*)(outRecord + 1) = 0; // offset 4
    *(char*)(outRecord + 9) = 0; // offset 36
    *(char*)(outRecord + 0x11) = 0; // offset 68
    *(char*)(outRecord + 0x19) = 0; // offset 100
    *(char*)(outRecord + 0x21) = 0; // offset 132
    outRecord->mArrayA = 0;
    outRecord->mArrayB = 0;
    // Clear remaining padding (indices 0x2A-0x2C)
    // Already done by assignments above
    // Call virtual function at vtable offset 8 (third entry)
    vtable = *(int**)thisPtr;
    ((void (__thiscall*)(void*))vtable[2])(thisPtr);

    strPtr = (char*)FUN_00605690(thisPtr, &outRecord);
    if (strPtr == 0) goto EXIT;
    
    count = FUN_00605df0();
    version = atol(strPtr);
    if (version != 7) goto EXIT;
    
    // numElements = (count - 6) / 6
    numElements = (count - 6) / 6;
    
    // Allocate two arrays: one of size (numElements * 0x61) and one of (numElements * 0x60)
    allocSizes[0] = 2; // alignment? actually stack variable for allocation flags
    allocSizes[1] = 0x10;
    allocSizes[2] = 0;
    outRecord->mArrayA = ((void* (__thiscall*)(void*, int, int*))vtable[0])(
        thisPtr, numElements * 0x61, allocSizes);
    
    allocSizes[0] = 2;
    allocSizes[1] = 0x10;
    allocSizes[2] = 0;
    outRecord->mArrayB = ((void* (__thiscall*)(void*, int, int*))vtable[0])(
        thisPtr, numElements * 0x60, allocSizes);
    
    // Allocate a temporary array of (count * 4) bytes (string pointers block)
    memBlock = FUN_009c8e80(count * 4);
    FUN_00605e30(unaff_ESI);
    
    // Copy strings from the temporary block into output record
    arrayPtr = (int*)memBlock;
    
    // First string at offset +4
    strPtr = (char*)arrayPtr[1];
    strLen = 0;
    if (strPtr != 0 && *strPtr != '\0') {
        strncpy((char*)(outRecord + 1), strPtr, 0x1f);
        strLen = 0x1f;
    }
    *(char*)((int)outRecord + 4 + strLen) = '\0';
    
    // Second string at offset +36 (0x24)
    strPtr = (char*)arrayPtr[2];
    strLen = 0;
    if (strPtr != 0 && *strPtr != '\0') {
        strncpy((char*)(outRecord + 9), strPtr, 0x1f);
        strLen = 0x1f;
    }
    *(char*)((int)outRecord + 0x24 + strLen) = '\0';
    
    // Third string at offset +68 (0x44)
    strPtr = (char*)arrayPtr[3];
    strLen = 0;
    if (strPtr != 0 && *strPtr != '\0') {
        strncpy((char*)(outRecord + 0x11), strPtr, 0x1f);
        strLen = 0x1f;
    }
    *(char*)((int)outRecord + 0x44 + strLen) = '\0';
    
    // Fourth string at offset +100 (0x64)
    strPtr = (char*)arrayPtr[4];
    strLen = 0;
    if (strPtr != 0 && *strPtr != '\0') {
        strncpy((char*)(outRecord + 0x19), strPtr, 0x1f);
        strLen = 0x1f;
    }
    *(char*)((int)outRecord + 0x64 + strLen) = '\0';
    
    // Fifth string at offset +132 (0x84)
    strPtr = (char*)arrayPtr[5];
    strLen = 0;
    if (strPtr != 0 && *strPtr != '\0') {
        strncpy((char*)(outRecord + 0x21), strPtr, 0x1f);
        strLen = 0x1f;
    }
    *(char*)((int)outRecord + 0x84 + strLen) = '\0';
    
    // Process element data (each element occupies 6 ints: fields 6-11)
    int* pElementData = arrayPtr;
    for (unsigned int elem = 0; elem < numElements; elem++) {
        int retVal;
        int elemA = pElementData[6];
        int elemB = pElementData[7];
        int elemC = pElementData[8];
        int elemD = pElementData[9];
        int elemE = pElementData[10];
        int elemF = pElementData[11];
        
        retVal = FUN_006052d0(outRecord, elemA);
        if (retVal < 0) {
            FUN_00605340(elemC, elemF, elemB);
        }
        retVal = FUN_006054b0(outRecord, elemB);
        if (retVal < 0) {
            FUN_00605520(elemC, elemD);
        }
        pElementData += 6;
    }
    
    FUN_009c8f10(memBlock);
    
    // Call final virtual function (vtable offset 4, second entry)
    vtable = *(int**)outRecord->mOwner;
    ((void (__thiscall*)(void*, int))vtable[1])(thisPtr, 0);

EXIT:
    return outRecord;
}