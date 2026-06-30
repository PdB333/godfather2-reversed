// FUNC_NAME: RenderManager::submitDrawCall

void RenderManager::submitDrawCall(int param_2, int param_3)
{
  char cVar1;
  int pProfile;
  undefined4 *pDestVertexBuffer;
  undefined4 *pSourceVertexArray;
  int unaff_FS_OFFSET;
  RenderState renderState;
  bool isInitialized;
  undefined4 local_50;
  undefined4 vertW1, vertW2, vertW3, vertW4;
  undefined4 vertW5, vertW6, vertW7, vertW8;
  
  pProfile = g_pAppSettings; // DAT_01205504
  RenderState_construct(&renderState, 0); // FUN_005334b0
  
  // Copy viewport/size from profile
  g_viewport[0] = *(undefined4 *)(pProfile + 0x10);
  g_viewport[1] = *(undefined4 *)(pProfile + 0x14);
  g_viewport[2] = *(undefined4 *)(pProfile + 0x18);
  g_viewport[3] = *(undefined4 *)(pProfile + 0x1c);
  
  // Set bloom render target if available
  if ((g_pBloomTexture == &g_nullBloom) && 
      (*(int *)(&g_bloomStates + (uint)g_currentBloomState * 0x30) != 0))
  {
    setBloomRenderTarget(g_bloomTextureHandle, 
                         *(int *)(&g_bloomStates + (uint)g_currentBloomState * 0x30),
                         pProfile + 0x10); // FUN_0060add0
  }
  
  // Clamp LOD/min quality levels
  if (g_minLod < 14) {
    g_minLod = 14;
  }
  if (14 < g_maxLod) {
    g_maxLod = 14;
  }
  
  g_someFlag = 0;
  cVar1 = *(char *)(*(int *)(pProfile + 0x24) + 0x2e); // may be 'renderMode'
  
  // Second clamp (to 27)
  if (g_minLod < 27) {
    g_minLod = 27;
  }
  if (26 < g_maxLod) {
    g_maxLod = 27;
  }
  
  g_useHDR = (uint)(cVar1 != 3); // DAT_011f3a44
  
  clearScreen(); // FUN_004ec7a0
  
  renderState = g_defaultTextureHandle; // DAT_00e2b1a4
  if (cVar1 == 1) {
    renderState = 0;
  }
  
  setViewport(1); // FUN_004eccc0
  
  // Check if current render target is not primary, switch if needed
  if ((undefined *)(*(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + 0x50 + *(int *)(pProfile + 8))
      != &g_primaryRenderTarget)
  {
    setRenderTarget(); // FUN_00417560
  }
  
  updateProjection(); // FUN_00535220
  enableScissorTest(0); // FUN_00534ff0
  
  if (!isInitialized) {
    setTexture(0, renderState); // FUN_00535450
    isInitialized = true;
  }
  
  pDestVertexBuffer = (undefined4 *)allocateVertexBuffer(0xD, param_3, 0, 1, 0); // FUN_0060cd00
  if (pDestVertexBuffer != nullptr) {
    // Process vertex/sprite data from param_2 (8 words per element)
    vertW1 = 0;
    vertW2 = 0;
    vertW3 = 0;
    vertW4 = 0;
    vertW5 = 0;
    vertW6 = g_defaultTextureHandle; // DAT_00e2b1a4
    if (0 < param_3) {
      pSourceVertexArray = (undefined4 *)(param_2 + 0x10);
      do {
        // Read 4 source values (positions? uv?)
        vertW1 = pSourceVertexArray[-4];
        vertW2 = pSourceVertexArray[-3];
        vertW3 = pSourceVertexArray[0];
        vertW4 = pSourceVertexArray[1];
        
        // Write 8-word vertex structure
        pDestVertexBuffer[0] = 0;
        pDestVertexBuffer[1] = vertW1;
        pDestVertexBuffer[2] = vertW2;
        pDestVertexBuffer[3] = g_defaultTextureHandle; // DAT_00e2b1a4
        pDestVertexBuffer[4] = vertW3;
        pDestVertexBuffer[5] = vertW4;
        pDestVertexBuffer[6] = 0;
        pDestVertexBuffer[7] = 0;
        
        pDestVertexBuffer += 8;
        pSourceVertexArray += 6;
        param_3--;
      } while (param_3 != 0);
    }
    local_50 = 0;
    submitDrawCall(); // FUN_0060cde0
  }
  
  RenderState_destruct(&renderState); // FUN_00533720
  return;
}