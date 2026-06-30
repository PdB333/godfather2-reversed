// FUNC_NAME: someConditionalTransformFetch
void someConditionalTransformFetch(void)
{
    // Define a 4-component vector (quaternion or position+padding)
    float outputVector[4]; // local_20 (first float), local_1c, local_18, local_14

    // Check a global indexed by (someIndex * 0x1b) offset
    // DAT_01198ed0 is a byte array, each entry is 0x1b bytes (likely a struct)
    // DAT_0121bf30 is the index (e.g., a controller slot or object ID)
    if ((g_byteArray[DAT_0121bf30 * 0x1b] != 0)) // index*27 bytes offset
    {
        // Initialize output vector to zero
        outputVector[0] = 0.0f;
        outputVector[1] = 0.0f;
        outputVector[2] = 0.0f;
        outputVector[3] = 0.0f;

        // Call a transform retrieval function
        // DAT_0121be9c is a global pointer (e.g., manager instance)
        // Second argument is the value from the byte array (could be an ID or another pointer)
        // Third argument is the output vector
        FUN_0060add0(DAT_0121be9c, g_byteArray[DAT_0121bf30 * 0x1b], outputVector);
    }
    return;
}