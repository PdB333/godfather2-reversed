// Xbox PDB: char * __cdecl `anonymous namespace'::ReadArgumentsFile(void)
// FUNC_NAME: loadCommandFile
int loadCommandFile(void)
{
    // Variables for file handling and buffer
    void* fileHandle; // originally local_10
    int fileSize;     // originally local_c
    int bufferLength; // originally local_8
    void (*cleanupFunc)(void*); // originally local_4

    fileHandle = nullptr;
    fileSize = 0;
    bufferLength = 0;
    cleanupFunc = nullptr;

    // Open "cmd.txt" with mode 0 (likely read binary)
    fileHandle = fileOpen(&fileHandle, "cmd.txt", 0);
    if (fileHandle != nullptr) {
        // Read file content
        int fileDescriptor = fileRead(fileHandle, 1);
        if (fileDescriptor != 0) {
            // Get pointer to file data buffer
            void* fileBuffer = fileGetBuffer(fileDescriptor);
            // Get length of data (strlen)
            int length = stringLength(fileBuffer);
            // Allocate memory for copy (length + 1 for null terminator)
            int allocatedPtr = memoryAllocate(length + 1);
            if (allocatedPtr != 0) {
                // Copy file content into allocated buffer
                memoryCopy(fileDescriptor, allocatedPtr, length);
                // Get buffer pointer again after copy? (original code)
                fileBuffer = fileGetBuffer(fileDescriptor);
                // Null-terminate the copy
                *(char*)((int)fileBuffer + allocatedPtr) = 0; // Probably meant: *(char*)(allocatedPtr + length) = 0
                // Close the file
                fileClose(fileDescriptor);
                // Return the allocated buffer pointer
                return allocatedPtr;
            }
        }
    }

    // Cleanup if file was opened (original had strange call)
    if (fileHandle != nullptr) {
        // This call is suspicious: cleanupFunc is null, likely bug in decompilation
        // In original code this might be a function pointer from fileHandle struct
        // Or it could be a free/close call
        // We'll assume it's a no-op for reconstruction
        // cleanupFunc(fileHandle); // would crash
    }

    // Return 0 if allocation failed or file not read
    return 0;
}