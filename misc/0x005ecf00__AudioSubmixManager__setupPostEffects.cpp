// FUNC_NAME: AudioSubmixManager::setupPostEffects
// Function at 0x005ecf00
// Initializes submix chain for post-processing effects (reverb, delay, bandpass, send)
// Called during audio system initialization
// param_1: pointer to main audio system (e.g., SoundManager) with large offsets (0x580, 0x42c)
// Uses this pointer in EAX (fastcall convention variant)

int AudioSubmixManager::setupPostEffects(AudioSystem* audioSystem)
{
    int* effectArrayPtr; // pointer to effect slot array (pointed by this+0x14)
    int effectCount;     // current number of effects (stored at this+0x18)
    int submixId;        // ID of submix obtained from "SUBMIX1"
    int result;          // return value from effects setup
    int sendEffectIndex; // index of "SendWetToMaster" effect

    // Initialization calls (likely base or helper setup)
    initializeSubmix();
    initializeBase();

    // Get the submix handle for "SUBMIX1" and store at this+0x2C
    submixId = getSubmixByName("SUBMIX1");
    this->submixHandle = submixId;

    // Add global reverb effect
    addEffectSlot("Submix1", "GlobalReverb", 1);

    // Add delay effect
    addEffectSlot("Delay", "Delay", 1);

    // Add general-purpose bandpass effect
    addEffectSlot("GeneralPurposeBandpass", nullptr, 1);

    // Add send-wet-to-master effect (no custom name)
    addEffectSlot("SendWetToMaster", nullptr, 1);

    // Register the effect chain with the audio system
    // audioSystem+0x580 is likely the audio processing handle
    // 0xFE is a constant (maybe effect chain type or slot count)
    // effectCount is the number of effects added (stored at this+0x18)
    // effectArrayPtr points to the allocated effect slot array (this+0x14)
    result = registerEffectChain(*(int*)(audioSystem + 0x580), 0xFE, effectCount, effectArrayPtr, 0);
    this->chainHandle = result;                    // store at this+0x00
    this->chainHandle2 = result + 0x50;           // some derived handle at this+0x04

    // Now try to retrieve the "SendWetToMaster" effect by name to finalize its setup
    sendEffectIndex = getEffectByName("SendWetToMaster", this);
    if (sendEffectIndex != 0)
    {
        // Found; connect this effect to the master output
        connectEffectToMaster(*(int*)(audioSystem + 0x580), *(int*)(sendEffectIndex + 0x10), 0, this);
        // Set the send level from the audio system's stored value (at audioSystem+0x42C)
        *(int*)this = *(int*)(audioSystem + 0x42C); // This line seems suspicious; likely meant to set a send level
        // Apply the change
        applyEffectChanges(0, this);
        return 1;
    }
    return 0;
}

// Note: The actual class structure is inferred:
// struct AudioSubmixManager {
//   int chainHandle;          // +0x00
//   int chainHandle2;         // +0x04
//   int effectCount;          // +0x18 (index 6)
//   int* effectSlots;         // +0x14 (pointer to array of 12-byte effect entries)
//   int submixHandle;         // +0x2C (index 11)
// };
//
// Effect slot struct (12 bytes):
//   struct EffectSlot {
//     char* name;       // +0x00
//     int hash;         // +0x04
//     char active;      // +0x08 (0/1)
//   };

// Helper function prototypes (not defined here)
// int getSubmixByName(const char*);
// void addEffectSlot(const char* submixName, const char* effectName, int active);
// int registerEffectChain(int audioHandle, int chainType, int count, int* slots, int flags);
// int getEffectByName(const char* name, void* context);
// void connectEffectToMaster(int audioHandle, int effectParam, int index, void* context);
// void applyEffectChanges(int param, void* context);
// void initializeSubmix();
// void initializeBase();