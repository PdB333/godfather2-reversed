// FUNC_NAME: UIElement::createFromTemplate
class UIElement {
public:
    int field_0x00; // vtable pointer
    int field_0x04; // +0x04: some render resource
    int field_0x08; // +0x08
    int field_0x0c; // +0x0c: possibly flag (checked at offset 0xd)
    void* field_0x10; // +0x10: position/offset?
    void* field_0x14; // +0x14: size?
    void* field_0x18; // +0x18
    void* field_0x1c; // +0x1c
    // +0x20: next field likely at index 8
    int field_0x20; // +0x20
    int field_0x24; // +0x24: source object pointer
    int field_0x28; // +0x28: first field of source
    int field_0x2c; // +0x2c: flag/state
    int field_0x30; // +0x30
    int field_0x34; // +0x34
    int field_0x38; // +0x38
    int field_0x3c; // +0x3c
    int field_0x40; // +0x40
    int field_0x44; // +0x44
    int field_0x48; // +0x48: index or paint ID
    int field_0x4c; // +0x4c: animation state
    int field_0x50; // +0x50
    int field_0x54; // +0x54: paint ID for second set
    int field_0x58; // +0x58: animation state 2
    unsigned char field_0x5c; // +0x5c: byte flag, set to 1
    float field_0x60; // +0x60: render X
    float field_0x64; // +0x64: render Y
    float field_0x68; // +0x68: render Z

    UIElement* create(void* srcObj);
};

extern float DAT_00e445c8; // scale factor
extern float DAT_00e44594; // offset for Y and Z in non-billboard mode
extern int DAT_00e2b1a4;   // some default value
extern float DAT_00e2eff4; // threshold for animation state

UIElement* UIElement::create(void* srcObj) {
    // Guard: if already initialized (field at +0x0d != 0), return early.
    if (*(char*)(this + 0x0d) != '\0') {
        return this;
    }

    // Initialization sequence
    FUN_00533cc0(); // unknown init
    this->field_0x00 = &PTR_FUN_00e37310; // set vtable

    float scale = DAT_00e445c8;
    // Get some thread-local pointer (TIB)
    int* tibPtr = *(int**)(__readfsdword(0x2c)); // offset 0x2c in TIB
    this->field_0x24 = (int)srcObj; // store source object

    bool isBillboard = (*(unsigned short*)(srcObj + 0x2c) & 0x200) != 0;
    if (!isBillboard) {
        // Non-billboard: scale position/rotation from source
        float srcX = *(float*)(srcObj + 0x14);
        float srcY = *(float*)(srcObj + 0x18);
        float srcZ = *(float*)(srcObj + 0x1c);
        FUN_0056b8a0(srcX * scale, srcY * scale, srcZ * scale, (tibPtr[2] + 0x10) + this->field_0x10);
        // capture source's rotation vector
        this->field_0x60 = *(float*)(srcObj + 0x20);
        this->field_0x64 = *(float*)(srcObj + 0x24);
        this->field_0x68 = *(float*)(srcObj + 0x28);
    } else {
        // Billboard mode: apply offset
        float srcX = *(float*)(srcObj + 0x14);
        float srcY = *(float*)(srcObj + 0x18) + DAT_00e44594;
        float srcZ = *(float*)(srcObj + 0x1c) + DAT_00e44594;
        FUN_0056bda0(srcX * scale, srcY * scale, srcZ * scale);
        // capture source's rotation vector (swizzled)
        this->field_0x60 = *(float*)(srcObj + 0x28);
        this->field_0x64 = *(float*)(srcObj + 0x20);
        this->field_0x68 = *(float*)(srcObj + 0x24);
    }

    // Clear state fields
    this->field_0x30 = 0;
    this->field_0x34 = 0;
    this->field_0x44 = 0;
    this->field_0x50 = 0;
    this->field_0x2c = 0;

    // More initialization
    FUN_00533fb0(); // unknown
    int defaultVal = DAT_00e2b1a4;
    FUN_0048ee40(); // unknown
    // Call sub-initializer with render resource and positions
    FUN_004ed620(this, srcObj, *(void**)(this->field_0x04 + 0x10), this->field_0x10, this->field_0x14);

    // Determine animation state based on thresholds in source object
    this->field_0x4c = 0;
    float threshold = DAT_00e2eff4;
    void* src = (void*)this->field_0x24; // source object pointer
    float* srcData = (float*)src;

    if (threshold < srcData[0x19]) { // offset 0x64
        if (srcData[0x17] <= threshold) { // offset 0x5c
            if (srcData[0x18] <= threshold) { // offset 0x60
                this->field_0x4c = 3;
                this->field_0x48 = srcData[0xf]; // offset 0x3c
            } else {
                this->field_0x4c = 2;
                this->field_0x48 = srcData[0x1c]; // offset 0x70
            }
        } else {
            this->field_0x4c = 1;
            this->field_0x48 = srcData[0x1c];
        }
    }

    this->field_0x58 = 0;
    if (threshold < srcData[0x20]) { // offset 0x80
        if (srcData[0x1e] <= threshold) { // offset 0x78
            if (srcData[0x1f] <= threshold) { // offset 0x7c
                this->field_0x58 = 3;
                this->field_0x54 = srcData[0x12]; // offset 0x48
            } else {
                this->field_0x58 = 2;
                this->field_0x54 = srcData[0x23]; // offset 0x8c
            }
        } else {
            this->field_0x58 = 1;
            this->field_0x54 = srcData[0x23];
        }
    }

    // Final field assignments
    this->field_0x28 = *(int*)src; // first field of source
    this->field_0x38 = defaultVal;
    this->field_0x3c = defaultVal;
    this->field_0x40 = 0xffffffff;
    *(unsigned char*)(&this->field_0x5c) = 1; // set byte at offset 0x5c
    // Note: field_0x60/64/68 already set above

    return this;
}