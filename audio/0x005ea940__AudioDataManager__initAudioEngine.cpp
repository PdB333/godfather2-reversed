// FUNC_NAME: AudioDataManager::initAudioEngine
byte __thiscall AudioDataManager::initAudioEngine(AudioDataManager* thisAudioManager, AudioMasterMixer* pMasterMixer, AudioInitParams* pInitParams)
{
    char cVar1;
    byte bResult;
    int iVar;
    uint* puVar;
    AudioMixerNode* pMixerNode;
    char** ppcString;
    uint8_t auStack16[12];
    char* apcStrings[2];

    // Allocate memory for audio system (0x40 bytes) and something else (4 bytes)
    MemAlloc(0x40);
    MemAlloc(4);

    // Store master mixer pointer
    thisAudioManager->masterMixer = pMasterMixer; // +0x157
    if (pMasterMixer != nullptr) {
        pMasterMixer->addRef(); // +8 (vtable)
    }

    // Get optional secondary mixer from init params
    int* pSecondaryMixer = (int*)pInitParams->secondaryMixer; // +0x1c
    thisAudioManager->secondaryMixer = pSecondaryMixer; // +0x158
    if (pSecondaryMixer == 0) {
        thisAudioManager->secondaryMixer = thisAudioManager->masterMixer; // fallback
    }
    if (thisAudioManager->secondaryMixer != nullptr) {
        (*(code**)(*(int*)thisAudioManager->secondaryMixer + 8))(); // addRef
    }

    // Store another mixer from params
    int* pThirdMixer = (int*)pInitParams->thirdMixer; // +0x20
    thisAudioManager->thirdMixer = pThirdMixer; // +0x159
    if (pThirdMixer != nullptr) {
        (*(code**)(*pThirdMixer + 8))(); // addRef
    }

    // Early exit if no master mixer
    if (thisAudioManager->masterMixer == 0) {
        return 1; // true (success)
    }

    // Create mixer node object
    pMixerNode = (AudioMixerNode*)MemAlloc(8);
    if (pMixerNode != nullptr) {
        pMixerNode->vtable = &g_AudioMixerNodeVTable1; // PTR_FUN_00e36f1c
        pMixerNode->pMixer = thisAudioManager->secondaryMixer; // link to secondary mixer
        if (thisAudioManager->secondaryMixer != nullptr) {
            (**(code**)(*(int*)thisAudioManager->secondaryMixer + 8))(); // addRef
        }
        pMixerNode->vtable = &g_AudioMixerNodeVTable2; // PTR_FUN_00e3fb8c
    }
    thisAudioManager->mixerNode = pMixerNode; // +0x15a

    // Create audio engine block with 0x20000 bytes
    int largeBlock = createAudioEngineBlock(pMixerNode, 0x20000); // FUN_00ca6240
    thisAudioManager->audioEngineBlock = largeBlock; // +0x160
    *(uint32_t*)(largeBlock + 0xcc) = g_SomeGlobal; // DAT_00e44594

    initializeAudioChannel(); // FUN_00c9eac0

    // If engine block has no submix channel, create default
    if (*(int*)(thisAudioManager->audioEngineBlock + 0x28) == 0) {
        createSubmixChannel(); // FUN_00ca3ee0
    }

    // Get the submix channel from engine block
    int submixChannel = *(int*)(thisAudioManager->audioEngineBlock + 0x28); // +0x15b
    thisAudioManager->submixChannel = submixChannel;

    if (submixChannel != 0) {
        // Register various audio effect modules
        registerAudioEffect(createEffect1()); // FUN_00caeb90 -> FUN_00c9ceb0
        registerAudioEffect(createEffect2()); // ...
        registerAudioEffect(createEffect3());
        registerAudioEffect(createEffect4());
        registerAudioEffect(createEffect5());
        registerAudioEffect(createEffect6());
        registerAudioEffect(createEffect7());
        registerAudioEffect(createEffect8());
        registerAudioEffect(createEffect9());
        registerAudioEffect(createEffect10());
        registerAudioEffect(createEffect11());
        registerAudioEffect(createEffect12());
        registerAudioEffect(createEffect13());
        registerAudioEffect(createEffect14());
        registerAudioEffect(createEffect15());
        registerAudioEffect(createEffect16());
        registerAudioEffect(createEffect17());
    }

    // Initialize sub-master (like a submix bus)
    int subMaster = createSubMaster(); // FUN_00ca3e90
    if (subMaster != 0) {
        attachMixerNode(createMixerNode2()); // FUN_00cc7220 -> FUN_00c96910
        // (Note: actual order might differ)
    }

    // Look up a mastering string constant
    thisAudioManager->masteringStringId = findStringId("MASTERING"); // FUN_004dafd0 -> +0x115

    // Initialize submix structures
    initSubmixStructures(); // FUN_005ef9a0
    initAudioRouting(); // FUN_005ef890

    // Create submix "Submix1"
    uint32_t submixId = createSubmix("Submix1"); // FUN_005e9ba0
    int index = thisAudioManager->submixCount; // +0x110
    int basePtr = thisAudioManager->submixBase; // +0x10f
    uint32_t soundId1 = createSoundId(0x53756230); // "Sub0" -> FUN_00c9cd50
    *(uint32_t*)(basePtr + index * 0xc - 8) = soundId1; // store ID

    char** strPtr = apcStrings;
    uint32_t soundId2 = createSoundId(0x53756230); // another Sub0
    registerSubmix(thisAudioManager->audioEngineBlock, soundId2, &strPtr); // FUN_00c9cba0
    apcStrings[0] = "Master";
    *(char***)(thisAudioManager->submixBase - 0xc + thisAudioManager->submixCount * 0xc) = apcStrings;
    *(uint8_t*)(thisAudioManager->submixBase - 4 + thisAudioManager->submixCount * 0xc) = 6; // submix type

    // Create submix "Highpass"
    createSubmix("Highpass");
    index = thisAudioManager->submixCount;
    basePtr = thisAudioManager->submixBase;
    uint32_t soundId3 = createSoundId(0x48493230); // "HI20"
    *(uint32_t*)(basePtr + index * 0xc - 8) = soundId3;
    *(uint32_t*)(thisAudioManager->submixBase - 0xc + thisAudioManager->submixCount * 0xc) = 0;
    *(uint8_t*)(thisAudioManager->submixBase - 4 + thisAudioManager->submixCount * 0xc) = 6;

    // Create submix "MasterCompressor"
    createSubmix("MasterCompressor");
    index = thisAudioManager->submixCount;
    basePtr = thisAudioManager->submixBase;
    uint32_t soundId4 = createSoundId(0x436f3130); // "Co10"
    *(uint32_t*)(basePtr + index * 0xc - 8) = soundId4;
    *(uint32_t*)(thisAudioManager->submixBase - 0xc + thisAudioManager->submixCount * 0xc) = 0;
    *(uint8_t*)(thisAudioManager->submixBase - 4 + thisAudioManager->submixCount * 0xc) = 6;

    // Create submix "PostCompressionGain"
    createSubmix("PostCompressionGain");
    index = thisAudioManager->submixCount;
    basePtr = thisAudioManager->submixBase;
    uint32_t soundId5 = createSoundId(0x47616930); // "Gai0"
    *(uint32_t*)(basePtr + index * 0xc - 8) = soundId5;
    *(uint32_t*)(thisAudioManager->submixBase - 0xc + thisAudioManager->submixCount * 0xc) = 0;
    *(uint8_t*)(thisAudioManager->submixBase - 4 + thisAudioManager->submixCount * 0xc) = 6;

    // Create submix for dynamic range compressor (name at DAT_00e3f95c)
    createSubmix(&g_SubmixNameDac); // likely "Dac0" or something
    index = thisAudioManager->submixCount;
    basePtr = thisAudioManager->submixBase;
    uint32_t soundId6 = createSoundId(0x44616330); // "Dac0"
    *(uint32_t*)(basePtr + index * 0xc - 8) = soundId6;
    *(uint32_t*)(thisAudioManager->submixBase - 0xc + thisAudioManager->submixCount * 0xc) = 0;
    *(uint8_t*)(thisAudioManager->submixBase - 4 + thisAudioManager->submixCount * 0xc) = 0; // type 0

    // Create mixer bank with full range
    int mixerBank = createMixerBank(thisAudioManager->audioEngineBlock, 0xff, thisAudioManager->submixCount, thisAudioManager->submixBase, 0); // FUN_00ca55a0
    thisAudioManager->mixerBankStart = mixerBank; // +0x10a
    thisAudioManager->mixerBankEnd = mixerBank + 0x50; // +0x10b

    // If mastering enabled, apply initial compressor settings
    int masteringEnabled = isMasteringEnabled(); // FUN_005e9d10
    if (masteringEnabled != 0) {
        char result = (**(code**)(*(int*)thisAudioManager + 0xd4))(pInitParams->someParam); // +0x28
        if (result == '\0') {
            result = (**(code**)(*thisAudioManager + 0xd4))(0);
            if (result != '\0') goto LAB_005eae5e;
        }
        uint8_t* stackBuf = auStack16;
        uint32_t param = 4;
        uint32_t soundId = createSoundId(0x44616330); // "Dac0"
        setSubmixParam(thisAudioManager->audioEngineBlock, soundId, param, stackBuf); // FUN_00c9cbe0
        readSubmixParam(4, auStack16); // FUN_00c9cd40
    }

LAB_005eae5e:
    // Another mastering setup
    if (isMasteringEnabled() != 0) {
        setMasteringVolume(0, g_SomeGlobal2); // DAT_00e2afb8, FUN_00ca4e90
    }

    // Additional initialization if mastering
    int masteringHandle = isMasteringEnabled();
    if (masteringHandle != 0) {
        registerAudioNode(masteringHandle); // FUN_00c9ebc0
        attachNodeToStream(masteringHandle); // FUN_00cd77c0
    }

    // Call sub-initialization functions (likely virtual calls)
    bResult = initComponent1(thisAudioManager); // FUN_005ecf00
    bResult = initComponent2(thisAudioManager) & bResult; // FUN_005ed150
    bResult = initComponent3(thisAudioManager) & bResult; // FUN_005ed2d0

    // Register two global sound controllers
    int controller1 = createSoundController1(); // FUN_00cd2b70
    setSoundController(controller1); // FUN_00ca3e90
    attachSoundController(controller1); // FUN_00c96910

    int controller2 = createSoundController2(); // FUN_00cd2bb0
    setSoundController(controller2);
    attachSoundController(controller2);

    // Set audio engine parameters from init
    int sampleRate = pInitParams->sampleRate; // +0x10
    thisAudioManager->audioSampleRate = sampleRate; // +0x2421

    // Create a large resource buffer
    int resourceBuffer = createResourceBuffer(0x2ea8fb98, 5, sampleRate, 10, thisAudioManager->audioEngineBlock,
                                              thisAudioManager->mixerNode, 0x1000); // FUN_00ca51e0
    thisAudioManager->resourceBuffer = resourceBuffer; // +0x15c

    // Final initialization steps
    preloadAudioResources(*(uint32_t*)thisAudioManager->somePointer); // +0xff, FUN_00cd7750
    finalizeAudioSetup(); // FUN_00c9eae0
    finalizeComponentSetup(thisAudioManager); // FUN_005eef50

    // Set flag that audio is ready
    *(uint8_t*)(thisAudioManager + 0x162) = 1; // +0x162

    // Initialize arrays of audio states (5 entries)
    int* pArray = thisAudioManager + 0x2070; // +0x2070
    int count = 5;
    do {
        int temp = count;
        *(uint8_t*)(pArray + 2) = 0; // some flag
        LOCK();
        pArray[-1] = 0; // clear
        UNLOCK();
        pArray[0] = 0;
        pArray[1] = 0;
        pArray += 4;
        count = temp - 1;
    } while (count != 0);

    // Initialize more arrays (9 entries, each 0x5c bytes)
    uint* puArr = (uint*)(thisAudioManager + 0x20d0); // +0x20d0
    int remain = temp + 9; // temp is the last loop count (0) +9 = 9
    do {
        initAudioSlot(); // FUN_005ea0d0
        puArr[-5] = 0;
        puArr[-2] = 0;
        puArr[-1] = 0;
        *puArr = *puArr | 1; // set flag
        puArr += 0x5c; // size of each slot
        remain--;
    } while (remain != 0);

    // Call remaining initialization functions
    bResult = initComponent4(thisAudioManager) & bResult; // FUN_005ee6e0
    bResult = initComponent5(thisAudioManager) & bResult; // FUN_005ec930
    bResult = initComponent6(thisAudioManager) & bResult; // FUN_005ed560
    bResult = initComponent7(thisAudioManager) & bResult; // FUN_005eda70
    bResult = initComponent8(thisAudioManager) & bResult; // FUN_005ee090

    return bResult; // returns combined success bits
}