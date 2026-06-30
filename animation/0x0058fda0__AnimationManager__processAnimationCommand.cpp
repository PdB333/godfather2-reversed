// FUNC_NAME: AnimationManager::processAnimationCommand
int AnimationManager::processAnimationCommand(AnimationManager* this, AnimationCommandData* commandData, undefined4 param3, undefined4 param4, undefined4 param5, uint flags, undefined4 param7)
{
    byte opcodeByte;
    short* jointIndices;
    int poseContext;
    char isOk;
    int newPoseContext;
    int poseSize;
    undefined4 tempTransform[3]; // stacked as uStack_17c/uStack_178/uStack_174 (copies of uStack_120 etc.)
    byte poseBuffer[80];
    undefined4 local_120[3]; // fake local for alignment (uStack_120 etc.)

    // Check if command data has valid count
    if (commandData->count > 0) {
        jointIndices = commandData->jointIndexArray; // +0x04
        opcodeByte = *(byte*)(commandData->opcodeData); // +0x0C, first byte

        // Check opcode is in range (max 0x23) and dispatch to handler
        if ((opcodeByte & 0x3F) < 0x23) {
            poseContext = ((code*)opcodeHandlers[opcodeByte & 0x3F])
                          (this, commandData->opcodeData, param3, param4, param5, flags, param7);
            if (poseContext != 0) {
                // Check if we should apply poses (flags and state bit)
                if (((flags & 4) == 0) && ((*(uint*)(this + 0x10) >> 8 & 1) == 0)) {
                    isOk = AnimationManager::getInstance();
                    if (isOk == '\0') {
                        // Allocate new pose context and copy data from the returned one
                        newPoseContext = AnimationManager::allocateAnimationPose();
                        AnimationManager::setupPosePart1();
                        AnimationManager::setupPosePart2();
                        AnimationManager::setupPosePart3();
                        AnimationManager::setupPosePart4();
                        poseSize = *(int*)(*(int*)(poseContext + 0x38) + 0x0C); // size in dwords? (bytes=poseSize<<5)
                        newPoseContext = AnimationManager::createPoseState(poseSize);
                        *(int*)(newPoseContext + 0x38) = newPoseContext;
                        _memcpy((void*)(newPoseContext + 0x10), (void*)(*(int*)(poseContext + 0x38) + 0x10), poseSize << 5);
                        AnimationManager::finalizePoseCopy();
                        poseContext = newPoseContext;
                    }

                    // Apply first joint pose (jointIndices[0], jointIndices[1])
                    if ((jointIndices[0] >= 0) && (jointIndices[1] >= 0) &&
                        (isOk = AnimationManager::isValidJointPose(poseContext, jointIndices[0]), isOk != '\0')) {
                        tempTransform[0] = local_120[0];
                        tempTransform[1] = local_120[1];
                        tempTransform[2] = local_120[2];
                        AnimationManager::getCharacterTransform(this, tempTransform);
                        AnimationManager::applyJointPose(poseBuffer, poseContext, (char)jointIndices[2]);
                    }

                    // Apply second joint pose (jointIndices[3], jointIndices[4])
                    if ((jointIndices[3] >= 0) && (jointIndices[4] >= 0) &&
                        (isOk = AnimationManager::isValidJointPose(poseContext, jointIndices[3]), isOk != '\0')) {
                        tempTransform[0] = local_120[0];
                        tempTransform[1] = local_120[1];
                        tempTransform[2] = local_120[2];
                        AnimationManager::getCharacterTransform(this, tempTransform);
                        AnimationManager::applyJointPose(poseBuffer, poseContext, (char)jointIndices[5]);
                    }
                }
                return poseContext;
            }
        }
    }
    return 0;
}