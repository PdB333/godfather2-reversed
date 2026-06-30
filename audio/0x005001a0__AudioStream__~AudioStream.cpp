// FUNC_NAME: AudioStream::~AudioStream
void __thiscall AudioStream::~AudioStream(void)
{
    int tableIndex;
    uint soundId;
    int* listPtr;
    // this = unaff_ESI

    // Set vtable to base destructor vtable
    *reinterpret_cast<int**>(this) = &PTR_FUN_00e37c78;

    // If certain flags are set and soundId is valid and a flag at byte +0x35 is zero, call cleanup
    if (((*reinterpret_cast<byte*>(reinterpret_cast<uint32>(this) + 0x2C) & 2) != 0) &&
        (reinterpret_cast<uint32*>(this)[0xC] != 0) &&
        (*reinterpret_cast<char*>(reinterpret_cast<uint32>(this) + 0x35) == '\0')) {
        FUN_004b1ca0(); // likely Stop() or ReleaseAudio()
    }

    soundId = reinterpret_cast<uint32*>(this)[0xC]; // offset +0x30
    if ((soundId != 0) && ((soundId & 0xFFFF) < 0x200)) {
        tableIndex = (soundId & 0xFFFF) * 0x30 + 0x10 + DAT_012234bc;
        if ((tableIndex != 0) &&
            (*reinterpret_cast<uint32*>(tableIndex + 0x2C) == soundId) && (tableIndex != 0)) {
            // Clear entries in the resource table
            *reinterpret_cast<uint32*>(tableIndex + 0x24) = 0;
            *reinterpret_cast<uint32*>(tableIndex + 0x28) = 0;
        }
    }

    // Switch to destructed vtable
    *reinterpret_cast<int**>(this) = &PTR_FUN_00e37110;

    // If a linked list pointer is valid, insert the soundId into a global free list
    if (reinterpret_cast<uint32*>(this)[4] != 0) { // offset +0x10
        listPtr = reinterpret_cast<int*>(DAT_01206880 + 0x14);
        **reinterpret_cast<int***>(DAT_01206880 + 0x14) = &PTR_LAB_01123be8; // set vtable of list node?
        *listPtr = *listPtr + 4;
        *reinterpret_cast<int*>(*listPtr) = reinterpret_cast<uint32*>(this)[4]; // store soundId
        *listPtr = *listPtr + 4;
        reinterpret_cast<uint32*>(this)[4] = 0;
        reinterpret_cast<uint32*>(this)[5] = 0; // clear offsets +0x10 and +0x14
    }

    return;
}