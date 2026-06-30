// FUNC_NAME: TransitionEffectManager::updateTransition

// Address: 0x005167d0
// This function handles the per-frame update of a screen transition effect.
// It scales transition parameters by delta time, processes flags to determine
// effect type, sets up post-processing render states, and applies fog/bloom/etc.
// Called from the main game update loop (0x004e3710).

#include <cstdint>

// Global state (offsets relative to 0x01206690 assumed)
static float& g_transitionDuration = *(float*)0x012066d0;       // +0x40 from base? Duration of transition
static float& g_currentTime = *(float*)0x00e2af44;              // Global game time
static float& g_transitionAccum = *(float*)0x012066bc;          // Accumulated time for transition
static float& g_transitionParam0 = *(float*)0x012066b0;         // Scaled parameter 0
static float& g_transitionParam1 = *(float*)0x012066b4;         // Scaled parameter 1
static float& g_transitionParam2 = *(float*)0x012066b8;         // Scaled parameter 2
static float& g_transitionParam3 = *(float*)0x012066bc;         // Scaled parameter 3 (same as accum?)
static uint32_t& g_transitionFlags = *(uint32_t*)0x012066c0;    // Controls effect flags
static float& g_transitionStartVal = *(float*)0x012066c4;       // Starting value for effect
static int32_t& g_transitionType = *(int32_t*)0x01205254;       // Type of transition (0,1,2)
static uint32_t& g_transitionEffectId = *(uint32_t*)0x01218e50; // Identifies which effect
static uint8_t& g_transitionActive = *(uint8_t*)0x012066e0;    // Flag if transition is active

// Renderer state globals
static uint32_t& g_savedStateA = *(uint32_t*)0x011f3910;       // Saved render state
static int32_t& g_savedStateB = *(int32_t*)0x011f3914;         // Saved render state
static void* g_pRenderDevice = *(void**)0x01205750;            // Render device pointer
static int32_t& g_minClampVal = *(int32_t*)0x012058d0;         // Lower clamp (e.g., viewport size)
static int32_t& g_maxClampVal = *(int32_t*)0x00f15988;         // Upper clamp
static int32_t& g_effectState0 = *(int32_t*)0x011f3a30;        // Effect state A
static int32_t& g_effectState1 = *(int32_t*)0x011f3a3c;        // Effect state B
static int32_t& g_effectState2 = *(int32_t*)0x011f3a38;        // Effect state C
static int32_t& g_effectState3 = *(int32_t*)0x011f3a14;        // Effect state D
static uint32_t& g_effectMask = *(uint32_t*)0x0121b874;        // Combined effect flags
static int32_t& g_effectIndex = *(int32_t*)0x0121b878;         // Index into effect table
static uint32_t& g_effectParamA = *(uint32_t*)0x0121b750;      // Parameter A (material?)
static uint32_t& g_effectParamB = *(uint32_t*)0x0121b754;      // Parameter B
static uint32_t& g_effectDefaultA = *(uint32_t*)0x01219908;    // Default value for A
static uint32_t& g_effectDefaultB = *(uint32_t*)0x0121bc0c;    // Default value for B
static uint32_t& g_effectConst0 = *(uint32_t*)0x0121bbc0;      // Constant 0
static uint32_t& g_effectConst1 = *(uint32_t*)0x0121bbc4;      // Constant 1
static uint32_t& g_effectConst2 = *(uint32_t*)0x0121bbc8;      // Constant 2
static uint32_t& g_fogColorHandle = *(uint32_t*)0x0121bb7c;    // Handle for fog color parameter
static uint32_t& g_fogParamsHandle = *(uint32_t*)0x0121bb80;   // Handle for fog params
static uint32_t& g_depthTexHandle = *(uint32_t*)0x0121bb84;    // Handle for depth texture
static void* g_pCurrentEffectPtr = *(void**)0x012058e8;       // Current effect pointer
static uint32_t& g_transitionBaseAddr = *(uint32_t*)0x0121b740;// Base address for effect
static float& g_frameDeltaTime = *(float*)0x00e2b1a4;         // Frame delta time
static uint32_t& g_newStateA = *(uint32_t*)0x012058a8;        // New render state A
static void* g_pSomeObject = *(void**)0x012054dc;              // Some object with a state at +0x170
static uint32_t* g_effectTable = (uint32_t*)0x0121bbd4;       // Table indexed by effect index

// Forward declarations for called functions (assumed)
void beginTransitionSetup();            // 0x005162a0
void setDepthTestState(int enable);     // 0x00412f50
void setAlphaTestState(int enable);     // 0x00412f10
void setBlendMode(int mode);            // 0x00417fe0
void setRenderState(int a, int b, int c); // 0x00417cf0
void setEffectParameter(uint32_t id, uint32_t flags); // 0x00606e60
void setupEffectPass1();                // 0x0053a050
void setupEffectPass2();                // 0x0053a090
void setupEffectCommon1();              // 0x00539a50
void resetRenderStates();               // 0x00417560
void applyParameter(float val);         // 0x00539aa0
void finalizeEffectSetup();             // 0x005388a0
void applyEffectType0();                // 0x00528010
void applyEffectType1();                // 0x00528070
void applyEffectFinalPart();            // 0x00539250
void setRenderTarget(int a, int b, int c); // 0x00609340
unsigned int getEffectParameterHandle(uint32_t effectPtr, const char* name); // 0x0060a580
void releaseEffectParameter(uint32_t handle); // 0x0060a460

void applyTransitionFrame()
{
    uint32_t uVar13 = 0;
    
    // Check if transition is active
    if ((g_transitionDuration != 0.0f) && (g_currentTime <= g_transitionAccum) && (g_transitionStartVal != 0.0f))
    {
        // Scale transition parameters by frame delta time / duration
        float scale = g_frameDeltaTime / g_transitionDuration;
        g_transitionParam0 *= scale;
        g_transitionParam1 *= scale;
        g_transitionParam2 *= scale;
        g_transitionParam3 *= scale; // Note: this overwrites accum? Possibly intended.
        
        // Check again after scaling
        if ((g_currentTime <= g_transitionAccum) && ((g_transitionFlags & 0x10000000) == 0))
        {
            // Extract bit fields from flags
            uint32_t bit13 = g_transitionFlags >> 0xd;   // bit 13
            uint32_t bit17 = g_transitionFlags >> 0x11;  // bit 17
            uint32_t bit18 = g_transitionFlags >> 0x12;  // bit 18
            uint32_t bit19 = g_transitionFlags >> 0x13;  // bit 19
            uint32_t bit14 = g_transitionFlags >> 0xe;   // bit 14
            uint32_t bit15 = g_transitionFlags >> 0xf;   // bit 15
            uint32_t bit16 = g_transitionFlags & 0x10000;
            
            // Decode two-bit field (bits 20-21) into multiplier value
            int iVar4;
            if ((g_transitionFlags & 0x200000) == 0)
            {
                iVar4 = ((g_transitionFlags & 0x100000) != 0) + 1;  // 1 or 2
            }
            else
            {
                iVar4 = 4;  // 4
            }
            
            bool bNeedSetup = (g_transitionType != 1);   // Type 1 may skip some setup
            uVar13 = g_transitionEffectId;
            
            // If bit13 is set, pick effect from table based on iVar4
            if ((bit13 & 1) != 0)
            {
                uVar13 = g_effectTable[iVar4 * 2];   // Actually accessing array at 0x00e2da08 + iVar4*4, but here we treat as g_effectTable
            }
            
            // Main transition update block
            if (g_transitionActive == 0)
            {
                // First time this frame? Do setup
                if (((bit14 & 1) == 0) && (bNeedSetup))
                {
                    beginTransitionSetup();
                    bNeedSetup = (bool)(byte)(bit14 & 1);  // This becomes false again (bit14 & 1 is 0)
                }
                
                // Save and clear render state
                int iSavedB = g_savedStateB;
                bool bSavedA = (g_savedStateA != 0);
                g_savedStateA = 0;
                g_savedStateB = 0;
                if ((bSavedA) || (iSavedB != 0))
                {
                    // Call virtual function at +0x9c on render device (likely resetRenderState)
                    (*(void (**)(void*, int))(*((uint32_t*)g_pRenderDevice) + 0x9c))(g_pRenderDevice, 0);
                }
                
                // Clamp values (possibly viewport/resolution settings)
                if (g_minClampVal < 0x16) g_minClampVal = 0x16;
                if (0x16 < g_maxClampVal) g_maxClampVal = 0x16;
                g_effectState0 = 1;
                
                setDepthTestState(0);
                setAlphaTestState(0);
                
                if (g_minClampVal < 0x19) g_minClampVal = 0x19;
                if (0x19 < g_maxClampVal) g_maxClampVal = 0x19;
                g_effectState1 = 5;
                
                if (g_minClampVal < 0x18) g_minClampVal = 0x18;
                if (0x18 < g_maxClampVal) g_maxClampVal = 0x18;
                g_effectState2 = 0;
                
                if (g_minClampVal < 0xf) g_minClampVal = 0xf;
                if (0xf < g_maxClampVal) g_maxClampVal = 0xf;
                g_effectState3 = 0;
                
                setBlendMode(1);
                setRenderState(1, 5, 6);
                
                // Determine effect type from flags
                if ((bit13 & 1) == 0)
                {
                    g_effectMask = 1;
                }
                else
                {
                    g_effectMask = 2;
                    if ((bit15 & 1) != 0)
                        g_effectMask = 10;
                    if ((bit17 & 1) == 0)
                    {
                        if ((bit18 & 1) != 0)
                            g_effectMask |= 0x20;
                    }
                    else
                    {
                        if ((bit18 & 1) != 0)
                            g_effectMask |= 0x40;
                    }
                    if ((bit19 & 1) != 0)
                        g_effectMask |= 0x80;
                    if (bit16 != 0)
                        g_effectMask |= 0x10;
                    if (iVar4 == 1)
                        g_effectMask |= 0x100;
                    else if (iVar4 == 2)
                        g_effectMask |= 0x200;
                    else if (iVar4 == 4)
                        g_effectMask |= 0x400;
                }
                
                // Select effect parameters based on mask
                g_effectParamA = g_effectDefaultA;
                
                if ((g_effectMask & 1) == 0)
                {
                    g_effectIndex = ((g_effectMask >> 4) & 8) +
                                    ((g_effectMask >> 5) & 2) +
                                    ((g_effectMask >> 3) & 2) +
                                    2 + ((g_effectMask >> 3) & 1);
                }
                else
                {
                    g_effectIndex = 0;
                }
                g_effectParamB = g_effectTable[g_effectIndex];
                
                if ((g_effectMask & 2) != 0)
                {
                    g_effectParamA = g_effectDefaultB;
                }
                
                // If the effect uses fog/depth, get parameter handles
                if ((g_effectParamB == g_effectConst0) ||
                    (g_effectParamB == g_effectConst1) ||
                    (g_effectParamB == g_effectConst2))
                {
                    g_fogColorHandle = getEffectParameterHandle(g_effectParamB, "fog_color");
                    g_fogParamsHandle = getEffectParameterHandle(g_effectParamB, "fog_params");
                    g_depthTexHandle = getEffectParameterHandle(g_effectParamB, "depth_texture");
                }
                
                // Release previous effect if changed
                if (g_pCurrentEffectPtr == (void*)&g_transitionBaseAddr)
                {
                    releaseEffectParameter(g_effectParamB);
                    releaseEffectParameter(g_effectParamA);
                }
                
                // Apply effect parameters and setup passes
                setEffectParameter(uVar13, 0x200000);
                setupEffectPass1();
                setupEffectPass2();
                setupEffectCommon1();
                resetRenderStates();
                applyParameter(g_transitionStartVal);
                finalizeEffectSetup();
                
                if ((bit13 & 1) == 0)
                    applyEffectType0();
                else
                    applyEffectType1();
                
                applyEffectFinalPart();
                
                // Update render state for new frame
                uint32_t uSavedA = g_savedStateA;
                int iSavedB2 = g_savedStateB;
                g_savedStateA = g_newStateA;
                if (g_pSomeObject != nullptr)
                {
                    g_savedStateA = *(uint32_t*)((uint8_t*)g_pSomeObject + 0x170);
                }
                g_savedStateB = 0;
                setRenderTarget(4, uSavedA, iSavedB2);
                
                // Second clamp and setup block (likely second render pass)
                if (g_minClampVal < 0x16) g_minClampVal = 0x16;
                if (0x16 < g_maxClampVal) g_maxClampVal = 0x16;
                g_effectState0 = 1;
                
                setDepthTestState(1);
                setAlphaTestState(1);
                
                if (g_minClampVal < 0x19) g_minClampVal = 0x19;
                if (0x19 < g_maxClampVal) g_maxClampVal = 0x19;
                g_effectState1 = 7;
                
                if (g_minClampVal < 0x18) g_minClampVal = 0x18;
                if (0x18 < g_maxClampVal) g_maxClampVal = 0x18;
                g_effectState2 = 0;
                
                if (g_minClampVal < 0xf) g_minClampVal = 0xf;
                if (0xf < g_maxClampVal) g_maxClampVal = 0xf;
                g_effectState3 = 0;
                
                setBlendMode(0);
                setRenderState(1, 5, 6);
            }
            else
            {
                g_transitionActive = 0; // If was active, deactivate
            }
            
            if (bNeedSetup)
            {
                beginTransitionSetup();
            }
            
            uVar13 = 0;
            resetRenderStates();
        }
        
        // Clear transition parameters
        g_transitionFlags = 0;
        g_transitionAccum = (float)uVar13;
        g_transitionParam2 = (float)uVar13;
        g_transitionParam1 = (float)uVar13;
        g_transitionParam0 = (float)uVar13;
        g_transitionStartVal = (float)uVar13;
        g_transitionDuration = (float)uVar13;
        return;
    }
    
    // If condition fails, mark transition as not active
    g_transitionActive = 1;
    return;
}