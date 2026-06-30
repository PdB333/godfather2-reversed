// FUNC_NAME: EARSStreamManager::readAndCallCallback
void EARSStreamManager::readAndCallCallback(int param_1, undefined4 *param_2)
{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  ulonglong uVar4;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  undefined8 local_8;
  
  uVar2 = **(undefined4 **)(param_1 + 0x18); // +0x18: current read pointer
  uVar1 = (int)*(undefined4 **)(param_1 + 0x18) + 7; // align to 4 bytes
  uVar3 = uVar1 & 0xfffffffc;
  uVar4 = CONCAT44(0x20,uVar1) & 0xfffffffffffffffc;
  *(uint *)(param_1 + 0x18) = uVar3; // advance read pointer
  _memcpy(&local_20,(void *)uVar4,(size_t)(uVar4 >> 0x20)); // copy 32 bytes of data
  *(uint *)(param_1 + 0x18) = uVar3 + 0x20; // advance read pointer by 32 bytes
  (*(code *)*param_2)(uVar2,local_20,local_18,local_10,local_8); // call callback with data
  return;
}