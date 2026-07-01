// FUNC_NAME: MathUtils::lerpProjectilePath
void MathUtils::lerpProjectilePath(float *startPos, float *endPos, float *velocity, float *outPos, float *outDir)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  
  fVar2 = *startPos;
  fVar1 = *velocity;
  fVar3 = SQRT((endPos[2] - startPos[2]) * (endPos[2] - startPos[2]) +
               (*endPos - fVar2) * (*endPos - fVar2));
  if (DAT_00e44598 < (float)((uint)fVar3 & DAT_00e44680)) {
    fVar3 = ((SQRT(velocity[2] * velocity[2] + fVar1 * fVar1) / fVar3) * (endPos[1] - startPos[1]) -
            velocity[1]) * _DAT_00d74f54;
    *outPos = fVar1 * fVar3 + fVar2;
    outPos[1] = velocity[1] * fVar3 + startPos[1];
    outPos[2] = velocity[2] * fVar3 + startPos[2];
    outPos[3] = velocity[3] * fVar3 + startPos[3];
    fVar2 = fVar3 * fVar3 * _DAT_00d5c458;
    local_24 = fVar2 * DAT_00e44830;
    fVar2 = fVar2 * _DAT_00d577a0;
    *outPos = fVar2 + *outPos;
    local_24 = outPos[1] - local_24;
    outPos[1] = local_24;
    outPos[2] = fVar2 + outPos[2];
    outPos[3] = fVar2 + outPos[3];
    local_28 = *outPos;
    local_20 = outPos[2];
    local_34 = *startPos;
    local_30 = startPos[1];
    local_2c = startPos[2];
    local_40 = *endPos;
    local_3c = endPos[1];
    local_38 = endPos[2];
    FUN_004a08d0(&local_1c,&local_28,&local_34,&local_40);
    *outDir = local_1c;
    outDir[1] = local_18;
    outDir[2] = local_14;
    outDir[3] = _DAT_00d5780c;
    return;
  }
  *outPos = fVar2;
  outPos[1] = startPos[1];
  outPos[2] = startPos[2];
  outPos[3] = startPos[3];
  *outDir = *startPos;
  outDir[1] = startPos[1];
  outDir[2] = startPos[2];
  outDir[3] = startPos[3];
  return;
}