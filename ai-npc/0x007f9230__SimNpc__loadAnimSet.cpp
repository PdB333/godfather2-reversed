// FUNC_NAME: SimNpc::loadAnimSet
void __thiscall SimNpc::loadAnimSet(int this, char param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 local_18 [6];
  
  local_18[0] = FUN_0043b490(); // some allocation or resource manager call
  uVar6 = 1;
  puVar5 = local_18;
  uVar4 = 0x20001;
  iVar1 = (-(uint)(param_2 != '\0') & 0x14) + 0x40b2a; // conditional offset based on param_2 (likely bool)
  uVar2 = FUN_0043b490(iVar1,0x20001,puVar5,1); // load resource with ID 0x20001
  puVar3 = (undefined8 *)FUN_00540bf0(4,uVar2,iVar1,uVar4,puVar5,uVar6); // allocate or fetch anim set data
  *(undefined8 *)(this + 0x828) = *puVar3; // +0x828: animSetData pointer (first 8 bytes)
  *(undefined8 *)(this + 0x830) = puVar3[1]; // +0x830: animSetData continuation
  *(undefined4 *)(this + 0x838) = *(undefined4 *)(puVar3 + 2); // +0x838: animSetData size/count
  uVar2 = FUN_00540cc0((undefined8 *)(this + 0x828)); // initialize anim set from loaded data
  FUN_0054e940(uVar2); // register or finalize anim set
  return;
}