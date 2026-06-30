// FUNC_NAME: EAString::replace
struct EAString {
    char*  mString;       // +0x00: pointer to allocated string buffer
    int    mLength;       // +0x04: current length of string (excluding null terminator)
    int    mAllocatedLen; // +0x08: allocated capacity (buffer size)
    void   (*mDealloc)(void* ptr); // +0x0C: deallocation function (e.g., standard free)
};

void __thiscall EAString::replace(char* findStr, char* replaceStr) {
    EAString* self;
    char* currentPos;
    char* nextPos;
    int findLen, replaceLen;
    char* oldString;
    int count;
    int newLen;
    char* newBuffer;
    char* src, *dst;

    self = (EAString*)this;

    if (self->mString == nullptr) {
        return;
    }

    // Compute length of find string
    findLen = 0;
    while (findStr[findLen] != '\0') {
        findLen++;
    }

    if (findLen == 0) {
        return; // nothing to replace
    }

    // Locate first occurrence
    currentPos = strstr(self->mString, findStr);
    if (currentPos == nullptr) {
        return; // no occurrences
    }

    // Compute length of replace string (null means empty)
    if (replaceStr == nullptr) {
        replaceLen = 0;
    } else {
        replaceLen = 0;
        while (replaceStr[replaceLen] != '\0') {
            replaceLen++;
        }
    }

    if (replaceLen == findLen) {
        // Case 1: Same length – in-place replacement
        do {
            // Copy replacement over find string
            for (int i = 0; i < replaceLen; i++) {
                currentPos[i] = replaceStr[i];
            }
            // Move to next occurrence
            currentPos = strstr(currentPos + findLen, findStr);
        } while (currentPos != nullptr);
        return;
    }

    if (replaceLen < findLen) {
        // Case 2: Shorter – in-place with left-shift
        do {
            // Copy replacement over find string
            for (int i = 0; i < replaceLen; i++) {
                currentPos[i] = replaceStr[i];
            }
            // Shift following characters left by (findLen - replaceLen) bytes
            src = currentPos + findLen;
            dst = currentPos + replaceLen;
            // Search next occurrence starting after the replacement
            nextPos = strstr(src, findStr);
            // Copy from src up to next occurrence or end of string
            while (src < nextPos) {
                *dst = *src;
                dst++;
                src++;
            }
            // Update length (negative delta)
            self->mLength += (replaceLen - findLen);
            currentPos = nextPos;
        } while (currentPos != nullptr);
        // Copy remaining characters after last occurrence
        while (*src != '\0') {
            *dst = *src;
            dst++;
            src++;
        }
        *dst = '\0';
        return;
    }

    // Case 3: Longer – need to reallocate buffer
    // Count total number of occurrences
    count = 0;
    currentPos = self->mString;
    do {
        count++;
        currentPos = strstr(currentPos + findLen, findStr);
    } while (currentPos != nullptr);

    // Compute new total length
    newLen = (replaceLen - findLen) * count + self->mLength;

    // Allocate new buffer
    newBuffer = (char*)FUN_009c8e50(newLen + 1); // custom malloc

    // Build new string with replacements
    currentPos = self->mString;
    dst = newBuffer;
    do {
        // Copy characters before match
        while (src < currentPos) {
            *dst = *src;
            dst++;
            src++;
        }
        // Copy replacement string
        if (replaceStr != nullptr && replaceLen > 0) {
            for (int i = 0; i < replaceLen; i++) {
                *dst = replaceStr[i];
                dst++;
            }
        }
        // Advance source past the found pattern
        src = currentPos + findLen;
        currentPos = strstr(src, findStr);
    } while (currentPos != nullptr);
    // Copy remaining characters after last match
    while (*src != '\0') {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';

    // Free old buffer
    if (self->mString != nullptr) {
        self->mDealloc(self->mString);
    }

    // Update members
    self->mAllocatedLen = newLen;
    self->mLength = newLen;
    self->mString = newBuffer;
    self->mDealloc = (void(*)(void*))thunk_FUN_009c8eb0; // standard free
}