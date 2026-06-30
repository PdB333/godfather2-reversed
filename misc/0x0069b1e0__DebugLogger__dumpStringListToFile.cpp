// FUNC_NAME: DebugLogger::dumpStringListToFile

#include <stdio.h>
#include <wchar.h>

// Forward declarations for external functions
// These functions set up cleanup function pointers in the caller's stack frame
bool getFilePath(const char* basePath, const char* subDir, const char* filename, wchar_t** outPath, int mode);
// Returns true on success. On success, outPath is allocated and must be freed via a cleanup function set by this call.

struct TempString {
    char* str;
    int field4;
    int field8;
    // The destructor function pointer for this temp string is stored externally (local_4 in the caller)
};

// Builds a temp string from two node fields, returns pointer to the string member within the TempString struct.
char** buildNodeString(TempString* temp, int nodeField1, int nodeField2);

// Linked list traversal: returns the next node pointer
int getNextNode(int currentNode);

// Empty string fallback
static const char* s_emptyString = "";

__thiscall bool DebugLogger::dumpStringListToFile(void* thisPtr, void* list) {
    wchar_t* filePath = nullptr;
    bool result = false;

    // Cleanup function pointers – initialized by the called functions
    void (*cleanupFilePath)(wchar_t*) = nullptr;
    void (*cleanupTempString)(int) = nullptr;

    if (getFilePath(
            *(const char**)((int)thisPtr + 0x28),     // +0x28: base directory
            (const char*)((int)thisPtr + 0x3c),       // +0x3c: subdirectory
            (const char*)((int)thisPtr + 0x2c),       // +0x2c: filename
            &filePath,
            1)) {
        const wchar_t* actualFilename = filePath ? filePath : L"";
        FILE* file = _wfopen(actualFilename, L"wt");
        if (file) {
            // linked list layout: sentinel at list+4, head pointer at list+8
            for (int node = *(int*)((int)list + 8);
                 node != (int)list + 4;
                 node = getNextNode(node)) {
                TempString temp;
                char** strPtr = buildNodeString(&temp,
                                                  *(int*)(node + 0x10),
                                                  *(int*)(node + 0x20));
                char* str = *strPtr;
                if (str == nullptr) {
                    str = s_emptyString;
                }
                fputs(str, file);
                if (temp.field4 != 0) {
                    cleanupTempString(temp.field4);
                }
            }
            fclose(file);
            result = true;
        }
        if (filePath) {
            cleanupFilePath(filePath);
        }
        return result;
    }
    if (filePath) {
        cleanupFilePath(filePath);
    }
    return false;
}