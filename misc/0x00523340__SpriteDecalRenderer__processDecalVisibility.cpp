// FUNC_NAME: SpriteDecalRenderer::processDecalVisibility
// Address: 0x00523340
// Processes a list of decal/sprites, computes screen-space coordinates, and culls/includes them.
// Returns true if any decals are visible after processing.

#include <math.h>

bool SpriteDecalRenderer::processDecalVisibility() {
    // m_spriteArray at +0xf0, m_spriteCount at +0x450
    // Each sprite structure is 0x28 bytes, with header fields at negative offsets from the data pointer.

    int totalVisibleVertices = 0;
    int spriteIndex = 0;
    // m_spriteCount is a char, so max 255 sprites
    if (this->spriteCount <= 0) {
        return false;
    }

    float* spriteData = reinterpret_cast<float*>(this + 0xf0);
    float one = 1.0f;  // constant DAT_00e2b1a4

    do {
        // Fetch some global ID? or texture handle? - stored at +0x464
        unsigned int textureId = *(unsigned int*)(this + 0x464);

        // Reset per-sprite vertex counts
        *(short*)(spriteData - 0x14) = 0;  // vertexCount
        *(short*)((int)spriteData - 0x4e) = 0;  // miscCount

        int createdVerts = 0;
        bool shouldProcess = (*(int*)(this + 0x454) != 0) &&
                             (spriteData[-0x18] != 0.0f) &&
                             (spriteData[-0x18] != 5.60519e-45f) &&
                             (((*(unsigned char*)(this + 0x460) >> 2) & 1) == 0 || (spriteData[-0x13] != 0.0f));

        if (!shouldProcess) {
            // Skip this sprite
            spriteData[-0x16] = 0.0f;
            if (*(short*)(spriteData - 0x14) != 0) {
                void* buffer = this->allocateVertexBuffer();  // FUN_0051ec30
                spriteData[-0x16] = (float)(int)buffer;
                if (buffer == nullptr) {
                    *(short*)(spriteData - 0x14) = 0;
                    *(short*)((int)spriteData - 0x4e) = 0;
                    one = 1.0f;
                } else {
                    spriteData[-0x15] = (float)((int)buffer + *(short*)(spriteData - 0x14) * 0x20);
                    memcpy(buffer, localVertBuffer, *(short*)(spriteData - 0x14) * 0x20);
                    memcpy((void*)(int)spriteData[-0x15], &localNormalBuffer, (int)*(short*)((int)spriteData - 0x4e) << 4);
                    one = 1.0f;
                }
            }
            totalVisibleVertices += *(short*)(spriteData - 0x14);
            spriteIndex++;
            spriteData += 0x28; // 10 floats stride
            continue;
        }

        // Compute screen-space rectangle from world coordinates
        float worldRect[8];
        worldRect[0] = *(float*)(this + 0x1c) * 0.5f; // half width? from DAT_00e2cd54
        worldRect[1] = (*(float*)(this + 0x38) - *(float*)(this + 0x3c)) * worldRect[0];
        worldRect[0] = (*(float*)(this + 0x38) + *(float*)(this + 0x3c)) * worldRect[0];
        worldRect[4] = 1.0f - worldRect[1];
        float leftRight = 1.0f - worldRect[0];
        // Store sprite color/alpha
        float spriteColor[4];
        spriteColor[0] = spriteData[0xc]; // R
        spriteColor[1] = spriteData[0xd]; // G
        spriteColor[2] = spriteData[0xe]; // B
        spriteColor[3] = spriteData[0xf]; // A

        worldRect[2] = 0.0f;
        worldRect[6] = 0.0f;
        worldRect[3] = one;
        worldRect[5] = worldRect[0];
        worldRect[7] = one;
        float worldRectTop = worldRect[1];
        float worldRectLeft = worldRect[0];

        // Initialize some matrix/vectors
        float matrixStack[16];
        initMatrix(matrixStack); // FUN_0044c1a0

        // Get sprite world transform
        float spriteTransform[16];
        spriteTransform[0] = spriteData[8];
        spriteTransform[1] = spriteData[9];
        spriteTransform[2] = spriteData[10];
        spriteTransform[3] = spriteData[11];
        float posX = *(float*)(this + 0x24); // camera or object offset
        float posY = *(float*)(this + 0x20);
        int objectPtr = *(int*)(this + 0x10);
        float camX = posX + *(float*)(objectPtr + 0xb4);
        float camY = posY + *(float*)(objectPtr + 0xb0);

        float cornerA[2] = {posX, posX + *(float*)(objectPtr + 0xb4)};
        float cornerB[2] = {posY, posY + *(float*)(objectPtr + 0xb0)};

        // More setup
        float uv0[2], uv1[2], uv2[2], uv3[2];
        uv0[0] = worldRect[0]; uv0[1] = worldRect[1];
        uv1[0] = worldRect[4]; uv1[1] = worldRect[0];
        uv2[0] = worldRect[4]; uv2[1] = leftRight;
        uv3[0] = worldRect[1]; uv3[1] = leftRight;

        // Project position onto screen? (FUN_0056c640)
        float screenPos[4];
        getWorldToScreenTransform(spriteData, screenPos); // FUN_0056c640

        // Set up clipping bounds
        float minScreen = 1.0f; // constant from DAT_00e2b1a4
        float maxScreen = 0.0f; // will be updated

        // If the object has some flag (bit 0 of byte at +0x44)
        if ((*(unsigned char*)(objectPtr + 0x44) & 1) != 0) {
            // Get screen rect from something
            float screenRect[4];
            float targetRect[4];
            getScreenRect(textureId, &screenRect, &targetRect); // FUN_0056c040
            // Random noise? (FUN_00417560)
            applyRandomOffset(); // modifies some globals that are then read
            // Update corner positions with noise
            uv0[0] = localNoise0; uv0[1] = localNoise1;
            // etc. (complex noise application)
        }

        // Compute size scaling
        float invWidth = 1.0f / *(float*)(this + 0x1c);
        float scaleX = *(float*)(objectPtr + 0xb0) * invWidth;
        float scaleY = *(float*)(objectPtr + 0xb4) * invWidth;
        // Build an array of vertices
        float vertexBuffer[8]; // actually local_21d0 series
        vertexBuffer[0] = scaleX;
        vertexBuffer[1] = scaleY;
        vertexBuffer[2] = 0.0f; // unused
        vertexBuffer[3] = 0.0f;
        // etc.

        // Apply noise again
        applyRandomOffset();

        // Compute world space corner positions from object data
        float worldCornerX = *(float*)(objectPtr + 0xb0) * 0.5f + *(float*)(this + 0x20);
        float worldCornerY = *(float*)(objectPtr + 0xb4) * 0.5f + *(float*)(this + 0x24);

        // Get object velocity or rotation
        float speed = *(float*)(objectPtr + 0xa4);
        float bulletSpeed = speed * 2.0f; // constant DAT_00e44718
        // Compute transformed vertex positions
        float transVerts[4];
        transVerts[0] = bulletSpeed * spriteTransform[0] + spriteColor[0];
        transVerts[1] = bulletSpeed * spriteTransform[1] + spriteColor[1];
        transVerts[2] = bulletSpeed * spriteTransform[2] + spriteColor[2];
        transVerts[3] = bulletSpeed * spriteTransform[3] + spriteColor[3];

        float magSq = speed * speed;
        float distance = sqrt(magSq * 2.0f * magSq * 2.0f +
                              worldRect[1] * worldRect[1] +
                              worldRect[0] * worldRect[0]); // roughly distance

        // Flags for culling
        int cullFlag = (*(unsigned short*)(objectPtr + 0x44) >> 2) & 1;
        if (cullFlag || (*(unsigned char*)(this + 0x460) & 1) == 0) {
            cullFlag = 1;
        }

        // More complex processing: clipping, sorting, etc.
        // Calls to FUN_00b99e20 and FUN_005208e0 which are likely helper functions for clipping
        processClipping(..., &vertexCount); // FUN_00b99e20
        processScreenTransform(..., &vertexCount); // FUN_005208e0

        // If culling succeeded
        if (*(short*)(spriteData - 0x14) > 0) {
            // Allocate and copy vertex data
            void* vertexBuffer = allocateVertexBuffer(); // FUN_0051ec30
            spriteData[-0x16] = (float)(int)vertexBuffer;
            if (vertexBuffer) {
                spriteData[-0x15] = (float)((int)vertexBuffer + *(short*)(spriteData - 0x14) * 0x20);
                memcpy(vertexBuffer, localVertBuffer, *(short*)(spriteData - 0x14) * 0x20);
                memcpy((void*)(int)spriteData[-0x15], &localNormalBuffer, (int)*(short*)((int)spriteData - 0x4e) << 4);
                one = 1.0f;
            } else {
                // Clear counts
                *(short*)(spriteData - 0x14) = 0;
                *(short*)((int)spriteData - 0x4e) = 0;
                one = 1.0f;
            }
        }

        // Reset per-sprite state
        spriteData[-0x16] = 0.0f;
        if (*(short*)(spriteData - 0x14) != 0) {
            // ... allocate and copy (duplicate code, likely same as above)
        }

        totalVisibleVertices += *(short*)(spriteData - 0x14);
        spriteIndex++;
        spriteData += 0x28; // next sprite
    } while (spriteIndex < this->spriteCount);

    return totalVisibleVertices != 0;
}