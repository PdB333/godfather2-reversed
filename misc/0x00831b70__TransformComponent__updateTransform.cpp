// FUNC_NAME: TransformComponent::updateTransform
void __thiscall TransformComponent::updateTransform(int this, int sourceTransformIdx) {
    int result;
    int tempBuffer[27]; // 108 bytes = 27 ints
    int tempBuffer2[24]; // 96 bytes = 24 ints
    int tempBuffer3[24]; // 96 bytes = 24 ints

    int transformType = *(int *)(this + 0x24); // +0x24: type of transform (0=world, 1=local, 2=???)

    if (transformType == 0) {
        result = FUN_0082e200(tempBuffer3, sourceTransformIdx); // Compute world transform into tempBuffer3
    } else if (transformType == 1) {
        result = FUN_0082df70(tempBuffer2, sourceTransformIdx, 0); // Compute local transform into tempBuffer2
    } else {
        result = FUN_0082df70(tempBuffer, sourceTransformIdx, 0); // Compute other transform into tempBuffer
    }

    // +0x30: pointer to current target transform buffer
    if (this + 0x30 != result) {
        FUN_00820830(result); // Assign/copy the result transform
        *(float *)(this + 0x7c) = *(float *)(result + 0x4c); // +0x7c: quaternion x
        *(float *)(this + 0x80) = *(float *)(result + 0x50); // +0x80: quaternion y
        *(float *)(this + 0x84) = *(float *)(result + 0x54); // +0x84: quaternion z
        *(float *)(this + 0x88) = *(float *)(result + 0x58); // +0x88: quaternion w
    }
}