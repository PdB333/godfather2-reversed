// FUNC_NAME: CharacterAIConfig::initializeFromProfile
void __thiscall CharacterAIConfig::initializeFromProfile(int thisPtr, int profileData)
{
    int extraData;
    int* configBlock;

    // Free any previously allocated configuration block
    if (*(int*)(thisPtr + 0x98) != 0) {
        FUN_009c8eb0(*(int*)(thisPtr + 0x98));  // likely operator delete or custom free
        *(int*)(thisPtr + 0x98) = 0;
    }

    // Allocate new configuration block (0x24 bytes = 36 bytes)
    configBlock = (int*)FUN_009c8e50(0x24);  // likely operator new or custom allocator
    if (configBlock == (int*)0x0) {
        configBlock = (int*)0x0;
    } else {
        // Zero first 6 integers (offsets 0x00..0x14)
        configBlock[0] = 0;
        configBlock[1] = 0;
        configBlock[2] = 0;
        configBlock[3] = 0;
        configBlock[4] = 0;
        configBlock[5] = 0;
        // Initialize last two integers to -1 (offsets 0x1C and 0x20)
        configBlock[7] = -1;
        configBlock[8] = -1;
    }

    *(int**)(thisPtr + 0x98) = configBlock;  // store pointer

    // Copy values from profileData at offsets 100 and 200 into block[7] and block[8]
    configBlock[7] = *(int*)(profileData + 100);   // +0x64
    configBlock[8] = *(int*)(profileData + 200);   // +0xC8

    // If there is additional sub-profile data, copy extended fields
    extraData = *(int*)(profileData + 0xd4);  // +212
    if (extraData != 0) {
        configBlock[0] = *(int*)(extraData + 0x26c);  // +620
        configBlock[1] = *(int*)(extraData + 0x274);  // +628
        configBlock[2] = *(int*)(extraData + 0x1dc);  // +476
        configBlock[4] = *(int*)(extraData + 0x1d8);  // +472 (offset 16)
        configBlock[3] = *(int*)(extraData + 0x29c);  // +668 (offset 12)
    }
    return;
}