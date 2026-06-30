// FUNC_NAME: InteractiveObject::handleActionEvent
// Function at 0x00747e90: Handle interaction events for an interactive object.
// Switch on actionId (param_5): 10=use, 11=inspect, 12=stop use, 13=something.
// Uses sound system, camera shake, and object spawning.

int __thiscall InteractiveObject::handleActionEvent(int *thisPtr, uint param_2, uint param_3, uint param_4, int actionId, uint param_6)
{
    int iVar1;
    int iVar2;
    uint uVar3;
    uint uVar4;
    undefined local_40;
    undefined ***local_3c;
    byte local_38; // flag
    undefined **local_24; // pointer to function table
    uint local_20; // sound ID? or flag
    uint local_1c;
    uint local_18;
    ulonglong local_14; // double? Actually 8 bytes
    uint local_c; // float? Actually int
    byte local_8; // bool
    uint local_4; // global data

    switch (actionId) {
        case 10: // Use
            // Call virtual function at vtable offset 0x2c (index 11) with sound hash? 0xbd9433df
            (**(code **)(*thisPtr + 0x2c))(0xbd9433df, 1, 0, 0, 0x3f800000, 0x3f800000);
            *(byte *)(thisPtr + 0x18) = 1; // +0x18: some flag
            if ((thisPtr[0x15] != 0) && (thisPtr[0x15] != 0x48)) { // +0x15: entity index or ID
                FUN_007f63e0(0x15); // SoundManager::playSound(0x15)
                if (thisPtr[0x15] == 0) {
                    iVar1 = 0;
                } else {
                    iVar1 = thisPtr[0x15] - 0x48; // offset by 0x48
                }
                iVar1 = FUN_006bc8d0(iVar1, 0x369ac561); // Resource lookup? Get object by hash
                if (iVar1 != 0) {
                    FUN_00747b80(); // Spawn or activate some object
                }
            }
            FUN_007f63e0(0x16); // Another sound play?
            if (thisPtr[0x17] == 1) { // +0x17: some condition flag
                FUN_006eafe0(thisPtr[0x14]); // +0x14: object ID? call some function
                uVar4 = 0;
                uVar3 = FUN_006fbc40(0, 0); // CameraManager::getActiveCamera? returns camera handle
                FUN_006f3eb0(0xf66987be, 0, uVar3, uVar4); // CameraShake? hash 0xf66987be
                FUN_006fbc70(); // CameraManager::releaseCamera?
            }
            break;

        case 11: // Inspect
            iVar1 = thisPtr[0x15];
            if (iVar1 != 0) {
                if (iVar1 != 0x48) {
                    // Build a local structure for object creation
                    local_c = 0;
                    local_14 = 0;
                    local_24 = &PTR_FUN_00d5dbbc; // Global function pointer table for creation
                    local_1c = 0;
                    local_18 = 0;
                    local_8 = 0;
                    local_4 = DAT_01205228; // Global data
                    local_20 = 0x2f5cae00; // Some hash or ID
                    iVar2 = FUN_00471610(); // Get some object? returns pointer
                    local_8 = 1;
                    local_14 = *(ulonglong *)(iVar2 + 0x30); // Copy from returned object
                    local_c = *(uint *)(iVar2 + 0x38);
                    FUN_0044b210(thisPtr[0x14]); // Prepare something with entity ID
                    local_3c = &local_24;
                    local_40 = DAT_0112ad8c; // Another global
                    local_38 = 0;
                    FUN_00408bf0(&local_40, iVar1 - 0xc, 0); // Create object from template? offset 0xc
                    FUN_006ad490(); // Finalize or delete temporary?
                }
                return 1;
            }
            break;

        case 12: // Stop use
            FUN_007f6420(0x16); // SoundManager::stopSound(0x16)
            return 1;

        case 13: // Some other event
            FUN_004abdd0(0x40000); // UIManager::setFlag? or maybe set a player state
            return 1;

        default:
            // Fallback to generic handler
            uVar3 = FUN_004ac700(param_2, param_3, param_4, actionId, param_6);
            return uVar3;
    }
    return 1;
}