// Xbox PDB: SM_Shader_Base::LoadBaseParams
// FUNC_NAME: Effect::resolveShaderConstants
void Effect::resolveShaderConstants(void)
{
  // this = unaff_ESI
  // this[4] = vertexShaderEffect (ID3DXEffect*)
  // this[5] = pixelShaderEffect (ID3DXEffect*)
  // FUN_0060a580 is Effect::GetParameterByName (returns handle)

  if (this->vertexShaderEffect != NULL) {
    this->hLightMatrix = this->vertexShaderEffect->GetParameterByName(NULL, "LightMatrix");               // +0x6
    this->hWorldEyePositionVS = this->vertexShaderEffect->GetParameterByName(NULL, "g_WorldEyePosition"); // +0x7
    this->hLightWVPTex = this->vertexShaderEffect->GetParameterByName(NULL, "matLightWVPTex");            // +0x8
    this->hZeroHalfTwoOne = this->vertexShaderEffect->GetParameterByName(NULL, "ZeroHalfTwoOne");         // +0x9
    this->hFogParamsVS = this->vertexShaderEffect->GetParameterByName(NULL, "fog_params");                // +0x23 (0x8C offset)
    this->hModel = this->vertexShaderEffect->GetParameterByName(NULL, "Model");                           // +0xA
    this->hModelRot = this->vertexShaderEffect->GetParameterByName(NULL, "ModelRot");                     // +0xB
    this->hModelView = this->vertexShaderEffect->GetParameterByName(NULL, "ModelView");                   // +0xC (approximation, original uses DAT_00e40b90 which is "ModelView" likely)
    this->hViewRot = this->vertexShaderEffect->GetParameterByName(NULL, "ViewRot");                       // +0xD
    this->hInvViewRot = this->vertexShaderEffect->GetParameterByName(NULL, "InvViewRot");                 // +0xE
    this->hInvModelView = this->vertexShaderEffect->GetParameterByName(NULL, "InvModelView");             // +0xF (DAT_00e40bac is "InvModelView")
    this->hModelView = this->vertexShaderEffect->GetParameterByName(NULL, "ModelView");                   // +0x10
    this->hModelViewRot = this->vertexShaderEffect->GetParameterByName(NULL, "ModelViewRot");             // +0x11
    this->hViewProj = this->vertexShaderEffect->GetParameterByName(NULL, "ViewProj");                     // +0x12
    this->hInvModelView = this->vertexShaderEffect->GetParameterByName(NULL, "InvModelView");             // +0x13
    this->hModelViewProj = this->vertexShaderEffect->GetParameterByName(NULL, "ModelViewProj");           // +0x14
    this->hOrientation = this->vertexShaderEffect->GetParameterByName(NULL, "Orientation");               // +0x15
    this->hTranslation = this->vertexShaderEffect->GetParameterByName(NULL, "Translation");               // +0x16
    this->hTranslationViewProj = this->vertexShaderEffect->GetParameterByName(NULL, "TranslationViewProj"); // +0x17
    this->hBlendMatricesVS = this->vertexShaderEffect->GetParameterByName(NULL, "g_BlendMatrices");        // +0x1A
    this->hPosScaleTranslationVS = this->vertexShaderEffect->GetParameterByName(NULL, "vPosScaleTranslationVS"); // +0x19
  }

  if (this->pixelShaderEffect != NULL) {
    this->hWorldEyePositionPS = this->pixelShaderEffect->GetParameterByName(NULL, "g_WorldEyePosition"); // +0x1B
    this->hAmbientColor = this->pixelShaderEffect->GetParameterByName(NULL, "g_AmbientColor");            // +0x1C
    this->hTint = this->pixelShaderEffect->GetParameterByName(NULL, "g_Tint");                            // +0x1D
    this->hFogColor = this->pixelShaderEffect->GetParameterByName(NULL, "fog_color");                      // +0x24
    this->hGamma = this->pixelShaderEffect->GetParameterByName(NULL, "cGamma");                           // +0x1E
    this->hModelViewPS = this->pixelShaderEffect->GetParameterByName(NULL, "ModelView");                  // +0x1F
    this->hViewRotPS = this->pixelShaderEffect->GetParameterByName(NULL, "ViewRot");                      // +0x20
    this->hInvViewRotPS = this->pixelShaderEffect->GetParameterByName(NULL, "InvViewRot");                // +0x21
    this->hDepthBias = this->pixelShaderEffect->GetParameterByName(NULL, "g_depthBias");                   // +0x25
    this->hDeferredLightingSampler = this->pixelShaderEffect->GetParameterByName(NULL, "g_DeferredLightingSampler"); // +0x28
    this->hPosScaleTranslationPS = this->pixelShaderEffect->GetParameterByName(NULL, "vPosScaleTranslation"); // +0x18

    // Call virtual method at vtable offset 0x34 (index 13) - e.g., CommitChanges
    this->pixelShaderEffect->CommitChanges();

    // If we have a deferred lighting texture (this[0x26])
    if (this->deferredLightingTexture != NULL) {
      // vtable offset 4 (index 1): SetTexture
      this->pixelShaderEffect->SetTexture(this->hDeferredLightingSampler, this->deferredLightingTexture);
      // vtable offset 0x14 (index 5): GetTechnique or similar, store result
      this->someTechnique = this->pixelShaderEffect->GetTechnique(0);
    }
  }
}