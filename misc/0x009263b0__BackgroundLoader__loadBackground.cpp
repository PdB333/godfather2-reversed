// FUNC_NAME: BackgroundLoader::loadBackground
void __thiscall BackgroundLoader::loadBackground(BackgroundLoader *this, int param_2)
{
    char cVar1;
    char *keyString;
    int inputManager;
    int renderManager;
    uint someFlag;
    char *pcVar6;
    int textureHandle;

    if (param_2 != 0) {
        inputManager = getGlobalInputManager(DAT_01131040);  // FUN_0043b870: returns InputManager*
        renderManager = getGlobalRenderManager();             // FUN_007351c0: returns RenderManager*
        if ((inputManager != 0) && (renderManager != 0)) {
            // Extract some flags from inputManager at offset 0x44, mask lower 2 bits
            this->inputFlag = *(byte *)(inputManager + 0x44) & 0xfc;   // +0x58 (0x16*4)
            // Store renderManager's background handle at offset 0x50
            this->renderHandle = *(int *)(renderManager + 0xc4);       // +0x50 (0x14*4)
            someFlag = getSomeRenderFlag();                             // FUN_00790150
            this->renderFlag = someFlag & 0xff;                         // +0x5C (0x17*4)

            keyString = PTR_s__background_00e56524;                     // "background"
            // Compute length of key string
            pcVar6 = keyString;
            do {
                cVar1 = *pcVar6;
                pcVar6 = pcVar6 + 1;
            } while (cVar1 != '\0');
            int stringLength = (int)pcVar6 - (int)(keyString + 1);     // length -1? Actually (pcVar6 - (keyString+1)) gives strlen-1? They subtract offset of first char? Wait: (int)(pcVar6) - (int)(keyString+1) = strlen - 1. But it's used as length parameter.

            // Load background texture via render manager, store result in this->textureHandle
            this->textureHandle = loadTextureFromKey(this->renderHandle, keyString, stringLength);  // FUN_004db3a0
            // Call virtual function at vtable+0x28 (e.g., applyBackground)
            (this->vtable[0x28])(this);
        }
    }
    return;
}