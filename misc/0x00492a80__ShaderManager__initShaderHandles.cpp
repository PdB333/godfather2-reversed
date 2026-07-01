// FUNC_NAME: ShaderManager::initShaderHandles
void __fastcall ShaderManager::initShaderHandles(void* this)
{
  int shaderProgram;
  int uniformLocation;
  
  // Get or create a shader program for rendering (probably a built-in shader)
  shaderProgram = ShaderManager::getBuiltInShader(&PTR_DAT_01109eec);
  *(int*)((char*)this + 0x14) = shaderProgram;
  
  // Initialize some global rendering state
  Renderer::initGlobalState();
  
  // If the standard shader program hasn't been created yet, create it now
  if (DAT_01205458 == 0) {
    DAT_01205458 = Renderer::createShaderProgram();          // +0x50: saved modelview-proj matrix pointer from this
    DAT_01205450 = *(int*)((char*)this + 0x50);              // Store ModelViewProj uniform location
    DAT_01205454 = Renderer::getUniformLocation(DAT_01205458, "ModelViewProj");
  }
  
  // Store the standard shader program handle
  *(int*)((char*)this + 0x10) = DAT_01205458;
  
  // Continue initialization (likely texture or other state)
  Renderer::initTextureState();
  
  // Cache uniform locations for lighting shader
  uniformLocation = Renderer::getUniformLocation(*(int*)((char*)this + 0x14), "g_lightDirection");
  *(int*)((char*)this + 0x1c0) = uniformLocation;
  
  uniformLocation = Renderer::getUniformLocation(DAT_01205458, "g_spotLightCoordScale");
  *(int*)((char*)this + 0x1e0) = uniformLocation;
}