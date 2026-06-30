// FUNC_NAME: GameStateManager::applyStateSettings

// 0x004e3110 - Sets up rendering/viewport parameters when transitioning between game states (free roam vs mission)
// Clamps screen scale values, updates camera, and applies rendering detail levels

#include <cstdint>

// Forward declarations of engine functions
extern void setRenderScale(int context, int oldValue, int newValue); // 0x00609340
extern void setFullscreenViewport(int x, int y, int width, int height, float scale); // 0x0060db60
extern void setScreenEffect(int effectId); // 0x00609890
extern void setTextureDetailLevel(int category, int level, int something); // 0x00417cf0
extern void setShadowDetailLevel(int category, int level, int something); // 0x0041e4d0
extern void releaseDynamicTexture(int handle); // 0x0060a460
extern void resetCameraTransform(); // 0x00530a60
extern void setStreamingBudget(int resource, int budget); // 0x00606e60
extern void setCameraFrustum(int width, int height); // 0x00530d80
extern void updateCameraMatrices(); // 0x00530ff0
extern void updateLightingEnvironment(); // 0x00528010
extern void flushResourceCache(); // 0x00612e00

// Globals
extern uint8_t gTransitionPending;                         // DAT_012054e9 - 0x012054e9
extern int gIsMissionActive;                               // DAT_011946b0 - 0x011946b0
extern int gPlayerDefaultWidth;                            // DAT_012058a4 - 0x012058a4
extern int gPlayerDefaultHeight;                           // DAT_012058a8 - 0x012058a8
extern void* gCurrentPlayerContext;                        // DAT_012054dc - 0x012054dc (pointer to player data)
extern int gCurrentResolutionWidth;                        // DAT_011f38f0 - 0x011f38f0
extern int gCurrentResolutionWidthPrev;                    // DAT_011f38f4 - 0x011f38f4 (old width)
extern int gCurrentResolutionHeight;                       // DAT_011f3910 - 0x011f3910
extern int gCurrentResolutionHeightPrev;                   // DAT_011f3914 - 0x011f3914 (old height)
extern int gMinScreenScale;                                // DAT_012058d0 - 0x012058d0
extern int gMaxScreenScale;                                // DAT_00f15988 - 0x00f15988
extern int gScreenScaleMainMenu;                           // _DAT_011f3aa8 - 0x011f3aa8
extern int gScreenScaleHUD;                                // _DAT_011f3a44 - 0x011f3a44
extern int gScreenScaleSubtitle;                           // _DAT_011f3a30 - 0x011f3a30
extern int gScreenScaleMap;                                // _DAT_011f39f4 - 0x011f39f4
extern int gScreenScaleDialog;                             // _DAT_011f3a3c - 0x011f3a3c
extern int gScreenScaleIcons;                              // _DAT_011f3a38 - 0x011f3a38
extern int gScreenScaleHealth;                             // _DAT_011f3a14 - 0x011f3a14
extern int gScreenScaleWeapon;                             // _DAT_011f3a34 - 0x011f3a34
extern int gScreenScaleRadar;                              // _DAT_011f3ab8 - 0x011f3ab8
extern int gScreenScaleCompass;                            // _DAT_011f3abc - 0x011f3abc
extern int gScreenScaleAmmo;                               // _DAT_011f3ac0 - 0x011f3ac0

// Array of player state flags (20 entries) at 0x01218e50 and 0x01218e54 (two parallel arrays)
extern int gPlayerFlagKeys[20];                            // DAT_01218e50 - each entry is 2 ints apart?
extern int gPlayerFlagValues[20];                          // DAT_01218e54 - each entry also 2 ints apart

// Dynamic texture handles
extern int gDynamicTextureA;                               // DAT_01219950 - 0x01219950
extern int gDynamicTextureB;                               // DAT_01219954 - 0x01219954
extern int gDynamicTextureSlot1;                           // DAT_01219a68 - 0x01219a68
extern int gDynamicTextureSlot2;                           // DAT_01219908 - 0x01219908
extern int gDynamicTextureRefs;                            // DAT_01219a6c - 0x01219a6c
extern uint8_t gCurrentPlayerIndex;                        // DAT_012054ea - 0x012054ea (not used in this function)

void GameStateManager::applyStateSettings()
{
    int newWidth;
    int newHeight;
    int oldWidth;
    int oldHeight;
    int oldWidthPrev;
    int oldHeightPrev;
    uint32_t i;

    newWidth = gPlayerDefaultWidth; // default width

    // Check if we have a pending transition
    if (gTransitionPending != 0)
    {
        gTransitionPending = 0;
        gCurrentPlayerIndex = 0; // reset player index

        if (gIsMissionActive == 0) // free roam state
        {
            newWidth = gPlayerDefaultWidth;
            if (gCurrentPlayerContext != 0)
            {
                newWidth = *(int*)((char*)gCurrentPlayerContext + 0x16C); // +0x16C: mission width
            }

            // Search for matching player flag and clear it (bit 0-1 mask)
            i = 0;
            do
            {
                if (gPlayerFlagKeys[i] == newWidth)
                {
                    if (i < 20)
                    {
                        gPlayerFlagValues[i] = gPlayerFlagValues[i] & 0xFFFFFFFC; // clear lower 2 bits
                    }
                    break;
                }
                i++;
            } while (i < 20);

            oldWidthPrev = gCurrentResolutionWidthPrev;
            oldWidth = gCurrentResolutionWidth;
            gCurrentResolutionWidthPrev = 0;
            gCurrentResolutionWidth = newWidth;
            setRenderScale(0, oldWidth, oldWidthPrev); // update resolution width

            oldHeightPrev = gCurrentResolutionHeightPrev;
            oldHeight = gCurrentResolutionHeight;
            gCurrentResolutionHeight = gPlayerDefaultHeight;
            if (gCurrentPlayerContext != 0)
            {
                gCurrentResolutionHeight = *(int*)((char*)gCurrentPlayerContext + 0x170); // +0x170: mission height
            }
            gCurrentResolutionHeightPrev = 0;
            setRenderScale(4, oldHeight, oldHeightPrev); // update resolution height

            // Set fullscreen viewport to (0,0,1.0,1.0)
            setFullscreenViewport(0, 0, 0, 0x3F800000, 0x3F800000); // float 1.0f for width and height
        }
        else // mission active state
        {
            // Apply cinematic effect (effect ID 3)
            int cinematicWidth = gPlayerFlagKeys[(gCurrentPlayerIndex != 1) ? 1 : 0] * 2; // indexing? Actually (&DAT_01218ea0)[uint(DAT_012054e0 != 1) * 2]
            setScreenEffect(3);

            // Clamp and set various screen scale values
            // Main menu scale
            gMinScreenScale = (gMinScreenScale < 0x34) ? 0x34 : gMinScreenScale;
            gMaxScreenScale = (gMaxScreenScale > 0x34) ? 0x34 : gMaxScreenScale;
            gScreenScaleMainMenu = 0;

            // Subtitle scale
            gMinScreenScale = (gMinScreenScale < 0x1B) ? 0x1B : gMinScreenScale;
            gMaxScreenScale = (gMaxScreenScale > 0x1A) ? 0x1B : gMaxScreenScale;
            gScreenScaleSubtitle = 1;

            // Map scale
            gMinScreenScale = (gMinScreenScale < 0x16) ? 0x16 : gMinScreenScale;
            gMaxScreenScale = (gMaxScreenScale > 0x16) ? 0x16 : gMaxScreenScale;
            gScreenScaleMap = 1;

            // Health bar scale
            gMinScreenScale = (gMinScreenScale < 7) ? 7 : gMinScreenScale;
            gMaxScreenScale = (gMaxScreenScale > 7) ? 7 : gMaxScreenScale;
            gScreenScaleHealth = 0;

            // Dialog scale
            gMinScreenScale = (gMinScreenScale < 0x19) ? 0x19 : gMinScreenScale;
            gMaxScreenScale = (gMaxScreenScale > 0x19) ? 0x19 : gMaxScreenScale;
            gScreenScaleDialog = 5;

            // Icons scale
            gMinScreenScale = (gMinScreenScale < 0x18) ? 0x18 : gMinScreenScale;
            gMaxScreenScale = (gMaxScreenScale > 0x18) ? 0x18 : gMaxScreenScale;
            gScreenScaleIcons = 0;

            // Weapon scale
            gMinScreenScale = (gMinScreenScale < 0x0F) ? 0x0F : gMinScreenScale;
            gMaxScreenScale = (gMaxScreenScale > 0x0F) ? 0x0F : gMaxScreenScale;
            gScreenScaleWeapon = 0;

            // Set texture detail levels
            setTextureDetailLevel(1, 2, 6);

            // Update resolution to mission dimensions
            newWidth = gPlayerDefaultWidth;
            if (gCurrentPlayerContext != 0)
            {
                newWidth = *(int*)((char*)gCurrentPlayerContext + 0x16C);
            }

            i = 0;
            do
            {
                if (gPlayerFlagKeys[i] == newWidth)
                {
                    if (i < 20)
                    {
                        gPlayerFlagValues[i] = gPlayerFlagValues[i] & 0xFFFFFFFC;
                    }
                    break;
                }
                i++;
            } while (i < 20);

            oldWidthPrev = gCurrentResolutionWidthPrev;
            oldWidth = gCurrentResolutionWidth;
            gCurrentResolutionWidthPrev = 0;
            gCurrentResolutionWidth = newWidth;
            setRenderScale(0, oldWidth, oldWidthPrev);

            int newHeightFromContext = gPlayerDefaultHeight;
            if (gCurrentPlayerContext != 0)
            {
                newHeightFromContext = *(int*)((char*)gCurrentPlayerContext + 0x170);
            }
            oldHeightPrev = gCurrentResolutionHeightPrev;
            oldHeight = gCurrentResolutionHeight;
            gCurrentResolutionHeight = newHeightFromContext;
            gCurrentResolutionHeightPrev = 0;
            setRenderScale(4, oldHeight, oldHeightPrev);

            // Set fullscreen viewport again
            setFullscreenViewport(0, 0, 0, 0x3F800000, 0x3F800000);

            // Swap dynamic texture handles
            gDynamicTextureB = gDynamicTextureSlot1;
            gDynamicTextureA = gDynamicTextureSlot2;
            gDynamicTextureRefs = 8;

            // Release old textures if they were previously bound
            if (something == &gScreenScaleDialog) // DAT_012058e8 == &DAT_01219940 (probably some pointer comparison)
            {
                releaseDynamicTexture(gDynamicTextureSlot1);
                releaseDynamicTexture(gDynamicTextureA);
            }

            // Update camera and lighting
            resetCameraTransform();
            setStreamingBudget(cinematicWidth, 0x200000); // maybe streaming budget for textures
            setStreamingBudget(oldWidth, 0x200000);       // old width? actually iVar5 is newWidth, uVar1 is cinematicWidth
            setCameraFrustum(newWidth, cinematicWidth);   // set frustum based on mission dimensions
            updateCameraMatrices();
            updateLightingEnvironment();
            flushResourceCache();

            // Clear texture handles
            gDynamicTextureA = 0;
            gDynamicTextureB = 0;
            gDynamicTextureRefs = 0;
        }

        // Common post-transition scaling adjustments (regardless of state)
        gMinScreenScale = (gMinScreenScale < 0x34) ? 0x34 : gMinScreenScale;
        gMaxScreenScale = (gMaxScreenScale > 0x34) ? 0x34 : gMaxScreenScale;
        gScreenScaleMainMenu = 0;

        gMinScreenScale = (gMinScreenScale < 0x16) ? 0x16 : gMinScreenScale;
        gMaxScreenScale = (gMaxScreenScale > 0x16) ? 0x16 : gMaxScreenScale;
        gScreenScaleSubtitle = 1;

        gMinScreenScale = (gMinScreenScale < 7) ? 7 : gMinScreenScale;
        gMaxScreenScale = (gMaxScreenScale > 7) ? 7 : gMaxScreenScale;
        gScreenScaleMap = 1;

        gMinScreenScale = (gMinScreenScale < 0x19) ? 0x19 : gMinScreenScale;
        gMaxScreenScale = (gMaxScreenScale > 0x19) ? 0x19 : gMaxScreenScale;
        gScreenScaleDialog = 7;

        gMinScreenScale = (gMinScreenScale < 0x18) ? 0x18 : gMinScreenScale;
        gMaxScreenScale = (gMaxScreenScale > 0x18) ? 0x18 : gMaxScreenScale;
        gScreenScaleIcons = 0;

        gMinScreenScale = (gMinScreenScale < 0x0F) ? 0x0F : gMinScreenScale;
        gMaxScreenScale = (gMaxScreenScale > 0x0F) ? 0x0F : gMaxScreenScale;
        gScreenScaleHealth = 0;

        // Apply additional texture/shadow settings for all states
        setTextureDetailLevel(1, 5, 6);

        gMinScreenScale = (gMinScreenScale < 0x1B) ? 0x1B : gMinScreenScale;
        gMaxScreenScale = (gMaxScreenScale > 0x1A) ? 0x1B : gMaxScreenScale;
        gScreenScaleWeapon = 0;

        gMinScreenScale = (gMinScreenScale < 0x17) ? 0x17 : gMinScreenScale;
        gMaxScreenScale = (gMaxScreenScale > 0x17) ? 0x17 : gMaxScreenScale;
        gScreenScaleWeapon = 4; // reassigned? original had _DAT_011f3a34 = 4

        setShadowDetailLevel(1, 1, 1);

        gMinScreenScale = (gMinScreenScale < 0x38) ? 0x38 : gMinScreenScale;
        gMaxScreenScale = (gMaxScreenScale > 0x38) ? 0x38 : gMaxScreenScale;
        gScreenScaleRadar = 8;

        gMinScreenScale = (gMinScreenScale < 0x39) ? 0x39 : gMinScreenScale;
        gMaxScreenScale = (gMaxScreenScale > 0x39) ? 0x39 : gMaxScreenScale;
        gScreenScaleCompass = 0;

        gMinScreenScale = (gMinScreenScale < 0x3A) ? 0x3A : gMinScreenScale;
        gMaxScreenScale = (gMaxScreenScale > 0x3A) ? 0x3A : gMaxScreenScale;
        gScreenScaleAmmo = -1;
    }
}