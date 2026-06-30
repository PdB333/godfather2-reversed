// FUNC_NAME: RenderTarget::createDepthStencilBuffer

bool __thiscall RenderTarget::createDepthStencilBuffer(undefined4 *outDepthFormat, undefined4 *outStencilFormat)
{
    undefined2 unkWord1;
    undefined2 unkWord2;
    int textureType;
    int rendererType;
    int result;
    uint flags;
    uint depthFormat;
    uint sampleType;
    uint multiSampleCount;
    undefined4 *handlePtr;

    rendererType = g_rendererType;
    *outDepthFormat = 0;
    textureType = *(int *)(this + 0x8);
    depthFormat = *(uint *)(&depthFormatTable + textureType * 4);
    *outStencilFormat = 0x404; // D3DFMT_D24S8 or equivalent

    // Determine depth format based on renderer capabilities
    if (rendererType == 3) {
        if (textureType == 0x19) { // D3DFMT_D24S8? check
            depthFormat = 0x34324644; // 'DF24' (depth format)
            goto createSurface;
        }
    }
    else if ((*(uint *)(this + 0xc) & 0x3000000) != 0x1000000) {
        if (rendererType == 2) {
            if ((textureType == 0x19) || (textureType == 0x1a)) {
                depthFormat = 0x5a544e49; // 'INTZ' (Intel depth format)
                goto createSurface;
            }
        }
        else if ((rendererType == 1) && ((textureType == 0x19) || (textureType == 0x1a))) {
            depthFormat = 0x5a574152; // 'RAWZ' (AMD depth format)
            goto createSurface;
        }
    }

    if (depthFormat == 0) {
        return false;
    }

createSurface:
    flags = *(uint *)(this + 0xc);
    multiSampleCount = 0;
    *(int *)(this + 0x30) = 1; // default multisample type
    if ((flags & 8) != 0) {
        *(int *)(this + 0x30) = 0; // no multisampling
        if ((((textureType == 0x18) || (textureType == 0x19) || (textureType == 0x1a)) ||
             ((textureType == 0x1b) || (textureType == 0x1c) || (textureType == 0x1d))) {
            multiSampleCount = 2;
        }
        else {
            multiSampleCount = 1;
        }
    }
    if ((flags & 0x200) != 0) {
        *(int *)(this + 0x30) = 2; // different multisample mode
        *outStencilFormat = 4; // override stencil format
    }

    handlePtr = (undefined4 *)(this + 0x14);
    *(int *)(this + 0x18) = 0;
    *handlePtr = 0;

    if ((flags & 2) == 0) {
        if ((flags & 4) == 0) {
            // Standard depth-stencil creation
            if ((((multiSampleCount & 2) == 0) || (rendererType == 1)) ||
                ((rendererType == 2 || (depthFormat == 0x34324644)))) {
                // Use vtable[0x5c] - CreateDepthStencilSurface
                undefined4 sampleType = *(uint *)(this + 0x30);
                uint byteVal = *(byte *)(this + 1);
                undefined2 word1 = *(undefined2 *)(this + 2);
                undefined2 word2 = *(undefined2 *)(this + 4);
                result = ((pfnCreateDepthStencilSurface)(g_pDevice->vtable[0x5c]))
                         (g_pDevice,
                          word1, word2,                     // width, height?
                          byteVal,                          // format?
                          multiSampleCount,
                          0,                                 // unused
                          sampleType,
                          handlePtr,
                          0);
            }
            else {
                // Use vtable[0x74] - alternative creation
                undefined4 sampleType = 1;
                multiSampleCount = 0;
                undefined2 word1 = *(undefined2 *)(this + 2);
                undefined2 word2 = *(undefined2 *)(this + 4);
                result = ((pfnCreateDepthStencilAlt)(g_pDevice->vtable[0x74]))
                         (g_pDevice,
                          word1, word2,
                          depthFormat,
                          0,
                          0,
                          sampleType,
                          (undefined4 *)(this + 0x18),
                          0);
            }
        }
        else {
            // Use vtable[0x60] - creation with flags
            result = ((pfnCreateDepthStencilWithFlags)(g_pDevice->vtable[0x60]))
                     (g_pDevice,
                      *(undefined2 *)(this + 2),
                      *(undefined2 *)(this + 4),
                      *(byte *)(this + 1),
                      1,
                      multiSampleCount,
                      depthFormat,
                      *(undefined4 *)(this + 0x30), // sampleType
                      handlePtr,
                      0);
        }
    }
    else {
        // Use vtable[0x64] - creation with different parameters
        result = ((pfnCreateDepthStencilSimple)(g_pDevice->vtable[0x64]))
                 (g_pDevice,
                  *(undefined2 *)(this + 2),
                  1,                                    // some mode
                  multiSampleCount,
                  depthFormat,
                  *(undefined4 *)(this + 0x30),
                  handlePtr,
                  0);
    }

    if (result == -0x7789fe84) {
        // Handle error - call error handler
        ((void (*)(int))PTR_g_errorHandler)(2);
    }
    return result == 0;
}