// FUNC_NAME: AnimationBlender::addPositionContribution
void __thiscall AnimationBlender::addPositionContribution(int boneCount, float* source) {
    float fVar1;
    float* bonesArray;
    int index;
    float delta[3];
    undefined4 transformed[3];
    float* bone;

    if ((source != nullptr) && (source[4] != 0.0f) && (boneCount != 0)) {
        index = 0;
        bonesArray = this;
        // iterate over each bone in the blend array
        do {
            float scaleFactor = source[4]; // weight or influence factor from source
            bone = bonesArray; // current bone data (size 48 bytes per bone)
            if (bone[8] != 0.0f) { // bone has non-zero blending weight
                if (source[7] == 0.0f) {
                    // compute delta from bone's own position to source position
                    delta[0] = source[0] - bone[0];
                    delta[1] = source[1] - bone[1];
                    delta[2] = source[2] - bone[2];
                    // transform delta using bone's scaling factor and store at output offset
                    FUN_0044c4c0(bone[8], delta, &transformed); // transforms delta by scaleFactor scaling
                    *(undefined4*)((int)index + 0xc + (int)scaleFactor) = transformed[0];
                    *(undefined4*)((int)index + 0x10 + (int)scaleFactor) = transformed[1];
                    *(undefined4*)((int)index + 0x14 + (int)scaleFactor) = transformed[2];
                } else {
                    // direct copy of source position into bone's contribution slot
                    *(float*)((int)index + 0xc + (int)scaleFactor) = source[0];
                    *(float*)((int)index + 0x10 + (int)scaleFactor) = source[1];
                    *(float*)((int)index + 0x14 + (int)scaleFactor) = source[2];
                }
            }
            bonesArray += 0xc; // advance to next bone (12 floats = 48 bytes per bone)
            index += 0xc; // byte offset increments by 12 (size of contribution block)
            boneCount--;
        } while (boneCount != 0);
    }
}