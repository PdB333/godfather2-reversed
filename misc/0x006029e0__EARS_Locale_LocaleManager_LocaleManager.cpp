// Xbox PDB: EARS::Locale::LocaleManager::LocaleManager
// FUNC_NAME: LocalizationManager::constructor
void * __thiscall LocalizationManager::constructor(int *this, void *param_unk)
{
    // +0x04: unknown field, set to 0
    this[1] = 0;
    // +0x08: vtable-like pointer (initialized, then overwritten)
    this[2] = (int)&DAT_00e2f19c;
    // +0x0c: some flag, set to 1
    this[3] = 1;
    // +0x10: unknown field, set to 0
    this[4] = 0;
    // +0x14: vtable-like pointer (initialized, then overwritten)
    this[5] = (int)&DAT_00e40894;

    // Store this instance globally (likely singleton)
    _DAT_012234a4 = (int)this;

    // Set vtable at +0x00
    this[0] = (int)&DAT_00e40874;
    // +0x08 and +0x14 are reassigned
    this[2] = (int)&DAT_00e40880;
    this[5] = (int)&DAT_00e40890;
    // +0x18: store the parameter (likely a callback or interface)
    this[6] = (int)param_unk;
    // +0x1c: byte field set to 0 (initialize flag)
    *(char *)(this + 7) = 0;
    // +0x20: pointer to sub-manager, initially null
    this[8] = 0;

    // Allocate two 0x20-byte buffers
    void *buf1 = FUN_009c8e80(0x20);
    this[9] = (int)buf1;
    // +0x24: counter? set to 0
    this[10] = 0;
    // +0x28: size? set to 8
    this[11] = 8;

    void *buf2 = FUN_009c8e80(0x20);
    this[12] = (int)buf2;
    // +0x30: counter? set to 0
    this[13] = 0;
    // +0x34: size? set to 8
    this[14] = 8;

    // Zero out many fields (likely a large array of (dword, byte) pairs)
    // This is probably a fixed-size array of localization entries or similar
    for (int i = 0; i < 10; i++) {
        // Each iteration sets two words and a byte?
        // Actually the decompiled code sets each pair individually.
        // We'll mimic the pattern:
        // +0x38, +0x3c, +0x40,... offsets: 0x3C,0x40,0x44,... but with byte after each dword
        // The decompiled code shows 10 pairs of (dword, byte) starting at offset 0x38 (0x0f) and ending at 0x38+(9*8)=0x38+0x48 = 0x80? Actually it goes up to offset 0x39? Wait, let's list:
        // Offset: 0x0f (0x3C) = 0
        // 0x10 (0x40) = 0
        // 0x11 (0x44) = 0
        // 0x12 (0x48) = 0
        // 0x13 (0x4C) = 0
        // 0x14 (0x50) = 0
        // 0x15 (0x54) byte = 0
        // 0x18 (0x60) = 0
        // 0x19 (0x64) byte = 0
        // 0x1c (0x70) = 0
        // 0x1d (0x74) byte = 0
        // 0x20 (0x80) = 0
        // 0x21 (0x84) byte = 0
        // 0x24 (0x90) = 0
        // 0x25 (0x94) byte = 0
        // 0x28 (0xA0) = 0
        // 0x29 (0xA4) byte = 0
        // 0x2c (0xB0) = 0
        // 0x2d (0xB4) byte = 0
        // 0x30 (0xC0) = 0
        // 0x31 (0xC4) byte = 0
        // 0x34 (0xD0) = 0
        // 0x35 (0xD4) byte = 0
        // 0x38 (0xE0) = 0
        // 0x39 (0xE4) byte = 0
        // That's 11 pairs (dword starting at +0x38, then +0x3C, +0x40, +0x44, +0x48, +0x4C, +0x50, +0x54, +0x58? Actually we have indices 0x0f to 0x39 inclusive, but not sequential.
    }
    // It's messy; we can simplify as initializing a region to zero.
    // But for accuracy, we'll just write assignments as in decomp.
    this[15] = 0; // offset +0x3C
    this[16] = 0; // +0x40
    this[17] = 0; // +0x44
    this[18] = 0; // +0x48
    this[19] = 0; // +0x4C
    this[20] = 0; // +0x50
    *(char *)(this + 21) = 0; // +0x54
    this[24] = 0; // +0x60
    *(char *)(this + 25) = 0; // +0x64
    this[28] = 0; // +0x70
    *(char *)(this + 29) = 0; // +0x74
    this[32] = 0; // +0x80
    *(char *)(this + 33) = 0; // +0x84
    this[36] = 0; // +0x90
    *(char *)(this + 37) = 0; // +0x94
    this[40] = 0; // +0xA0
    *(char *)(this + 41) = 0; // +0xA4
    this[44] = 0; // +0xB0
    *(char *)(this + 45) = 0; // +0xB4
    this[48] = 0; // +0xC0
    *(char *)(this + 49) = 0; // +0xC4
    this[52] = 0; // +0xD0
    *(char *)(this + 53) = 0; // +0xD4
    this[56] = 0; // +0xE0
    *(char *)(this + 57) = 0; // +0xE4

    // Call virtual function on the passed object (at vtable+8)
    (**(code **)(**(int **)param_unk + 8))();

    // Subscribe to localization message IDs
    // FUN_00408260 likely registers a message handler
    int msgId1 = FUN_004dafd0("iMsgLocalizedTextLoadRequested");
    FUN_00408260(&DAT_01222258, msgId1);
    int msgId2 = FUN_004dafd0("iMsgLocalizedTextLoadCompleted");
    FUN_00408260(&DAT_01222238, msgId2);
    int msgId3 = FUN_004dafd0("iMsgLocalizedTextDataLoaded");
    FUN_00408260(&DAT_01222248, msgId3);
    int msgId4 = FUN_004dafd0("iMsgLocalizedTextDataUnloaded");
    FUN_00408260(&DAT_01222230, msgId4);
    int msgId5 = FUN_004dafd0("iMsgLanguageChanged");
    FUN_00408260(&DAT_01222240, msgId5);
    int msgId6 = FUN_004dafd0("iMsgAllLocalizedTextUnloaded");
    FUN_00408260(&DAT_01222250, msgId6);

    // Increment reference counts and enable? for each message ID
    if ((DAT_01222258 != 0) && (FUN_00402080(&DAT_01222258) == '\0')) {
        _DAT_0122225c = _DAT_0122225c + 1;
        FUN_004084d0(&DAT_01222258, 0x8000);
    }
    if ((DAT_01222238 != 0) && (FUN_00402080(&DAT_01222238) == '\0')) {
        _DAT_0122223c = _DAT_0122223c + 1;
        FUN_004084d0(&DAT_01222238, 0x8000);
    }
    if ((DAT_01222248 != 0) && (FUN_00402080(&DAT_01222248) == '\0')) {
        _DAT_0122224c = _DAT_0122224c + 1;
        FUN_004084d0(&DAT_01222248, 0x8000);
    }
    if ((DAT_01222230 != 0) && (FUN_00402080(&DAT_01222230) == '\0')) {
        _DAT_01222234 = _DAT_01222234 + 1;
        FUN_004084d0(&DAT_01222230, 0x8000);
    }

    // Register/unregister callbacks? (argument 1)
    FUN_0049c6e0(&DAT_00e40858, 1);
    FUN_0049c6e0(&DAT_00e40854, 1);

    // Create the sub-manager object (size 0xB4)
    int subObj = FUN_009c8e50(0xB4);
    if (subObj != 0) {
        subObj = FUN_00604ff0(subObj); // call sub-constructor
    }
    this[8] = subObj; // store at +0x20

    // Access a buffer from sub-object: if current index (this[16]) < subObj->someCount (+0xA8)
    // then get pointer to subObj->buffer ([subObj+0xB0] + index * 0x60)
    // otherwise use a default buffer (DAT_012222c8)
    int index = this[16]; // +0x40
    int subCount = *(int *)(subObj + 0xA8);
    unsigned char *targetBuf;
    if ((unsigned int)index < (unsigned int)subCount) {
        targetBuf = (unsigned char *)(*(int *)(subObj + 0xB0) + index * 0x60);
    } else {
        targetBuf = (unsigned char *)&DAT_012222c8;
    }
    // Initialize targetBuf + 0x40 (FUN_004d3d90 likely a string/resource init)
    FUN_004d3d90(targetBuf + 0x40);

    // Mark initialization flag at +0x1c as complete
    *(char *)(this + 7) = 1;

    return (void *)this;
}