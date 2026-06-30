// FUNC_NAME: HardwareInfoLogger::logHardwareInfo
void __fastcall HardwareInfoLogger::logHardwareInfo(int *this)
{
    int vtable;
    unsigned int infoValue;
    BOOL success;
    float freeSpace;
    ULARGE_INTEGER freeBytesAvailable;
    char buf[15];
    
    vtable = *this; // vtable pointer
    infoValue = getSystemInfo(); // returns some OS/hardware identifier
    // Log hardware info: category "HDWR", key "OPSY" (maybe OS version)
    (*(void (__fastcall **)(int *, unsigned int, unsigned int, unsigned int))(vtable + 0x14))(this, 0x48445752, 0x4f505359, infoValue);
    
    freeSpace = 0.0f;
    success = GetDiskFreeSpaceExA(NULL, &freeBytesAvailable, NULL, NULL);
    if (success) {
        freeSpace = (float)(__int64)freeBytesAvailable * freeSpaceConversionFactor; // DAT_00e2cbe0
    }
    __snprintf(buf, 0x10, "%f", (double)freeSpace);
    buf[14] = '\0'; // uStack_4d = 0
    // Log disk space: category "HDWR", key "HDSP"
    (*(void (__fastcall **)(int *, unsigned int, unsigned int, char *))(*(int *)0x012234e0 + 0x14))(0x012234e0, 0x48445752, 0x48445350, buf);
}