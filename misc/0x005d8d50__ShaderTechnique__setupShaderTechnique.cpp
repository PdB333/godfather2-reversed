// FUNC_NAME: ShaderTechnique::setupShaderTechnique
void __thiscall ShaderTechnique::setupShaderTechnique(ShaderTechnique *this)
{
  int textureSetHandle;
  int firstTextureHandle;
  int secondTextureHandle;
  int thirdTextureHandle;
  int *currentPassPtr;
  
  // Get various textures/objects from virtual functions
  textureSetHandle = (**(code **)(*(int *)this + 0x48))();  // vtable+0x48: get texture set
  (**(code **)(*(int *)this + 0x54))();                      // vtable+0x54: unknown (release/set)
  (**(code **)(*(int *)this + 0x44))();                      // vtable+0x44: unknown
  (**(code **)(*(int *)this + 0x40))();                      // vtable+0x40: unknown
  int baseTextureId = (**(code **)(*(int *)this + 0x3c))();  // vtable+0x3c: get base texture ID
  
  if (baseTextureId != 0) {
    int newTextureId = FUN_0060a380();                      // Create or allocate texture resource
    this->field_0x10 = newTextureId;                        // store at offset 0x10
  }
  if (textureSetHandle != 0) {
    int dupTextureSet = FUN_0060a2e0(textureSetHandle);     // Duplicate or obtain reference
    this->field_0x14 = dupTextureSet;                       // store at offset 0x14
  }
  
  FUN_006127d0();                                           // Unknown reset/state function
  
  // Assign three texture handles from virtual calls
  this->field_0x104 = this->field_0x14;                     // copy from field_0x14
  int texA = (**(code **)(*(int *)this + 0x4c))();          // vtable+0x4c: get texture A
  this->field_0x108 = FUN_0060a2e0(texA);                  // duplicate
  int texB = (**(code **)(*(int *)this + 0x50))();          // vtable+0x50: get texture B
  this->field_0x10C = FUN_0060a2e0(texB);                  // duplicate
  
  // Look up shader parameters by name
  this->field_0xA8 = FUN_0060a580(this->field_0x10, "transU");   // parameter index for transU
  this->field_0xAC = FUN_0060a580(this->field_0x10, "transV");   // parameter index for transV
  
  // Initialize three pass structures
  currentPassPtr = &this->field_0xB0;                       // base of first pass struct
  *currentPassPtr = this->field_0x104;                      // first texture handle
  this->field_0xBC = this->field_0x108;                     // second texture handle (at offset 0xBC)
  this->field_0xC0? Actually need to check: param_1[0x2f] is at offset 0x2f*4 = 0xBC, yes.
  And param_1[0x32] at 0x32*4 = 0xC8, which is third texture handle.
  It seems each "pass" struct is 3 ints: texture handle, then two parameters.
  But the loop increments piVar4 by 3 (12 bytes) each iteration.
  So we have three structs at offsets: 0xB0, 0xBC, 0xC8.
  Each struct: [0] = texture handle, [1] = apttexture param index, [2] = kDelta param index.
  The code sets the texture handles first, then loops to fill the other two fields.
  Let's represent as an array of structs.
  
  // Declare struct for a pass
  struct PassInfo {
    int textureHandle;
    int apttextureParam;
    int kDeltaParam;
  };
  
  PassInfo *passes = (PassInfo *)&this->field_0xB0;
  passes[0].textureHandle = this->field_0x104;
  passes[1].textureHandle = this->field_0x108; // Actually this is at field_0xBC? But we need to set passes[1].textureHandle. The code does param_1[0x2f] = param_1[0x42]; which is at offset 0xBC. So passes[1].textureHandle = texture second handle.
  passes[2].textureHandle = this->field_0x10C;
  
  // Now loop three times to fill param indices for each pass
  int i = 3;
  do {
    passes[0].apttextureParam = FUN_0060a580(passes[0].textureHandle, "apttexture");
    passes[0].kDeltaParam = FUN_0060a580(passes[0].textureHandle, "kDelta");
    passes++;
    i--;
  } while (i != 0);
  
  this->field_0x110 = 0;       // offset 0x44 * 4 = 0x110, set to 0
}
// Additional comments: field offsets relative to 'this' (int* base):
// +0x10 : texture set handle
// +0x14 : duplicate texture set
// +0xA8 : transU parameter index
// +0xAC : transV parameter index
// +0xB0 : first pass structure (texture handle, apttexture param, kDelta param)
// +0xBC : second pass structure
// +0xC8 : third pass structure
// +0x104: first pass texture (duplicate of +0x14)
// +0x108: second pass texture
// +0x10C: third pass texture
// +0x110: some flag (set to 0)