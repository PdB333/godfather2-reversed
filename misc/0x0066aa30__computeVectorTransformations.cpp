// FUNC_NAME: computeVectorTransformations
int computeVectorTransformations(int* param_1)
{
    // Local arrays of 16 bytes each (likely 4 floats)
    Vector4 local_d4;
    Vector4 local_c4;
    Vector4 local_b4;
    Vector4 local_a4;
    Vector4 local_94;
    Vector4 local_84;
    Vector4 local_74;
    Vector4 local_64;
    Vector4 local_54;
    Vector4 local_44;
    Vector4 local_34;
    Vector4 local_24;
    // local_14 is 20 bytes, possibly a struct with extra data
    char local_14[20]; // unknown structure

    int result;

    // Initialize all vectors with some base data
    result = initVectors(local_14, &local_94, &local_b4, &local_a4, &local_64, &local_24,
                         &local_84, &local_54, &local_34, &local_74, &local_44,
                         &local_d4, &local_c4, 0);
    if (result != 0) {
        return result;
    }

    // Determine a scaling factor from the input and a global/register value
    int inputValue = *param_1;
    int globalValue = *in_EAX; // value passed in EAX (likely a global or parameter)
    int minValue = (inputValue < globalValue) ? inputValue : globalValue;
    int scaledValue = minValue / 3;
    int stepSize = scaledValue * 0x1c; // 28 bytes

    // Attempt to allocate/initialize buffers with retries
    result = allocateBuffer(stepSize);
    if (result != 0) return result;
    result = checkBufferReady();
    if (result != 0) return result;
    setBufferSize(scaledValue);
    result = allocateBuffer(stepSize);
    if (result != 0) return result;
    result = checkBufferReady();
    if (result != 0) return result;
    setBufferSize(scaledValue * 2);
    result = allocateBuffer(stepSize);
    if (result != 0) return result;
    result = checkBufferReady();
    if (result != 0) return result;
    setBufferSize(scaledValue);
    result = allocateBuffer(stepSize);
    if (result != 0) return result;
    result = checkBufferReady();
    if (result != 0) return result;
    setBufferSize(scaledValue * 2);

    // Series of vector operations
    result = addVectors(&local_24, &local_34, &local_14);
    if (result != 0) return result;
    result = addVectors(&local_54, &local_44, &local_64);
    if (result != 0) return result;
    result = copyVector(&local_24, &local_d4);
    if (result != 0) return result;
    result = clearVector(&local_d4);
    if (result != 0) return result;
    result = copyVector(&local_d4, &local_d4);
    if (result != 0) return result;
    result = clearVector(&local_d4);
    if (result != 0) return result;
    result = copyVector(&local_34, &local_c4);
    if (result != 0) return result;
    result = clearVector(&local_c4);
    if (result != 0) return result;
    result = copyVector(&local_c4, &local_c4);
    if (result != 0) return result;
    result = clearVector(&local_c4);
    if (result != 0) return result;
    result = addVectors(&local_d4, &local_c4, &local_94);
    if (result != 0) return result;
    result = copyVector(&local_54, &local_d4);
    if (result != 0) return result;
    result = clearVector(&local_d4);
    if (result != 0) return result;
    result = copyVector(&local_d4, &local_d4);
    if (result != 0) return result;
    result = clearVector(&local_d4);
    if (result != 0) return result;
    result = copyVector(&local_44, &local_c4);
    if (result != 0) return result;
    result = clearVector(&local_c4);
    if (result != 0) return result;
    result = copyVector(&local_c4, &local_c4);
    if (result != 0) return result;
    result = clearVector(&local_c4);
    if (result != 0) return result;
    result = addVectors(&local_d4, &local_c4, &local_a4);
    if (result != 0) return result;
    result = clearVector(&local_54);
    if (result != 0) return result;
    result = clearVector(&local_d4);
    if (result != 0) return result;
    result = clearVector(&local_44);
    if (result != 0) return result;
    result = clearVector(&local_c4);
    if (result != 0) return result;
    result = addVectors(&local_d4, &local_c4, &local_b4);
    if (result != 0) return result;
    result = dotProduct(&local_94, &local_64);
    if (result != 0) return result;
    result = dotProduct(&local_a4, &local_14);
    if (result != 0) return result;
    result = scaleVector(&local_94);
    if (result != 0) return result;
    result = scaleVector(&local_a4);
    if (result != 0) return result;
    result = dotProduct(&local_b4, &local_14);
    if (result != 0) return result;
    result = dotProduct(&local_b4, &local_64);
    if (result != 0) return result;
    result = dotProduct(&local_94, &local_b4);
    if (result != 0) return result;
    result = dotProduct(&local_a4, &local_b4);
    if (result != 0) return result;
    result = setConstant(3);
    if (result != 0) return result;
    result = dotProduct(&local_94, &local_d4);
    if (result != 0) return result;
    result = setConstant(3);
    if (result != 0) return result;
    result = dotProduct(&local_a4, &local_d4);
    if (result != 0) return result;
    result = multiplyByScalar(&local_b4, 3, &local_b4);
    if (result != 0) return result;
    result = dotProduct(&local_b4, &local_94);
    if (result != 0) return result;
    result = dotProduct(&local_b4, &local_a4);
    if (result != 0) return result;
    result = dotProduct(&local_94, &local_b4);
    if (result != 0) return result;
    result = dotProduct(&local_a4, &local_b4);
    if (result != 0) return result;
    result = lerp(&local_94, &local_94, 0);
    if (result != 0) return result;
    result = lerp(&local_a4, &local_a4, 0);
    if (result != 0) return result;
    result = allocateBuffer(scaledValue);
    if (result != 0) return result;
    result = allocateBuffer(scaledValue * 2);
    if (result != 0) return result;
    result = allocateBuffer(scaledValue * 3);
    if (result != 0) return result;
    result = allocateBuffer(scaledValue * 4);
    if (result != 0) return result;
    result = clearVector(&local_14);
    if (result != 0) return result;
    result = clearVector(&local_b4);
    if (result != 0) return result;
    result = clearVector(&local_64);
    if (result != 0) return result;
    result = clearVector(&local_d4);
    if (result != 0) return result;

    // Cleanup vectors
    result = cleanupVectors(local_14, &local_94, &local_b4, &local_a4, &local_64, &local_24,
                            &local_84, &local_54, &local_34, &local_74, &local_44,
                            &local_d4, &local_c4, 0);
    return result;
}