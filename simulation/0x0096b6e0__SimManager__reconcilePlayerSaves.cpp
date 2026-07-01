// FUNC_NAME: SimManager::reconcilePlayerSaves
void __fastcall SimManager::reconcilePlayerSaves(SimManager* this)
{
    int fileList[5]; // array for file enumeration
    int fileCount = 0;
    int processedCount = 0;
    int fileIndex;
    int someId;
    char* str1;
    char* str2;

    if (DAT_012233bc != (int*)0x0) {
        // Get save directory path
        int pathResult = (**(code**)(*(int*)DAT_012233bc + 0x28))();
        FUN_0096ae10(pathResult); // likely normalize path or similar

        fileList[0] = 0;
        fileIndex = 0;
        if (fileList[2] != 0) { // if there are files to iterate
            int* fileEntry = (int*)(fileList[1] + 0x18); // file info struct +0x18
            int remaining = fileList[2];
            do {
                if (*(char*)(fileEntry[-1]) == '\0') { // if filename[0] != 0
                    str1 = (char*)0x0;
                    str2 = (char*)0x0;
                    if (*fileEntry != 0) {
                        FUN_004d3e20(*fileEntry); // likely free/delete
                    }
                    someId = fileEntry[-2];
                    FUN_004d3b50(&str1); // likely string copy
                    FUN_004d4300(&DAT_00e2f048); // global string
                    FUN_004d43f0(fileEntry[-6], 0, fileEntry[-5]); // some path operation

                    char* s1 = str1 ? str1 : (char*)&DAT_0120546e;
                    char* s2 = str2 ? str2 : (char*)&DAT_0120546e;

                    int result = FUN_00412740(s1); // likely strlen or hash
                    int handle = FUN_00403a50(s2, 0, 4, &someId, result); // open file
                    int fileHandle = FUN_004025a0(handle); // wrap handle
                    if ((fileHandle == 0) || (*(int*)(fileHandle + 0x24) != 3)) {
                        // Not a valid save file - delete it
                        int dest = (this == 0) ? 0 : this + 0x50;
                        FUN_004035c0(handle, 0x100, dest); // delete file with path
                        processedCount++;
                    }
                    if (str2 != (char*)0x0) {
                        (*(code**)str2)(); // likely free
                    }
                    if (str1 != (char*)0x0) {
                        (*(code**)str1)(); // likely free
                    }
                }
                fileEntry += 7; // advance to next entry
                remaining--;
                fileIndex = processedCount;
            } while (remaining != 0);
        }
        *(int*)(this + 0x2e8) = processedCount; // store count of deleted files
        if (processedCount != 0) {
            *(uint*)(this + 0x6f4) |= 0x8000; // set some flag
            FUN_00905600(); // likely notify/refresh
            return;
        }
        *(uint*)(this + 0x6f4) &= 0xffff7fff; // clear flag
        FUN_00905600();
    }
}