// FUNC_NAME: ChaseCamera::CalculateAttachmentPosition
void __thiscall ChaseCamera::CalculateAttachmentPosition(int this, float* outPos)
{
    // Retrieve global camera/transform data (singleton)
    void* cameraData = GetGlobalStruct(); // returns pointer to camera transformation block

    // Read camera translation (packed as double at +0x30 to load two floats quickly)
    uint64_t transPacked = *(uint64_t*)((int)cameraData + 0x30);
    float transX = (float)(transPacked & 0xFFFFFFFF);        // +0x30
    float transY = (float)(transPacked >> 32);               // +0x34
    float transZ = *(float*)((int)cameraData + 0x38);        // +0x38

    // Read first offset vector (e.g., forward direction) from +0x10
    float vec1X = *(float*)((int)cameraData + 0x10);        // +0x10
    float vec1Y = *(float*)((int)cameraData + 0x14);        // +0x14
    float vec1Z = *(float*)((int)cameraData + 0x18);        // +0x18

    // Read second offset vector (e.g., right/up) from +0x20
    float vec2X = *(float*)((int)cameraData + 0x20);        // +0x20
    float vec2Y = *(float*)((int)cameraData + 0x24);        // +0x24
    float vec2Z = *(float*)((int)cameraData + 0x28);        // +0x28

    // Retrieve same pointer again for initialization call
    void* initData = GetGlobalStruct();

    // Initialize the output structure (probably zeros out or sets identity)
    ClearOutput(outPos, initData);

    // Load this object's stored offset scalars
    float scalar1 = *(float*)(this + 0x4FC);                 // mOffsetScalar1
    float scalar2 = *(float*)(this + 0x500) + gDeltaTime;    // mOffsetScalar2 + global time delta

    // Compute final world-space position:
    // result = vec2 * scalar2 + vec1 * scalar1 + cameraTranslation
    outPos[0x30 / 4] = vec2X * scalar2 + vec1X * scalar1 + transX;   // x
    outPos[0x34 / 4] = vec2Y * scalar2 + vec1Y * scalar1 + transY;   // y
    outPos[0x38 / 4] = vec2Z * scalar2 + vec1Z * scalar1 + transZ;   // z
    outPos[0x3C / 4] = gDeltaTime;                                    // w (time or homogeneous)
}