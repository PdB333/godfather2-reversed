// FUNC_NAME: TextureManager::loadSurfaceFromSurface
void TextureManager::loadSurfaceFromSurface(void)
{
  undefined1 *puVar1;
  int *piVar2;
  undefined4 uVar3;
  int *piStack_14;
  undefined4 uStack_10;
  undefined4 *puStack_c;
  undefined4 local_4;
  
  if (DAT_012058a4 < 0x1000) {
    puVar1 = &DAT_011a0f28 + DAT_012058a4 * 0x38;
  }
  else {
    puVar1 = (undefined1 *)0x0;
  }
  piStack_14 = *(int **)(puVar1 + 0x14);
  puStack_c = &local_4;
  local_4 = 0;
  uStack_10 = 0;
  (**(code **)(*piStack_14 + 0x48))();
  piStack_14 = (int *)0x0;
  uVar3 = 0;
  piVar2 = DAT_01205750;
  (**(code **)(*DAT_01205750 + 0x48))(DAT_01205750,0,0,0,&piStack_14);
  D3DXLoadSurfaceFromSurface(piVar2,0,0,uVar3,0,0,1,0);
  (**(code **)(*piVar2 + 8))(piVar2);
  (**(code **)(*piVar2 + 8))(piVar2);
  return;
}