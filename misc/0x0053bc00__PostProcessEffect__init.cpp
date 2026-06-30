// FUNC_NAME: PostProcessEffect::init
void __fastcall PostProcessEffect::init(int this)
{
  undefined4 uVar1;
  
  FUN_006127d0();
  uVar1 = FUN_0060a2e0(&PTR_DAT_010bea20);
  *(undefined4 *)(this + 0xc4) = uVar1; // +0xC4: pShader1
  uVar1 = FUN_0060a2e0(&PTR_DAT_010bea30);
  *(undefined4 *)(this + 200) = uVar1;   // +0xC8: pShader2
  uVar1 = FUN_0060a2e0(&PTR_DAT_010bea40);
  *(undefined4 *)(this + 0xcc) = uVar1;  // +0xCC: pShader3
  uVar1 = FUN_0060a2e0(&PTR_DAT_010bea50);
  *(undefined4 *)(this + 0xd0) = uVar1;  // +0xD0: pShader4
  uVar1 = FUN_0060a580(DAT_012198f8,"screen_color");
  *(undefined4 *)(this + 0xbc) = uVar1;  // +0xBC: screenColorParam
  uVar1 = FUN_0060a580(*(undefined4 *)(this + 0xd0),"depth_texture");
  *(undefined4 *)(this + 0xa8) = uVar1;  // +0xA8: depthTextureParam
  uVar1 = FUN_0060a580(*(undefined4 *)(this + 0xd0),"dof_params");
  *(undefined4 *)(this + 0xac) = uVar1;  // +0xAC: dofParamsParam
  uVar1 = FUN_0060a580(*(undefined4 *)(this + 200),"alphaScale1_alphaScale2_alphaDelta_notused");
  *(undefined4 *)(this + 0xb0) = uVar1;  // +0xB0: alphaParams
  uVar1 = FUN_0060a580(*(undefined4 *)(this + 0xc4),"imageSizeXY_centerZoom");
  *(undefined4 *)(this + 0xb4) = uVar1;  // +0xB4: imageSizeCenterZoom1
  uVar1 = FUN_0060a580(*(undefined4 *)(this + 200),"imageSizeXY_centerZoom");
  *(undefined4 *)(this + 0xb8) = uVar1;  // +0xB8: imageSizeCenterZoom2
  return;
}