// FUNC_NAME: BoxLightEffect::initialize
void __thiscall BoxLightEffect::initialize(BoxLightEffect *this)
{
  uint shaderHandle;
  
  // Store self-pointer at +0x1e0 (likely for internal callbacks)
  *(int *)(this + 0x1e0) = (int)this;
  
  // Get the shader system instance from a global singleton
  shaderHandle = getShaderManager(&PTR_DAT_0110a16c);
  *(uint *)(this + 0x14) = shaderHandle;  // +0x14: shader manager handle
  
  // Internal setup (e.g., enable shader passes, set render state)
  beginBoxLightPass();
  
  // Resolve shader constant handles from the shader manager
  *(uint *)(this + 0x1e4) = getShaderConstantHandle(*(uint *)(this + 0x14), "g_boxLightInvMtx");   // +0x1e4
  *(uint *)(this + 0x230) = getShaderConstantHandle(*(uint *)(this + 0x14), "g_boxLightFBScale");  // +0x230
  *(uint *)(this + 0x250) = getShaderConstantHandle(*(uint *)(this + 0x14), "g_boxLightFBOffset"); // +0x250
  
  // Additional internal setup (e.g., commit shader constants)
  endBoxLightPass();
  
  // Resolve global light direction parameter
  *(uint *)(this + 0x1c0) = getShaderConstantHandle(*(uint *)(this + 0x14), "g_lightDirection");   // +0x1c0
}