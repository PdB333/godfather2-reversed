// FUN_005b6640: AptCharacter::load
// Loads an SWF character file, validates it ends with .swf, and processes it.
// Assumes param_1 is 'this' (unused in this function) and param_2 is the filename.
int AptCharacter::load(const char* filename) {
    // EA-specific debug initialization
    someInit(0);

    // Quick exit if filename is a sentinel (1 used for "no parameter" in debug)
    if (filename == (const char*)1) {
        goto done;
    }

    // Assert: "nParams == 1" – custom EA assert macro checking that exactly one parameter was passed.
    // In practice, this verifies filename != NULL.
    {
        char* expr = (char*)"nParams == 1";
        char* file = (char*)"..\\source\\Apt\\AptCharacter.cpp";
        int line = 0x582;
        // Assert condition: always true? Actually checks if DAT_01129131 (global assert flag) is set.
        // If set and assertion fails (filename == 1?), it breaks.
        // Skipping detailed assert implementation.
    }

done:
    // Buffer for processing filename
    struct {
        int length;
        int padding;
    } strInfo;
    char buffer[32]; // allocated on stack
    strInfo.length = 0;
    strInfo.padding = 0;
    // Zero out buffer
    buffer[0] = '\0';

    // Get string length? Actually FUN_005a92b0 probably retrieves filename into strInfo.
    getStringLength(&strInfo); // Uses local_38/buffer

    // Check if filename ends with ".swf" (case insensitive)
    if (strInfo.length == 0 ||
        (strInfo.length >= 4 &&
         (buffer[strInfo.length - 1] == 'f' || buffer[strInfo.length - 1] == 'F') &&
         (buffer[strInfo.length - 2] == 'w' || buffer[strInfo.length - 2] == 'W') &&
         (buffer[strInfo.length - 3] == 's' || buffer[strInfo.length - 3] == 'S') &&
         buffer[strInfo.length - 4] == '.')) {
        // Not a .swf file – skip loading
    } else {
        // .swf file processing
        char* pathPtr = nullptr; // local_5c
        char* basePtr = nullptr; // local_58
        // Initialize for file operations
        loadFile(&strInfo);
        readData();
        // Extract the base filename (without extension)
        if (basePtr != buffer && basePtr != nullptr) {
            free(basePtr);
        }
        if (strInfo.length > 3) {
            char* end = &buffer[strInfo.length];
            char* start = end - 4;
            extractFilenameSegment(&start, &end);
        }
        // Parse and load the SWF
        parseSwf(&strInfo);
        finalizeLoad();
        // Close and cleanup
        loadFile(&strInfo);
        closeFile(pathPtr);
        if (pathPtr != &buffer && pathPtr != nullptr) {
            free(pathPtr);
        }
    }

    // Return a global success/result flag
    void* result = (void*)DAT_0119cbbc;
    if (buffer != nullptr && buffer != (char*)0x0) {
        free(buffer);
    }
    return (int)result;
}