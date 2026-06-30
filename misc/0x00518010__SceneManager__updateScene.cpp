// FUNC_NAME: SceneManager::updateScene

#include <cstdint>

// Global state pointers and values - replace with meaningful names based on context
static uint32_t g_currentSceneId;            // DAT_011f38f0
static uint32_t g_nextSceneId;               // DAT_01218e58
static uint32_t g_sceneLoadingFlag;          // DAT_011f38f4
static uint32_t g_previousEntityIndex;       // DAT_011f3914
static uint32_t g_entityIndexToActivate;     // DAT_011f3910
static uint32_t* g_renderManagerPtr;         // DAT_01205750 (vtable pointer)
static uint32_t g_maxParamValue;             // DAT_012058d0 (upper clamp bound)
static uint32_t g_minParamValue;             // DAT_00f15988 (lower clamp bound)

// Parameters for various visual effects (offsets relative to a base struct)
static uint32_t g_paramA;                    // _DAT_011f3a10
static uint32_t g_paramB;                    // _DAT_011f3a30
static uint32_t g_paramC;                    // _DAT_011f39f4
static uint32_t g_paramD;                    // _DAT_011f3a3c
static uint32_t g_paramE;                    // _DAT_011f3a38
static uint32_t g_paramF;                    // _DAT_011f3a14
static uint32_t g_paramG;                    // _DAT_011f3a44

// Material and fog handles
static uint32_t g_defaultMaterial;           // DAT_01219908
static uint32_t g_currentMaterial;           // DAT_0121bbbc
static uint32_t g_materialAlt1;              // DAT_0121bbc0
static uint32_t g_materialAlt2;              // DAT_0121bbc4
static uint32_t g_materialAlt3;              // DAT_0121bbc8
static uint32_t g_fogColorHandle;            // DAT_0121bb7c
static uint32_t g_fogParamsHandle;           // DAT_0121bb80
static uint32_t g_depthTextureHandle;        // DAT_0121bb84
static uint32_t g_currentRenderTarget;       // DAT_012058e8
static uint32_t g_renderTargetPtr;           // &DAT_0121b740 (address)
static uint32_t g_secondaryMaterial;         // DAT_0121b754
static uint32_t g_primaryMaterial;           // DAT_0121b750
static uint32_t g_someFlag;                  // DAT_0121b874

// Entity system globals
static uint32_t g_entityManagerPtr;          // DAT_012054dc (non-zero if valid)
static uint32_t g_currentEntityId;           // DAT_012058a8
// Entity array at DAT_011a0f28, each entry 0x38 bytes
// Offsets within entity: 0x00 = state byte, 0x0c = flags, 0x1c = object pointer

// Camera/view parameters
static uint32_t g_cameraPosX;                // DAT_012192bc (destination)
static uint32_t g_cameraSourceX;             // DAT_012192dc
static uint32_t g_cameraPosY;                // DAT_0121b890
static uint32_t g_cameraSourceY;             // DAT_012192b0
static uint32_t g_cameraPosZ;                // DAT_0121b894
static uint32_t g_cameraSourceZ;             // DAT_012192b4
static uint32_t g_cameraPosW;                // DAT_0121b898
static uint32_t g_cameraSourceW;             // DAT_012192b8
static uint32_t g_cameraPosV;                // DAT_0121b89c

// Color constants (likely RGBA)
static uint32_t g_colorConstant1;            // DAT_00e2eff4
static uint32_t g_colorConstant2;            // DAT_00e2b1a4

// External functions (stubs with actual addresses)
void setLoadingState(int32_t state);                         // 0x00609890
void switchScene(uint32_t currentId, uint32_t nextId);     // 0x0060df60
void callVtableMethod_0x9c(void* obj, int32_t param);     // 0x005??? (vtable call)
uint32_t getMaterialHandle(uint32_t material, const char* param); // 0x0060a580
void releaseMaterial(uint32_t material);                    // 0x0060a460
void setEntityFlag(uint32_t entityObj, uint32_t flag);      // 0x00606e60
void rebuildRenderData();                                    // 0x006189c0
void updatePerFrame();                                       // 0x0053a180
void applyMaterialParameters(uint32_t material, uint32_t baseMat, uint32_t* params); // 0x0060add0
void updateCamera();                                         // 0x00518510
void performSimulationStep(uint8_t* stackBuffer);            // 0x0053a110
void updateAnimation();                                      // 0x005388a0
void* allocateMemory(uint32_t size, uint32_t align, uint32_t flags); // 0x0060cd00 (size=5? actually first arg is size category)
void deallocateMemory();                                     // 0x0060cde0
void updateAudio();                                          // 0x00539250
void applyGameplaySettings(int32_t a, int32_t b, int32_t c); // 0x00417cf0
void setGameStateIndex(uint32_t category, uint32_t oldIndex, uint32_t newIndex); // 0x00609340

void SceneManager::updateScene()
{
    // Check if scene switching is requested
    if ((g_currentSceneId == g_nextSceneId) && (g_sceneLoadingFlag == 0))
    {
        setLoadingState(1);
    }
    else
    {
        switchScene(g_currentSceneId, g_nextSceneId);
    }

    // Preserve previous entity activation state
    int32_t previousIndex = g_previousEntityIndex;
    bool wasActive = (g_entityIndexToActivate != 0);
    g_entityIndexToActivate = 0;
    g_previousEntityIndex = 0;

    // If either was set, call vtable method on render manager
    if ((wasActive) || (previousIndex != 0))
    {
        // vtable +0x9c is likely a "notify" or "reset" method
        callVtableMethod_0x9c(g_renderManagerPtr, 0);
    }

    // --- Clamp and set visual parameters (first pass) ---
    if (g_maxParamValue < 0xe)
        g_maxParamValue = 0xe;
    if (g_minParamValue > 0xe)
        g_minParamValue = 0xe;
    g_paramA = 0;

    if (g_maxParamValue < 0x16)
        g_maxParamValue = 0x16;
    if (g_minParamValue > 0x16)
        g_minParamValue = 0x16;
    g_paramB = 1;

    if (g_maxParamValue < 7)
        g_maxParamValue = 7;
    if (g_minParamValue > 7)
        g_minParamValue = 7;
    g_paramC = 0;

    if (g_maxParamValue < 0x19)
        g_maxParamValue = 0x19;
    if (g_minParamValue > 0x19)
        g_minParamValue = 0x19;
    g_paramD = 5;

    if (g_maxParamValue < 0x18)
        g_maxParamValue = 0x18;
    if (g_minParamValue > 0x18)
        g_minParamValue = 0x18;
    g_paramE = 0;

    if (g_maxParamValue < 0xf)
        g_maxParamValue = 0xf;
    if (g_minParamValue > 0xf)
        g_minParamValue = 0xf;
    g_paramF = 0;

    if (g_maxParamValue < 0x1b)
        g_maxParamValue = 0x1b;
    if (g_minParamValue > 0x1b)   // note: uses 0x1b for both? actual: g_minParamValue > 0x1a then set to 0x1b
        g_minParamValue = 0x1b;
    g_paramG = 0;

    // Apply gameplay settings (first call)
    applyGameplaySettings(1, 2, 1);

    // Set up material pointers
    g_primaryMaterial = g_defaultMaterial;
    g_someFlag = 0;
    g_secondaryMaterial = g_currentMaterial;

    // Check if current material is one of three alternatives
    if ((g_currentMaterial == g_materialAlt1) ||
        (g_currentMaterial == g_materialAlt2) ||
        (g_currentMaterial == g_materialAlt3))
    {
        g_fogColorHandle  = getMaterialHandle(g_currentMaterial, "fog_color");
        g_fogParamsHandle = getMaterialHandle(g_secondaryMaterial, "fog_params");
        g_depthTextureHandle = getMaterialHandle(g_secondaryMaterial, "depth_texture");
    }

    // Release previous materials if render target is the default one
    if (g_currentRenderTarget == &g_renderTargetPtr)
    {
        releaseMaterial(g_secondaryMaterial);
        releaseMaterial(g_primaryMaterial);
    }

    // --- Entity state update ---
    uint32_t entityId = g_currentEntityId;
    if (g_entityManagerPtr != 0)
    {
        entityId = *(uint32_t*)(g_entityManagerPtr + 0x170);  // gets entity ID from manager
    }

    if ((entityId != 0xFFFFFFFF) && (entityId < 0x1000))
    {
        int32_t index = entityId * 0x38;  // stride of entity block
        uint8_t* entityBlock = (uint8_t*)(0x011a0f28);  // base address of entity array
        uint8_t stateByte = entityBlock[index];  // +0x00
        if ((entityBlock + index != nullptr) && (stateByte < 4))
        {
            uint32_t entityObj = *(uint32_t*)(entityBlock + index + 0x1c);  // +0x1c: object pointer
            if (entityObj != 0)
            {
                setEntityFlag(entityObj, 0x210000);
            }
            uint32_t flags = *(uint32_t*)(entityBlock + index + 0x0c);  // +0x0c: flags
            flags = (flags & 0xFCAD8FFF) | 0x210000;  // clear some bits and set new
            *(uint32_t*)(entityBlock + index + 0x0c) = flags;
            rebuildRenderData();
        }
    }

    // Similar update for next scene ID
    if ((g_nextSceneId != 0xFFFFFFFF) && (g_nextSceneId < 0x1000))
    {
        int32_t index = g_nextSceneId * 0x38;
        uint8_t* entityBlock = (uint8_t*)(0x011a0f28);
        uint8_t stateByte = entityBlock[index];
        if ((entityBlock + index != nullptr) && (stateByte < 4))
        {
            uint32_t entityObj = *(uint32_t*)(entityBlock + index + 0x1c);
            if (entityObj != 0)
            {
                setEntityFlag(entityObj, 0x200000);
            }
            uint32_t flags = *(uint32_t*)(entityBlock + index + 0x0c);
            flags = (flags & 0xFCAC8FFF) | 0x200000;
            *(uint32_t*)(entityBlock + index + 0x0c) = flags;
            rebuildRenderData();
        }
    }

    // --- Frame update sequence ---
    updatePerFrame();                          // 0x0053a180

    // Copy camera/view parameters from source to destination
    g_cameraPosX = g_cameraSourceX;
    g_cameraPosY = g_cameraSourceY;
    g_cameraPosZ = g_cameraSourceZ;
    g_cameraPosW = g_cameraSourceW;
    g_cameraPosV = g_cameraSourceX;  // using sourceX again? Possibly intentional

    // Apply fog/material parameters to view if render target is default and material matches
    if ((g_currentRenderTarget == &g_renderTargetPtr) && (g_secondaryMaterial == g_currentMaterial))
    {
        applyMaterialParameters(g_currentMaterial, g_defaultMaterial, &g_cameraPosY);
    }

    updateCamera();                            // 0x00518510

    // Perform a simulation step (uses stack buffer 44 bytes)
    uint8_t simStackBuffer[44];
    performSimulationStep(simStackBuffer);    // 0x0053a110

    updateAnimation();                         // 0x005388a0

    // Allocate and fill a small vector (maybe color)
    void* allocated = allocateMemory(5, 4, 0, 1, 0);   // size=5, align=4
    if (allocated != nullptr)
    {
        uint32_t* vec = (uint32_t*)allocated;
        vec[0] = g_colorConstant1;
        vec[1] = g_colorConstant1;  // actually uVar3 second assignment? Wait: first assigned uVar3 = DAT_00e2eff4, then *puVar4 = DAT_00e2eff4; puVar4[1]=uVar3 (same); puVar4[2]=uVar2 (DAT_00e2b1a4); puVar4[3]=uVar3; puVar4[4]=uVar3; puVar4[5]=uVar2; puVar4[6]=uVar2; puVar4[7]=uVar2;
        vec[2] = g_colorConstant2;
        vec[3] = g_colorConstant1;
        vec[4] = g_colorConstant1;
        vec[5] = g_colorConstant2;
        vec[6] = g_colorConstant2;
        vec[7] = g_colorConstant2;
        deallocateMemory();  // ? Actually FUN_0060cde0 likely finalizes allocation
    }

    updateAudio();                             // 0x00539250

    // --- Clamp and set visual parameters (second pass) ---
    if (g_maxParamValue < 0x16)
        g_maxParamValue = 0x16;
    if (g_minParamValue > 0x16)
        g_minParamValue = 0x16;
    g_paramB = 1;

    if (g_maxParamValue < 7)
        g_maxParamValue = 7;
    if (g_minParamValue > 7)
        g_minParamValue = 7;
    g_paramC = 1;

    if (g_maxParamValue < 0x19)
        g_maxParamValue = 0x19;
    if (g_minParamValue > 0x19)
        g_minParamValue = 0x19;
    g_paramD = 7;

    if (g_maxParamValue < 0x18)
        g_maxParamValue = 0x18;
    if (g_minParamValue > 0x18)
        g_minParamValue = 0x18;
    g_paramE = 0;

    if (g_maxParamValue < 0xf)
        g_maxParamValue = 0xf;
    if (g_minParamValue > 0xf)
        g_minParamValue = 0xf;
    g_paramF = 0;

    if (g_maxParamValue < 0x1b)
        g_maxParamValue = 0x1b;
    if (g_minParamValue > 0x1b) // note: code has 0x1a check? actual: if 0x1a < DAT_00f15988 then set to 0x1b
        g_minParamValue = 0x1b;
    g_paramG = 0;

    // Apply gameplay settings (second call with different parameters)
    applyGameplaySettings(1, 5, 6);

    // Save old activation state and update with new entity ID
    uint32_t oldEntityIndex = g_previousEntityIndex;   // actually read from g_previousEntityIndex? Code: uVar3 = DAT_011f3914; uVar2 = DAT_011f3910;
    uint32_t oldActivateFlag = g_entityIndexToActivate;
    g_entityIndexToActivate = g_currentEntityId;
    if (g_entityManagerPtr != 0)
    {
        g_entityIndexToActivate = *(uint32_t*)(g_entityManagerPtr + 0x170);
    }
    g_previousEntityIndex = 0;

    // Notify state change
    setGameStateIndex(4, oldActivateFlag, oldEntityIndex);
}