// FUNC_NAME: Matrix4x4::setWithChangeDetection
bool __fastcall Matrix4x4::setWithChangeDetection(float *destMatrix, float *srcMatrix) // dest passed in EAX, src in ECX
{
    float old0, old1, old2, old3;
    float new0, new1, new2, new3;
    float old4, old5, old6, old7;
    float new4, new5, new6, new7;
    float old8, old9, old10, old11;
    float new8, new9, new10, new11;
    float old12, old13, old14, old15;
    float new12, new13, new14, new15;

    // Save old values from destination (in_EAX)
    old0 = destMatrix[0];
    old1 = destMatrix[1];
    old2 = destMatrix[2];
    old3 = destMatrix[3];
    old4 = destMatrix[4];
    old5 = destMatrix[5];
    old6 = destMatrix[6];
    old7 = destMatrix[7];
    old8 = destMatrix[8];
    old9 = destMatrix[9];
    old10 = destMatrix[10];
    old11 = destMatrix[11];
    old12 = destMatrix[12];
    old13 = destMatrix[13];
    old14 = destMatrix[14];
    old15 = destMatrix[15];

    // Copy source matrix into destination (param_1 = srcMatrix in ECX)
    destMatrix[0] = srcMatrix[0];
    destMatrix[1] = srcMatrix[1];
    destMatrix[2] = srcMatrix[2];
    destMatrix[3] = srcMatrix[3];
    destMatrix[4] = srcMatrix[4];
    destMatrix[5] = srcMatrix[5];
    destMatrix[6] = srcMatrix[6];
    destMatrix[7] = srcMatrix[7];
    destMatrix[8] = srcMatrix[8];
    destMatrix[9] = srcMatrix[9];
    destMatrix[10] = srcMatrix[10];
    destMatrix[11] = srcMatrix[11];
    destMatrix[12] = srcMatrix[12];
    destMatrix[13] = srcMatrix[13];
    destMatrix[14] = srcMatrix[14];
    destMatrix[15] = srcMatrix[15];

    // Compare old vs new; return 1 if any element changed
    if (destMatrix[0] != old0 || destMatrix[1] != old1 || destMatrix[2] != old2 || destMatrix[3] != old3 ||
        destMatrix[4] != old4 || destMatrix[5] != old5 || destMatrix[6] != old6 || destMatrix[7] != old7 ||
        destMatrix[8] != old8 || destMatrix[9] != old9 || destMatrix[10] != old10 || destMatrix[11] != old11 ||
        destMatrix[12] != old12 || destMatrix[13] != old13 || destMatrix[14] != old14 || destMatrix[15] != old15)
        return 1;

    return 0;
}