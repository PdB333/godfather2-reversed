// FUNC_NAME: Math::computeAABBFrustumIntersection
void Math::computeAABBFrustumIntersection(int param_1, float *outMinX, float *outMinY, float *outMaxX, float *outMaxY)
{
    float fVar1;
    int iVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    float fVar15;
    
    FUN_005c4850(); // Math::initializeFrustumData
    FUN_00417560(); // Math::getCameraTransform
    FUN_00417560(); // Math::getProjectionMatrix
    fVar3 = DAT_00e2fc48; // frustumNearPlane
    fVar1 = DAT_00e2b1a4; // frustumFarPlane
    iVar2 = *(int *)(param_1 + 4); // object transform matrix
    *(undefined4 *)(param_1 + 0xc) = 0; // clear bounding box flag
    fVar5 = fRam01225e04; // camera forward Y
    fVar4 = _DAT_01225e00; // camera forward X
    fVar15 = *(float *)(iVar2 + 0x44) * fRam01225de4; // object scale * camera up Y
    fVar13 = *(float *)(iVar2 + 0x40) * fRam01225dd4; // object scale * camera up X
    fVar14 = fVar3 * fRam01225df4; // near plane * camera right Y
    fVar6 = fVar1 * fRam01225e04; // far plane * camera forward Y
    fVar9 = *(float *)(iVar2 + 0x58) * _DAT_01225dd0; // object position Y * camera up Y
    fVar11 = *(float *)(iVar2 + 0x58) * fRam01225dd4; // object position Y * camera up X
    fVar7 = *(float *)(iVar2 + 0x5c) * _DAT_01225de0; // object position Z * camera right X
    fVar8 = *(float *)(iVar2 + 0x5c) * fRam01225de4; // object position Z * camera right Y
    fVar10 = fVar3 * _DAT_01225df0; // near plane * camera up Y
    fVar12 = fVar3 * fRam01225df4; // near plane * camera up X
    *outMinX = *(float *)(iVar2 + 0x44) * _DAT_01225de0 + *(float *)(iVar2 + 0x40) * _DAT_01225dd0 +
             fVar3 * _DAT_01225df0 + fVar1 * _DAT_01225e00; // compute min X
    *outMaxX = fVar7 + fVar9 + fVar10 + fVar1 * fVar4; // compute max X
    *outMinY = fVar15 + fVar13 + fVar14 + fVar6; // compute min Y
    *outMaxY = fVar8 + fVar11 + fVar12 + fVar1 * fVar5; // compute max Y
    fVar1 = *outMinX;
    if (*outMaxX < fVar1) {
        *outMinX = *outMaxX;
        *outMaxX = fVar1;
    }
    fVar1 = *outMinY;
    if (*outMaxY < fVar1) {
        *outMinY = *outMaxY;
        *outMaxY = fVar1;
    }
    return;
}