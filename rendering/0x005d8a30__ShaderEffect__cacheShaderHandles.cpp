// FUNC_NAME: ShaderEffect::cacheShaderHandles
void __fastcall ShaderEffect::cacheShaderHandles(int this)
{
  undefined4 uVar1;
  
  uVar1 = FUN_0060a580(*(undefined4 *)(this + -0xa0), "inColor");
  *(undefined4 *)(this + 0x60) = uVar1;
  uVar1 = FUN_0060a580(*(undefined4 *)(this + -0xa0), "ModelViewProj");
  *(undefined4 *)(this + -0x60) = uVar1;
  return;
}