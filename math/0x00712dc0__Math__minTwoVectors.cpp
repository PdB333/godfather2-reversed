// FUNC_NAME: Math::minTwoVectors
void __cdecl Math::minTwoVectors(float *outPair1, float *outPair2, const float *in1A, const float *in2A, const float *in1B, const float *in2B)
{
    float temp;

    // Pair1: component-wise min of in1A and in1B into outPair1
    temp = *in1A;
    if (*in1B < *in1A) {
        temp = *in1B;
    }
    *outPair1 = temp;

    temp = in1A[1];
    if (in1B[1] < in1A[1]) {
        temp = in1B[1];
    }
    outPair1[1] = temp;

    temp = in1A[2];
    if (in1B[2] < in1A[2]) {
        temp = in1B[2];
    }
    outPair1[2] = temp;

    // Pair2: component-wise min of in2A and in2B into outPair2
    temp = *in2A;
    if (*in2B < *in2A) {
        temp = *in2B;
    }
    *outPair2 = temp;

    temp = in2A[1];
    if (in2B[1] < in2A[1]) {
        temp = in2B[1];
    }
    outPair2[1] = temp;

    if (in2B[2] < in2A[2]) {
        outPair2[2] = in2B[2];
        return;
    }
    outPair2[2] = in2A[2];
}