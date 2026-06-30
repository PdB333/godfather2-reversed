// FUNC_NAME: EARS::Core::Name::assign
void __thiscall EARSName::assign(int *this, undefined4 source)
{
    // Check if global name system is initialized; if not, initialize it
    if (!FUN_0067e210()) {
        FUN_006817c0();
        FUN_004e0180();
    }

    // Resolve source to a Name object pointer
    int *sourceName = (int *)FUN_006833d0(source);
    if (sourceName != this) {
        // Copy short name (64 bytes) from source's virtual method
        size_t shortNameLen = 0x40;
        char *shortNameSrc = (char *)(**(code **)(*sourceName + 0x18))(); // +0x18: virtual getShortName
        _strncpy((char *)((int)this + 0x0b), shortNameSrc, shortNameLen); // this+0x0b: shortName buffer

        // Copy long name (256 bytes) from source's virtual method
        size_t longNameLen = 0x100;
        char *longNameSrc = (char *)(**(code **)(*sourceName + 0x1c))(); // +0x1c: virtual getLongName
        _strncpy((char *)((int)this + 0x4c), longNameSrc, longNameLen); // this+0x4c: longName buffer (int offset 0x13 -> byte offset 0x4c)

        // Null-terminate the names explicitly
        *(char *)((int)this + 0x4b) = '\0'; // Null terminate shortName at offset 0x0b+0x40=0x4b
        *(char *)((int)this + 0x14c) = '\0'; // Null terminate longName at offset 0x4c+0x100=0x14c (int offset 0x53 * 4 = 0x14c)
    }

    // Perform name hash/registration
    FUN_009c7700();
    char nameFlags = FUN_0067c9f0((int)this + 0x0b, (int)this + 0x4c); // compute comparison result
    *(char *)((int)this + 0x0a) = nameFlags; // store at this+0x0a

    // Additional post-assignment processing
    FUN_00411cf0();
    FUN_0068c590(nameFlags == '\0'); // signal if names are empty

    // Set a global flag indicating a name has been assigned
    *(uint *)(DAT_012234a4 + 0x4c) |= 1;
}