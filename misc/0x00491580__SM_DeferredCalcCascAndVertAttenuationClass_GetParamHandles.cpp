// Xbox PDB: SM_DeferredCalcCascAndVertAttenuationClass::GetParamHandles
// FUNC_NAME: ShadowEffect::initShaderHandles
void ShadowEffect::initShaderHandles(void)
{
  // Call base initialization (probably sets up effect interface)
  baseInit();

  // Retrieve shader parameter handles via name lookup
  undefined4 hSampler = getShaderParameterHandle(*(undefined4 *)(this + 0x14), "g_2ndShadowSampler");
  *(undefined4 *)(this + 0x2D0) = hSampler;                         // m_hShadowSampler2

  hSampler = getShaderParameterHandle(*(undefined4 *)(this + 0x14), "g_view_to_2nd_shadow");
  *(undefined4 *)(this + 0x2D8) = hSampler;                         // m_hViewTo2ndShadow

  hSampler = getShaderParameterHandle(*(undefined4 *)(this + 0x14), "g_2ndAnd3rdShadowTextureSize");
  *(undefined4 *)(this + 0x320) = hSampler;                         // m_hShadowTextureSize

  hSampler = getShaderParameterHandle(*(undefined4 *)(this + 0x14), "g_CascadedShadowFadeControl");
  *(undefined4 *)(this + 0x340) = hSampler;                         // m_hCascadedShadowFadeControl

  hSampler = getShaderParameterHandle(*(undefined4 *)(this + 0x14), "g_stencilBuffer");
  *(undefined4 *)(this + 0x344) = hSampler;                         // m_hStencilBuffer

  hSampler = getShaderParameterHandle(*(undefined4 *)(this + 0x14), "g_stencilBufferHalfPixelOffset");
  *(undefined4 *)(this + 0x34C) = hSampler;                         // m_hStencilBufferHalfPixelOffset

  // Store a global stencil buffer value
  *(undefined4 *)(this + 0x348) = DAT_0120535c;                    // m_fStencilBufferValue (global constant)
  return;
}