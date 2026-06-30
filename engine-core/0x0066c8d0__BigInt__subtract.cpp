// FUNC_NAME: BigInt::subtract
int __thiscall BigInt::subtract(int *this, int *other)
{
  int iVar1;
  int iVar2;
  int *in_EAX;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int *piVar6;
  uint uVar7;
  int iVar8;
  uint *puVar9;
  int local_c;
  int local_8;
  
  iVar8 = *other; // other->numDigits
  iVar1 = *this; // this->numDigits
  if ((iVar8 <= in_EAX[1]) || (iVar3 = FUN_00667740(), iVar3 == 0)) {
    iVar3 = *in_EAX; // this->numDigits
    *in_EAX = iVar8; // set result numDigits to other->numDigits
    piVar6 = (int *)other[3]; // other->digits
    uVar7 = 0;
    piVar4 = (int *)this[3]; // this->digits
    puVar9 = (uint *)in_EAX[3]; // result->digits
    local_8 = 0;
    local_c = iVar1;
    if (0 < iVar1) {
      do {
        iVar2 = *piVar4;
        piVar4 = piVar4 + 1;
        uVar7 = (*piVar6 - iVar2) - uVar7;
        *puVar9 = uVar7 & 0xfffffff;
        piVar6 = piVar6 + 1;
        uVar7 = uVar7 >> 0x1f;
        puVar9 = puVar9 + 1;
        local_c = local_c + -1;
        local_8 = iVar1;
      } while (local_c != 0);
    }
    if (local_8 < iVar8) {
      iVar8 = iVar8 - local_8;
      do {
        uVar5 = *piVar6 - uVar7;
        uVar7 = uVar5 >> 0x1f;
        *puVar9 = uVar5 & 0xfffffff;
        piVar6 = piVar6 + 1;
        puVar9 = puVar9 + 1;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
    if (*in_EAX < iVar3) {
      for (iVar3 = iVar3 - *in_EAX; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar9 = 0;
        puVar9 = puVar9 + 1;
      }
    }
    iVar8 = *in_EAX;
    if (0 < iVar8) {
      do {
        if (*(int *)(in_EAX[3] + -4 + *in_EAX * 4) != 0) break;
        iVar8 = *in_EAX + -1;
        *in_EAX = iVar8;
      } while (0 < iVar8);
      iVar8 = *in_EAX;
    }
    if (iVar8 == 0) {
      in_EAX[2] = 0;
    }
    iVar3 = 0;
  }
  return iVar3;
}