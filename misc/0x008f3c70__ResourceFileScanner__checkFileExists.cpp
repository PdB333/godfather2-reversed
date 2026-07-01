// FUNC_NAME: ResourceFileScanner::checkFileExists
// Function address: 0x008f3c70
// Scans for a file matching a name pattern in a directory. Returns 1 if found, 0 otherwise.

#include <windows.h>
#include <string>

// Forward declarations for internal engine functions
// (placeholders – not part of the reconstruction)
typedef void* HString; // Handle to internal string object
typedef void (*StringDestructor)(void*); // destructor callback

// Internal functions called (renamed based on patterns)
HString __fastcall stringPoolAlloc();                                 // FUN_00697cb0
HString __fastcall stringGetContent(HString str);                     // FUN_004dbef0
void __fastcall stringSetContent(HString str, HString content);      // FUN_004dba00
void __fastcall stringSetFromInts(HString str, int a, int b);        // FUN_004dbf70 (stores two ints as string?)
void __fastcall stringConstructFromData(HString str, int flag, HString data); // FUN_004dbd90 (creates string with destructor)
int __fastcall parseSearchPattern(int mode, int* tmpHandle, int* resultArr, wchar_t** patternOut, int unknown); // FUN_00698f20 (mode 3: extract pattern from some config)
void __fastcall stringSetFromUnicode(HString str, const wchar_t* src); // FUN_004dd9e0 (assigns unicode string to a string object)

// Class representing a file scanner object
// Fields offset 0x2260 and 0x2264 likely hold a name string (wide) or path components
class ResourceFileScanner {
public:
    // Locates a file matching the pattern derived from internal data.
    // Returns 1 if a matching file exists, 0 otherwise.
    int __fastcall checkFileExists();
};

int __fastcall ResourceFileScanner::checkFileExists()
{
    wchar_t* searchPattern = nullptr; // The wildcard pattern for FindFirstFile (e.g., L"*.ext")
    int dummyArr[3] = {0};            // Temporary storage for parse results (not used directly)
    int tmpHandleResult = 0;          // Handle for temporary string from parse
    void* tmpDestructor = nullptr;    // Destructor for temporary string

    // Step 1: Initialize internal string pool and set up a string from two member ints
    HString poolStr = stringPoolAlloc();
    HString content = stringGetContent(poolStr); // gets content representation
    stringSetContent(poolStr, content);
    stringSetFromInts(poolStr, *(int*)(this + 0x2260), *(int*)(this + 0x2264)); // store member data as string

    // Construct a temporary string from the pool string (may involve destructor)
    stringConstructFromData(tmpHandleResult, 0, content);
    if (tmpHandleResult != 0) {
        // The destructor is stored at some fixed address; here we call it to clean up later
        // (pcStack_254 points to destructor function)
        ((void(*)(int))DestructorArray[0])(tmpHandleResult);
    }

    // Step 2: Parse a search pattern (mode=3) from some global configuration storage
    // Result: searchPattern will contain the wildcard string (e.g., L"*.abc")
    // dummyArr may contain additional information but is only freed later.
    int parseSuccess = parseSearchPattern(3, &tmpHandleResult, dummyArr, &searchPattern, 0);
    if (tmpHandleResult != 0) {
        ((void(*)(int))DestructorArray[0])(tmpHandleResult);
    }

    if (parseSuccess != 0) {
        // Step 3: Obtain the expected file name (without extension) from the object's data
        HString nameContent = stringGetContent(poolStr);
        stringConstructFromData(poolStr, 0, nameContent); // reinitialize string with destructor

        // Variables for file search
        int dirHandle = 0;          // handle for directory iterator
        wchar_t* expectedName = nullptr; // the base name to compare against
        size_t compareLength = 0;   // length for comparison

        // Initialize the directory iterator and extract the expected name from poolStr
        stringSetFromUnicode(dirHandle, expectedName); // sets expectedName from poolStr contents
        // (In the original code, FUN_004dd9e0 assigns the unicode string to expectedName; we replicate that)

        // Start file search using the pattern
        wchar_t* effectivePattern = (searchPattern != nullptr) ? searchPattern : L"";
        WIN32_FIND_DATAW findData;
        HANDLE hFind = FindFirstFileW(effectivePattern, &findData);
        if (hFind != INVALID_HANDLE_VALUE) {
            // Iterate through files
            while (FindNextFileW(hFind, &findData) != 0) {
                // Compare the found file name (case-insensitive) with the expected name
                wchar_t* compareName = (expectedName != nullptr) ? expectedName : L"";
                if (__wcsnicmp(findData.cFileName, compareName, compareLength) == 0) {
                    // Match found – clean up and return 1
                    FindClose(hFind);
                    if (expectedName != nullptr) {
                        ((void(*)(wchar_t*))DestructorArray[1])(expectedName);
                    }
                    if (dirHandle != 0) {
                        ((void(*)(int))DestructorArray[2])(dirHandle);
                    }
                    if (searchPattern != nullptr) {
                        ((void(*)(wchar_t*))DestructorArray[3])(searchPattern);
                    }
                    if (dummyArr[0] != 0) {
                        ((void(*)(int))DestructorArray[4])(dummyArr[0]);
                    }
                    return 1;
                }
            }
            FindClose(hFind);
        }
        // Clean up if no match or error
        if (expectedName != nullptr) {
            ((void(*)(wchar_t*))DestructorArray[1])(expectedName);
        }
        if (dirHandle != 0) {
            ((void(*)(int))DestructorArray[2])(dirHandle);
        }
    }
    // General cleanup
    if (searchPattern != nullptr) {
        ((void(*)(wchar_t*))DestructorArray[3])(searchPattern);
    }
    if (dummyArr[0] != 0) {
        ((void(*)(int))DestructorArray[4])(dummyArr[0]);
    }
    return 0;
}