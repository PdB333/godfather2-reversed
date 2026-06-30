// FUNC_NAME: ViewportManager::setupRect
// Function address: 0x004EF520
// Role: Sets up a screen-space rectangle for rendering, handling clipping, texture selection, and vertex data based on mode.

void ViewportManager::setupRect(void* thisPtr, float x1, float y1, float x2, float y2,
                                DepthObject* depthObj, uint mode, bool useTexture,
                                float uvLeft, float uvRight, float uvTop, float uvBottom)
{
    // Check if depth test should abort
    if (depthObj->zValue <= gZFar && gZFar != depthObj->zValue) {
        return;
    }

    // Compute screen-space coordinates from world space using camera/zoom globals
    float right   = ((gCameraX + x2) * gScaleX * gZoomFactor) - gScreenCenterX;
    float left    = ((gCameraX + x1) * gScaleX * gZoomFactor) - gScreenCenterX;
    float top     = gScreenCenterY - ((gCameraY + y1) * gScaleY * gZoomFactor);
    float bottom  = gScreenCenterY - ((gCameraY + y2) * gScaleY * gZoomFactor);

    // Set clipping bounds (min/max X values)
    setClippingBounds(0x16, 0x16);
    gDrawFlags[0] = 1;
    setClippingBounds(7, 7);
    gDrawFlags[1] = 0;
    setClippingBounds(0x19, 0x19);
    gDrawFlags[2] = 5;
    setClippingBounds(0x18, 0x18);
    gDrawFlags[3] = 1;
    setClippingBounds(0x0F, 0x0F);
    gDrawFlags[4] = 1;
    setClippingBounds(0x1B, 0x1B);
    gDrawFlags[5] = 1;

    uint stateA, stateB, stateC;
    switch (mode) {
        case 0:
            stateA = 2;
            stateB = 5;
            break;
        case 1:
            stateA = 6;
            stateB = 5;
            break;
        case 2:
            stateA = 2;
            stateB = 5;
            stateC = 3;
            goto applyState;
        case 3:
        default:
            stateA = 1;
            stateB = 2;
            break;
        case 4:
            stateA = 1;
            stateB = 9;
            break;
        case 5:
            stateA = 2;
            stateB = 9;
            break;
        case 6:
            setBlendMode(9, 1, 1, 1, 2);
            goto skipStateSetup;
        case 7:
            setBlendMode(9, 1, 1, 2, 1);
            goto skipStateSetup;
    }
    stateC = 1;
applyState:
    setRenderState(stateC, stateB, stateA);
skipStateSetup:

    if (!useTexture) {
        // Simple quad (no texture)
        gCurrentTexture = gDefaultTextureA;
        gSecondaryTexture = gDefaultTextureB;
        gTextureLayerCount = 0;
        if (gCurrentRenderTarget == &gBuiltinRenderTarget) {
            releaseTexture(gDefaultTextureA);
            releaseTexture(gSecondaryTexture);
        }
        resetRenderState();
        clearBuffer();

        float* vertices = (float*)allocateMemory(5, 4, 0, 1, 0);
        if (vertices == nullptr) goto cleanup;

        // Set four vertices (two triangles forming quad)
        vertices[0] = left;    // Vertex 0 x
        vertices[4] = left;   // Vertex 2 x (in some layout)
        vertices[1] = top;    // Vertex 0 y
        vertices[2] = right;  // Vertex 1 x
        vertices[3] = top;    // Vertex 1 y
        vertices[5] = bottom; // Vertex 3 y? Actually index 5 is bottom
        vertices[6] = right;  // Vertex 2 x? (duplicate)
        vertices[7] = bottom; // Vertex 3 y? (duplicate)
    }
    else {
        // Textured quad (uses UV coordinates)
        gCurrentTexture = gTexturedTextureA;
        gSecondaryTexture = gTexturedTextureB;
        gTextureLayerCount = 3;
        if (gCurrentRenderTarget == &gBuiltinRenderTarget) {
            releaseTexture(gTexturedTextureA);
            releaseTexture(gSecondaryTexture);
        }
        setTextureState();
        resetRenderState();
        clearBuffer();

        float* vertices = (float*)allocateMemory(5, 4, 0, 1, 0);
        if (vertices == nullptr) goto cleanup;

        // Set 8 vertices for a textured quad (likely 2 triangles with explicit UVs)
        // Order: x,y for each of 4 corners, then uv for each corner? Actually indices up to 0xF = 16 floats.
        // This fills positions and UV coordinates in an interleaved or separate buffer.
        vertices[1]  = top;
        vertices[2]  = uvLeft;
        vertices[3]  = uvTop;
        vertices[5]  = top;
        vertices[7]  = uvTop;
        vertices[10] = uvLeft;
        vertices[0]  = left;
        vertices[4]  = right;
        vertices[6]  = uvRight;
        vertices[8]  = left;
        vertices[9]  = bottom;
        vertices[11] = uvBottom;
        vertices[12] = right;
        vertices[13] = bottom;
        vertices[14] = uvRight;
        vertices[15] = uvBottom;
    }

    submitDrawCall();
cleanup:
    flipBuffers();
    resetStatePostDraw();
}