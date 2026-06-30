// FUNC_NAME: ShaderManager::initializeShaderParameters
void __fastcall ShaderManager::initializeShaderParameters(int *this)
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  
  // Call virtual methods via vtable (+0x48 = getVertexShader, +0x54 = setPixelShader, +0x44 = setVertexShader, +0x40 = setGeometryShader, +0x3c = getPixelShader)
  iVar1 = (**(code **)(*this + 0x48))();  // getVertexShader
  (**(code **)(*this + 0x54))();          // setPixelShader
  (**(code **)(*this + 0x44))();          // setVertexShader
  (**(code **)(*this + 0x40))();          // setGeometryShader
  iVar2 = (**(code **)(*this + 0x3c))();  // getPixelShader
  if (iVar2 != 0) {
    iVar2 = FUN_0060a380();  // likely createShaderParameterBlock
    this[4] = iVar2;  // +0x10: pixelShaderParams
  }
  if (iVar1 != 0) {
    iVar1 = FUN_0060a2e0(iVar1);  // likely getShaderParameters
    this[5] = iVar1;  // +0x14: vertexShaderParams
  }
  FUN_006127d0();  // likely resetShaderState
  this[0x41] = this[5];  // +0x104: currentVertexParams = vertexShaderParams
  uVar3 = (**(code **)(*this + 0x4c))();  // getGeometryShader
  iVar1 = FUN_0060a2e0(uVar3);
  this[0x42] = iVar1;  // +0x108: geometryShaderParams
  uVar3 = (**(code **)(*this + 0x50))();  // getHullShader
  iVar1 = FUN_0060a2e0(uVar3);
  this[0x43] = iVar1;  // +0x10c: hullShaderParams
  
  // Look up texture coordinate parameters
  iVar1 = FUN_0060a580(this[4], "transU");  // findParameterByName
  this[0x2a] = iVar1;  // +0xa8: transUParam
  iVar1 = FUN_0060a580(this[4], "transV");
  this[0x2b] = iVar1;  // +0xac: transVParam
  
  // Initialize texture parameter arrays for 3 texture stages
  piVar4 = this + 0x2c;  // +0xb0: textureParams[0]
  *piVar4 = this[0x41];  // currentVertexParams
  this[0x2f] = this[0x42];  // +0xbc: textureParams[1].shaderParams = geometryShaderParams
  this[0x32] = this[0x43];  // +0xc8: textureParams[2].shaderParams = hullShaderParams
  
  iVar1 = 3;
  do {
    iVar2 = FUN_0060a580(*piVar4, "apttexture");  // find texture parameter
    piVar4[1] = iVar2;  // +0x4: aptTextureParam
    iVar2 = FUN_0060a580(*piVar4, "kDelta");  // find delta parameter
    piVar4[2] = iVar2;  // +0x8: kDeltaParam
    piVar4 = piVar4 + 3;  // move to next texture stage (0x0c stride)
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  
  this[0x44] = 0;  // +0x110: someFlag = false
  return;
}