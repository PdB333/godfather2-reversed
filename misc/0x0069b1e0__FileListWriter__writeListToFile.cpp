// FUNC_NAME: FileListWriter::writeListToFile
undefined1 __thiscall FileListWriter::writeListToFile(int thisPtr, int listPtr) {
    char success = 0;
    wchar_t* filePath = nullptr;
    int unused1 = 0; // local_1c
    int unused2 = 0; // local_18
    void (*destroyFilePath)(wchar_t*) = nullptr; // local_14 - actually a destructor/free for filePath
    int stringNodeBuffer[3]; // local_10
    void (*destroyString)(void*) = nullptr; // local_4 - destructor for retrieved string node

    // Resolve output file path from internal parameters
    // First argument: resource ID at this+0x28, then two config pointers at this+0x3c and this+0x2c
    bool ok = resolveFilePath(*(int*)(thisPtr + 0x28), (void*)(thisPtr + 0x3c), (void*)(thisPtr + 0x2c), &filePath, 1);
    if (ok) {
        wchar_t* filename = filePath ? filePath : L"";
        FILE* file = _wfopen(filename, L"wt");
        if (file) {
            // Iterate over linked list: listPtr is a list head with next pointer at +8, sentinel at listPtr+4
            for (int node = *(int*)(listPtr + 8); node != listPtr + 4; node = getNextNode(node)) {
                // Extract string from node fields (at offsets +0x10 and +0x20)
                int* strPtr = extractString(stringNodeBuffer, node + 0x10, node + 0x20);
                char* str = (char*)*strPtr;
                if (str == nullptr) {
                    str = ""; // fallback empty string
                }
                fputs(str, file);
                // If string buffer has allocated memory, free it
                if (stringNodeBuffer[0] != 0) {
                    (*destroyString)((void*)stringNodeBuffer[0]);
                }
            }
            fclose(file);
            success = 1;
        }
        // Free file path if allocated
        if (filePath) {
            (*destroyFilePath)(filePath);
        }
        return success;
    }
    if (filePath) {
        (*destroyFilePath)(filePath);
    }
    return 0;
}