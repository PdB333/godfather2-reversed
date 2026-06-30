// FUNC_NAME: FileLoader::initializeFromFile
// Function address: 0x00699c00
// Opens a file, reads its size, and ensures a minimum 8-byte header buffer exists,
// computing a hash of that header. Uses a caller-provided string deallocation callback.

// Class layout (partial, offsets based on decompilation):
// class FileLoader {
//     // +0x00: uint32_t fileHash;          // computed hash (stored twice)
//     // +0x14: uint8_t* headerBuffer;      // allocated header buffer (≥8 bytes)
//     // +0x18: HANDLE hFile;               // Win32 file handle
//     // +0x1C: uint32_t headerHash;        // copy of file hash
//     // +0x24: uint32_t fileSize;          // total file size
//     // +0x28: uint32_t currentSize;        // tracked current size
// };

int __fastcall FileLoader::initializeFromFile(void* thisPtr, void (*freeString)(LPCWSTR))
{
    LPCWSTR fileName = NULL;
    int result;

    // Retrieve the file path from some internal source
    result = getFilePath(&fileName);
    if (result != 8) {
        if (fileName != NULL) {
            freeString(fileName);
        }
        return result;
    }

    // Default to empty string if no filename was returned
    LPCWSTR filePath = (fileName != NULL) ? fileName : L"";

    // Open the file for reading (GENERIC_READ), sharing allowed, sequential scan hint
    HANDLE hFile = CreateFileW(filePath,
                               GENERIC_READ,
                               FILE_SHARE_READ,
                               NULL,
                               OPEN_EXISTING,
                               FILE_FLAG_SEQUENTIAL_SCAN,
                               NULL);
    // Store handle at +0x18
    *(HANDLE*)((uint8_t*)thisPtr + 0x18) = hFile;

    if (hFile == INVALID_HANDLE_VALUE) {
        if (fileName != NULL) {
            freeString(fileName);
        }
        return 0; // failure
    }

    // Check if file already existed (ERROR_ALREADY_EXISTS = 0xB7)
    DWORD lastError = GetLastError();
    if (lastError == ERROR_ALREADY_EXISTS) {
        DWORD fileSize = GetFileSize(hFile, NULL);
        // Store at +0x24 and +0x28
        *(uint32_t*)((uint8_t*)thisPtr + 0x24) = fileSize;
        *(uint32_t*)((uint8_t*)thisPtr + 0x28) = fileSize;
    }

    // Ensure we have at least 8 bytes of header data
    uint32_t currentSize = *(uint32_t*)((uint8_t*)thisPtr + 0x28);
    if (currentSize < 8) {
        // Allocate 8-byte header buffer
        uint8_t* buffer = (uint8_t*)malloc(8);
        if (buffer != NULL) {
            // Initialize header: magic 4, then two zero words
            *(uint32_t*)buffer = 4;                // +0x00: 4
            *(uint16_t*)(buffer + 4) = 0;          // +0x04: 0
            *(uint16_t*)(buffer + 6) = 0;          // +0x06: 0
        }
        // Store buffer at +0x14
        *(uint8_t**)((uint8_t*)thisPtr + 0x14) = buffer;

        // Compute hash of the header (seed=0)
        uint32_t hashValue = computeHash(0, buffer, 8);
        // Store hash at +0x1C and +0x00 (two copies)
        *(uint32_t*)((uint8_t*)thisPtr + 0x1C) = hashValue;
        *(uint32_t*)((uint8_t*)thisPtr + 0x00) = hashValue;

        // Reset current size to 0
        *(uint32_t*)((uint8_t*)thisPtr + 0x28) = 0;
    }

    // Free the filename string using the provided callback
    if (fileName != NULL) {
        freeString(fileName);
    }

    return 8; // success
}