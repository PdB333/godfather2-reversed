// FUNC_NAME: AudioDataManager::loadBank
// Address: 0x0061ee20
// Role: Loads an audio bank (BNK/stream) into the AudioDataManager. If the bank name matches the existing one and it's already loaded, skips. Otherwise, copies the name, initializes or updates the audio stream resources.
// Field offsets: +0x0c = bankName[128], +0x90 = streamHandle (int/void*), +0x94 = loadedFlag (byte), +0x98 = streamObject (void*), +0x9c = soundEngineObject (void*), +0xac = engineConfig (void* or struct)

int __thiscall AudioDataManager::loadBank(int this, const char* bankName, int streamId, int bitrate)
{
    byte bVar1;
    bool bVar8;
    int cmpResult;
    char* pbVar3;
    char* pbVar7;
    int iVar4;
    void* pvVar5;
    void** ppvVar6;
    undefined4 local_c;
    undefined4 local_8;
    undefined4 local_4;

    // Call base cleanup/reset
    FUN_0061e9d0(); // likely AudioDataManager::reset or similar

    if (bankName != (char*)0x0) {
        if (*(int*)(this + 0x90) == 0) {
            // First load: compare bank name with existing (at this+0xC)
            pbVar3 = (char*)bankName;
            pbVar7 = (char*)(this + 0xC);
            do {
                bVar1 = *pbVar3;
                bVar8 = bVar1 < *pbVar7;
                if (bVar1 != *pbVar7) {
                    cmpResult = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
                    goto LAB_0061ee76;
                }
                if (bVar1 == 0) break;
                bVar1 = pbVar3[1];
                bVar8 = bVar1 < pbVar7[1];
                if (bVar1 != pbVar7[1]) {
                    cmpResult = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
                    goto LAB_0061ee76;
                }
                pbVar3 = pbVar3 + 2;
                pbVar7 = pbVar7 + 2;
            } while (bVar1 != 0);
            cmpResult = 0;
LAB_0061ee76:
            if (cmpResult != 0) {
                // Names differ, copy new name
                _strncpy((char*)(this + 0xC), bankName, 0x80);
                if (FUN_0061e810(this) == 0) { // validate bank name? returns char
                    return 0;
                }
            }
            // Set up stream ID and configuration
            FUN_0061e960(streamId); // EARS stream setup? (param_3)
            *(byte*)(this + 0x94) = 0; // mark as not loaded
            local_c = 0x10004; // some config struct
            local_8 = 1;
            local_4 = 0;
            iVar4 = FUN_009c8e50(0x48); // alloc size 0x48
            if (iVar4 == 0) {
                *(int*)(this + 0x90) = 0; // streamHandle null
            } else {
                pvVar5 = FUN_004b4d10(&local_c); // initialize handle from config
                *(int*)(this + 0x90) = (int)pvVar5;
            }
        } else {
            // Already have a handle: just copy name and mark as loaded
            _strncpy((char*)(this + 0xC), bankName, 0x80);
            *(byte*)(this + 0x94) = 1; // loaded flag
            // streamHandle already set (param_1+0x90), no change
        }
    }

    if (*(int*)(this + 0x90) != 0) {
        // Allocate and initialize EARS stream objects
        iVar4 = FUN_009c8e50(0x280); // alloc size 0x280
        if (iVar4 == 0) {
            pvVar5 = 0;
        } else {
            if (*(int*)(this + 0x90) == 0) {
                iVar4 = 0;
            } else {
                iVar4 = *(int*)(this + 0x90) + 4; // offset into handle
            }
            pvVar5 = FUN_00d087f0(iVar4, DAT_01143360, 0, 0); // EARS stream creation
        }
        *(int*)(this + 0x98) = (int)pvVar5; // stream object

        ppvVar6 = (void**)FUN_009c8f80(); // get EARS engine singleton?
        local_c = 2;
        local_8 = 0x10;
        local_4 = 0;
        iVar4 = (*(code**)*ppvVar6)(0xe0, &local_c); // create sound engine object
        if (iVar4 == 0) {
            pvVar5 = 0;
        } else {
            pvVar5 = FUN_0061f3e0(); // initialize sound engine callbacks?
        }
        *(int*)(this + 0x9C) = (int)pvVar5; // sound engine object

        ppvVar6 = (void**)FUN_009c8e50(8); // alloc vtable/struct
        if (ppvVar6 == (void**)0x0) {
            ppvVar6 = (void**)0x0;
        } else {
            *ppvVar6 = &PTR_LAB_00e413c4; // set vtable pointer
        }
        *(void***)(this + 0xAC) = ppvVar6; // engine config pointer

        if (((*(int*)(this + 0x98) != 0) && (*(int*)(this + 0x9C) != 0)) &&
            (ppvVar6 != (void**)0x0)) {
            // Configure EARS audio system
            FUN_00d01230(2); // set playback mode?
            FUN_00d01760(bitrate, (uint)(bitrate * 2) / 3, 0, 0, 0); // set stream parameters (bitrate, etc.)
            FUN_00d01250(3); // set sample rate?
            FUN_00d01300(0); // set channels?
            pvVar5 = FUN_00d17c60(); // get buffer size
            FUN_00d015e0(pvVar5); // set buffer size
            FUN_00d09a80(*(undefined4*)(this + 0x9C)); // configure sound engine
            FUN_00d01210(*(undefined4*)(this + 0xAC)); // set engine config
            pvVar5 = FUN_00d15e20(); // get audio format
            FUN_00d01660(pvVar5); // set format
            FUN_00d016e0(&PTR_LAB_00f0ce30); // set callback
            FUN_00d0a640(this + 0xC); // open stream with bank name
            return 1;
        }
        // Cleanup on failure
        FUN_0061e9d0();
    }
    return 0;
}