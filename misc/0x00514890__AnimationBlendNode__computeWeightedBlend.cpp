// FUNC_NAME: AnimationBlendNode::computeWeightedBlend
// Address: 0x00514890
// Role: Blends two stored quaternion poses (offset 0 and 0x10) by weight values (offset 0x40 and 0x4C) 
//       using global thresholds and scale factors. Outputs scaled poses to provided buffers.

void __thiscall AnimationBlendNode::computeWeightedBlend(float* outPose1, float* outPose2) {
    float maxWeight = DAT_00e44634;          // Global max blend weight threshold
    float scaleFactor = DAT_00e445f0;        // Global blend scale factor
    float defaultWeight = DAT_00e2b1a4;      // Default blend weight (used as fallback)

    float weight1 = defaultWeight;           // Weight for first pose
    float weight2 = defaultWeight;           // Weight for second pose

    // If stored weight at offset 0x40 is below threshold, compute scaled weight
    if (this->storedWeight1 < maxWeight) {
        weight1 = this->storedWeight1 * scaleFactor;
    }

    // Scale first pose (quaternion at offset 0) by weight1
    outPose1[0] = weight1 * this->pose1[0]; // +0x00
    outPose1[1] = weight1 * this->pose1[1]; // +0x04
    outPose1[2] = weight1 * this->pose1[2]; // +0x08
    outPose1[3] = weight1 * this->pose1[3]; // +0x0C

    // If stored weight at offset 0x4C is below threshold, compute scaled weight
    if (this->storedWeight2 < maxWeight) {
        weight2 = this->storedWeight2 * scaleFactor;
    }

    // Scale second pose (quaternion at offset 0x10) by weight2
    outPose2[0] = weight2 * this->pose2[0]; // +0x10
    outPose2[1] = weight2 * this->pose2[1]; // +0x14
    outPose2[2] = weight2 * this->pose2[2]; // +0x18
    outPose2[3] = weight2 * this->pose2[3]; // +0x1C
}