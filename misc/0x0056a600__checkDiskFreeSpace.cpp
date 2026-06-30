//FUNC_NAME: checkDiskFreeSpace
// Address: 0x0056a600
// Role: Queries free disk space on current drive (likely for save/streaming checks). Result is unused.

void checkDiskFreeSpace(void)
{
    ULARGE_INTEGER freeBytesAvailable;
    GetDiskFreeSpaceExA(nullptr, &freeBytesAvailable, nullptr, nullptr);
    return;
}