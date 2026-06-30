// FUNC_NAME: SomeClass::updatePositionDelta
void __thiscall SomeClass::updatePositionDelta(int this, float *param_2)
{
  float fVar1;
  float fVar2;
  float fVar3;
  char cVar4;
  
  cVar4 = FUN_006d1890((float *)(this + 0x10),param_2);
  if (cVar4 != '\0') {
    fVar1 = param_2[1];
    fVar2 = param_2[2];
    fVar3 = param_2[3];
    *(float *)(this + 0x60) = *param_2 - *(float *)(this + 0x10);
    *(float *)(this + 100) = fVar1 - *(float *)(this + 0x14);
    *(float *)(this + 0x68) = fVar2 - *(float *)(this + 0x18);
    *(float *)(this + 0x6c) = fVar3 - *(float *)(this + 0x1c);
  }
  return;
}