// FUNC_NAME: LocalizedStringEntry::setFromData
void LocalizedStringEntry::setFromData(void* parentObject, const SourceEntry* srcEntry) {
    int* refCountPtr;
    char* dest;
    char* dest2;
    char valid;
    int refCount;
    const int* dataPtr;
    char buffer[28];

    // Initialize memory manager (assumed)
    MemoryManager::init();

    // Set vtable pointer
    this->vtable = &LocalizedStringEntry_VTable;

    // Initialize shared reference count pointer
    refCountPtr = &this->sharedRefCount;
    *refCountPtr = 0;
    this->sharedRefCount2 = 0;

    // Check if parent object has a flag set; if so, return early
    if (*(char*)((int)parentObject + 0xd) != '\0') {
        return;
    }

    // Store source entry and initialize some fields
    this->sourceEntry = srcEntry;
    this->field_0x2d = 0;
    this->field_0x2e = srcEntry->firstField;

    // If shared ref count pointer is non-zero, release it
    if (*refCountPtr != 0) {
        releaseSharedData(refCountPtr);
        *refCountPtr = 0;
    }

    // Get some thread-local data
    int* threadData = *(int**)(__readfsdword(0x2c));
    this->field_0x09 = this->field_0x01;
    this->field_0x0a = *(int*)(threadData + 2) + 0x80 + this->field_0x04;
    this->field_0x0b = 0;
    this->field_0x0c = 0;
    this->field_0x0d = 0;
    this->field_0x0e = 0;

    // Check if the source data is empty (four consecutive zero ints)
    dataPtr = &srcEntry->field_0x02;
    if (*dataPtr == 0 && dataPtr[1] == 0 && dataPtr[2] == 0 && dataPtr[3] == 0) {
        goto errorReturn;
    }

    // Read three strings from the source entry into local buffer, then copy into this object
    readString(&srcEntry->string1, buffer);
    this->string1[0] = '\0';
    _strncpy(this->string1, buffer, 0x23);

    readString(&srcEntry->string2, buffer);
    _strncpy(this->string2, buffer, 0x23);

    readString(&srcEntry->string3, buffer);
    _strncpy(this->string3, buffer, 0x23);

    // Validate all three strings; if any are empty or fail validation, handle accordingly
    if (((this->string1[0] != '\0' && ((char*)this->string1 == NULL || !validateString()))) ||
        ((this->string2[0] != '\0' && (this->string2 == NULL || !validateString()))) ||
        ((this->string3[0] != '\0' && (this->string3 == NULL || !validateString())))) {
        // If the data pointer is null, set error flag and return
        if (dataPtr == NULL) {
            goto errorReturn;
        }

        refCount = addRef(dataPtr);
        refCountPtr = &this->sharedRefCount;

        if (this->sharedRefCount != refCount) {
            // Release old shared data if any
            if (this->sharedRefCount != 0) {
                releaseSharedData(refCountPtr);
            }
            // Assign new shared data
            *refCountPtr = refCount;
            if (refCount != 0) {
                this->sharedRefCount2 = *(int*)(refCount + 4);
                *(int**)(refCount + 4) = refCountPtr;
            }
        }

        // If shared data is still null, set error and return
        if (*refCountPtr == 0) {
            goto errorReturn;
        }

        updateStringTable(0);
    }

    finalizeInit(this + 9);
    return;

errorReturn:
    *(char*)((int)parentObject + 0xc) = 1;
    return;
}