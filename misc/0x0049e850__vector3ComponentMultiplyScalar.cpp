// FUNC_NAME: vector3ComponentMultiplyScalar
void __fastcall vector3ComponentMultiplyScalar(float* dest, const float* a, const float* b) {
    float fVar1 = a[1];
    float fVar2 = a[2];
    float fVar3 = a[3];
    float fVar4 = b[1];
    float fVar5 = b[2];
    float fVar6 = b[3];
    float fVar7 = dest[3]; // Save original w component

    dest[0] = a[0] * b[0];
    dest[1] = fVar1 * fVar4;
    dest[2] = fVar2 * fVar5;
    dest[3] = fVar3 * fVar6; // This write is immediately overwritten
    dest[3] = fVar7;         // w component is preserved
}