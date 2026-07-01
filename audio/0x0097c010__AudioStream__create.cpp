// FUNC_NAME: AudioStream::create
void AudioStream::create(uint32_t* outStream, const StreamSourceInfo* sourceInfo, uint32_t param3, int32_t param4)
{
    // outStream is expected to be an array of 3 pointers (to sub-objects)
    // sourceInfo contains source data: [0] = some handle, [2] = another handle (offset 8)
    if (sourceInfo == nullptr) {
        return;
    }

    uint32_t sourceHandle0 = sourceInfo->field0;   // +0x00
    uint32_t sourceHandle2 = sourceInfo->field8;   // +0x08

    // Get thread-local storage (likely allocator context)
    TlsGetValue(g_tlsIndex);  // DAT_01139810

    // Allocate first sub-object: size 0x20, tag 0x27
    int32_t* subObj1 = (int32_t*)allocateMemory(0x20, 0x27);  // FUN_00aa2680
    *(uint16_t*)(subObj1 + 4) = 0x20;  // store size at offset 4

    uint32_t engineHandle = getAudioEngine(g_globalAudioEngine);  // FUN_00a64b00, _DAT_00d8fd74
    *outStream = engineHandle;

    // Build a local structure (64 bytes) for stream initialization
    StreamInitInfo initInfo;
    initInfo.field0  = g_someConstant;  // _DAT_00d5780c
    initInfo.field4  = 0;
    initInfo.field8  = 0;
    initInfo.fieldC  = 0;
    initInfo.field10 = g_someConstant;
    initInfo.field14 = 0;
    initInfo.field18 = 0;
    initInfo.field1C = 0;
    initInfo.field20 = g_someConstant;
    initInfo.field24 = 0;
    initInfo.field28 = 0;
    initInfo.field2C = sourceHandle0;
    initInfo.field30 = 0;
    initInfo.field34 = sourceHandle2;
    initInfo.field38 = 0;

    // Allocate second sub-object: size 0x70, tag 0x27
    int32_t* subObj2 = (int32_t*)allocateMemory(0x70, 0x27);  // FUN_00aa2680
    *(uint16_t*)(subObj2 + 4) = 0x70;

    uint32_t bufferHandle = createAudioBuffer(*outStream, &initInfo);  // FUN_00a6be50
    outStream[1] = bufferHandle;

    // Register thread or perform some global init
    registerAudioThread();  // FUN_009f9620

    // Build another local structure (smaller) for decoder creation
    DecoderCreateInfo decoderInfo;
    decoderInfo.engineHandle = *outStream;
    decoderInfo.field4 = 0;
    decoderInfo.field8 = 0;
    decoderInfo.someFlag = 7;  // local_20 = 7
    decoderInfo.sourceHandle0 = sourceHandle0;
    decoderInfo.sourceHandle2 = sourceHandle2;

    // Allocate third sub-object: size 0x200, tag 0x2d
    int32_t* subObj3 = (int32_t*)allocateMemory(0x200, 0x2d);  // FUN_00aa2680
    *(uint16_t*)(subObj3 + 4) = 0x200;

    uint32_t decoderHandle = createStreamDecoder(&decoderInfo);  // FUN_009f4640
    outStream[2] = decoderHandle;

    // Set some resource handle at offset 0x2c of the decoder
    uint32_t resourceHandle = allocateResource(0x19, 0x1f, 0);  // FUN_00540c60
    *(uint32_t*)(decoderHandle + 0x2c) = resourceHandle;

    // Initialize the stream info struct (maybe finalize)
    initializeStreamInfo(&initInfo);  // FUN_009f4cd0

    // Schedule a timer or event with param4
    setTimer(0xa1e6d360, param4, param4 >> 0x1f);  // FUN_009f01f0

    // Start the stream (play)
    startStream(decoderHandle, 1);  // FUN_009e6ff0
}