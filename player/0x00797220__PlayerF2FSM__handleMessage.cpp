// FUNC_NAME: PlayerF2FSM::handleMessage
void __thiscall PlayerF2FSM::handleMessage(uint this, int *messageData)
{
    int *msgIter;
    char flag;
    undefined4 someValue;
    int targetObj;
    int* compareResult;
    
    msgIter = messageData;
    processMessageBase(messageData); // FUN_00541a30: base message processing
    
    someValue = DAT_00d5ccf8; // some global target? or directional input?
    int msgId = *msgIter;
    
    if (msgId == DAT_01206778) { // Attack/Punch message
        // Check if any of the 4-direction inputs are non-zero
        if ((((*(int *)(this + 0x3d0) != 0) || (*(int *)(this + 0x3d4) != 0)) ||
            (*(int *)(this + 0x3d8) != 0)) || (*(int *)(this + 0x3dc) != 0))
        {
            // Get target object from message data
            if (*(int *)(msgIter[1] + 0xc) == 0) {
                someValue = 0;
            } else {
                someValue = *(undefined4 *)(*(int *)(msgIter[1] + 0xc) + 0x1c);
            }
            targetObj = getTargetObject(someValue); // FUN_004025a0
            if (targetObj == 0) {
                messageData = (int *)0xfe16702f; // error/null marker
            } else {
                messageData = *(int **)(targetObj + 0x2c);
            }
            // Compare combined 4-input vector with target object's direction
            if (messageData == (int *)(((*(int *)(this + 0x3d0) * 0x21 + *(int *)(this + 0x3d4)) * 0x21 +
                                        *(int *)(this + 0x3d8)) * 0x21 + *(int *)(this + 0x3dc)))
            {
                // Set hit flag in state flags
                *(uint *)(this + 0x280) |= 0x8000000;
                setFightingAnimation(1); // FUN_00794600: play punch animation?
                setAnimationLayer(0x10, -(uint)(this != 0x3c) & this); // FUN_00403720: start animation layer
                *(undefined1 *)(this + 0x3ec) = 0; // clear some byte flag
                setAnimationLayerParam(2, -(uint)(this != 0x3c) & this, 0x8000); // FUN_00403620: set layer parameter
                return;
            }
        }
    }
    else if (msgId == DAT_01206760) { // Kick/Attack message 2
        if (((*(int *)(this + 0x3d0) != 0) || (*(int *)(this + 0x3d4) != 0)) ||
            ((*(int *)(this + 0x3d8) != 0 || (*(int *)(this + 0x3dc) != 0))))
        {
            if (*(int *)(msgIter[1] + 0xc) == 0) {
                someValue = 0;
            } else {
                someValue = *(undefined4 *)(*(int *)(msgIter[1] + 0xc) + 0x1c);
            }
            compareDirectionWithTarget(&messageData, someValue); // FUN_00411750: compare direction with target
            if (messageData == (int *)(((*(int *)(this + 0x3d0) * 0x21 + *(int *)(this + 0x3d4)) * 0x21 +
                                        *(int *)(this + 0x3d8)) * 0x21 + *(int *)(this + 0x3dc)))
            {
                // Clear hit flag
                *(uint *)(this + 0x280) &= 0xf7ffffff;
                flag = checkCameraState(0, 0); // FUN_00795a90: check if camera is in a certain state
                if (flag == 0) {
                    setFightingAnimation(0); // stop animation?
                }
                // Get current player state from global
                if (**(int **)(DAT_012233a0 + 4) == 0) {
                    targetObj = 0;
                } else {
                    targetObj = **(int **)(DAT_012233a0 + 4) - 0x1f30; // offset to some object
                }
                flag = checkCameraState(targetObj, 0);
                if (flag == 0) {
                    playKickSound(0); // FUN_00793ce0: play sound
                }
                setAnimationLayer(2, -(uint)(this != 0x3c) & this); // switch to other animation layer
                setAnimationLayerParam(0x10, -(uint)(this != 0x3c) & this, 0x8000);
                *(undefined1 *)(this + 0x3ec) = 1; // set byte flag
                return;
            }
        }
    }
    else {
        if (msgId == DAT_0112a618) {
            loadSpecialAnimation(); // FUN_00794800
            return;
        }
        if (msgId == DAT_0112a5cc) {
            // Call function at vtable offset 0x54 on parent object (this - 0x3c)
            (**(code **)(*(int *)(this - 0x3c) + 0x54))(1);
            // Call function at offset 0x5c with parameters 0x80, 0xc0
            (**(code **)(*(int *)(this - 0x3c) + 0x5c))(0x80, 0xc0);
            return;
        }
        if (msgId == DAT_0120e93c) {
            handleSomeEvent(); // FUN_00796e10
            return;
        }
        // Check for custom message handlers (vtable-like)
        if (msgId == *(int *)(this + 0x238)) { // handler for msg ID at +0x238
            *(uint *)(this + 0x280) &= 0xbfffffff;
            transitionToState(this - 0x3c, someValue); // FUN_00796ba0: transition to a new state
            return;
        }
        if (msgId == *(int *)(this + 0x240)) {
            *(uint *)(this + 0x280) |= 0x40000000;
            transitionToState(this - 0x3c, someValue);
            *(uint *)(this + 0x280) &= 0xbfffffff;
            return;
        }
        if (msgId == *(int *)(this + 0x248)) { // e.g., "block" or "defend" message
            if ((*(uint *)(this + 0x280) >> 4 & 1) == 0) {
                flag = checkCanBlock(); // FUN_004209a0
                if (((flag == 0) && (*(int *)(this + 0x27c) == 0)) &&
                    ((targetObj = getTargetFromDirection(this + 0x3d0), targetObj == 0 ||
                     (flag = isTargetBlockable(targetObj), flag == 0))))
                {
                    *(uint *)(this + 0x280) |= 0x8000000; // set hit flag
                }
            } else {
                *(uint *)(this + 0x280) |= 0x8000000;
            }
            if (((*(uint *)(this + 0x280) >> 0x1b & 1) == 0) && (flag = checkComboInput(), flag != 0)) {
                // Start combo sequence
                *(undefined4 *)(this + 0x268) = 0; // clear timer
                *(uint *)(this + 0x280) |= 0x4000000;
                return;
            }
        }
        else if (msgId == *(int *)(this + 0x250)) { // e.g., "attack start" message
            if (((*(uint *)(this + 0x280) >> 7 & 1) != 0) ||
                ((*(uint *)(this + 0x280) >> 0x1c & 1) == 0))
            {
                *(uint *)(this + 0x280) |= 1;
                // Notify network object if exists
                if (*(int **)(this + 0xf4) != (int *)0x0) {
                    (**(code **)(**(int **)(this + 0xf4) + 0x44))(0x6f74af5b, 1);
                }
                goto handleAttackEndOrStart;
            }
        }
        else if (msgId == *(int *)(this + 600)) { // "attack end" message? offset 0x258? note: this+600 = this+0x258
            if (((*(uint *)(this + 0x280) >> 7 & 1) != 0) ||
                ((*(uint *)(this + 0x280) >> 0x1c & 1) == 0))
            {
                *(uint *)(this + 0x280) &= 0xfffffffe;
                // Notify network object if in state 2
                if ((*(int *)(this + 0x27c) == 2) && (*(int **)(this + 0xf4) != (int *)0x0)) {
                    (**(code **)(**(int **)(this + 0xf4) + 0x44))(0x6f74af5b, 0);
                }
                goto handleAttackEndOrStart;
            }
        }
        else if (msgId == DAT_0112a620) {
            // Check if message's character ID matches current character ID
            if (*(int *)(*(int *)(msgIter[1] + 4) + 0x38) == *(int *)(this + 0x234)) {
                playSpecificAction(); // FUN_007947b0
                return;
            }
        }
        else if (msgId == DAT_0112a600) {
            if (*(int *)(*(int *)(msgIter[1] + 4) + 0x38) == *(int *)(this + 0x234)) {
                someValue = 0;
                int cameraHandle = getCameraHandle(0); // FUN_006b48b0
                setCameraState(cameraHandle, someValue); // FUN_00796b40
                return;
            }
        }
        else if (msgId == DAT_0112a628) {
            int dataPtr = msgIter[1];
            if (*(int *)(*(int *)(dataPtr + 4) + 0x38) == *(int *)(this + 0x234)) {
                someValue = 0;
                int cameraHandle = getCameraHandle(0);
                setCameraState(cameraHandle, someValue);
                int dist = getDistanceToTarget(*(undefined4 *)(dataPtr + 4)); // FUN_008dd580
                playAnimationForTarget(dist); // FUN_00796210
                playSpecificAction(); // FUN_007947b0
                return;
            }
        }
        else if (msgId == DAT_0112a5f0) {
            if ((*(int *)(*(int *)(msgIter[1] + 4) + 0x38) == *(int *)(this + 0x234)) &&
                ((*(uint *)(this + 0x280) >> 7 & 1) == 0))
            {
                *(uint *)(this + 0x280) |= 0x10000000;
                setActionState(1, 1); // FUN_00796120
                return;
            }
        }
        else if (msgId == DAT_0112a5e8) {
            if (*(int *)(*(int *)(msgIter[1] + 4) + 0x38) == *(int *)(this + 0x234)) {
                setCameraState(0, 0); // FUN_00796b40
                return;
            }
        }
        else if (((msgId == DAT_0112a5d8) &&
                  (int dataPtr2 = msgIter[1], *(char *)(dataPtr2 + 0x10) == 0)) &&
                 ((*(int *)(*(int *)(dataPtr2 + 4) + 0x38) == *(int *)(this + 0x234) &&
                   (flag = isLocationValid(*(undefined4 *)(dataPtr2 + 8), *(undefined4 *)(dataPtr2 + 0xc)), // FUN_00793950
                    flag != 0))))
        {
            *(undefined1 *)(dataPtr2 + 0x10) = 1; // mark message as handled
        }
    }
    return;

handleAttackEndOrStart:
    // Common path for attack start/end messages
    someValue = checkCameraState(0, 1); // FUN_00795a90
    setFightingAnimation(someValue);
    return;
}