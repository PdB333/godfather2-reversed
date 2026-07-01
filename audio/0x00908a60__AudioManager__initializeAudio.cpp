// FUNC_NAME: AudioManager::initializeAudio
// Based on Ghidra decompilation at 0x00908a60.
// This function initializes the audio system: checks for resources, clears memory,
// registers a configuration, and finalizes initialization.

// Global pointer to the AudioManager singleton (address DAT_012234e0)
extern AudioManager* g_pAudioManager;

// Forward declarations of helper functions
int checkEngineResource(int size);          // FUN_009c8e50
void clearMemory(int size);                 // FUN_00568640
void initializeAudioOutput();               // FUN_00908820

// Known string/data references (provided by Ghidra)
extern char DAT_00908510[];                 // Some string, e.g., "AudioConfig"
extern char LAB_00908520[];                 // Another string/label, e.g., a callback name

void AudioManager::initializeAudio()
{
    int iVar1;

    // Check if audio resource of size 0x10 exists
    iVar1 = checkEngineResource(0x10);
    if (iVar1 != 0) {
        clearMemory(0x80);  // Clear 128 bytes (likely a buffer)
    }

    // Check if audio resource of size 0x9C exists
    iVar1 = checkEngineResource(0x9C);
    if (iVar1 != 0) {
        initializeAudioOutput();  // Set up audio output stream
    }

    // Call virtual method at vtable offset +4: LoadConfig(configName, callback, flags)
    // Parameters: address of config name, address of label/callback, flag=0
    (g_pAudioManager->*reinterpret_cast<void(__thiscall*)(AudioManager*, char*, char*, int)>
        (*(void***)g_pAudioManager)[1])(DAT_00908510, LAB_00908520, 0);

    // Call virtual method at vtable offset +0x14: FinalizeInit(bankID1, bankID2, finalLabel)
    // Parameters: two four-character codes (likely bank identifiers) and string "FINAL"
    (g_pAudioManager->*reinterpret_cast<void(__thiscall*)(AudioManager*, int, int, const char*)>
        (*(void***)g_pAudioManager)[5])(0x5549464C, 0x494E4954, "FINAL");
}