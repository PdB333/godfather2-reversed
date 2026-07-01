// FUNC_NAME: Entity::setParentEntity
uint __thiscall Entity::setParentEntity(int *this, uint newParentId, undefined4 param_3)
{
  int *piVar1;
  uint in_EAX;
  int iVar2;
  uint uVar3;
  
  if ((*(byte *)(this + 0x141) & 1) != 0) {
    if (this[0x142] == 0) {
      in_EAX = 0;
    }
    else {
      in_EAX = this[0x142] - 0x48;
    }
    if (((newParentId != in_EAX) && (in_EAX = this[0x142], in_EAX != 0)) &&
       (in_EAX = in_EAX - 0x48, in_EAX != 0)) {
      if (this[0x142] == 0) {
        in_EAX = 0;
      }
      else {
        in_EAX = this[0x142] - 0x48;
      }
      if ((*(byte *)(in_EAX + 0x120) & 8) == 0) goto LAB_007ffc64;
      if (this[0x142] == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = this[0x142] + -0x48;
      }
      in_EAX = (**(code **)(*this + 0x18))(iVar2);
    }
  }
  if (((*(byte *)(this + 0x141) & 1) == 0) && (((uint)this[0x141] >> 3 & 1) == 0)) {
    piVar1 = this + 0x142;
    if (newParentId == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = newParentId + 0x48;
    }
    if (*piVar1 != iVar2) {
      if (*piVar1 != 0) {
        FUN_004daf90(piVar1); // likely unlink from parent list
      }
      *piVar1 = iVar2;
      if (iVar2 != 0) {
        this[0x143] = *(int *)(iVar2 + 4);
        *(int **)(iVar2 + 4) = piVar1;
      }
    }
    uVar3 = (**(code **)(this[-0xe4] + 0x1ec))(newParentId,param_3); // likely some base class method
    this[0x141] = this[0x141] | 8;
    return uVar3 & 0xffffff00;
  }
  if (((char)param_3 != '\0') && (in_EAX = FUN_00625050(0xe8b1c0e8,0), in_EAX != 0)) {
    *(uint *)(in_EAX + 100) = *(uint *)(in_EAX + 100) | 1;
  }
LAB_007ffc64:
  return in_EAX & 0xffffff00;
}