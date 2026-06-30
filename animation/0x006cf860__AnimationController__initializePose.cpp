// FUNC_NAME: AnimationController::initializePose
void __fastcall AnimationController::initializePose(int this)
{
    undefined4 uVar1;
    undefined4 uVar2;
    int iVar3;
    int iVar4;
    undefined4 *srcPoseData;
    undefined4 *dstPoseData;

    // Check if animation state machine exists and pose not yet initialized
    if ((*(int *)(this + 0xd0) != 0) && (*(char *)(this + 0x188) == '\0')) {
        iVar3 = getAnimStateMachine(this + 0xd0); // FUN_004ee450
        if ((iVar3 != 0) &&
            ((iVar3 = getPoseDataByIndex(this + 0xd0, 0), // FUN_004ee3a0 (index 0)
             uVar2 = _DAT_00d5780c,
             iVar3 != 0 &&
             (*(undefined4 **)(iVar3 + 0x24) != (undefined4 *)0x0)))) {
            // Save current position (from this + 0xe0)
            uVar1 = *(undefined4 *)(this + 0xe0);
            // Copy bone pose data from source (0x26 = 38 bones, each 4 bytes = 0x98 bytes)
            srcPoseData = *(undefined4 **)(iVar3 + 0x24);
            dstPoseData = (undefined4 *)(this + 0xf0);
            for (iVar4 = 0x26; iVar4 != 0; iVar4 = iVar4 + -1) {
                *dstPoseData = *srcPoseData;
                srcPoseData = srcPoseData + 1;
                dstPoseData = dstPoseData + 1;
            }
            // Set rotation/quaternion from original position (appears to be a rotation or orientation)
            *(undefined4 *)(this + 0x110) = uVar1;
            *(undefined4 *)(this + 0x114) = *(undefined4 *)(this + 0xe4);
            *(undefined4 *)(this + 0x118) = *(undefined4 *)(this + 0xe8);
            // Additional global constants
            *(undefined4 *)(this + 0x138) = uVar2;
            *(undefined4 *)(this + 0x100) = DAT_00d5f208;
            *(undefined4 *)(this + 0xf4) = 0x2d2307a5;
            *(undefined2 *)(this + 0x11c) = 0x81;
            *(undefined4 *)(this + 0x130) = DAT_00d5ef90;
            // Initialize the copied pose data structure
            initPoseData((undefined4 *)(this + 0xf0)); // FUN_004ee5a0
            // Mark pose as initialized
            *(undefined1 *)(this + 0x188) = 1;
        }
        if (*(char *)(this + 0x188) != '\0') {
            // Global debug/log functions
            debugPrint(&DAT_00e510b0); // FUN_004df870
            debugFlush(); // FUN_004df6e0
            return;
        }
    }
    return;
}