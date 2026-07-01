// FUNC_NAME: Entity::doSomething
void __thiscall Entity::doSomething(int this, undefined4 param_2)
{
  byte uVar1;
  int somePtr;
  uint local_4;
  
  if (((*(int *)(this + 0x1b4) != 0) && (*(int *)(this + 0x1b4) != 0x48)) &&
     (somePtr = FUN_00625050(0x187b7e2b,0), somePtr != 0)) {
    FUN_007cb610();
    local_4._1_3_ = (undefined3)((uint)this >> 8);
    local_4 = CONCAT31(local_4._1_3_,(char)(*(uint *)(this + 0x1d0) >> 6)) & 0xffffff01;
    uVar1 = FUN_00772de0(param_2,*(undefined2 *)(this + 0x1d6),1,local_4);
    *(byte *)(this + 0x20c) = uVar1;
    return;
  }
  *(uint *)(this + 0x1d0) = *(uint *)(this + 0x1d0) | 2;
  return;
}