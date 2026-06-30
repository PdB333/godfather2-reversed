// FUNC_NAME: BNKStreamManager::createStream
// Address: 0x0054e040
// Description: Factory method to create a new audio stream object with a vtable and attached pointers.
// Called with __thiscall? param_1 is BNKStreamManager* this, param_2 is a float (duration?), param_3 is some data, EDI register holds additional pointer (owner or callback)

class AudioStream; // forward declaration (0x170 byte object with vtable at 0x00e39ec0)

AudioStream* BNKStreamManager::createStream(float audioParam, int streamData, int ownerPtr /* EDI */)
{
    float field0x84;
    int heapContext;
    void* tempAlloc1;   // 0x20 bytes
    void* tempAlloc2;   // 0x70 bytes
    AudioStream* newStream; // 0x170 bytes
    float multipliedParam;
    struct AutoStreamSettings {
        uint32_t field0;   // offset 0x00
        uint32_t field1;   // offset 0x04
        uint32_t field2;   // offset 0x08
        uint32_t field3;   // offset 0x0C
        uint32_t field4;   // offset 0x10
        uint32_t field5;   // offset 0x14
        uint32_t field6;   // offset 0x18
        uint32_t field7;   // offset 0x1C
        float    durationDivider; // offset 0x20
        uint32_t field9;   // offset 0x24
        uint32_t field10;  // offset 0x28
    } settings; // 44 bytes
    int soundValue; // result of FUN_00a64b00

    // Obtain thread-local heap context
    heapContext = TlsGetValue(DAT_01139810);

    // Allocate a temporary 0x20-byte block (tag 0x27)
    tempAlloc1 = alloc(0x20, 0x27); // FUN_00aa2680
    *(uint16_t*)((uint8_t*)tempAlloc1 + 4) = 0x20;

    // Convert the float parameter (e.g., audio time)
    soundValue = convertFloatToAudioValue(audioParam); // FUN_00a64b00

    // Read field at offset 0x84 from the current manager object (param_1 = this)
    field0x84 = *(float*)((uint8_t*)this + 0x84);

    // Unknown debug/log call?
    logFunction(); // FUN_0045cbe0

    // Initialize auto stream settings with a global constant (likely 0 or an ID)
    settings.field0 = DAT_00e2b1a4;
    settings.field1 = DAT_00e2b1a4;
    settings.field2 = DAT_00e2b1a4;
    settings.field3 = 0;
    settings.field4 = 0;
    settings.field5 = 0;
    settings.field6 = 0;    // Not explicitly set? The code sets field6, field7 but not indexed properly.
    settings.field7 = 0;    // Actually local_20 = 0, local_18 =0, local_14 =0 => these correspond to some subset.
    // Correction: local_20 is offset 0x1C? local_18 offset 0x24, local_14 offset 0x28.
    // The code sets: local_50[0] = DAT (offset0), local_3c = DAT (offset0x14?), local_28 = DAT (offset0x18?), local_20=0 (offset0x1C), local_18=0 (offset0x24), local_14=0 (offset0x28)
    // So we set only those:
    settings.durationDivider = field0x84 * audioParam;
    // Actually the float is at offset 0x20 (local_1c), so that is settings.durationDivider.

    // Allocate a temporary 0x70-byte block (tag 0x27)
    heapContext = TlsGetValue(DAT_01139810);
    tempAlloc2 = alloc(0x70, 0x27);
    *(uint16_t*)((uint8_t*)tempAlloc2 + 4) = 0x70;

    // Initialize something using soundValue and the settings struct
    initializeStreamConfig(soundValue, &settings); // FUN_00a6be50

    // Allocate the final audio stream object (0x170 bytes, tag 0x31)
    heapContext = TlsGetValue(DAT_01139810);
    newStream = (AudioStream*)alloc(0x170, 0x31);
    *(uint16_t*)((uint8_t*)newStream + 4) = 0x170;

    // Set up internal references: soundValue, a global static, and the streamData parameter
    setupInternalRef(soundValue, &DAT_011397d0, streamData); // FUN_009f0c70

    // Set vtable pointer at beginning of newStream
    newStream->vtable = &PTR_FUN_00e39ec0;

    // Store ownerPtr (from EDI) at offset 0x160 *4? Actually puVar4[0x58] -> offset 0x160
    newStream->owner = ownerPtr; // offset 0x160
    // Store this manager pointer at offset 0x164
    newStream->manager = this;   // offset 0x164

    // Unknown post-init call?
    postInitFunction(); // FUN_0043b490

    // Send a message (0x2001) with ownerPtr and 0
    sendMessage(0x2001, ownerPtr, 0); // FUN_009f01f0

    return newStream;
}