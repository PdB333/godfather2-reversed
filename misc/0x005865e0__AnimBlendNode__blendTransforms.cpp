// FUNC_NAME: AnimBlendNode::blendTransforms
// Function at 0x005865e0: Blends two animation transform nodes (rotation and translation) with interpolation factor t.

struct AnimBlendNode {
    uint8_t* type;     // +0x00: pointer to type byte (0=invalid, 2=valid)
    float* rotation;   // +0x04: pointer to 8 floats (first 8 floats of transform)
    float* translation; // +0x08: pointer to 4 floats (last 4 floats of transform)
};

// forward declaration – function at 0x005781f0
void interpolateRotation(float* outRotation, float t);

void blendTransforms(AnimBlendNode* outNode, const AnimBlendNode* nodeA, const AnimBlendNode* nodeB, float t)
{
    uint8_t* outType = outNode->type;
    uint8_t aType = *nodeA->type;
    uint8_t bType = *nodeB->type;

    if (aType != 2)
    {
        if (bType == 2)
        {
            // Only nodeB is valid: copy from nodeB to output
            *outType = 2;

            // Copy rotation (8 floats)
            for (int i = 0; i < 8; ++i)
                outNode->rotation[i] = nodeB->rotation[i];

            // Copy translation (4 floats)
            for (int i = 0; i < 4; ++i)
                outNode->translation[i] = nodeB->translation[i];
        }
        else
        {
            // Both invalid: mark output as invalid
            *outType = 0;
        }
    }
    else  // aType == 2
    {
        *outType = 2;

        if (bType == 2)
        {
            // Both valid: interpolate rotation and translation
            // Interpolate rotation part using specialized function (e.g. quaternion slerp)
            interpolateRotation(outNode->rotation, t);

            // Linearly interpolate translation (4 floats)
            const float* aPos = nodeA->translation;
            const float* bPos = nodeB->translation;
            float* outPos = outNode->translation;

            outPos[0] = (bPos[0] - aPos[0]) * t + aPos[0];
            outPos[1] = (bPos[1] - aPos[1]) * t + aPos[1];
            outPos[2] = (bPos[2] - aPos[2]) * t + aPos[2];
            outPos[3] = (bPos[3] - aPos[3]) * t + aPos[3];
        }
        else
        {
            // Only nodeA is valid: copy from nodeA to output
            for (int i = 0; i < 8; ++i)
                outNode->rotation[i] = nodeA->rotation[i];

            for (int i = 0; i < 4; ++i)
                outNode->translation[i] = nodeA->translation[i];
        }
    }
}