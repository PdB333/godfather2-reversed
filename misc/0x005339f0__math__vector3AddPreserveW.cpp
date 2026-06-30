// FUNC_NAME: math::vector3AddPreserveW
// Function address: 0x005339f0
// Addition of two 4-component vectors, but only the first three components are summed; the fourth component (w) of the output is left unchanged.
// Called with __fastcall: output pointer in EAX, first input in ECX? (param_1 ignored), second input in EDX? (param_2, param_3).
// Although Ghidra signature shows param_1 (undefined4), it is unused. The effective signature is:
// void __fastcall vector3AddPreserveW(float* out, const float* a, const float* b);
void __fastcall vector3AddPreserveW(float* out, const float* a, const float* b)
{
    float aw = out[3]; // preserve original w component
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
    out[3] = aw;
}