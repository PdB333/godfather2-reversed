// FUNC_NAME: MemoryMappedFile::openOrCreate
// Function Address: 0x00699c00
// Role: Opens or creates a memory-mapped file (shared memory) for inter-process communication or recording.
// Uses a file path obtained from getSharedMemoryFilePath (FUN_00699280). Creates file if not exists,
// maps a view if file size < 8, stores handles and pointers in the object.

class MemoryMappedFile {
public:
    // Struct offsets (relative to this pointer, sizeof(undefined4)=4)
    // +0x00: mappedBase (void*)
    // +0x14: headerBuffer (allocated 8-byte header)
    // +0x18: fileHandle (HANDLE)
    // +0x1C: mappingHandle (or duplicate of mappedBase)
    // +0x24: fileSize (DWORD)
    // +0x28: currentSize (DWORD, used as read/write position)

    int __thiscall openOrCreate() {
        LPCWSTR path = nullptr;
        int result;

        // Get the shared memory file path (likely a fixed path like "Godfather2SharedMem")
        // Returns 8 on success, fills path
        result = getSharedMemoryFilePath(&path);  // FUN_00699280
        if (result != 8) {
            if (path) {
                freePathString(path);  // unknown deallocator function pointer (local_4)
            }
            return result;
        }

        // Open or create the file (OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL)
        LPCWSTR fileName = (path) ? path : L"";
        HANDLE hFile = CreateFileW(fileName,
                                   GENERIC_READ,
                                   0,
                                   nullptr,
                                   OPEN_ALWAYS,
                                   FILE_ATTRIBUTE_NORMAL,
                                   nullptr);
        this->fileHandle = hFile;  // param_1[6]

        if (hFile == INVALID_HANDLE_VALUE) {
            if (path) {
                freePathString(path);
            }
            return 0;  // failure
        }

        DWORD lastError = GetLastError();
        if (lastError == ERROR_ALREADY_EXISTS) {
            DWORD fileSize = GetFileSize(hFile, nullptr);
            this->fileSize = fileSize;      // param_1[9]
            this->currentSize = fileSize;   // param_1[10]
        }

        // If file is too small (< 8 bytes), allocate a header and map a view
        if (this->currentSize < 8) {
            // Allocate 8-byte header (DWORD version + two SHORT flags)
            DWORD* header = (DWORD*)allocMemory(8);  // FUN_009c8e50, likely heapAlloc
            if (header) {
                header[0] = 4;          // version = 4
                *(WORD*)((BYTE*)header + 4) = 0;  // unused short
                *(WORD*)((BYTE*)header + 6) = 0;  // unused short
            }
            this->headerBuffer = header;  // param_1[5]

            // Map a view of the file (or set up the memory block)
            // Parameters: 0 (unknown), header, 8
            void* mappedView = mapViewOfFile(0, header, 8);  // FUN_00ab8560
            this->mappingHandle = mappedView;  // param_1[7]
            this->mappedBase = mappedView;     // param_1[0]

            // Reset current size to 0 because file is new
            this->currentSize = 0;  // param_1[10]
        }

        if (path) {
            freePathString(path);
        }
        return 8;  // success code
    }

private:
    // Placeholder for unknown external functions
    // These would be resolved from FUN_00699280, FUN_009c8e50, FUN_00ab8560
    int getSharedMemoryFilePath(LPCWSTR* outPath);
    void freePathString(LPCWSTR path);
    void* allocMemory(DWORD size);
    void* mapViewOfFile(DWORD unknown, void* buffer, DWORD size);

    // Data members (in order of offsets used)
    void* mappedBase;          // +0x00
    // other fields...
    void* headerBuffer;        // +0x14
    HANDLE fileHandle;         // +0x18
    void* mappingHandle;       // +0x1C
    DWORD fileSize;            // +0x24
    DWORD currentSize;         // +0x28
};