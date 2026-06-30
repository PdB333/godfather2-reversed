// FUNC_NAME: AnimationBlendNode::updateBlendWeights
undefined4 AnimationBlendNode::updateBlendWeights(void)

{
  int *this;
  int iVar1;
  int iVar2;
  undefined2 in_FPUControlWord;
  int local_24;
  undefined4 local_20;
  longlong local_1c;
  undefined4 local_10;
  float local_c;
  float local_8;
  
  local_24 = CONCAT22(local_24._2_2_,in_FPUControlWord);
  iVar2 = this[1]; // +0x04: pointer to animation state data
  local_1c = (longlong)ROUND((float)this[2]); // +0x08: blend weight as float
  if ((*(uint *)(iVar2 + 4) & 0xff) < 10) { // check animation state type
    local_10 = *(undefined4 *)(iVar2 + 0x24); // +0x24: some state data
  }
  else {
    local_10 = *(undefined4 *)(iVar2 + 0x2c); // +0x2c: alternative state data
  }
  local_c = (float)(int)local_1c;
  if ((int)local_1c < 0) {
    local_c = local_c + DAT_00e44578; // float constant for negative handling
  }
  local_c = (float)this[2] - local_c; // fractional part of blend weight
  local_8 = 1.0 - local_c;
  if ((local_c <= DAT_00e2e780) || (local_8 <= DAT_00e2e780)) { // near 0 or 1
    local_c = 0.0;
    local_24 = (uint)local_24._1_3_ << 8; // clear blend flag
  }
  else {
    local_24 = CONCAT31(local_24._1_3_,1); // set blend flag
  }
  iVar2 = *this; // +0x00: vtable or base pointer
  iVar1 = *(int *)(iVar2 + 0x38); // +0x38: cached function pointer
  if (iVar1 == 0) {
    iVar1 = FUN_0056ef10(this[3]); // +0x0C: some identifier
    iVar2 = *this;
    *(int *)(iVar2 + 0x38) = iVar1;
  }
  iVar2 = *(int *)(iVar2 + 0x34) + 0x14; // +0x34: base offset + 0x14
  local_1c = CONCAT44(local_1c._4_4_,iVar1 + 0x10);
  local_20 = 0;
  FUN_0057cd80(iVar2,local_24,&local_20,&DAT_01223d40); // blend calculation
  FUN_0057caa0(local_24); // apply blend
  if ((char)local_24 != '\0') {
    FUN_0057cc40(); // finalize blend
    FUN_0057ccc0(iVar2); // update animation
    return 1;
  }
  FUN_0057cd30(iVar2,&DAT_01223d40); // cleanup
  return 1;
}