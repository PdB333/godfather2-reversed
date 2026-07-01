// FUNC_NAME: PlayerCamera::computeShakeOffset
void __thiscall PlayerCamera::computeShakeOffset(int *this, float *outOffset, char param_3)

{
  byte bVar1;
  int iVar2;
  float unaff_ESI;
  float *pfVar3;
  float unaff_EDI;
  float fVar4;
  float fVar5;
  float *unaff_retaddr;
  float local_c [2];
  float *pfStack_4;
  
  iVar2 = FUN_00471610(); // likely getCurrentTime() or global camera manager
  pfVar3 = (float *)(iVar2 + 0x20); // +0x20: camera transform/position
  (**(code **)(*this + 0xa4))(local_c,this + 0x793); // vtable[0xa4]: getLagOffset or similar
  fVar5 = DAT_00d71c14;  // shake magnitude multiplier
  if (param_3 == '\0') {
    *(ulonglong *)pfStack_4 = CONCAT44(unaff_ESI,unaff_EDI);
    fVar4 = _DAT_00d5c458;  // high intensity shake scale
    pfStack_4[2] = local_c[0];
    *unaff_retaddr = *pfVar3 * fVar4 + unaff_EDI;
    unaff_retaddr[1] = *(float *)(iVar2 + 0x24) * fVar4 + unaff_ESI;
    fVar5 = DAT_00d5c454;   // low intensity shake scale
    unaff_retaddr[2] = *(float *)(iVar2 + 0x28) * fVar4 + local_c[0];
    *outOffset = *pfVar3 * fVar5 + unaff_EDI;
    outOffset[1] = *(float *)(iVar2 + 0x24) * fVar5 + unaff_ESI;
    outOffset[2] = *(float *)(iVar2 + 0x28) * fVar5 + local_c[0];
    return;
  }
  bVar1 = *(byte *)((int)this + 0x8e3) & 1; // +0x8e3: shaking flag
  if ((((uint)this[0x23a] >> 1 & 1) == 0) { // +0x8e8: some other state flag
    if (bVar1 == 0) {
      *pfStack_4 = *pfVar3 * DAT_00d71c14 + unaff_EDI;
      pfStack_4[1] = *(float *)(iVar2 + 0x24) * fVar5 + unaff_ESI;
      fVar4 = _DAT_00d5cf70;  // alternative shake scale
      pfStack_4[2] = *(float *)(iVar2 + 0x28) * fVar5 + local_c[0];
      *unaff_retaddr = *pfVar3 * fVar4 + unaff_EDI;
      unaff_retaddr[1] = *(float *)(iVar2 + 0x24) * fVar4 + unaff_ESI;
      unaff_retaddr[2] = *(float *)(iVar2 + 0x28) * fVar4 + local_c[0];
      *(ulonglong *)outOffset = CONCAT44(unaff_ESI,unaff_EDI);
      outOffset[2] = local_c[0];
      return;
    }
  }
  else {
    fVar5 = DAT_00d5f520;  // another shake scale
    if (bVar1 == 0) goto LAB_007f432a;
  }
  fVar5 = _DAT_00d5cf70;
LAB_007f432a:
  *(ulonglong *)pfStack_4 = CONCAT44(unaff_ESI,unaff_EDI);
  pfStack_4[2] = local_c[0];
  fVar4 = fVar5 * DAT_00d5eee4;  // combined multiplier
  *unaff_retaddr = *pfVar3 * fVar4 + unaff_EDI;
  unaff_retaddr[1] = *(float *)(iVar2 + 0x24) * fVar4 + unaff_ESI;
  unaff_retaddr[2] = *(float *)(iVar2 + 0x28) * fVar4 + local_c[0];
  *outOffset = *pfVar3 * fVar5 + unaff_EDI;
  outOffset[1] = *(float *)(iVar2 + 0x24) * fVar5 + unaff_ESI;
  outOffset[2] = *(float *)(iVar2 + 0x28) * fVar5 + local_c[0];
  return;
}