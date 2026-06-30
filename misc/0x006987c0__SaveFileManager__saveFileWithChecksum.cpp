// FUNC_NAME: SaveFileManager::saveFileWithChecksum
int __thiscall SaveFileManager::saveFileWithChecksum(int this, wchar_t** filePath)
{
    HANDLE hFile;
    DWORD bytesWritten;
    DWORD bytesRead;
    LPVOID buffer;
    DWORD fileSize;
    DWORD checksum;
    int blockIndex;
    int currentOffset;
    wchar_t* path;

    if (*(int*)(this + 0x18) != -1) {
        return 3; // File already open
    }

    path = *filePath;
    if (path == (wchar_t*)0x0) {
        path = L"";
    }

    // Open file for writing (GENERIC_WRITE, CREATE_ALWAYS)
    hFile = CreateFileW(path, 0x40000000, 0, (LPSECURITY_ATTRIBUTES)0x0, 5, 0x80, (HANDLE)0x0);
    *(HANDLE*)(this + 0x18) = hFile;
    if (hFile == INVALID_HANDLE_VALUE) {
        return 3;
    }

    bytesWritten = 0;
    // Write a placeholder for the checksum (4 bytes)
    DWORD placeholder = 4;
    WriteFile(hFile, &placeholder, 4, &bytesWritten, (LPOVERLAPPED)0x0);
    if (bytesWritten == 4) {
        // Write the header (8 bytes) from the data buffer at +0x14
        // The header likely contains a count of blocks (short at offset 4)
        DWORD headerSize = 8;
        WriteFile(hFile, *(LPCVOID*)(this + 0x14), 8, &bytesWritten, (LPOVERLAPPED)0x0);
        if (bytesWritten == 8) {
            blockIndex = 0;
            // Number of blocks is stored in the header at offset 4 (short)
            short blockCount = *(short*)(*(int*)(this + 0x14) + 4);
            if (blockCount != 0) {
                currentOffset = 0;
                while (blockIndex < blockCount) {
                    bytesWritten = 0;
                    // Write a block of 0x504 bytes from the data at +0x4
                    WriteFile(hFile, (LPCVOID)(*(int*)(this + 0x4) + currentOffset), 0x504,
                              &bytesWritten, (LPOVERLAPPED)0x0);
                    if (bytesWritten != 0x504) {
                        return 3; // Write error
                    }
                    blockIndex++;
                    currentOffset += 0x504;
                }
            }

            // Close the file after writing
            if (CloseHandle(*(HANDLE*)(this + 0x18)) == 0) {
                return 2; // Close handle failed
            }
            *(int*)(this + 0x18) = -1;

            // Reopen the file for reading and writing (GENERIC_READ | GENERIC_WRITE, OPEN_EXISTING)
            path = *filePath;
            if (path == (wchar_t*)0x0) {
                path = L"";
            }
            hFile = CreateFileW(path, 0xC0000000, 0, (LPSECURITY_ATTRIBUTES)0x0, 4, 0x80, (HANDLE)0x0);
            *(HANDLE*)(this + 0x18) = hFile;
            if (hFile != INVALID_HANDLE_VALUE) {
                // Seek to offset 4 (skip checksum placeholder)
                SetFilePointer(hFile, 4, (PLONG)0x0, FILE_BEGIN);
                fileSize = GetFileSize(hFile, (LPDWORD)0x0);
                fileSize -= 4; // Exclude the checksum itself
                // Allocate buffer for the data
                buffer = (LPVOID)FUN_009c8e80(fileSize); // HeapAlloc or similar
                if (ReadFile(hFile, buffer, fileSize, &bytesRead, (LPOVERLAPPED)0x0) != 0) {
                    // Compute checksum of the data
                    checksum = FUN_00ab8560(0, buffer, fileSize); // Some checksum function
                    FUN_009c8f10(buffer); // HeapFree
                    // Seek to beginning of file to overwrite checksum
                    SetFilePointer(hFile, 0, (PLONG)0x0, FILE_BEGIN);
                    DWORD checksumSize = 4;
                    WriteFile(hFile, &checksum, 4, &bytesWritten, (LPOVERLAPPED)0x0);
                    if (bytesWritten == 4) {
                        // Call finalization function
                        return FUN_00697fa0();
                    }
                }
            }
            return 3;
        }
    }
    return 3;
}
```