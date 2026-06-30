// FUNC_NAME: Sentient::getBoneWorldPosition
bool __fastcall Sentient::getBoneWorldPosition(void *thisPtr, Vector3 *outPos) // boneIndex passed in EDI (unaff_EDI)
{
    // +0xB4: pointer to bone index mapping (byte array)
    byte *boneMapping = *(byte **)((int)thisPtr + 0xB4);
    if (boneMapping != nullptr) {
        byte boneId = boneMapping[boneIndex]; // boneIndex from EDI
        if (boneId != 0xFF) {
            // +0xB8: pointer to bone world matrix array (each 0x40 bytes)
            float *boneMatrices = *(float **)((int)thisPtr + 0xB8);
            if (boneMatrices != nullptr) {
                // Translation part of the 4x4 matrix at offset 0x30, 0x34, 0x38
                outPos->x = boneMatrices[boneId * 0x40 / 4 + 0x30 / 4];
                outPos->y = boneMatrices[boneId * 0x40 / 4 + 0x34 / 4];
                outPos->z = boneMatrices[boneId * 0x40 / 4 + 0x38 / 4];
                return true;
            }
        }
    }
    outPos->x = 0.0f;
    outPos->y = 0.0f;
    outPos->z = 0.0f;
    return false;
}