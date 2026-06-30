// FUNC_NAME: blendTransforms
void blendTransforms(Transform* outTransform, const Transform* fromTransform, const Transform* toTransform, float blendFactor)
{
    char fromType = *(char*)fromTransform;
    char toType = *(char*)toTransform;
    char* outType = (char*)outTransform;

    if (fromType == 2) // Dual quaternion type
    {
        *outType = 2;
        if (toType == 2)
        {
            // Both are dual quaternions: interpolate dual quaternion part (8 floats) via slerp, then linear interpolate translation part (4 floats)
            slerpDualQuaternion((float*)outTransform->dualQuat, blendFactor);
            float* fromTrans = (float*)fromTransform->translation;
            float* toTrans = (float*)toTransform->translation;
            float* outTrans = (float*)outTransform->translation;
            outTrans[0] = (toTrans[0] - fromTrans[0]) * blendFactor + fromTrans[0];
            outTrans[1] = (toTrans[1] - fromTrans[1]) * blendFactor + fromTrans[1];
            outTrans[2] = (toTrans[2] - fromTrans[2]) * blendFactor + fromTrans[2];
            outTrans[3] = (toTrans[3] - fromTrans[3]) * blendFactor + fromTrans[3];
            return;
        }
        // from is dual quaternion, to is not: copy from to out (no interpolation)
        // Already set type above, now copy from's data
        float* fromDual = (float*)fromTransform->dualQuat;
        float* outDual = (float*)outTransform->dualQuat;
        outDual[0] = fromDual[0]; outDual[1] = fromDual[1]; outDual[2] = fromDual[2]; outDual[3] = fromDual[3];
        outDual[4] = fromDual[4]; outDual[5] = fromDual[5]; outDual[6] = fromDual[6]; outDual[7] = fromDual[7];
        float* fromTrans = (float*)fromTransform->translation;
        float* outTrans = (float*)outTransform->translation;
        outTrans[0] = fromTrans[0]; outTrans[1] = fromTrans[1]; outTrans[2] = fromTrans[2]; outTrans[3] = fromTrans[3];
        return;
    }
    else // fromType != 2
    {
        if (toType == 2)
        {
            // to is dual quaternion, from is not: copy to to out
            *outType = 2;
            float* toDual = (float*)toTransform->dualQuat;
            float* outDual = (float*)outTransform->dualQuat;
            outDual[0] = toDual[0]; outDual[1] = toDual[1]; outDual[2] = toDual[2]; outDual[3] = toDual[3];
            outDual[4] = toDual[4]; outDual[5] = toDual[5]; outDual[6] = toDual[6]; outDual[7] = toDual[7];
            float* toTrans = (float*)toTransform->translation;
            float* outTrans = (float*)outTransform->translation;
            outTrans[0] = toTrans[0]; outTrans[1] = toTrans[1]; outTrans[2] = toTrans[2]; outTrans[3] = toTrans[3];
            return;
        }
        // Neither is dual quaternion: set type to 0 (none) and return
        *outType = 0;
        return;
    }
}