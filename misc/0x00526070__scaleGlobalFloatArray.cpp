// FUNC_NAME: scaleGlobalFloatArray

void scaleGlobalFloatArray(float scale)
{
    // These four consecutive floats at 0x01125200 likely represent a vector or color array
    // Possibly used for global audio or visual scale factors
    *(float*)0x01125200 = scale * *(float*)0x01125200;
    *(float*)0x01125204 = scale * *(float*)0x01125204;
    *(float*)0x01125208 = scale * *(float*)0x01125208;
    *(float*)0x0112520c = scale * *(float*)0x0112520c;
}