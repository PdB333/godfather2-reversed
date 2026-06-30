// FUNC_NAME: getDiskFreeSpace
void getDiskFreeSpace(void)
{
    ULARGE_INTEGER freeBytesAvailable;

    // Query disk free space for current directory (NULL = current directory)
    // Results are discarded - typical of a debug/profiling call
    GetDiskFreeSpaceExA(
        (LPCSTR)0x0,                       // lpDirectoryName (current directory)
        &freeBytesAvailable,               // lpFreeBytesAvailable
        (PULARGE_INTEGER)0x0,              // lpTotalNumberOfBytes (unused)
        (PULARGE_INTEGER)0x0               // lpTotalNumberOfFreeBytes (unused)
    );
}