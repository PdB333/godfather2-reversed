// FUNC_NAME: AudioDataManager::AudioDataManager (constructor)
undefined4* __fastcall AudioDataManager::AudioDataManager(AudioDataManager* this) {
    // Set up vtable pointers for this class (likely two levels of inheritance)
    this->vtable1 = &PTR_FUN_00d8bfd4;        // primary vtable
    this->vtable2 = &PTR_LAB_00d8bfcc;        // secondary vtable (overwritten below)

    // Store singleton reference
    gAudioDataManager = this;                 // DAT_011307c4

    this->vtable1 = &PTR_FUN_00d8bfd4;        // redundant but kept
    this->vtable2 = &PTR_LAB_00d8bfd0;        // corrected secondary vtable

    // Initialize fields
    this->field_8 = 0;                        // likely a pointer or uint
    this->field_C = 0;                        // another field

    // Allocate a buffer of 0xC bytes (e.g., audio device info)
    this->deviceInfo = (SomeStruct*)allocMem(0xC);  // FUN_009c8e80
    this->field_14 = 0;                       // unused or initialization

    // Set some constant (e.g., max buffers or stream count)
    this->numBuffers = 3;                     // +0x14? actually +0x18? depending on sizeof pointers

    // Get default audio device info
    uint32_t deviceHandle = getDefaultAudioDevice(); // FUN_0060d850
    AudioDeviceFormat* format = getAudioDeviceFormat(deviceHandle); // FUN_00606370
    // Assume format has width/height at offsets +2 and +4
    this->screenWidth = (float)*(uint16_t*)((uint8_t*)format + 2);
    this->screenHeight = (float)*(uint16_t*)((uint8_t*)format + 4);

    // Register a periodic callback (e.g., main update timer)
    registerUpdateCallback(0, &LAB_00953320, 0x80); // FUN_00607ca0
    // Register an event handler for a specific message hash
    registerMessageHandler(0x9CB5151C, &FUN_00953DE0); // FUN_00446b60

    return this;
}