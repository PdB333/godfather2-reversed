// FUNC_NAME: EARSString::replaceAll
// Replaces all occurrences of a substring with another substring in a custom string buffer.
// String struct layout: +0x00 char* buffer, +0x04 int length, +0x08 int capacity, +0x0C void (*deallocator)(char*)

#include <cstring>   // for strlen, strstr
#include <cstddef>   // for NULL

extern "C" void* __cdecl memoryAlloc(int size);     // FUN_009c8e50
extern "C" void  __cdecl memoryFree(void* ptr);     // thunk_FUN_009c8eb0

struct EARSString {
    char*  buffer;       // +0x00
    int    length;       // +0x04 (number of characters, not including null terminator)
    int    capacity;     // +0x08 (allocated size, including null terminator)
    void (*deallocator)(char*); // +0x0C (deallocation function for buffer)
};

void __thiscall EARSString::replaceAll(const char* searchStr, const char* replaceStr) {
    if (buffer == NULL) return;

    size_t searchLen = strlen(searchStr);
    if (searchLen == 0) return; // empty search string -> nothing to replace

    // compute replace length (0 if replaceStr is NULL)
    size_t replaceLen = (replaceStr != NULL) ? strlen(replaceStr) : 0;

    // find first occurrence
    char* pos = strstr(buffer, searchStr);
    if (pos == NULL) return; // no occurrences

    // Case 1: same length -> in-place overwrite without buffer change
    if (replaceLen == searchLen) {
        do {
            if (replaceLen != 0) {
                // copy replacement over the occurrence
                char* p = pos;
                char* r = const_cast<char*>(replaceStr);
                for (size_t i = 0; i < replaceLen; ++i) {
                    *p++ = *r++;
                }
            }
            // move past the just-replaced block
            pos = strstr(pos + replaceLen, searchStr);
        } while (pos != NULL);
        return;
    }

    // Case 2: replacement is shorter -> shift left in-place
    if (replaceLen < searchLen) {
        char* dst = pos;  // destination for compacted text
        char* src = pos + searchLen; // source after occurrence
        int diff = static_cast<int>(replaceLen - searchLen); // negative shift

        do {
            // copy replacement over the occurrence
            if (replaceStr != NULL && replaceLen != 0) {
                char* p = pos;
                char* r = const_cast<char*>(replaceStr);
                for (size_t i = 0; i < replaceLen; ++i) {
                    *p++ = *r++;
                }
            }

            // advance destination past the replacement
            dst = pos + replaceLen;
            // search for next occurrence from after the original occurrence
            char* nextPos = strstr(src, searchStr);
            // shift text from src up to next occurrence (or end) to dst
            while (src < nextPos) {
                *dst++ = *src++;
            }
            // update length: each replacement reduces total length by (searchLen - replaceLen)
            length += diff;

            // set up for next iteration
            pos = nextPos;
            if (pos != NULL) {
                src = pos + searchLen;
            }
        } while (pos != NULL);

        // copy remaining characters after the last occurrence
        while (*src != '\0') {
            *dst++ = *src++;
        }
        *dst = '\0'; // null-terminate
        return;
    }

    // Case 3: replacement is longer -> allocate new buffer
    {
        // count occurrences to compute new length
        int count = 0;
        char* p = buffer;
        while (true) {
            p = strstr(p, searchStr);
            if (p == NULL) break;
            ++count;
            p += searchLen;
        }

        // new string length = old length + count * (replaceLen - searchLen)
        int newLength = length + static_cast<int>((replaceLen - searchLen) * count);
        // allocate new buffer (size = newLength + 1 for null terminator)
        char* newBuffer = static_cast<char*>(memoryAlloc(newLength + 1));

        // iterate again to fill new buffer
        char* readPtr = buffer;
        char* writePtr = newBuffer;
        char* searchPos = strstr(readPtr, searchStr);

        while (searchPos != NULL) {
            // copy characters before the occurrence
            while (readPtr < searchPos) {
                *writePtr++ = *readPtr++;
            }
            // copy replacement
            if (replaceStr != NULL && replaceLen != 0) {
                char* r = const_cast<char*>(replaceStr);
                for (size_t i = 0; i < replaceLen; ++i) {
                    *writePtr++ = *r++;
                }
            }
            // skip the original occurrence
            readPtr += searchLen;
            // find next occurrence
            searchPos = strstr(readPtr, searchStr);
        }

        // copy remaining characters
        while (*readPtr != '\0') {
            *writePtr++ = *readPtr++;
        }
        *writePtr = '\0'; // null-terminate

        // deallocate old buffer using stored deallocator
        if (buffer != NULL) {
            deallocator(buffer);
        }

        // update members
        capacity = newLength + 1; // we allocated exactly newLength+1
        length = newLength;
        buffer = newBuffer;
        deallocator = memoryFree; // store standard deallocator
    }
}