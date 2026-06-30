// FUNC_NAME: SoundTestManager::initializeSpeakerTest

#include <cstdint>

// Forward declarations for external functions (assuming from EARS engine)
extern void audioDeviceInitialize(void* device);                     // FUN_004d3e20
extern uint32_t stringToHash(const char* str);                      // FUN_004dafd0
extern void enumerationBegin();                                     // FUN_00c9eac0
extern void enumerationEnd();                                       // FUN_00c9eae0
extern void* getResourceByTag(uint32_t tag);                        // FUN_00c9cd50
extern void setResource(void* manager, void* resource, int, void*); // FUN_00c9cbe0
extern void* createDacObject();                                     // FUN_00c9ebd0
extern void setDacObject(int, void*);                               // FUN_00c9cd40
extern void debugLog(void* manager, int* severity, const char* fmt, void* data, int channel); // FUN_005e25f0
extern void flushDebugMessages();                                   // FUN_005e1fd0
extern void finalizeSpeakerTest(SoundTestManager* self, int handle);// FUN_005ef5f0

// Global variables
extern uint8_t g_speakerTestModeFlag;       // DAT_01194749
extern char* g_debugManager;                // DAT_0122350c (pointer to debug manager)
extern const char* g_defaultSpeakerString;  // DAT_0120546e

// Tag constants
const uint32_t TAG_SEN0 = 0x53656e30;  // "Sen0"
const uint32_t TAG_DAC0 = 0x44616330;  // "Dac0"

// Structure for a sound bank entry (12 bytes)
struct SoundBankEntry {
    void*   pData;      // pointer to data (used for tag check at +0x28)
    uint8_t unused[8];  // remaining 8 bytes (not used in this function)
};

// Structure for a sound bank (12 bytes)
struct SoundBank {
    void*           pEntryArray;  // pointer to array of SoundBankEntry
    int32_t         entryCount;   // number of entries
    // no explicit field for flag array; flags are stored in parallel array at m_flagArrays
};

// Main class
class SoundTestManager {
public:
    // Offsets (in bytes from this)
    // +0x08: uint8_t m_enabled;
    // +0x0c: int32_t m_speakerTestHandle;
    // +0x10: const char* m_defaultString;
    // +0x20: uint32_t m_configData[27]; // 108 bytes
    // +0x58: uint32_t m_speakerTestHash;
    // +0x88: SoundTestManager* m_self;
    // +0x42c: void** m_dacFlagArray; // pointer to array of flags for Dac entries
    // +0x43c: void* m_dacData;       // pointer to array of Dac entries (each 12 bytes?)
    // +0x440: int32_t m_dacCount;
    // +0x470: void* m_flagArrays[5]; // each is pointer to array of flags (or null?)
    // +0x480: SoundBank m_soundBanks[5]; // array of 5 SoundBank structures
    // +0x56c: void* m_streamManager;
    // +0x580: void* m_audioManager;

    void __thiscall initializeSpeakerTest(int32_t param_device, uint32_t* param_config, uint8_t param_enableGlobal, int32_t param_handle);

private:
    // Helper to process one sound bank
    void processSoundBank(SoundBank* bank, void** flagArray, void* audioManager);
};

// The function address 0x005ef2f0
void __thiscall SoundTestManager::initializeSpeakerTest(int32_t param_device, uint32_t* param_config, uint8_t param_enableGlobal, int32_t param_handle)
{
    // Local variables
    int32_t outerCount;          // local_14
    uint32_t idx;                // uVar2
    SoundBank* currentBank;      // piVar6
    SoundBankEntry** entryPtr;   // piVar5
    uint32_t temp1;              // uVar8
    uint32_t result;             // uVar1
    uint32_t local10[3];         // used for Sen0/Dac0 operations

    // Initialize basic fields
    this->m_speakerTestHandle = param_handle;               // +0x0c
    this->m_enabled = 1;                                   // +0x08
    g_speakerTestModeFlag = param_enableGlobal;             // global

    // Initialize audio device
    audioDeviceInitialize((void*)param_device);

    // Copy configuration data (27 dwords = 108 bytes) from param_config to this+0x20
    uint32_t* dest = &this->m_configData[0];
    for (int i = 27; i > 0; --i) {
        *dest++ = *param_config++;
    }

    // Hash "SPEAKER_TEST" and store
    this->m_speakerTestHash = stringToHash("SPEAKER_TEST");  // +0x58

    // Overwrite first dword of config data with a function pointer (LAB_005ef250)
    // This is likely a virtual function table or callback pointer.
    // We place it as a function pointer type for clarity.
    this->m_configData[0] = reinterpret_cast<uint32_t>(&SoundTestManager::someInternalHandler); // placeholder

    // Store self pointer
    this->m_self = this;                                     // +0x88

    // Check if audio and stream managers exist (at +0x580 and +0x56c)
    if ((this->m_audioManager != nullptr) && (this->m_streamManager != nullptr)) {
        // Begin enumeration of resources
        enumerationBegin();

        // Iterate over the 5 sound banks
        currentBank = &this->m_soundBanks[0];  // +0x480
        outerCount = 5;

        do {
            idx = 0;
            if (currentBank->entryCount != 0) {
                entryPtr = reinterpret_cast<SoundBankEntry**>(currentBank->pEntryArray) + 1; // skip first 4 bytes? Actually original: piVar5 = (int*)(*piVar6 + 4); // *piVar6 is the pointer to entry array, add 4 bytes (?) -> likely points to array of pointers, each pointer is at +0 of entry? Hmm.
                // The original code: piVar5 = (int *)(*piVar6 + 4); // *piVar6 is a pointer to array of 12-byte entries, then +4 bytes. But we treat each entry as a 12-byte struct where first 4 bytes is a pointer to data. piVar5 is then a pointer to that pointer? Actually piVar5 is used as *piVar5 which gives the pointer. So we can model entryPtr as pointer to the data pointer inside each entry.
                // To match, we iterate through entries with step 12 bytes, and the data pointer is at offset 0 of each entry.
                do {
                    // Check if the tag at (pData + 0x28) equals TAG_SEN0
                    SoundBankEntry* entry = reinterpret_cast<SoundBankEntry*>(entryPtr); // entryPtr points to array of entries
                    if (*(uint32_t*)((uint8_t*)entry->pData + 0x28) == TAG_SEN0) {
                        // Only proceed if the corresponding flag array entry is non-null
                        // flagArray is borrowed from m_flagArrays at respective index
                        // We use the __thiscall: param1=this, but we need the flag array pointer.
                        // In original: piVar6[-4] accesses the flag array for current bank.
                        // So flagArray = this->m_flagArrays[ (currentBank - &this->m_soundBanks[0]) ].
                        int32_t bankIndex = currentBank - &this->m_soundBanks[0];
                        void** flagArray = this->m_flagArrays[bankIndex];
                        if ((int32_t)idx >= 0 && flagArray[idx] != nullptr) {
                            // Get resource by tag and set it
                            void* resource = getResourceByTag(TAG_SEN0); // FUN_00c9cd50
                            setResource(this->m_audioManager, resource, 0, local10); // FUN_00c9cbe0
                            idx = 0;
                            // Now check for Dac0 entries in the same bank
                            if (this->m_dacCount != 0) {
                                // Start iterating over Dac entries (from +0x43c)
                                void** dacEntryPtr = reinterpret_cast<void**>(this->m_dacData) + 1; // +4 as original
                                // Actually original sets piVar5 = *(int *)(param_1 + 0x43c) + 4; then loops.
                                // That pointer is to array of 12-byte Dac entries? We'll follow original logic.
                                uint32_t dacIdx = 0;
                                while (dacIdx < (uint32_t)this->m_dacCount) {
                                    dacEntryPtr = reinterpret_cast<void**>(reinterpret_cast<uint32_t>(this->m_dacData) + 4); // not correct, need careful offset
                                    // better to simulate loop:
                                    // original while( true ) loop:
                                    // uVar2 = 0; before entering, then:
                                    // while(true) { uVar2++; piVar5 +=3; if (uVar2 >= dacCount) break; LAB_005ef400: if (*(int*)(*piVar5 + 0x28) == 0x44616330) { check flag... } }
                                    // So we need to iterate over an array at this->m_dacData of 12-byte structures, each with pointer at offset0.
                                    // We'll implement as:
                                    for (; dacIdx < (uint32_t)this->m_dacCount; ++dacIdx) {
                                        void* dacEntryData = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this->m_dacData) + dacIdx * 12 + 0);
                                        if (*(uint32_t*)((uint8_t*)dacEntryData + 0x28) == TAG_DAC0) {
                                            // Check flag array at +0x42c
                                            void** dacFlagArray = reinterpret_cast<void**>(this->m_dacFlagArray);
                                            // The original uses *(int *)(*(int *)(param_1 + 0x42c) + uVar2 * 4)
                                            // So m_dacFlagArray is a pointer to an array of flags
                                            if ((int32_t)dacIdx >= 0 && dacFlagArray[dacIdx] != nullptr) {
                                                local10[0] = reinterpret_cast<uint32_t>(createDacObject()); // FUN_00c9ebd0
                                                setDacObject(0, local10); // FUN_00c9cd40
                                            }
                                            break; // after handling Dac0, break inner loop
                                        }
                                    }
                                    break; // after the while loop, break to outer (out of do)
                                }
                            }
                        }
                        break; // after processing Sen0, break out of entry loop
                    }
                    idx++;
                    entryPtr += 3; // each entry is 12 bytes, so jump 3 dwords
                } while (idx < (uint32_t)currentBank->entryCount);
            }
            // Move to next bank
            currentBank++;
            outerCount--;
        } while (outerCount != 0);

        // End enumeration
        enumerationEnd();
    }

    // Finalization part
    const char* str = this->m_defaultString;
    if (str == nullptr) {
        str = g_defaultSpeakerString;
    }

    // If debug logging enabled (global flag at offset 0x1744 of debug manager)
    if (*(uint8_t*)((uint8_t*)g_debugManager + 0x1744) != 0) {
        // Log a debug message with the config data (param_1 + 0x20) and channel -1
        // The function expects a pointer to int for severity (we pass local variable not used later)
        int32_t severity = 0; // placeholder, original uses local_14 but after loop it holds something else
        debugLog(g_debugManager, &severity, str, &this->m_configData, -1);
    }

    flushDebugMessages();

    // Call finalize method with this and the handle
    finalizeSpeakerTest(this, this->m_speakerTestHandle);
}