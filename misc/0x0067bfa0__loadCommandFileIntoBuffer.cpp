// FUNC_NAME: loadCommandFileIntoBuffer
int loadCommandFileIntoBuffer(void)
{
    // Local variables for a smart buffer wrapper (likely a struct with buffer pointer, size, and destructor)
    ScopedBuffer* scopedBuffer = nullptr; // +0x00: buffer pointer? (local_10)
    int dummy1 = 0;                // +0x04: unused? (local_c)
    int dummy2 = 0;                // +0x08: unused? (local_8)
    void (*destructor)(void*) = nullptr; // +0x0C: destructor function pointer (local_4)

    // Try to open "cmd.txt" with mode 0 (possibly read-only, or path resolution)
    // This function initializes the scopedBuffer (sets buffer pointer and destructor)
    fileManagerOpen(&scopedBuffer, "cmd.txt", 0);

    // If the file could not be opened, fall back to a default embedded string
    const char* filename = (scopedBuffer != nullptr) ? (const char*)scopedBuffer : (const char*)0x0120546e;

    // Open the file with mode 1 (likely "r")
    FILE* fileHandle = fileOpen(filename, 1);
    int fileSize = 0;

    if (fileHandle != nullptr)
    {
        // Get the underlying file descriptor (or stream identifier)
        int fileDesc = fileGetDescriptor(fileHandle);
        // Get the file size
        int rawSize = fileGetSize(fileDesc);

        // Allocate memory for the file content plus null terminator
        fileSize = memoryAllocate(rawSize + 1);

        if (fileSize != 0)
        {
            // Read the file content into the allocated buffer
            fileRead(fileHandle, (void*)fileSize, rawSize);
            // Null-terminate the string
            *(char*)(fileGetDescriptor(fileHandle) + fileSize) = '\0';
            // Close the file
            fileClose(fileHandle);
        }
    }

    // Clean up the scoped buffer if it was allocated
    if (scopedBuffer != nullptr)
    {
        // Note: destructor is uninitialized here, which would cause a crash.
        // This suggests the function is either never called with a valid scopedBuffer,
        // or the decompiler missed that destructor is set by fileManagerOpen.
        // In practice, fileManagerOpen would set destructor to a proper deallocation function.
        destructor(scopedBuffer);
    }

    return fileSize; // Returns the size of the file content (or 0 if failed)
}