// FUNC_NAME: UIRenderer::drawMultiPassSprite

int __thiscall UIRenderer::drawMultiPassSprite(
    RenderNode* node,
    BoneTransform* boneTransform,
    int renderPass,
    SpriteParams* spriteParams,
    int blendMode,
    int textureHandle
)
{
    bool bHasPassThroughState;
    byte stateByte;
    int deviceContextPtr;
    int localDevicePtr;
    int vertexBuffer;
    int vertexBufferOffset;
    int meshData;
    int subMeshIndex;
    int materialIndex;
    int curRenderTarget;
    int drawStatus1;
    int drawStatus2;
    float spriteZ;
    float spriteOffsetY;
    int pushCount;
    int finalColor;
    int alphaBlendResult;
    float spriteAlpha;

    // +0x0: this->device?
    // +0x4: this->renderer?
    if (this == 0 || node == 0 || renderPass == 0)
        return 0;

    // node->flags & 0xFF, possibly LOD index
    stateByte = *(byte*)(node + 4) & 0xFF;
    if (stateByte < 10)
        localDevicePtr = *(int*)(node + 0x24);
    else
        localDevicePtr = *(int*)(node + 0x2c);

    if (localDevicePtr == 0)
        return 0;

    // Check bone index match (boneTransform->boneIndex)
    if (stateByte > 8)
    {
        deviceContextPtr = getBoneIndex(); // FUN_005939c0
        if (deviceContextPtr != *(short*)(boneTransform + 0xb2))
            return 0;
    }

    // Get render device (this->device->surface?)
    deviceContextPtr = getRenderDevice(*(int*)(*(int*)(this + 4) + 4)); // FUN_0056f270
    vertexBufferOffset = (int)*(short*)(boneTransform + 0xb2);
    subMeshIndex = 0;
    vertexBuffer = 0;
    meshData = 0;

    // Get vertex buffer from device context
    byte status = getVertexBuffer(&subMeshIndex, &vertexBuffer, &meshData, deviceContextPtr + 0x14, boneTransform); // FUN_00593a40
    *(byte*)(deviceContextPtr + 0x10) = status;

    // Check current render pass kind
    int passKind = getRenderPassKind(); // FUN_0056ec50
    bHasPassThroughState = false;
    if ((passKind == 1 || passKind == 3 || passKind == 4) && (*(char*)(spriteParams + 1) == 0)) // spriteParams->noBlend?
    {
        bHasPassThroughState = true;
    }

    spriteZ = *spriteParams; // spriteParams->z
    curRenderTarget = getCurrentRenderTarget(); // FUN_0056fdd0
    float spriteZCopy = spriteZ;

    setMaterial(vertexBuffer, vertexBufferOffset); // FUN_0056df50

    int globalShader = DAT_012234e8; // global shader handle
    drawStatus1 = beginDraw(); // FUN_0056e290

    if (drawStatus1 != 0)
    {
        // Error path: pop all states
        pushState();
        pushBlendState();
        pushDepthState();
        pushRasterState();
        popState();
        return curRenderTarget;
    }

    // Check if alpha equals global constant
    if (spriteParams[3] == DAT_00e2b05c)
    {
        pushState();
        setRenderTarget(meshData, curRenderTarget); // FUN_0056e310
        applyTexture(textureHandle); // FUN_00593bc0
        popState();
        return curRenderTarget;
    }

    int curRenderTarget2 = getCurrentRenderTarget(); // FUN_0056fdd0
    int curRenderTarget3 = getCurrentRenderTarget(); // FUN_0056fdd0
    float spriteOffsetX = (float)(int)spriteParams[1]; // spriteParams->offsetX
    spriteOffsetY = (float)(int)spriteParams[2]; // spriteParams->offsetY

    setMaterial(vertexBuffer, vertexBufferOffset);
    setMaterial(vertexBuffer, vertexBufferOffset);

    meshData = beginDraw(); // FUN_0056e290
    drawStatus2 = beginDraw(); // FUN_0056e290

    curRenderTarget = curRenderTarget;

    if (meshData == 0)
    {
        // First path: no mesh data
        if (drawStatus2 == 0)
        {
            if (bHasPassThroughState)
            {
                pushState();
                // Set up for pass-through rendering
                pushState();
                setRenderTarget(meshData, curRenderTarget); // FUN_0056e310 (set render target)
                applyTexture(textureHandle);
                goto end;
            }
            // Default branch
            setRenderTarget(&curRenderTarget, curRenderTarget2); // FUN_0056e310
            pushState();
            setRenderTarget(meshData, curRenderTarget);
            applyTexture(textureHandle);
            setRenderTarget(meshData, curRenderTarget3);
            pushState();
            setRenderTarget(meshData, curRenderTarget3);
            applyTexture(textureHandle);
            // Continue to second part
            {
                pushState();
                setRenderTarget(meshData, curRenderTarget);
                applyTexture(textureHandle);
                spriteAlpha = spriteParams[3];
            }
        }
        else
        {
            pushState();
            pushBlendState();
            pushDepthState();
            pushRasterState();
            setRenderTarget(&curRenderTarget, curRenderTarget2); // FUN_0056e310
            pushState();
            setRenderTarget(meshData, curRenderTarget);
            applyTexture(textureHandle);
            spriteAlpha = spriteParams[3];
        }
    }
    else
    {
        if (drawStatus2 == 0)
        {
            pushState();
            pushBlendState();
            pushDepthState();
            pushRasterState();
            setRenderTarget(meshData, curRenderTarget3);
            pushState();
            setRenderTarget(meshData, curRenderTarget3);
            applyTexture(textureHandle);
            spriteAlpha = spriteParams[3];
        }
        else
        {
            pushState();
            pushState();
            pushBlendState();
            pushBlendState();
            pushDepthState();
            pushDepthState();
            pushRasterState();
            pushRasterState();
            spriteAlpha = spriteParams[3];
        }
    }

    alphaBlendResult = computeFinalColor(spriteAlpha, blendMode); // FUN_005832d0

end:
    popState(); // FUN_0056fb60
    popState(); // FUN_0056fb60
    curRenderTarget = alphaBlendResult;
    popState(); // FUN_0056f1a0
    return curRenderTarget;
}