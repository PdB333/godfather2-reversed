// FUNC_NAME: setTextureBlendOperation (0x005dc6e0)
// Called from Presentation layer to configure texture blend/replace operation.
// This function expects a pointer to 8 floats (blendInfo) that define blend parameters.
// blendInfo[7] determines mode: 0.0 = COMBINE, non-zero = REPLACE.
// It retrieves a texture name from the blendManager (+0x2a0) and calls the render system.

undefined4 __fastcall setTextureBlendOperation(float *blendInfo)
{
    undefined4 in_EAX; // passed via EAX? Unused except as argument to getBlendManager
    int blendManager;
    const char *baseTextureName;
    undefined4 resultHandle;
    char *blendMode;
    char outputBuffer[39];

    // Get blend manager instance
    blendManager = getBlendManager(in_EAX);
    if (blendManager != 0) {
        // Determine blend mode string: "COMBINE" (default) or "REPLACE"
        if (blendInfo[7] != 0.0f) {
            blendMode = "REPLACE";
        } else {
            blendMode = "COMBINE";
        }

        // Flush or prepare render state before setting blend
        flushRenderCommands();

        // Get base texture name from manager
        baseTextureName = *(const char **)(blendManager + 0x2a0);
        if (baseTextureName == (const char *)0x0) {
            baseTextureName = &DAT_0120546e; // default fallback texture name
        }

        // Set the blend with parameters: baseTextureName, position x,y, size? and mode
        setBlendParameters(baseTextureName,
                          (double)*blendInfo,          // param0: x position?
                          (double)blendInfo[1],        // param1: y position?
                          (double)blendInfo[3],        // param3: width?
                          (double)blendInfo[4],        // param4: height?
                          (double)blendInfo[5],        // param5: ?
                          (double)blendInfo[6],        // param6: ?
                          blendMode,
                          outputBuffer);               // output buffer (possibly unused)

        // Finalize and return handle
        resultHandle = getBlendResultHandle();
        return resultHandle;
    }
    return 0;
}