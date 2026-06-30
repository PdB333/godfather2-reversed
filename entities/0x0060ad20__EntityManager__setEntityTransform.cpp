// FUNC_NAME: EntityManager::setEntityTransform
void EntityManager::setEntityTransform(uint entityIndex, float* transform)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float *pfVar7;
  uint uVar8;
  
  if (entityIndex != 0) {
    uVar8 = entityIndex & 0xff;
    if ((entityIndex & 0x80000000) == 0) {
      pfVar7 = (float *)(&DAT_011d97f0 + uVar8 * 0x10); // +0x0: entity transform array (positive indices)
    }
    else {
      pfVar7 = (float *)(&DAT_011ea8f0 + uVar8 * 0x10); // +0x0: entity transform array (negative indices)
    }
    fVar1 = *pfVar7;
    fVar2 = *transform;
    if (fVar1 != fVar2) {
      *pfVar7 = fVar2;
    }
    fVar3 = transform[1];
    fVar4 = pfVar7[1];
    if (fVar4 != fVar3) {
      pfVar7[1] = fVar3;
    }
    fVar5 = transform[2];
    fVar6 = pfVar7[2];
    if (fVar6 != fVar5) {
      pfVar7[2] = fVar5;
    }
    if (fVar6 != fVar5 || (fVar4 != fVar3 || fVar1 != fVar2)) {
      if ((entityIndex & 0x80000000) != 0) {
        (**(code **)(*DAT_01205750 + 0x178))(); // call to some update function for negative indices
        return;
      }
      (**(code **)(*DAT_01205750 + 0x1b4))(DAT_01205750,uVar8,pfVar7,1); // call to some update function for positive indices
    }
  }
  return;
}