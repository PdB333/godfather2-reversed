// FUNC_NAME: PlayerEffectManager::Update

void PlayerEffectManager::Update()
{
    // Call FUN_005379d0 with effect parameters from this object
    SetEffectParameter(this->m_effectID1, this->m_effectID2);  // off +0x64 and +0x68

    // Determine input manager based on global flag
    int iManager;
    if (g_bUseSecondaryInput == 0)  // DAT_0121b638
    {
        iManager = *(int *)(g_pPrimaryInputManager + 0x20);  // DAT_0121b63c
    }
    else
    {
        iManager = *(int *)(g_pSecondaryInputManager + 0x18);  // DAT_0121b638
    }

    // If manager exists, apply feedback effect
    if (iManager != 0)
    {
        ApplyFeedbackEffect(g_pRenderSystem, iManager, &s_feedbackParam);  // FUN_0060b020
    }

    // Call virtual function on Presentation object
    // vtable offset 0x08: likely SetBackgroundClearMode or similar
    Presentation* pPres = g_pPresentation;  // DAT_0121b0a4
    (pPres->vtable[2])  // offset 8 in vtable = index 2 (8/4)
    (
        this->m_someParam,                        // +0x58
        this->m_pSubObject->m_clearFlag          // +0x10 + 0x61 (byte)
    );

    // Compute scaled color from global scale factor and ambient color table
    float fScale = g_fTimeScale;  // DAT_00e2b04c
    float fColor[4];
    fColor[0] = fScale * g_ambientColor[0];  // DAT_012233a4 + 0x40
    fColor[1] = fScale * g_ambientColor[1];  // +0x44
    fColor[2] = fScale * g_ambientColor[2];  // +0x48
    fColor[3] = fScale * g_ambientColor[3];  // +0x4c

    // Set lighting parameters for thread-local render context
    int renderCtx = **(int**)(*(int*)(_fs_base + 0x2c) + 8);  // FS segment -> TLS
    SetLightParameters(
        renderCtx + 0x50 + this->m_renderOffset,   // +0x08
        this->m_pSubObject + 0x70,                 // +0x10 + 0x70
        &fColor                                    // stack array
    );

    // Store a value from sub-object (possibly unused)
    int subValue = *(int*)(this->m_pSubObject + 0x6c);

    // Set ambient color for this sub-object
    SetAmbientColor(
        *(int*)(this->m_pSubObject + 0x64),        // +0x10 + 0x64
        &fColor
    );

    return;
}