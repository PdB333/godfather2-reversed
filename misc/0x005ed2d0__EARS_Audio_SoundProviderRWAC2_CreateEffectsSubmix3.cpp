// Xbox PDB: EARS::Audio::SoundProviderRWAC2::CreateEffectsSubmix3
// FUNC_NAME: AudioMixer::setupSubmixChain
// Function address: 0x005ed2d0
// Initializes audio submix graph with reverb, delay, bandpass, and wet-to-master send.

uint AudioMixer::setupSubmixChain() {
    int *submixArray;       // pointer to array of submix entries (12 bytes each), offset +0x14
    int submixCount;        // number of submix entries, stored at +0x18
    int submixIndex;        // index for current submix being added
    int submixHash;         // hash code for submix name
    char **submixNamePtr;   // pointer to store string pointer in entry
    undefined4 *floatParamPtr; // for setting float parameter
    int busHandle;          // result from FUN_004dafd0 (get bus by name)
    int result;             // return value
    char *localName[2];     // for local storage of name pointer
    float localFloat[2];    // for parameter value
    undefined4 localHash[2]; // for temporary hash

    // Get the current submix count (in_EAX[6])
    submixCount = this->submixCount; // offset +0x18
    submixArray = this->submixArray; // offset +0x14, pointer to array of submix entries

    // Initialize submix entry helpers? (FUN_005ef9a0, FUN_005ef890 are likely setting up state)
    FUN_005ef9a0(); // unknown initialization
    FUN_005ef890(); // unknown initialization

    // Retrieve main bus handle for "SUBMIX3" and store it
    busHandle = FUN_004dafd0("SUBMIX3"); // get bus by name
    this->mainBusHandle = busHandle;     // offset +0x2c

    // Begin building "Submix1" chain
    FUN_005e9ba0("Submix1"); // likely begins or selects submix named "Submix1"

    // --- Submix: GlobalReverb ---
    submixIndex = this->submixCount; // current count, will be incremented after adding?
    submixArray = this->submixArray; // refresh pointer? possibly modified by FUN_005e9ba0
    submixHash = FUN_00c9cd50(0x53756230); // hash "Sub0"
    *(int*)((char*)submixArray + submixIndex * 12 - 8) = submixHash; // entry[submixIndex].hash = submixHash (offset -8)
    submixHash = FUN_00c9cd50(0x53756230); // hash "Sub0" again
    submixNamePtr = localName;
    FUN_00c9cba0(this->audioBusPtr, submixHash, submixNamePtr); // offset +0x580, set name pointer
    localName[0] = "GlobalReverb";
    *(char***)((char*)submixArray + submixIndex * 12 - 12) = submixNamePtr; // entry.name = localName (offset -12)
    *(char*)((char*)submixArray + submixIndex * 12 - 4) = 1; // entry.flag = 1 (offset -4)
    FUN_005e9ba0("Delay");

    // --- Submix: Delay ---
    submixIndex = this->submixCount;
    submixArray = this->submixArray;
    submixHash = FUN_00c9cd50(0x44656c30); // hash "Del0"
    *(int*)((char*)submixArray + submixIndex * 12 - 8) = submixHash;
    submixHash = FUN_00c9cd50(0x44656c30);
    floatParamPtr = localFloat; // note: localFloat[] is reused for hash storage? probably used as a pointer to store parameter info
    FUN_00c9cba0(this->audioBusPtr, submixHash, floatParamPtr);
    localFloat[0] = DAT_00e2cd54; // some float constant
    *(undefined4**)((char*)submixArray + submixIndex * 12 - 12) = floatParamPtr;
    *(char*)((char*)submixArray + submixIndex * 12 - 4) = 1;
    FUN_005e9ba0("GeneralPurposeBandpass");

    // --- Submix: GeneralPurposeBandpass ---
    submixIndex = this->submixCount;
    submixArray = this->submixArray;
    submixHash = FUN_00c9cd50(0x42493230); // hash "BI20"
    *(int*)((char*)submixArray + submixIndex * 12 - 8) = submixHash;
    *(undefined4**)((char*)submixArray + submixIndex * 12 - 12) = 0; // no name pointer
    *(char*)((char*)submixArray + submixIndex * 12 - 4) = 1;
    FUN_005e9ba0("Model1Reverb");

    // --- Submix: Model1Reverb ---
    submixIndex = this->submixCount;
    submixArray = this->submixArray;
    submixHash = FUN_00c9cd50(0x524d3130); // hash "RM10"
    *(int*)((char*)submixArray + submixIndex * 12 - 8) = submixHash;
    *(undefined4**)((char*)submixArray + submixIndex * 12 - 12) = 0;
    *(char*)((char*)submixArray + submixIndex * 12 - 4) = 6; // flag = 6 (different value)
    FUN_005e9ba0("SendWetToMaster");

    // --- Submix: SendWetToMaster ---
    submixIndex = this->submixCount;
    submixArray = this->submixArray;
    submixHash = FUN_00c9cd50(0x53656e30); // hash "Sen0"
    *(int*)((char*)submixArray + submixIndex * 12 - 8) = submixHash;
    *(undefined4**)((char*)submixArray + submixIndex * 12 - 12) = 0;
    *(char*)((char*)submixArray + submixIndex * 12 - 4) = 6;
    // Finalize all submixes? last arguments: this->audioBusPtr, 0xfe, this->submixCount, this->submixArray, 0
    result = FUN_00ca55a0(this->audioBusPtr, 0xfe, this->submixCount, this->submixArray, 0);
    this->someResult = result;   // stored at +0x00
    this->someResult2 = result + 0x50; // +0x04

    // Find the "SendWetToMaster" submix by name and possibly set its target bus
    floatParamPtr = &someVar; // pointer to this? param_1 address used as placeholder
    busHandle = FUN_004dafd0("SendWetToMaster", &someVar);
    result = FUN_005e9d90(busHandle, &someVar); // get submix by name
    if (result != 0) {
        // Get parameter at offset 0x10 from the submix and set its value
        FUN_00c9cbe0(this->audioBusPtr, *(int*)(result + 0x10), 0, localHash);
        localHash[0] = *(float*)(this->wetGainPtr); // offset +0x42c, dereferenced as float
        FUN_00c9cd40(0, localHash); // set parameter value
        return 1;
    }
    return 0;
}