// FUNC_NAME: Vector4::subtractXYZPreserveW
void __fastcall Vector4::subtractXYZPreserveW(float *out, float *in1, float *in2)
{
    // in1 and in2 are 4-float vectors, out is the result (passed in EAX)
    // Only X, Y, Z are subtracted; W is preserved in the output
    float in1Y = in1[1];
    float in1Z = in1[2];
    float in1W = in1[3];
    float in2Y = in2[1];
    float in2Z = in2[2];
    float in2W = in2[3];
    float origW = out[3]; // save original W

    out[0] = in1[0] - in2[0]; // X
    out[1] = in1Y - in2Y;      // Y
    out[2] = in1Z - in2Z;      // Z
    out[3] = in1W - in2W;      // temporary assign (overwritten below)
    out[3] = origW;            // restore original W
}