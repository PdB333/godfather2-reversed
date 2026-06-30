// FUNC_NAME: AudioSubmixManager::setupSubmixChain

// 0x005ed2d0
// __thiscall AudioSubmixManager::setupSubmixChain(this)
// Sets up a submix chain: Submix1 -> GlobalReverb, Delay, GeneralPurposeBandpass, Model1Reverb, SendWetToMaster

#include <cstdint>

struct SubmixEntry {
    char** namePtr;       // +0x00
    uint32_t hash;        // +0x04
    uint8_t flag;         // +0x08
};

struct SubmixChainData {
    uint32_t outputHandle;    // +0x00
    // +0x04 unknown
    SubmixEntry* entries;     // +0x14 (in_EAX+5)
    int32_t currentIndex;     // +0x18 (in_EAX+6)
    // +0x1C padding?
    uint32_t masterSubmixID;  // +0x2C (in_EAX[0xB])
};

// Forward declarations for external functions
extern uint32_t getSubmixID(const char* name);                           // FUN_004dafd0
extern void setCurrentSubmix(const char* name);                          // FUN_005e9ba0
extern uint32_t createUniqueHash(uint32_t fourCC);                       // FUN_00c9cd50
extern void setSubmixParameter(uint32_t submixHandle, uint32_t hash, void* param); // FUN_00c9cba0
extern int32_t connectSubmixes(uint32_t submixHandle, uint8_t connectionIndex, 
                                int32_t numEntries, SubmixEntry* entries, int32_t unknown); // FUN_00ca55a0
extern void* getSubmixByID(uint32_t id);                                // FUN_005e9d90
extern void getSubmixParameter(void* submix, uint32_t paramID, uint32_t unknown, void* output); // FUN_00c9cbe0
extern void setSubmixParameterValue(uint32_t paramID, void* value);     // FUN_00c9cd40
extern void submixInit1();                                               // FUN_005ef9a0
extern void submixInit2();                                               // FUN_005ef890

extern char* DAT_00e2cd54;  // "Delay" or similar?

bool __thiscall AudioSubmixManager::setupSubmixChain() {
    SubmixChainData* chainData;  // in_EAX
    int32_t submixID;
    uint32_t hash;
    char** namePtr;
    void* submixHandle;
    uint32_t paramValue[2];

    // Initialization calls
    submixInit1();
    submixInit2();

    // Get the master submix ID for "SUBMIX3" and store it
    submixID = getSubmixID("SUBMIX3");
    chainData->masterSubmixID = submixID;

    // Begin building the submix chain starting from "Submix1"
    setCurrentSubmix("Submix1");

    // --- Add GlobalReverb submix ---
    submixID = chainData->currentIndex;
    hash = createUniqueHash(0x53756230); // "Sub0" little-endian
    // Write hash to entry at offset +4 relative to entry base (backwards list)
    chainData->entries[chainData->currentIndex].hash = hash;
    // Set parameter on the submix handle (this+0x580)
    submixHandle = *(void**)((uint32_t)this + 0x580);
    setSubmixParameter((uint32_t)submixHandle, hash, &namePtr);
    // Store the name pointer and flag
    namePtr = &"GlobalReverb";
    chainData->entries[chainData->currentIndex].namePtr = namePtr;
    chainData->entries[chainData->currentIndex].flag = 1;
    chainData->currentIndex++;

    // --- Add Delay submix ---
    submixID = chainData->currentIndex;
    hash = createUniqueHash(0x44656c30); // "Del0"
    chainData->entries[chainData->currentIndex].hash = hash;
    submixHandle = *(void**)((uint32_t)this + 0x580);
    setSubmixParameter((uint32_t)submixHandle, hash, &namePtr);
    namePtr = DAT_00e2cd54; // Global string, likely "Delay"
    chainData->entries[chainData->currentIndex].namePtr = namePtr;
    chainData->entries[chainData->currentIndex].flag = 1;
    chainData->currentIndex++;

    // --- Add GeneralPurposeBandpass submix ---
    setCurrentSubmix("GeneralPurposeBandpass");
    submixID = chainData->currentIndex;
    hash = createUniqueHash(0x42493230); // "BI20"
    chainData->entries[chainData->currentIndex].hash = hash;
    chainData->entries[chainData->currentIndex].namePtr = nullptr;
    chainData->entries[chainData->currentIndex].flag = 1;
    chainData->currentIndex++;

    // --- Add Model1Reverb submix ---
    setCurrentSubmix("Model1Reverb");
    submixID = chainData->currentIndex;
    hash = createUniqueHash(0x524d3130); // "RM10"
    chainData->entries[chainData->currentIndex].hash = hash;
    chainData->entries[chainData->currentIndex].namePtr = nullptr;
    chainData->entries[chainData->currentIndex].flag = 6;
    chainData->currentIndex++;

    // --- Add SendWetToMaster submix ---
    setCurrentSubmix("SendWetToMaster");
    submixID = chainData->currentIndex;
    hash = createUniqueHash(0x53656e30); // "Sen0"
    chainData->entries[chainData->currentIndex].hash = hash;
    chainData->entries[chainData->currentIndex].namePtr = nullptr;
    chainData->entries[chainData->currentIndex].flag = 6;
    chainData->currentIndex++;

    // Connect the submix chain: connection index 0xFE (254), with current number of entries
    submixHandle = *(void**)((uint32_t)this + 0x580);
    int32_t result = connectSubmixes((uint32_t)submixHandle, 0xFE, chainData->currentIndex, chainData->entries, 0);
    chainData->outputHandle = result;
    chainData->outputHandle += 0x50; // +0x04 offset? Actually chainData[1] = result+0x50

    // Look up the "SendWetToMaster" submix and set its master send level
    void* sendSubmix = getSubmixByID(getSubmixID("SendWetToMaster"));
    if (sendSubmix != nullptr) {
        // Obtain the parameter (likely a float send level)
        getSubmixParameter(sendSubmix, *(uint32_t*)((uint32_t)sendSubmix + 0x10), 0, paramValue);
        // Set the value from the first DWORD at this+0x42c
        paramValue[0] = **(uint32_t**)((uint32_t)this + 0x42c);
        setSubmixParameterValue(0, paramValue);
        return true;
    }
    return false;
}