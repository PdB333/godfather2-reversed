// FUNC_NAME: EAString::insert
// Address: 0x004d41f0
// Inserts a substring from a source buffer with offset into a dynamic string.
// Structure layout: +0x00 char* buffer, +0x04 size_t length, +0x08 size_t capacity, +0x0C void (*deallocator)(void*)

typedef void (*DeallocFunc)(void*);

extern void* stringAlloc(size_t size);   // FUN_009c8e50
extern void  stringFree(void* ptr);      // thunk_FUN_009c8eb0

class EAString {
    char*       buffer;      // +0x00
    size_t      length;      // +0x04
    size_t      capacity;    // +0x08
    DeallocFunc deallocator; // +0x0C

public:
    EAString& insert(size_t pos, const char* src, size_t srcOffset, size_t count) {
        if (count == 0) {
            return *this;
        }

        size_t oldLen = length;

        if (oldLen == 0) {
            // Empty string: assign directly (handled by helper)
            return assignHelper(src, srcOffset, count);
        }

        if (pos >= oldLen) {
            // Insert at end: append instead
            return appendHelper(src, srcOffset, count);
        }

        size_t newLen = oldLen + count;
        if (newLen > capacity) {
            // Need to reallocate
            char* newBuffer = (char*)stringAlloc(newLen + 1);
            // Copy first part (0..pos)
            memcpy(newBuffer, buffer, pos);
            // Insert substring
            memcpy(newBuffer + pos, src + srcOffset, count);
            // Copy the rest (including null terminator)
            char* srcRest = buffer + pos;
            char* dstRest = newBuffer + pos + count;
            char c;
            do {
                c = *srcRest;
                *dstRest = c;
                ++srcRest;
                ++dstRest;
            } while (c != '\0');

            // Free old buffer
            if (buffer != nullptr) {
                deallocator(buffer);
            }

            length = newLen;
            capacity = newLen;
            buffer = newBuffer;
            deallocator = stringFree;
            return *this;
        } else {
            // Shift the tail to make room
            memmove(buffer + pos + count, buffer + pos, oldLen - pos);
            // Insert substring
            memcpy(buffer + pos, src + srcOffset, count);
            length = newLen;
            // Null-terminate at new length
            buffer[newLen] = '\0';
            return *this;
        }
    }

private:
    EAString& assignHelper(const char* src, size_t offset, size_t count);
    EAString& appendHelper(const char* src, size_t offset, size_t count);
};