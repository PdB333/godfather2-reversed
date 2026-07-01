// FUNC_NAME: DebugRenderer::renderDebugColors
void __fastcall DebugRenderer::renderDebugColors(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  uint local_20c;
  undefined1 local_200;
  undefined1 local_1ff [127];
  undefined1 local_180;
  undefined1 local_17f [127];
  undefined1 local_100;
  undefined1 local_ff [127];
  undefined1 local_80;
  undefined1 local_7f [127];
  
  local_80 = 0;
  _memset(local_7f,0,0x7f);
  local_180 = 0;
  _memset(local_17f,0,0x7f);
  local_100 = 0;
  _memset(local_ff,0,0x7f);
  local_200 = 0;
  _memset(local_1ff,0,0x7f);
  uVar1 = FUN_009bf910(); // Get number of debug categories
  if ((uVar1 != 0) && (local_20c = 0, uVar1 != 0)) {
    do {
      FUN_009bf960(local_20c); // Set current category
      uVar5 = 0;
      iVar2 = FUN_009bf9f0(); // Get number of debug items in category
      if (iVar2 != 0) {
        do {
          uVar3 = FUN_009bfa00(uVar5); // Get number of color variants for item
          iVar2 = FUN_009bf9a0(uVar5); // Get debug item
          if (iVar2 != 0) {
            FUN_0090fd10(iVar2,&local_80,&local_180,&local_100,&local_200); // Get RGBA color components
            uVar6 = 0;
            if (uVar3 != 0) {
              do {
                uVar4 = FUN_009bfa20(uVar5,uVar6); // Get color variant
                *(undefined4 *)(param_1 + 0x2e4) = uVar4; // Store color variant
                *(uint *)(param_1 + 0x2e8) = uVar6; // Store variant index
                FUN_005a04a0("SetColor",0,&DAT_00d83ad0,4,&local_80,&local_180,&local_100,&local_200
                            ); // Set color for rendering
                uVar6 = uVar6 + 1;
              } while (uVar6 < uVar3);
            }
          }
          uVar5 = uVar5 + 1;
          uVar3 = FUN_009bf9f0();
        } while (uVar5 < uVar3);
      }
      local_20c = local_20c + 1;
    } while (local_20c < uVar1);
  }
  return;
}