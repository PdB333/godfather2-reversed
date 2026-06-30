//FUNC_NAME: Transform::copyFrom
void __thiscall Transform::copyFrom(Transform* this, Transform* fromTransform, Transform* overrideTransform)
{
    char fromType = *(char*)*fromTransform;      // Type of the 'from' transform (first byte of its data)
    char* destTypePtr = (char*)*this;            // Pointer to this transform's type byte
    char overrideType = *(char*)*overrideTransform; // Type of the override transform

    if (overrideType == 2) {
        *destTypePtr = 2; // Set this transform's type to 2
        if (fromType != 2) {
            // Copy override transform's data (matrix and translation) to this
            float* overrideMatrix = (float*)overrideTransform[1]; // +0x04: pointer to 8 floats
            float* overrideTranslation = (float*)overrideTransform[2]; // +0x08: pointer to 4 floats
            float* destMatrix = (float*)this[1];
            float* destTranslation = (float*)this[2];

            destMatrix[0] = overrideMatrix[0];
            destMatrix[1] = overrideMatrix[1];
            destMatrix[2] = overrideMatrix[2];
            destMatrix[3] = overrideMatrix[3];
            destMatrix[4] = overrideMatrix[4];
            destMatrix[5] = overrideMatrix[5];
            destMatrix[6] = overrideMatrix[6];
            destMatrix[7] = overrideMatrix[7];

            destTranslation[0] = overrideTranslation[0];
            destTranslation[1] = overrideTranslation[1];
            destTranslation[2] = overrideTranslation[2];
            destTranslation[3] = overrideTranslation[3];
            return;
        }
    } else {
        if (fromType != 2) {
            *destTypePtr = 0; // Set type to 0 (invalid/uninitialized)
            return;
        }
        *destTypePtr = 2; // Keep type 2 from 'from' transform
    }

    // Copy from 'from' transform's data to this
    float* fromMatrix = (float*)fromTransform[1];
    float* fromTranslation = (float*)fromTransform[2];
    float* destMatrix = (float*)this[1];
    float* destTranslation = (float*)this[2];

    destMatrix[0] = fromMatrix[0];
    destMatrix[1] = fromMatrix[1];
    destMatrix[2] = fromMatrix[2];
    destMatrix[3] = fromMatrix[3];
    destMatrix[4] = fromMatrix[4];
    destMatrix[5] = fromMatrix[5];
    destMatrix[6] = fromMatrix[6];
    destMatrix[7] = fromMatrix[7];

    destTranslation[0] = fromTranslation[0];
    destTranslation[1] = fromTranslation[1];
    destTranslation[2] = fromTranslation[2];
    destTranslation[3] = fromTranslation[3];
}