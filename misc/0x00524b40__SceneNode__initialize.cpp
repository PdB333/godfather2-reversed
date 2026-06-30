// FUNC_NAME: SceneNode::initialize
void __thiscall SceneNode::initialize(SceneNode* pParent, uint32_t param3, bool bActive) {
    // Offset +0x130: 16-bit flags (e.g., dirty or transform flags)
    *(uint16_t*)(this + 0x130) = 0;
    if (bActive) {
        *(uint16_t*)(this + 0x130) |= 1;
    }

    // Offset +0x12C: parent/owner pointer
    *(uint32_t*)(this + 0x12C) = (uint32_t)pParent;

    // Offset +0x120: some identifier/parameter
    *(uint32_t*)(this + 0x120) = param3;

    // Intrusive list management at offset +0x124 (pointer to next node)
    int** ppNext = (int**)(this + 0x124);
    int newNextAddr = (in_EAX == 0) ? 0 : (in_EAX + 4);  // in_EAX likely holds a new node address or null
    if (*ppNext != (int*)newNextAddr) {
        if (*ppNext != nullptr) {
            // Free the old next node (FUN_004daf90 likely a custom free)
            FUN_004daf90(*ppNext);
        }
        *ppNext = (int*)newNextAddr;
        if (newNextAddr != 0) {
            // Update back pointer of the new node (assumes +0x128 is back link)
            *(uint32_t*)(this + 0x128) = *(uint32_t*)(newNextAddr + 4);
            *(int**)(newNextAddr + 4) = ppNext;
        }
    }

    // Copy 4x4 transformation matrix from EDI pointer (16 floats)
    // Offsets +0xE0 through +0x11C hold the 16 floats (row-major)
    uint32_t* src = unaff_EDI;  // EDI register holds source matrix
    *(uint32_t*)(this + 0xE0) = src[0];
    *(uint32_t*)(this + 0xE4) = src[1];
    *(uint32_t*)(this + 0xE8) = src[2];
    *(uint32_t*)(this + 0xEC) = src[3];
    *(uint32_t*)(this + 0xF0) = src[4];
    *(uint32_t*)(this + 0xF4) = src[5];
    *(uint32_t*)(this + 0xF8) = src[6];
    *(uint32_t*)(this + 0xFC) = src[7];
    *(uint32_t*)(this + 0x100) = src[8];
    *(uint32_t*)(this + 0x104) = src[9];
    *(uint32_t*)(this + 0x108) = src[10];
    *(uint32_t*)(this + 0x10C) = src[11];
    *(uint32_t*)(this + 0x110) = src[12];
    *(uint32_t*)(this + 0x114) = src[13];
    *(uint32_t*)(this + 0x118) = src[14];
    *(uint32_t*)(this + 0x11C) = src[15];

    // Additional 16-bit flag at +0x132
    *(uint16_t*)(this + 0x132) = 0;

    // Initialize sub-object at offset +0x134 (internal component)
    FUN_005205b0(this + 0x134);

    // Global engine registration calls
    FUN_00424470();
    FUN_00417560();
}