// FUNC_NAME: AudioDataManager::loadBank

// Global pointer to audio bank data (DAT_0112f9dc)
extern void* g_pAudioBankData;

// Memory copy function (FUN_00408900) - likely memcpy or decompress
void __cdecl copyMemory(void* dest, void* src, int size);

void __thiscall AudioDataManager::loadBank(void* this_ptr)
{
    // Check if already loaded (flag at +0x80)
    if (*(char*)((int)this_ptr + 0x80) == 0)
    {
        // If global bank data exists, copy 0x8000 bytes to local buffer at +0x4c
        if (g_pAudioBankData != 0)
        {
            copyMemory((void*)((int)this_ptr + 0x4c), g_pAudioBankData, 0x8000);
        }
        // Mark as loaded
        *(char*)((int)this_ptr + 0x80) = 1;
    }
}