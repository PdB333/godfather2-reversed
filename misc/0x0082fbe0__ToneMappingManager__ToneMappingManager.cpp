// FUNC_NAME: ToneMappingManager::ToneMappingManager
// Address: 0x0082fbe0
// Constructor for ToneMappingManager (handles time-of-day tone mapping).

class ToneMappingManager {
public:
    // Vtable pointers
    void* vtable1;  // +0x00
    int field_0x04; // +0x04
    int field_0x08; // +0x08
    int field_0x0C; // +0x0C
    int field_0x10; // +0x10
    int field_0x14; // +0x14
    int field_0x18; // +0x18
    int field_0x1C; // +0x1C
    bool enabled;   // +0x20 (byte) - actually at byte offset 0x20 (param_1+8 as byte)
    int field_0x24; // +0x24
    void* vtable2;  // +0x30? Wait, param_1[0xc] is at offset 0x30, but let's recalc
    // Actually param_1[0xc] is at byte offset 0x30 (12*4)
    // We'll define fields sequentially:
    int field_0x28; // +0x28
    int field_0x2C; // +0x2C
    void* vtable2;  // +0x30 (param_1[0xc])
    int field_0x34; // +0x34
    int field_0x38; // +0x38
    int field_0x3C; // +0x3C
    int field_0x40; // +0x40
    int field_0x44; // +0x44
    int field_0x48; // +0x48
    int field_0x4C; // +0x4C
    int field_0x50; // +0x50
    int field_0x54; // +0x54
    int field_0x58; // +0x58
    int field_0x5C; // +0x5C
    int field_0x60; // +0x60
    int field_0x64; // +0x64
    int field_0x68; // +0x68
    int field_0x6C; // +0x6C
    // ... up to offset 0xA0 is accessed (param_1[0x28])
    // We'll skip many for brevity; only critical fields.
    void* vtable3;          // +0x90? param_1[0x24] is at 0x90
    int someFlag;           // +0x94
    void* allocatedBuffer;  // +0x98 (allocated with size 0x40)
    int field_0x9C;         // +0x9C
    int bufferSize;         // +0xA0 (initially 0x10)
    // ... rest
};

// Constructor implementation
ToneMappingManager* __fastcall ToneMappingManager::ToneMappingManager(ToneMappingManager* this) {
    // Initialize base class / fields
    this->field_0x04 = 0;
    this->field_0x08 = 0;
    this->field_0x0C = 0;
    this->field_0x10 = 0;
    this->field_0x14 = 0;
    this->field_0x18 = 0;
    this->field_0x1C = 0;
    this->enabled = true;  // +0x20 byte
    this->vtable1 = &PTR_FUN_00d73844; // First vtable
    this->field_0x24 = 1;  // Some flag

    // Call base class initialization (likely for message system)
    BaseClassInit(); // FUN_008334a0

    // Read global tone mapping constants
    uint32_t uVar1 = DAT_00e44630;
    uint32_t uVar2 = DAT_00d5ef88;

    this->vtable2 = &PTR_LAB_00d7377c; // Second vtable
    this->field_0x7C = uVar2;  // +0x7C (param_1[0x1f])
    this->field_0x80 = DAT_00d6471c; // +0x80
    this->field_0x84 = _DAT_00d5cf70; // +0x84
    this->field_0x88 = uVar1;  // +0x88
    this->field_0x8C = uVar2;  // +0x8C
    this->vtable3 = &PTR_FUN_00d73840; // Third vtable
    this->someFlag = 0;        // +0x94

    // Allocate internal buffer (0x40 bytes)
    this->allocatedBuffer = allocateBuffer(0x40); // FUN_009c8e80
    this->field_0x9C = 0;
    this->bufferSize = 0x10; // Initial size

    // Register message listener for tone mapping TOD
    MessageListener listener; // local_10 (3 ints + function pointer)
    listener.data[0] = 0;
    listener.data[1] = 0;
    listener.data[2] = 0;
    listener.callback = nullptr;

    registerTODMessage(&listener, &DAT_00e2f0b0, "ToneMappingTODMessage", "Sequence"); // FUN_004d4ad0
    releaseMessageListener(&listener); // FUN_004d3e20

    // Load shader/texture for tone mapping
    uint8_t* shaderData = (uint8_t*)this->field_0x10; // param_1[4]
    if (shaderData == nullptr) {
        shaderData = &DAT_0120546e; // Default shader data
    }
    this->field_0x0C = loadShader(shaderData); // FUN_004dafd0

    // Cleanup listener if needed
    if (listener.data[0] != 0) {
        listener.callback(listener.data[0]);
    }

    return this;
}