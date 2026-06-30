// FUNC_NAME: scaleFloat6Array
// Address: 0x0052faa0
// Role: Scales an array of 6 consecutive floats by a scalar value.
// The pointer to the array is passed in EAX, the scalar in XMM1.
void scaleFloat6Array(float* data, float scale)
{
    data[0] *= scale;
    data[1] *= scale;
    data[2] *= scale;
    data[3] *= scale;
    data[4] *= scale;
    data[5] *= scale;
}