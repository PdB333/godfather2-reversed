// FUNC_NAME: Player::Init
// Address: 0x00809330
// Role: Initializes player state, sound randomization, control mapping, and placement
void __fastcall Player::Init(int* thisPlayer)
{
    char cVar1;
    int iVar2;
    int iVar4;
    undefined4* puVar5;
    undefined4* puVar6;
    float fVar7;
    undefined4 uVar8;
    undefined* puVar9;
    int iStack_b0;
    undefined4 uStack_a0;
    undefined4 local_9c;
    undefined1* puStack_98;
    int iStack_94;
    undefined4 uStack_84;
    undefined4 uStack_74;
    undefined4 uStack_64;
    undefined4 auStack_60[23];

    // Call base class init or subsystem init with type 3
    FUN_0043c490(thisPlayer, 3);

    // Get a component or manager pointer from global
    if (thisPlayer == nullptr) {
        iVar2 = 0;
    } else {
        iVar2 = FUN_0043b870(DAT_01131018); // likely SoundManager or similar
    }
    thisPlayer[0x17d] = iVar2; // +0x5f4 = component pointer

    // Initialize some buffers at offsets 0xe5 and 0xe8 (maybe float arrays?)
    FUN_009aefd0(thisPlayer + 0xe5, 0x8000);
    FUN_009af050(thisPlayer + 0xe8);

    // Set flag on component at +0x18
    *(uint*)(thisPlayer[0x17d] + 0x18) |= 0x20000;

    // Store a function pointer (maybe callback) at component +0x34
    iVar2 = thisPlayer[0x17d];
    *(ulonglong*)(iVar2 + 0x34) = CONCAT44(FUN_008001e0, thisPlayer);

    // Zero out some fields on component
    uStack_a0 = 0;
    *(undefined8*)(iVar2 + 0x3c) = 0;
    puStack_98 = &LAB_007fa6a0; // address of some label
    local_9c = 0;
    *(undefined4*)(iVar2 + 0x44) = 0;
    *(undefined1**)(iVar2 + 0x48) = &LAB_007fa6a0;

    // If there's a child object at +0x4c, call its virtual method at 0x2c (maybe release)
    if (*(int**)(thisPlayer[0x4c]) != nullptr) {
        (**(code**)(*(int*)thisPlayer[0x4c] + 0x2c))();
    }

    // Call event manager function with event ID 0x16 (22)
    FUN_008f6f50(0x16, thisPlayer);

    // Get another global for input or something and store at +0x210
    iVar2 = FUN_0043b870(DAT_0112a9fc);
    thisPlayer[0x210] = iVar2; // +0x840 = input manager?

    // Check if any of four flags at +0x6f4..0x6f7 are non-zero (sound random)
    if (thisPlayer[0x6f4] != 0 || thisPlayer[0x6f5] != 0 || thisPlayer[0x6f6] != 0 || thisPlayer[0x6f7] != 0) {
        iVar2 = FUN_007f2f10(thisPlayer + 0x6f4); // init sound randomization
        thisPlayer[0x6f1] = iVar2; // +0x1bc4
        FUN_007f0740(iVar2, *(undefined4*)thisPlayer[0x6f2], 0, 0);
        fVar7 = (float)FUN_007ef4a0(); // random float
        thisPlayer[0x1c9] = (int)fVar7; // +0x724 = some timing
        fVar7 = (float)FUN_007ef4b0(); // another random float
        thisPlayer[0x1cc] = (int)fVar7; // +0x730
    }

    // Call virtual method at offset 0x44 (possibly can do something)
    cVar1 = (**(code**)(*thisPlayer + 0x44))();
    if (cVar1 == '\0' &&
        ((thisPlayer[0x6f8] != 0 || thisPlayer[0x6f9] != 0 ||
          (thisPlayer[0x6fa] != 0 || thisPlayer[0x6fb] != 0)) &&
         (iVar2 = FUN_00421170(thisPlayer + 0x6f8), iVar2 != 0))) {
        uVar8 = 1;
        uVar3 = FUN_00558260(thisPlayer, *(undefined4*)(iVar2 + 0x14), 0, 1);
        FUN_00460720(uVar3, uVar8);
    }

    // Check if we have input profiles or control mappings
    iVar2 = FUN_004603f0();
    if (iVar2 != 0) {
        iStack_94 = FUN_005589e0(); // get number of player controllers?
        iStack_b0 = 0;
        if (0 < iStack_94) {
            do {
                iVar2 = FUN_00558a10(iStack_b0);
                if (iVar2 != 0) {
                    iVar4 = FUN_00558a70(iStack_b0);
                    // Write index to a byte array at offset 0x6bc from iVar4 (maybe player slot mapping)
                    *(undefined1*)(iVar4 + 0x6bc + (int)thisPlayer) = (undefined1)iStack_b0;
                    switch (iVar4) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 0xc:
                    case 0xd:
                    case 0xe:
                    case 0xf:
                    case 0x10:
                    case 0x11:
                    case 0x12:
                    case 0x13:
                    case 0x14:
                    case 0x16:
                        puVar9 = &DAT_00e53b3c; // some data pointer
                        break;
                    case 0xb:
                    case 0x15:
                        puVar9 = &DAT_00e53b28;
                        break;
                    default:
                        goto switchD_00809525_default;
                    }
                    FUN_005589d0(iVar2, puVar9); // set something for this controller
                }
switchD_00809525_default:
                iStack_b0 = iStack_b0 + 1;
            } while (iStack_b0 < iStack_94);
        }
    }

    // Call virtual method at 0x14c (maybe can set something) on object at +0x7c4
    cVar1 = (**(code**)(*thisPlayer + 0x14c))(thisPlayer[0x7c4], 0, 0);
    if (cVar1 != '\0') {
        // Call virtual at 0x178 on global DAT_012067e8
        (**(code**)(*thisPlayer + 0x178))(DAT_012067e8, 0);
    }

    thunk_FUN_007ef4d0(); // maybe finalize randomization
    FUN_008032d0(); // another init

    // Call virtual at 0x1c4 on object at +0x180
    (**(code**)(*thisPlayer + 0x1c4))(thisPlayer[0x180]);

    // If flag at +0xea is set, handle placement/camera
    if ((char)thisPlayer[0xea] != '\0') {
        puVar5 = (undefined4*)FUN_00471610(); // get transform matrix?
        iVar2 = thisPlayer[0xf5];
        puVar6 = auStack_60;
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar6 = *puVar5;
            puVar5 = puVar5 + 1;
            puVar6 = puVar6 + 1;
        }
        if (iVar2 == 0) {
            // No existing placement object: create new one
            iStack_94 = 0;
            uStack_84 = 0;
            uStack_74 = 0;
            uStack_64 = _DAT_00d5780c; // some constant
            FUN_0043a2a0(&uStack_a0, auStack_60);
            uVar8 = 0;
            uVar3 = FUN_00540cc0(thisPlayer + 0x20a, 0);
            FUN_0054e530(thisPlayer, thisPlayer[0x723], thisPlayer[0x729], thisPlayer[0x724], thisPlayer[0x72a], &uStack_a0, uVar3, uVar8);
            thisPlayer[0x129] = thisPlayer[0x129] | 0x600; // set flags
            if (thisPlayer[0xed] == 0) {
                puVar5 = (undefined4*)FUN_009c8e50(8);
                if (puVar5 == nullptr) {
                    puVar5 = nullptr;
                } else {
                    *puVar5 = &PTR_FUN_00d71bfc; // vtable for some object
                }
                thisPlayer[0xed] = (int)puVar5;
                FUN_0054e310(puVar5);
                *(int**)(thisPlayer[0xed] + 4) = thisPlayer + 0xf0;
            }
        } else {
            // Existing placement: call release or something
            FUN_00551260(&stack0xffffff44);
        }
        FUN_00805ed0(DAT_00d5efb8, 0);
    }

    // Check if debug mode and set flag
    cVar1 = FUN_00481640();
    if (cVar1 != '\0') {
        thisPlayer[0x129] = thisPlayer[0x129] | 1;
    }

    FUN_007fee80(); // finalize
    return;
}