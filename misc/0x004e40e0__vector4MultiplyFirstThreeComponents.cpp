// FUNC_NAME: vector4MultiplyFirstThreeComponents
void __fastcall vector4MultiplyFirstThreeComponents(float *out, float *a, float *b)
{
    float a_x = a[0];
    float a_y = a[1];
    float a_z = a[2];
    float a_w = a[3];
    float b_x = b[0];
    float b_y = b[1];
    float b_z = b[2];
    float b_w = b[3];
    float orig_out_w = out[3];  // preserve original w (homogeneous coordinate)

    out[0] = a_x * b_x;
    out[1] = a_y * b_y;
    out[2] = a_z * b_z;
    out[3] = orig_out_w;        // w unchanged
}