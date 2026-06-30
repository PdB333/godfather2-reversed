// FUNC_NAME: MathUtils::springDampen
void MathUtils::springDampen(float *position, float *velocity, float *acceleration, float springConstant, float dampingCoeff)
{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  fVar3 = *velocity;
  fVar1 = *position;
  fVar2 = ((fVar3 - fVar1) * springConstant + *acceleration) * dampingCoeff;
  dVar4 = (double)(DAT_00e44564 - springConstant * dampingCoeff);
  FUN_00b9be2b();
  fVar3 = (fVar2 + (fVar3 - fVar1)) * (float)dVar4 + *position;
  *position = fVar3;
  *velocity = fVar3;
  *acceleration = (*acceleration - fVar2 * springConstant) * (float)dVar4;
  return;
}