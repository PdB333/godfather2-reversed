// FUNC_NAME: Effect::reinitScreenDimensions
void __thiscall Effect::reinitScreenDimensions(void)
{
    float screenScale;

    // Update global screen dimension globals? (resets aspect ratio references)
    updateScreenGlobals();

    // Fetch global screen width/height (presumably from globals updated above)
    screenScale = g_screenWidthFloat;
    this->screenWidthNorm = g_screenWidthFloat / (float)g_screenWidthDivisor;   // +0x1a4
    this->screenHeightNorm = screenScale / (float)g_screenHeightDivisor;        // +0x1a8

    // Release any existing per‑effect resources (e.g., textures, buffers)
    if (this->pEffectA != NULL) {       // +0xa4
        releaseEffectResource();
    }
    if (this->pEffectB != NULL) {       // +0xa8
        releaseEffectResource();
    }

    // Re‑initialize effect sub‑objects with new screen dimensions
    if (this->pEffectC != NULL) {       // +0xac
        initEffectType1(this->contextId, this->pEffectC, &this->effectCData);   // +0x14, +0xac, +0xb0
    }
    if (this->pEffectD != NULL) {       // +0xc0
        initEffectType2(this->contextId, this->pEffectD, &this->effectDData);   // +0x14, +0xc0, +0xd0
    }
    if (this->pEffectE != NULL) {       // +0xe0
        initEffectType2(this->contextId, this->pEffectE, &this->effectEData);   // +0x14, +0xe0, +0xf0
    }
    if (this->pEffectF != NULL) {       // +0x100
        initEffectType3(this->contextId, this->pEffectF, &this->effectFData);   // +0x14, +0x100, +0x110
    }
    if (this->pEffectG != NULL) {       // +0x150
        initEffectType3(this->contextId, this->pEffectG, &this->effectGData);   // +0x14, +0x150, +0x160
    }
    if (this->pScreenEffect != NULL) {   // +0x1a0
        initFullScreenEffect(this->contextId, this->pScreenEffect, &this->screenWidthNorm); // +0x14, +0x1a0, +0x1a4
    }
    if (this->pAudioEffect != NULL) {    // +0x1ac
        initAudioEffect(this->contextId, this->pAudioEffect, this->audioEffectParam); // +0x14, +0x1ac, +0x1b0
    }
}