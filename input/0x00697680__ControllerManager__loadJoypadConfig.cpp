//FUNC_NAME: ControllerManager::loadJoypadConfig
// Address: 0x00697680
// Reads "joypad.txt" and initializes global joypad configuration (gJoypadConfig, 0xbc bytes).
// Parses 12 primary mappings, 4 secondary mappings, and 4 extra mappings from the file.

#include <cstring>
#include <cstdint>

// Global joypad configuration structure (size 0xbc)
struct JoypadConfig {
    uint32_t field_0;      // +0x00
    uint32_t field_4;      // +0x04 (low byte at +0x05)
    uint8_t  field_8;      // +0x08 (actually +0x05? but aligned)
    // ... more fields up to 0xbc
};

// Global arrays for joypad mappings
extern JoypadConfig gJoypadConfig;          // 0x01129c68
extern uint32_t gJoypadMappings[32];        // 0x01129c70 (16 pairs? actually used as [i*2] and [i*2+1])
extern uint32_t gJoypadExtraMappings[12];   // 0x01129cf4 (4 triplets)

// Forward declarations of helper functions (from other modules)
extern "C" {
    void* openFileForReading(const wchar_t* filename, int mode); // FUN_00699080
    int   checkFileExists(void* handle, char* buffer);          // FUN_00b97651
    void* openConfigFile(const char* filename, int a, int b, void* callback); // FUN_0069bb60
    int   getFileSize(void* file);                              // FUN_00697ea0
    void  initJoypadSystem();                                   // FUN_00698760
    void  initJoypadDefaults();                                 // FUN_006939b0
    void  initJoypadMapping();                                  // FUN_00696f70
    void  initJoypadAxes();                                     // FUN_00697310
    int   parseJoypadFile(void* file, uint32_t* outPairs, void** outList, void* outBuffer); // FUN_006952c0
    char  isStringEmpty(uint32_t str);                          // FUN_00699f30
    void  stringCopy(const char* src);                          // FUN_004d3bc0
    int   parseToken(void** outToken, uint32_t str, int* outLen); // FUN_0069be40
    int   findMapping(void** mapping, void** list);             // FUN_00694f60
    void  assertFail();                                         // FUN_00b97aea
    int   compareStrings(int* a);                               // FUN_004d4b20
    void  cleanupMapping(void** token, void* buffer, void* list); // FUN_006961f0
    void  freeMemory(void* ptr);                                // FUN_009c8eb0
    void  cleanupAnother(void** token, void** buffer, void* list); // FUN_00695e30
}

void loadJoypadConfig() {
    void* fileHandle = nullptr;
    void* filePtr = nullptr;
    uint32_t fileSize = 0;
    uint32_t pairs[29]; // parsed pairs from file
    void* listBuffer = nullptr;
    void* tempBuffer = nullptr;
    void* token = nullptr;
    int tokenLen = 0;
    void* mapping = nullptr;
    void* mappingList = nullptr;
    void* defaultString = (void*)0x0120546e; // some default string

    // Clear global config
    memset(&gJoypadConfig, 0, 0xbc);

    // Try to open joypad.txt
    fileHandle = openFileForReading(L"joypad.txt", 3);
    if (fileHandle == nullptr) {
        fileHandle = (void*)0x00e2df14; // default handle
    }

    // Check if file exists
    char buffer[52];
    if (checkFileExists(fileHandle, buffer) != 0) {
        // File not found, skip parsing
        goto cleanup;
    }

    // Open file with callback
    filePtr = openConfigFile("joypad.txt", 3, 6, (void*)0x00693b10);
    fileSize = getFileSize(filePtr);
    initJoypadSystem();

    // Set global config pointer
    *(void**)0x01205468 = &gJoypadConfig;
    gJoypadConfig.field_0 = 0;
    gJoypadConfig.field_4 = 0;
    *(uint8_t*)((uintptr_t)&gJoypadConfig + 5) = 1; // set byte at offset 5

    // Initialize subsystems
    initJoypadDefaults();
    initJoypadMapping();
    initJoypadAxes();

    // Parse the file into pairs array
    parseJoypadFile(filePtr, pairs, &listBuffer, &tempBuffer);

    // Process first 12 mappings (indices 0-11)
    for (int i = 0; i < 12; i++) {
        uint32_t str = pairs[i * 2];
        if (isStringEmpty(str) == 0) {
            // Empty string -> set default mapping value 0x10
            gJoypadMappings[i * 2] = 0x10;
        } else {
            // Parse the string token
            stringCopy((const char*)0x00e2f044);
            tokenLen = parseToken(&token, str, &tokenLen);
            if (tokenLen != 0) {
                // Call function pointer on token (likely a destructor or free)
                ((void(*)(int))0x00e2f044)(tokenLen);
            }
            void* tokenPtr = token;
            if (tokenPtr == nullptr) {
                tokenPtr = defaultString;
            }
            stringCopy((const char*)tokenPtr);

            // Find mapping in list
            mapping = findMapping(&mappingList, (void**)&tempBuffer);
            if (mapping == nullptr) {
                // No mapping found, set default
                gJoypadMappings[i * 2] = 0x10;
            } else {
                // Extract mapping values
                uint32_t* mappingData = (uint32_t*)mapping;
                uint32_t value1 = mappingData[7];
                uint32_t value2 = mappingData[8];
                uint32_t str2 = pairs[i * 2 + 1];
                // Store mapping (note: first assignment overwritten, final values from str2 and value2)
                gJoypadMappings[i * 2] = str2;
                gJoypadMappings[i * 2 + 1] = value2;
                // Free token if allocated
                if (token != nullptr) {
                    ((void(*)(void*))0x00e2f044)(token);
                }
            }
        }
    }

    // Process next 4 mappings (indices 12-15)
    for (int i = 12; i < 16; i++) {
        uint32_t str = pairs[i + 12]; // pairs[24..27]
        gJoypadMappings[i * 2] = i - 12; // 0,1,2,3
        gJoypadMappings[i * 2 + 1] = str;
    }

    // Process extra mappings (4 triplets at gJoypadExtraMappings)
    uint32_t* extraSrc = (uint32_t*)&pairs[28]; // after pairs[27]? Actually pairs has 29 elements, indices 0..28. We used 0..27, so index 28 is available.
    uint32_t* extraDst = gJoypadExtraMappings;
    for (int i = 0; i < 4; i++) {
        uint32_t str = extraSrc[i * 2]; // pairs[28], then pairs[30]? This is messy; assume correct indexing.
        if (isStringEmpty(str) == 0) {
            // Empty -> set default
            extraDst[2] = *(uint32_t*)0x00d5780c;
            extraDst[0] = str;
            extraDst[1] = 0xc;
        } else {
            // Parse token
            stringCopy((const char*)0x00e2f044);
            tokenLen = parseToken(&token, str, &tokenLen);
            if (tokenLen != 0) {
                ((void(*)(int))0x00e2f044)(tokenLen);
            }
            void* tokenPtr = token;
            if (tokenPtr == nullptr) {
                tokenPtr = defaultString;
            }
            stringCopy((const char*)tokenPtr);

            // Find mapping in list (complex traversal)
            void* current = listBuffer;
            while (current != nullptr && *(char*)((uintptr_t)current + 0x29) == 0) {
                int cmp = compareStrings((int*)&tokenLen);
                if (cmp < 0) {
                    current = *(void**)((uintptr_t)current + 8); // next
                } else {
                    current = *(void**)current; // prev?
                }
            }
            // After loop, current points to a valid mapping
            if (current == listBuffer || compareStrings((int*)((uintptr_t)current + 12)) < 0) {
                // Use tempBuffer
                mapping = tempBuffer;
            } else {
                mapping = current;
            }
            // Extract values
            uint32_t* mappingData = (uint32_t*)mapping;
            uint32_t val0 = mappingData[7];
            uint32_t val1 = mappingData[8];
            uint32_t val2 = mappingData[9];
            extraDst[0] = val0;
            extraDst[1] = val1;
            extraDst[2] = val2;
            // Overwrite with original str? (decompiler artifact)
            extraDst[0] = str;
            // Free token
            if (token != nullptr) {
                ((void(*)(void*))0x00e2f044)(token);
            }
        }
        extraSrc += 2; // advance source
        extraDst += 3; // advance destination
    }

    // Cleanup
    getFileSize(filePtr); // actually FUN_00697ea0 called again? Might be a different function
    cleanupMapping(&token, tempBuffer, listBuffer);
    freeMemory(listBuffer);
    listBuffer = nullptr;
    cleanupAnother(&token, &listBuffer, nullptr); // second cleanup
    freeMemory(tempBuffer);
    tempBuffer = nullptr;

cleanup:
    if (fileHandle != nullptr && fileHandle != (void*)0x00e2df14) {
        ((void(*)(void*))0x00e2f044)(fileHandle);
    }
    return;
}