// FUNC_NAME: SoundManager::createSoundEffectInstance
void __fastcall SoundManager::createSoundEffectInstance(int thisPtr)
{
    // +0x19c: previous sound effect handle (to free if exists)
    if (*(int *)(thisPtr + 0x19c) != 0) {
        FUN_0094b0e0(*(int *)(thisPtr + 0x19c)); // release sound effect
        *(int *)(thisPtr + 0x19c) = 0;
    }

    // local_64 holds a default string name (from global DAT_0112a680)
    undefined1 local_64 = (undefined1)DAT_0112a680;
    undefined1 uStack_63 = (undefined1)((uint)DAT_0112a680 >> 8);
    undefined2 uStack_62 = (undefined2)((uint)DAT_0112a680 >> 16);
    undefined1 *local_68 = nullptr; // string override (used if non-null)

    // Determine sound effect type ID (uVar2) and optional string
    uint uVar2;
    if (*(int *)(thisPtr + 0xc0) == 0) { // +0xc0: flag indicating use named string?
        switch(*(int *)(thisPtr + 0xc4)) { // +0xc4: sound effect category
        case 0:
        case 2:
            goto default_case; // fall through to default
        default:
            goto skip; // no creation? actually skip to end
        case 3:
            uVar2 = 10; // priority/category ID? 
            break;
        case 4:
            uVar2 = 1;
            break;
        case 5:
            uVar2 = 0x2f;
            break;
        case 7:
            uVar2 = 0x2d;
            break;
        case 8:
            uVar2 = 0;
        }
    } else {
default_case:
        uVar2 = 0xb; // default category
        // +0x40: pointer to a string ID (maybe a hash or name)
        undefined4 *puVar1 = (undefined4 *)FUN_008c7550(*(int *)(thisPtr + 0x40));
        local_68 = (undefined1 *)*puVar1;
        if (local_68 == nullptr) {
            local_68 = &DAT_0120546e; // default string ("none"?)
        }
    }

    // local_5c array: probably a 4x4 matrix or 4-vector, initialized to identity/zero
    int local_5c[4];
    local_5c[0] = 0;
    local_5c[1] = 0;
    local_5c[2] = 0;
    // Call a helper to get some data from a pool (maybe transform data)
    undefined4 *puVar1 = (undefined4 *)FUN_006b4d50((undefined4 *)(thisPtr + 0x48)); // +0x48: some struct
    if (puVar1 != nullptr) {
        *puVar1 = *(int *)(thisPtr + 0x48); // copy data
    }
    local_5c[3] = _DAT_00d5780c; // global constant (maybe 0 or identity component)

    // Additional vector components (likely position + padding)
    // These are set from thisPtr offsets (+0x10, +0x14, +0x18) and global constants
    undefined4 uStack_4c = 0;
    undefined4 uStack_48 = 0;
    undefined4 uStack_44 = 0;
    undefined4 local_40 = 0;
    undefined4 uStack_3c = _DAT_00d5780c;
    undefined4 uStack_38 = 0;
    undefined4 uStack_34 = 0;
    undefined4 local_30 = 0;
    undefined4 uStack_2c = 0;
    undefined4 uStack_28 = _DAT_00d5780c;
    undefined4 uStack_24 = 0;
    undefined4 local_20 = *(int *)(thisPtr + 0x10);
    undefined4 uStack_1c = *(int *)(thisPtr + 0x14);
    undefined4 uStack_18 = *(int *)(thisPtr + 0x18);
    undefined4 uStack_14 = _DAT_00d5780c;

    // Create actual sound effect object (returns handle)
    int newHandle = FUN_0094ca20(uVar2, local_5c + 3, 0, 3, 0, 0, 1, local_5c, 0, 0, 0, local_68);
    *(int *)(thisPtr + 0x19c) = newHandle;

    if (local_5c[0] != 0) {
        FUN_009c8f10(local_5c[0]); // free temporary allocation if any
    }

skip:
    // If creation succeeded, set a name/identifier from the global and string at +0x40
    if (*(int *)(thisPtr + 0x19c) != 0) {
        FUN_008c76a0(&local_64, *(int *)(thisPtr + 0x40)); // concatenate string/format name
        FUN_0094ac00(*(int *)(thisPtr + 0x19c), // on the new sound effect
                     CONCAT22(uStack_62, CONCAT11(uStack_63, local_64)),
                     CONCAT13(uStack_60, CONCAT21(uStack_62, uStack_63)),
                     CONCAT13(uStack_5f, CONCAT12(uStack_60, uStack_62)));
    }
    return;
}