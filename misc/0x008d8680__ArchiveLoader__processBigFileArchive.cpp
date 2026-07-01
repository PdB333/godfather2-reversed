// FUNC_NAME: ArchiveLoader::processBigFileArchive
void __thiscall ArchiveLoader::processBigFileArchive(void* thisPtr, const char* archivePath) {
    char cVar1;
    int fileType;
    int fileEntry;
    undefined4 local_90;
    undefined4 local_8c;
    undefined4 local_88;
    undefined4 local_84;

    // Open the big file archive using the provided path
    FUN_0046f160(archivePath);
    // Find/hash a specific file within the archive (hash constant 0x84ecd042)
    FUN_0043aff0(archivePath, 0x84ecd042);
    cVar1 = FUN_0043b120(); // Check if archive is ready
    while (cVar1 == '\0') {
        FUN_0043b210(); // Get next file entry
        fileType = FUN_0043ab70(); // Determine file type/index
        if (fileType == 0) {
            fileEntry = FUN_0043b210(); // Re-get entry pointer
            *(undefined4*)(thisPtr + 0x188) = *(undefined4*)(fileEntry + 8); // Store some data at +0x188
        }
        else if ((fileType == 1) && (fileEntry = FUN_0043b210(), *(int*)(fileEntry + 8) != 0)) {
            *(undefined1*)(thisPtr + 0x18c) = 1; // Set flag at +0x18c to true
        }
        FUN_0043b1a0(); // Advance to next file or close?
        cVar1 = FUN_0043b120();
    }
    // After loop, check if load state at +0x184 is null
    if (*(int*)(thisPtr + 0x184) == 0) {
        FUN_008d8340(); // Perform additional loading
        int loadState = *(int*)(thisPtr + 0x184);
        if ((loadState != 0) && (*(int*)(loadState + 8) == 0)) {
            FUN_009e7450(loadState); // Cleanup / free
        }
        int globalObj = FUN_00471610(); // Get global object (e.g., player camera)
        if ((*(int*)(thisPtr + 0x184) != 0) && (*(int*)(*(int*)(thisPtr + 0x184) + 8) != 0)) {
            local_90 = *(undefined4*)(globalObj + 0x30);
            local_8c = *(undefined4*)(globalObj + 0x34);
            local_88 = *(undefined4*)(globalObj + 0x38);
            local_84 = 0;
            FUN_009f1820(&local_90, 0); // Set vector or transform to zero
        }
    }
    return;
}