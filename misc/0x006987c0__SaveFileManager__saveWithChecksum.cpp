// FUNC_NAME: SaveFileManager::saveWithChecksum
// Address: 0x006987c0
// Saves data to a file, writing a checksum at the beginning.
// Writes 4-byte placeholder, then 8-byte header, then array of 0x504-byte chunks.
// Then reopens the file, reads data after the first 4 bytes, computes CRC32, and writes it back at position 0.

int __thiscall SaveFileManager::saveWithChecksum(int this, const wchar_t** filenamePtr) {
    LPCWSTR filename;
    HANDLE fileHandle;
    BOOL success;
    DWORD bytesWritten;
    DWORD bytesToWrite;
    LPVOID buffer;
    int result;
    int chunkIndex;
    int bufferOffset;
    DWORD readBytes;
    DWORD checksum; // 4 bytes

    // If the file handle is not -1, it means a file is already open? Return error 3.
    if (*(int*)(this + 0x18) != -1) {
        return 3;
    }

    filename = *filenamePtr;
    if (filename == nullptr) {
        filename = L"";
    }

    // Create/overwrite file: desired access GENERIC_WRITE (0x40000000), share mode 0, security NULL,
    // creation disposition CREATE_ALWAYS? (5), flags FILE_ATTRIBUTE_NORMAL (0x80), template NULL.
    fileHandle = CreateFileW(filename, 0x40000000, 0, nullptr, 5, 0x80, nullptr);
    *(HANDLE*)(this + 0x18) = fileHandle;
    if (fileHandle == INVALID_HANDLE_VALUE) {
        return 3;
    }

    // Write 4-byte placeholder (value 4) at the start. This will later be overwritten with the checksum.
    bytesToWrite = 4;
    WriteFile(fileHandle, &bytesToWrite, 4, &bytesWritten, nullptr);
    if (bytesWritten != bytesToWrite) {
        // If write failed, cleanup? But handles aren't closed; function returns error without closing.
        return 3;
    }

    // Write 8 bytes from header pointer (usually a magic/version identifier).
    bytesToWrite = 8;
    WriteFile(fileHandle, *(LPCVOID*)(this + 0x14), 8, &bytesWritten, nullptr);
    if (bytesWritten != bytesToWrite) {
        return 3;
    }

    // Write chunks: each 0x504 bytes, count from header's short at offset 4.
    chunkIndex = 0;
    bufferOffset = 0;
    if (*(short*)(*(int*)(this + 0x14) + 4) != 0) {
        do {
            bytesWritten = 0;
            WriteFile(*(HANDLE*)(this + 0x18),
                      (LPCVOID)(*(int*)(this + 4) + bufferOffset),
                      0x504,
                      &bytesWritten,
                      nullptr);
            if (bytesWritten != 0x504) {
                return 3;
            }
            chunkIndex++;
            bufferOffset += 0x504;
        } while (chunkIndex < (int)(uint)*(ushort*)(*(int*)(this + 0x14) + 4));
    }

    // Close the file after writing.
    success = CloseHandle(*(HANDLE*)(this + 0x18));
    if (!success) {
        return 2;
    }
    *(int*)(this + 0x18) = -1; // Reset handle to -1

    // Reopen the same file for reading and writing (GENERIC_READ|GENERIC_WRITE = 0xC0000000)
    filename = *filenamePtr;
    if (filename == nullptr) {
        filename = L"";
    }
    fileHandle = CreateFileW(filename, 0xC0000000, 0, nullptr, 4, 0x80, nullptr);
    *(HANDLE*)(this + 0x18) = fileHandle;
    if (fileHandle == INVALID_HANDLE_VALUE) {
        return 3;
    }

    // Seek to position 4 (skip the placeholder checksum).
    SetFilePointer(fileHandle, 4, nullptr, FILE_BEGIN);

    // Get the file size remaining (from position 4 to end).
    DWORD dataSize = GetFileSize(fileHandle, nullptr);
    dataSize -= 4; // Exclude the checksum word

    // Allocate memory for the data (CHeap::Alloc).
    buffer = FUN_009c8e80(dataSize);
    // Read the rest of the file into buffer.
    success = ReadFile(fileHandle, buffer, dataSize, &readBytes, nullptr);
    if (!success) {
        return 0;
    }

    // Compute checksum of the data (CRC32?).
    checksum = FUN_00ab8560(0, buffer, dataSize);
    // Free the buffer (CHeap::Free).
    FUN_009c8f10(buffer);

    // Seek back to beginning.
    SetFilePointer(fileHandle, 0, nullptr, FILE_BEGIN);

    // Write the computed checksum (4 bytes) at the start.
    bytesToWrite = 4;
    WriteFile(fileHandle, &checksum, 4, &bytesWritten, nullptr);
    if (bytesWritten != bytesToWrite) {
        return 3;
    }

    // Finalize or return status.
    result = FUN_00697fa0();
    return result;
}