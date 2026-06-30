// FUNC_NAME: LocalizedTextManager::LocalizedTextManager(void*)
undefined4* __thiscall LocalizedTextManager::LocalizedTextManager(undefined4* this, undefined4 param_2)
{
    char cVar1;
    undefined4 uVar2;
    int iVar3;
    undefined* puVar4;

    // Initialize fields (offsets relative to this)
    this[1] = 0;                                    // +4: some integer
    this[2] = &PTR_FUN_00e2f19c;                    // +8: vtable pointer (probably for base class)
    this[3] = 1;                                    // +12: reference count?
    this[4] = 0;                                    // +16: something
    this[5] = &PTR_LAB_00e40894;                    // +20: another vtable or pointer
    DAT_012234a4 = this;                            // store global instance pointer
    *this = &PTR_FUN_00e40874;                      // +0: vtable for this class
    this[2] = &PTR_LAB_00e40880;                    // +8: update vtable pointer
    this[5] = &PTR_LAB_00e40890;                    // +20: update pointer
    this[6] = param_2;                              // +24: store parameter (e.g., parent object)
    *(undefined1*)(this + 7) = 0;                   // +28: bool flag (set to false)
    this[8] = 0;                                    // +32: pointer (sub-object)
    
    // Allocate buffer for some data (size 0x20 = 32 bytes)
    uVar2 = FUN_009c8e80(0x20);                     // likely operator new
    this[9] = uVar2;                                // +36: buffer pointer
    this[10] = 0;                                   // +40: count?
    this[0xb] = 8;                                  // +44: capacity?

    // Allocate another buffer
    uVar2 = FUN_009c8e80(0x20);
    this[0xc] = uVar2;                              // +48: second buffer pointer
    this[0xd] = 0;                                  // +52: count?
    this[0xe] = 8;                                  // +56: capacity?

    // Zero out many fields (likely arrays of bools or small structs)
    this[0xf] = 0;                                  // +60
    this[0x10] = 0;                                 // +64
    this[0x11] = 0;                                 // +68
    this[0x12] = 0;                                 // +72
    this[0x13] = 0;                                 // +76
    this[0x14] = 0;                                 // +80
    *(undefined1*)(this + 0x15) = 0;                // +84: bool
    this[0x18] = 0;                                 // +96: (note offset 0x18*4 = 96)
    *(undefined1*)(this + 0x19) = 0;                // +100: bool
    this[0x1c] = 0;                                 // +112
    *(undefined1*)(this + 0x1d) = 0;                // +116: bool
    this[0x20] = 0;                                 // +128
    *(undefined1*)(this + 0x21) = 0;                // +132: bool
    this[0x24] = 0;                                 // +144
    *(undefined1*)(this + 0x25) = 0;                // +148: bool
    this[0x28] = 0;                                 // +160
    *(undefined1*)(this + 0x29) = 0;                // +164: bool
    this[0x2c] = 0;                                 // +176
    *(undefined1*)(this + 0x2d) = 0;                // +180: bool
    this[0x30] = 0;                                 // +192
    *(undefined1*)(this + 0x31) = 0;                // +196: bool
    this[0x34] = 0;                                 // +208
    *(undefined1*)(this + 0x35) = 0;                // +212: bool
    this[0x38] = 0;                                 // +224
    *(undefined1*)(this + 0x39) = 0;                // +228: bool

    // Call a function through the vtable of the parameter (param_2)
    (**(code**)(*(int*)this[6] + 8))();

    // Register message handlers for localized text loading
    uVar2 = FUN_004dafd0("iMsgLocalizedTextLoadRequested");
    FUN_00408260(&DAT_01222258, uVar2);
    uVar2 = FUN_004dafd0("iMsgLocalizedTextLoadCompleted");
    FUN_00408260(&DAT_01222238, uVar2);
    uVar2 = FUN_004dafd0("iMsgLocalizedTextDataLoaded");
    FUN_00408260(&DAT_01222248, uVar2);
    uVar2 = FUN_004dafd0("iMsgLocalizedTextDataUnloaded");
    FUN_00408260(&DAT_01222230, uVar2);
    uVar2 = FUN_004dafd0("iMsgLanguageChanged");
    FUN_00408260(&DAT_01222240, uVar2);
    uVar2 = FUN_004dafd0("iMsgAllLocalizedTextUnloaded");
    FUN_00408260(&DAT_01222250, uVar2);

    // Increment count for each message type if it's active
    if ((DAT_01222258 != 0) && (cVar1 = FUN_00402080(&DAT_01222258), cVar1 == '\0')) {
        _DAT_0122225c = _DAT_0122225c + 1;
        FUN_004084d0(&DAT_01222258, 0x8000);
    }
    if ((DAT_01222238 != 0) && (cVar1 = FUN_00402080(&DAT_01222238), cVar1 == '\0')) {
        _DAT_0122223c = _DAT_0122223c + 1;
        FUN_004084d0(&DAT_01222238, 0x8000);
    }
    if ((DAT_01222248 != 0) && (cVar1 = FUN_00402080(&DAT_01222248), cVar1 == '\0')) {
        _DAT_0122224c = _DAT_0122224c + 1;
        FUN_004084d0(&DAT_01222248, 0x8000);
    }
    if ((DAT_01222230 != 0) && (cVar1 = FUN_00402080(&DAT_01222230), cVar1 == '\0')) {
        _DAT_01222234 = _DAT_01222234 + 1;
        FUN_004084d0(&DAT_01222230, 0x8000);
    }

    // Increment reference counts for string table data
    FUN_0049c6e0(&DAT_00e40858, 1);
    FUN_0049c6e0(&DAT_00e40854, 1);

    // Allocate a sub-object of size 0xb4 (180 bytes) and construct it
    iVar3 = FUN_009c8e50(0xb4);
    if (iVar3 == 0) {
        iVar3 = 0;
    } else {
        iVar3 = FUN_00604ff0(iVar3);               // constructor for sub-object
    }
    this[8] = iVar3;                                // store sub-object pointer

    // Access a data array from the sub-object (offset +0xa8 is count, +0xb0 is data pointer)
    if ((uint)this[0x10] < *(uint*)(iVar3 + 0xa8)) {
        puVar4 = (undefined*)(this[0x10] * 0x60 + *(int*)(iVar3 + 0xb0));
    } else {
        puVar4 = &DAT_012222c8;                     // fallback pointer
    }
    FUN_004d3d90(puVar4 + 0x40);                    // initialize at offset 0x40

    // Set initialization flag
    *(undefined1*)(this + 7) = 1;                   // bool = true

    return this;
}