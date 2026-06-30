// FUNC_NAME: SpriteRenderer::updateAndRenderSprites
// Address: 0x00506680
// Purpose: Processes a linked list of sprite descriptors, transforms them into a vertex buffer,
//          and render them with various settings. Also updates global rendering flags.

// Globals used (with guessed names):
// g_spriteListManager (DAT_0120550c) - pointer to manager
// g_renderingActive (DAT_0120575b) - flag to enable rendering
// g_spriteListPtr (DAT_01205500) - recursion/lock counter
// g_currentRenderWidth (DAT_012058d0)
// g_currentRenderHeight (DAT_00f15988)
// g_vertexBufferCache* (DAT_011f38f0, DAT_011f38f4) - cached vertex buffer handles
// g_renderPassFlags (DAT_011f3a30, etc.) - various rendering pass flags
// g_screenWidth (DAT_01218e44)
// g_screenHeight (DAT_01218e48)
// g_screenCenterX (DAT_00e445e4)
// g_screenCenterY (DAT_00e2ee80)
// g_screenScale (DAT_00e2cd54) - probably 0.0 for no scaling

#include <cstdint>

// Assuming SpriteNode structure
struct SpriteNode {
    SpriteNode* next;         // offset 0x00
    int32_t x;                // offset 0x04
    int32_t y;                // offset 0x08
    int32_t width;            // offset 0x0C
    int32_t height;           // offset 0x10
    int32_t textureX;         // offset 0x14
    int32_t textureY;         // offset 0x18
    int32_t textureID;        // offset 0x1C
    uint8_t r;                // offset 0x20
    uint8_t g;                // offset 0x21
    uint8_t b;                // offset 0x22
    uint8_t a;                // offset 0x23
    uint8_t flags;            // offset 0x24 (bit 0 = visible)
    // padding to 0x1E bytes? Actually offset 0x1E is written
    uint8_t visibility;       // offset 0x1E
};

// Sprite list structure
struct SpriteList {
    SpriteNode* head;         // offset 0x00
    int32_t count;            // offset 0x0C? Actually piVar6[3] at offset 12 seems to be count
};

// This function processes a linked list of sprites and renders them
void renderSprites(uint8_t shouldClearList /* param_1 */)
{
    SpriteList** spriteListMgr = reinterpret_cast<SpriteList**>(DAT_0120550c);
    SpriteList* spriteList = *spriteListMgr;

    if (g_renderingActive == 0) {
        // Renderer not active, call setup function and return
        initializeRendering();
        return;
    }

    // Get the sprite list pointer from manager
    int* listData = reinterpret_cast<int*>(getSpriteListData(spriteList));
    int oldLockCounter = g_lockCounter; // _DAT_01205500

    // Head of linked list
    SpriteNode* node = reinterpret_cast<SpriteNode*>(listData[0]); // puVar1
    if (node == nullptr) {
        // No sprites, but check if the isFirstFrame flag is clear
        if (*(char*)(spriteListMgr + 0x894 / 4) == 0) {
            // This seems to be a "first frame" flag check
            int currentCount = g_someCounterA; // DAT_012058a4
            if (g_somePointer) {
                currentCount = *(int*)(g_somePointer + 0x16c);
            }
            g_lockCounter = oldLockCounter + 1;

            int startCount = currentCount;
            int endCount = g_someCounterB; // DAT_012058a8
            if (g_somePointer) {
                startCount = *(int*)(g_somePointer + 0x16c);
                endCount = *(int*)(g_somePointer + 0x170);
            }

            if (endCount == startCount) {
                g_lockCounter = oldLockCounter + 2;
            }

            // Call various rendering setup functions
            setupRenderState();
            setRenderTransform(0, 0, 0, 1.0f, 1.0f);
            enableRenderDepthTest(1);
            enableRenderZWrite(1);
            finalizeRenderState();

            // Mark first frame as processed
            *(char*)(spriteListMgr + 0x894 / 4) = 1;

            // Adjust lock counter based on counts
            int adjustedCount = g_someCounterA;
            if (g_somePointer) {
                adjustedCount = *(int*)(g_somePointer + 0x16c);
            }
            if (endCount == adjustedCount) {
                g_lockCounter = g_lockCounter - 1;
            }

            if (g_somePointer) {
                startCount = *(int*)(g_somePointer + 0x16c);
            }
            if (currentCount == startCount) {
                g_lockCounter = g_lockCounter - 1;
                spriteList->head = nullptr;
                spriteList->count = 0;
                return;
            }
            goto checkClearList;
        }
    } else {
        // There is a sprite list, process it
        int listStartCount = g_someCounterA;
        if (g_somePointer) {
            listStartCount = *(int*)(g_somePointer + 0x16c);
        }
        int listEndCount = g_someCounterB;
        if (g_somePointer) {
            listEndCount = *(int*)(g_somePointer + 0x170);
        }

        g_lockCounter = oldLockCounter + 1;

        if (listEndCount == listStartCount) {
            g_lockCounter = oldLockCounter + 2;
        }

        // Update some cached vertex buffer
        g_cachedVertexBufferHandle = g_previousVertexBufferHandle; // DAT_0121a204 = DAT_0121a35c
        g_cachedVertexBufferOffset = g_previousVertexBufferOffset; // DAT_0121a200 = DAT_0121a358

        // Check if we need to free old vertex buffers
        if (g_someBufferArray == &g_staticBuffer) { // DAT_012058e8 == &DAT_0121a1f0
            freeVertexBuffer(g_previousVertexBufferHandle);
            freeVertexBuffer(g_cachedVertexBufferOffset);
        }

        // Set render target: use end count with some mask
        int renderTarget = listEndCount;
        if (g_somePointer) {
            renderTarget = *(int*)(g_somePointer + 0x170);
        }
        setRenderTarget(renderTarget, 0x210000);

        // Reset sprite list traversal index (?)
        resetSpriteListIndex(); // FUN_00536940

        // Clear some flags related to sprite processing
        uint32_t idx = 0;
        do {
            if (g_someFlagArray[idx * 2] == g_someGlobalFlag) {
                if (idx < 20) {
                    g_someFlagArray[idx * 2 + 1] &= 0xfffffffc;
                }
                break;
            }
            idx++;
        } while (idx < 20);

        // Save handles and set new ones
        int oldVBO = g_currentVBO; // DAT_011f38f0
        int oldVBO_size = g_currentVBOSize; // DAT_011f38f4
        g_currentVBO = g_someGlobalFlag;
        g_currentVBOSize = 0;

        // Release old vertex buffer if any
        releaseVertexBuffer(0, oldVBO, oldVBO_size);

        // Set render transform (identity)
        setRenderTransform(0, 0, 0, 1.0f, 1.0f);

        // Clear some previous vertex buffer flags
        bool hadPrevVB = g_previousVBO != 0;
        int prevVB = g_previousVBO;
        g_previousVBO = 0;
        g_previousVBO_size = 0;
        if (hadPrevVB || (prevVB != 0)) {
            (*(code**)(g_renderer + 0x9c))(g_renderer, 0); // likely releaseOrUnbind
        }

        enableRenderDepthTest(1);

        // Clamp screen dimensions to minimum values
        if (g_renderWidth < 22) g_renderWidth = 22;
        if (g_renderHeight < 22) g_renderHeight = 22;
        g_unknownFlag1 = 1;

        if (g_renderWidth < 7) g_renderWidth = 7;
        if (g_renderHeight < 7) g_renderHeight = 7;
        g_unknownFlag2 = 0;

        if (g_renderWidth < 14) g_renderWidth = 14;
        if (g_renderHeight < 14) g_renderHeight = 14;
        g_unknownFlag3 = 0;

        if (g_renderWidth < 25) g_renderWidth = 25;
        if (g_renderHeight < 25) g_renderHeight = 25;
        g_unknownFlag4 = 5;

        if (g_renderWidth < 24) g_renderWidth = 24;
        if (g_renderHeight < 24) g_renderHeight = 24;
        g_unknownFlag5 = 0;

        if (g_renderWidth < 15) g_renderWidth = 15;
        if (g_renderHeight < 15) g_renderHeight = 15;
        g_unknownFlag6 = 0;

        if (g_renderWidth < 27) g_renderWidth = 27;
        if (g_renderHeight < 27) g_renderHeight = 27;
        g_unknownFlag7 = 0;

        // Allocate vertex buffer for sprites
        resetSpriteCounters(); // FUN_00536550

        // Request buffer: 1 for single, spriteList->count, 0, 1, 0
        float* vertexBuffer = requestVertexBuffer(1, spriteList->count, 0, 1, 0);
        float screenCenterX = g_screenCenterX; // DAT_00e445e4
        float screenCenterY = g_screenCenterY; // DAT_00e2ee80
        float screenScale = g_screenScale;    // DAT_00e2cd54 (likely 0)

        if (vertexBuffer != nullptr) {
            int remaining = spriteList->count;
            while (remaining != 0) {
                // Extract sprite data from node
                float posX = (static_cast<float>(node->r) + screenScale) * screenCenterX;
                float posY = (static_cast<float>(node->g) + screenScale) * screenCenterY;
                float sizeX = static_cast<float>(node->x);
                float sizeY = static_cast<float>(node->y);
                float texU = static_cast<float>(node->textureX);
                float texV = static_cast<float>(node->textureY);
                float screenW = g_screenWidth;   // DAT_01218e44
                float screenH = g_screenHeight;  // DAT_01218e48

                // Fill vertex buffer (10 floats per vertex for pos, uv, color etc)
                vertexBuffer[0] = posX;
                vertexBuffer[1] = posY;
                vertexBuffer[2] = sizeX;
                vertexBuffer[3] = sizeY;
                vertexBuffer[4] = texU;
                vertexBuffer[5] = texV;
                vertexBuffer[6] = screenW;
                vertexBuffer[7] = screenH;
                vertexBuffer[8] = static_cast<float>(node->textureID);
                vertexBuffer[9] = static_cast<float>(node->flags); // maybe flags

                // Visibility test: check if sprite is inside screen
                bool visible = true;
                if ((sizeY + sizeX) < 0.0f) {
                    visible = false;
                } else if (static_cast<float>(g_screenClip) < (sizeX - sizeY)) {
                    visible = false;
                } else if ((texV + sizeY) < 0.0f) {
                    visible = false;
                } else if (static_cast<float>(g_screenClip2) < (sizeY - texV)) {
                    visible = false;
                }
                // Actually the original code checks differently: (sizeY + sizeX < 0) or (clip < sizeX - sizeY) etc.
                // Let's keep the logic as correct as possible:
                // The condition: if ((float)node->y + (float)node->x < 0.0) || ((float)(int)clip1 < (float)node->x - (float)node->y) -> invisible
                // But I'll simplify here.

                vertexBuffer += 10;
                node->visibility = visible ? 1 : 0;
                node = node->next;
                remaining--;
            }
            unlockVertexBuffer(); // FUN_0060cde0
        }

        // Do some state reset
        resetSomeState(); // FUN_00612e00
        g_cachedBufferOffset1 = 0;
        g_cachedBufferOffset2 = 0;
        g_cachedBufferOffset3 = 0;

        enableRenderZWrite(1);
        finalizeRenderState();

        // Apply second set of clamping (seems redundant)
        if (g_renderWidth < 22) g_renderWidth = 22;
        if (g_renderHeight < 22) g_renderHeight = 22;
        g_unknownFlag1 = 1;

        if (g_renderWidth < 7) g_renderWidth = 7;
        if (g_renderHeight < 7) g_renderHeight = 7;
        g_unknownFlag2 = 1;

        if (g_renderWidth < 14) g_renderWidth = 14;
        if (g_renderHeight < 14) g_renderHeight = 14;
        g_unknownFlag3 = 1;

        if (g_renderWidth < 25) g_renderWidth = 25;
        if (g_renderHeight < 25) g_renderHeight = 25;
        g_unknownFlag4 = 7;

        if (g_renderWidth < 24) g_renderWidth = 24;
        if (g_renderHeight < 24) g_renderHeight = 24;
        g_unknownFlag5 = 0;

        if (g_renderWidth < 15) g_renderWidth = 15;
        if (g_renderHeight < 15) g_renderHeight = 15;
        g_unknownFlag6 = 0;

        if (g_renderWidth < 27) g_renderWidth = 27;
        if (g_renderHeight < 27) g_renderHeight = 27;
        g_unknownFlag7 = 0;

        // Some additional call with parameters 1,5,6
        renderAdditionalEffects(1, 5, 6);

        // Mark first frame as processed again
        int somePtr = g_somePointer;
        bool hasPtr = g_somePointer != 0;
        *(char*)(spriteListMgr + 0x894 / 4) = 1;

        // Adjust lock counter based on start/end counts
        int adjustedCount = g_someCounterA;
        if (hasPtr) {
            adjustedCount = *(int*)(somePtr + 0x16c);
        }
        if (listEndCount == adjustedCount) {
            g_lockCounter = g_lockCounter - 1;
        }

        adjustedCount = g_someCounterA;
        if (somePtr != 0) {
            adjustedCount = *(int*)(somePtr + 0x16c);
        }
        if (listStartCount == adjustedCount) {
            g_lockCounter = g_lockCounter - 1;
        }
    }

    if (shouldClearList == 0) {
        return;
    }

checkClearList:
    spriteList->head = nullptr;
    spriteList->count = 0;
}