// FUNC_NAME: CameraController::switchCameraState

#include <cstdint>

// Global constants
extern float g_fCameraEpsilon;          // DAT_00e2af44 - threshold for zero check
extern float g_fDefaultZoom;            // DAT_00e2b1a4 - default FOV/zoom value
extern float g_fGlobalScale;            // DAT_00e445a4 - global multiplier

// State globals
extern int32_t g_cameraSwitchCounter;   // _DAT_01205500
extern uint32_t g_currentCameraID;      // DAT_01218eb8 - active camera index
extern uint32_t g_playerCameraID;       // DAT_012058a4 - current player camera
extern int32_t g_cameraFOV;             // DAT_012058d0 - FOV (clamped)
extern int32_t g_maxCameraFOV;          // DAT_00f15988 - maximum FOV allowed

// Object pointer (e.g., PlayerState)
extern uint32_t* g_playerStatePtr;      // DAT_012054dc - pointer with cameraID at +0x16c

// Effect flags (array-like globals for different effect indices)
extern int32_t g_cameraEffect1;         // _DAT_011f3a30
extern int32_t g_cameraEffect2;         // _DAT_011f39f4
extern int32_t g_cameraEffect3;         // _DAT_011f3a10
extern int32_t g_cameraEffect4;         // _DAT_011f3a3c
extern int32_t g_cameraEffect5;         // _DAT_011f3a38
extern int32_t g_cameraEffect6;         // _DAT_011f3a14
extern int32_t g_cameraEffect7;         // _DAT_011f3a44

// Camera target/current values
extern uint32_t g_prevCameraID;         // DAT_011f38f0
extern uint32_t g_prevCameraID2;        // DAT_011f38f4
extern float g_cameraTargetX;           // DAT_0121b810
extern float g_cameraTargetY;           // DAT_0121b814
extern float g_cameraTargetZ;           // DAT_0121b818
extern float g_cameraTargetW;           // DAT_0121b81c

// Array of camera slot pairs (size 0x14, stride 8 bytes each)
extern uint32_t g_cameraSlotIDs[20];    // DAT_01218e50 - pairs of IDs
extern uint32_t g_cameraSlotFlags[20];  // DAT_01218e54 - per-slot flags

// Camera slot data array (size 0x1000, 0x38 bytes each)
extern unsigned char g_cameraSlotData[0x1000 * 0x38]; // DAT_011a0f28...
extern uint32_t g_cameraSlotInfo[0x1000];              // DAT_011a0f34? offset +0x0c
extern uint32_t g_cameraSlotEntity[0x1000];           // DAT_011a0f44? offset +0x1c

// Special camera/entity pointers
extern void* g_cameraTargetPtr;         // DAT_012058e8
extern void* g_cameraDefaultPtr;        // DAT_0121b740

// Structure definition for Camera (hypothetical)
struct Camera {
    float posX;       // +0x20
    float posY;       // +0x24
    float posZ;       // +0x28
    // padding
    float targetX;    // +0x30
    float targetY;    // +0x34
    float targetZ;    // +0x38
    float fov;        // +0x40
    float nearPlane;  // +0x4c
};

// Forward declarations of called functions
extern int32_t allocateCameraResource(uint32_t* outHandle); // FUN_00507150
extern void setViewportEnabled(bool enable);                // FUN_00609890
extern void playSoundEffect(int32_t group, int32_t index, int32_t subIndex); // FUN_00417cf0
extern void setCameraTarget(uint32_t slot, float x, float y, float z, float w); // FUN_00609340 simplified?
extern void setViewportRect(float x, float y, float w, float h); // FUN_0060db60 simplified
extern void updateCameraViewport();                         // FUN_00609810
extern void updateCameraMatrices();                         // FUN_005392b0
extern void updateCameraPostProcess();                      // FUN_005388a0
extern void setEntityFlags(void* entity, uint32_t flags);   // FUN_00606e60
extern void notifyEntityChange();                           // FUN_006189c0
extern void transformCameraSpace(void* src, void* dst, float* matrix); // FUN_0060add0
extern void finalizeCameraTransition();                     // FUN_005394e0
extern void applyCameraPositionEffects();                   // FUN_005398d0
extern void applyCameraTargetEffects();                     // FUN_005399a0
extern float* allocateFloatArray(uint32_t size, uint32_t align, uint32_t unk1, uint32_t unk2, uint32_t unk3); // FUN_0060cd00
extern void releaseFloatArray();                            // FUN_0060cde0
extern void updateCameraState();                            // FUN_00539250
extern void selectPlayerCamera(uint32_t cameraID, uint32_t mode); // FUN_0052c420

// Main function
int32_t CameraController::switchCameraState(Camera* camera, uint32_t flags, bool bForce)
{
    int32_t result;
    float defaultZoom = g_fDefaultZoom;
    uint32_t playerCameraFlags = 0;           // local_28
    uint32_t savedPlayerID;                   // local_24

    // Early exit if camera position/fov are not within valid range
    if ((camera->fov <= g_fCameraEpsilon && g_fCameraEpsilon != camera->fov) ||
        ((camera->posX <= g_fCameraEpsilon && g_fCameraEpsilon != camera->posX &&
          camera->posY <= g_fCameraEpsilon && g_fCameraEpsilon != camera->posY &&
          camera->posZ <= g_fCameraEpsilon && g_fCameraEpsilon != camera->posZ) &&
         (camera->targetX <= g_fCameraEpsilon && g_fCameraEpsilon != camera->targetX ||
          camera->targetY <= g_fCameraEpsilon && g_fCameraEpsilon != camera->targetY ||
          camera->targetZ <= g_fCameraEpsilon && g_fCameraEpsilon != camera->targetZ)))
    {
        return 0; // camera not in a valid state to switch
    }

    // If flag 0x10 is set, allocate a resource and check for failure
    if (flags & 0x10)
    {
        uint32_t* handlePtr = (g_playerStatePtr != 0) ? &playerCameraFlags : 0;
        result = allocateCameraResource(handlePtr);
        if (result != 0 && result == -1)
        {
            return 0;
        }
    }

    // Determine the player's current camera ID
    if (g_playerStatePtr != 0)
        savedPlayerID = *(uint32_t*)(g_playerStatePtr + 0x16c); // +0x16c: cameraId
    else
        savedPlayerID = g_playerCameraID;

    // Increment camera switch counter
    g_cameraSwitchCounter++;

    // If not forced, enable the viewport for the new camera
    if (!bForce)
    {
        setViewportEnabled(1);
    }

    // First set of FOV clamping and effect presets (likely for "normal" mode)
    if (g_cameraFOV < 0x16) g_cameraFOV = 0x16;
    if (g_maxCameraFOV > 0x16) g_maxCameraFOV = 0x16;
    g_cameraEffect1 = 1;
    if (g_cameraFOV < 7) g_cameraFOV = 7;
    if (g_maxCameraFOV > 7) g_maxCameraFOV = 7;
    g_cameraEffect2 = 0;
    if (g_cameraFOV < 0xe) g_cameraFOV = 0xe;
    if (g_maxCameraFOV > 0xe) g_maxCameraFOV = 0xe;
    g_cameraEffect3 = 0;
    if (g_cameraFOV < 0x19) g_cameraFOV = 0x19;
    if (g_maxCameraFOV > 0x19) g_maxCameraFOV = 0x19;
    g_cameraEffect4 = 5;
    if (g_cameraFOV < 0x18) g_cameraFOV = 0x18;
    if (g_maxCameraFOV > 0x18) g_maxCameraFOV = 0x18;
    g_cameraEffect5 = 0;
    if (g_cameraFOV < 0xf) g_cameraFOV = 0xf;
    if (g_maxCameraFOV > 0xf) g_maxCameraFOV = 0xf;
    g_cameraEffect6 = 0;
    if (g_cameraFOV < 0x1b) g_cameraFOV = 0x1b;
    if (g_maxCameraFOV > 0x1b) g_maxCameraFOV = 0x1b;
    g_cameraEffect7 = 0;

    // Play sound effect for transition (group 1, index 2, subIndex 1)
    playSoundEffect(1, 2, 1);

    // Find the slot index for the current camera (g_currentCameraID) and clear its flag bit 2
    uint32_t currentCamID = g_currentCameraID;
    uint32_t idx;
    for (idx = 0; idx < 0x14; idx++)
    {
        if (g_cameraSlotIDs[idx * 2] == currentCamID)
        {
            g_cameraSlotFlags[idx * 2] &= 0xfffffffc; // clear bit 2 (0x04)
            break;
        }
    }

    // Save previous camera IDs and set new current camera
    uint32_t prevID1 = g_prevCameraID;
    uint32_t prevID2 = g_prevCameraID2;
    g_prevCameraID = currentCamID;      // DAT_011f38f0 = DAT_01218eb8
    g_prevCameraID2 = 0;                // DAT_011f38f4 = 0

    // Update the camera target to the previous camera's values
    setCameraTarget(0, prevID1, prevID2); // call with slot 0

    // Set viewport to full size (0,0,0) but with scale factors 1.0,1.0 (0x3f800000)
    setViewportRect(0, 0, 0, 1.0f, 1.0f);

    // Enable the new viewport
    setViewportEnabled(1);

    // Update camera math
    updateCameraMatrices();
    updateCameraPostProcess();

    // Modify entity flags for the player's camera slot
    uint32_t playerID = savedPlayerID;
    if (g_playerStatePtr != 0)
        playerID = *(uint32_t*)(g_playerStatePtr + 0x16c);

    if (playerID != 0xffffffff && playerID < 0x1000)
    {
        uint32_t slotOffset = playerID * 0x38;
        // Check slot state (at offset 0x00)
        if (g_cameraSlotData[slotOffset] < 4)
        {
            // Set entity flag 0x200000
            if (*(int32_t*)(&g_cameraSlotData[slotOffset + 0x1c]) != 0)
            {
                setEntityFlags((void*)*(int32_t*)(&g_cameraSlotData[slotOffset + 0x1c]), 0x200000);
            }
            // Also set another flag at offset 0x0c
            *(uint32_t*)(&g_cameraSlotData[slotOffset + 0x0c]) |= 0x200000;
            notifyEntityChange();
        }
    }

    // Store the saved zoom value
    g_cameraTargetW = defaultZoom;

    // If the default camera target pointers match, apply a transform
    if ((g_cameraTargetPtr == g_cameraDefaultPtr) &&
        (*(uint32_t*)(&g_cameraDefaultPtr[0x14]) == *(uint32_t*)0x0121bbb4) && // some global pointer
        (*(uint32_t*)0x0121b9c0 != 0))
    {
        transformCameraSpace(*(void**)(&g_cameraDefaultPtr[0x14]), *(void**)0x0121b9c0, &g_cameraTargetW);
    }

    // Finalize camera transition
    finalizeCameraTransition();

    // Determine which set of camera positions to use for effects (first triple 0x20..0x28)
    float effectPosX, effectPosY, effectPosZ;
    float unused0 = 0;
    if ((camera->fov <= g_fCameraEpsilon && g_fCameraEpsilon != camera->fov) ||
        ((camera->posX <= g_fCameraEpsilon && g_fCameraEpsilon != camera->posX &&
          camera->posY <= g_fCameraEpsilon && g_fCameraEpsilon != camera->posY &&
          camera->posZ <= g_fCameraEpsilon && g_fCameraEpsilon != camera->posZ)))
    {
        effectPosX = g_fDefaultZoom;
        effectPosY = g_fDefaultZoom;
        effectPosZ = g_fDefaultZoom;
    }
    else
    {
        effectPosX = camera->posX;
        effectPosY = camera->posY;
        effectPosZ = camera->posZ;
    }
    // Call with these positions
    applyCameraPositionEffects();

    // Determine effect positions for the second triple (0x30..0x38)
    if ((camera->fov <= g_fCameraEpsilon && g_fCameraEpsilon != camera->fov) ||
        ((camera->targetX <= g_fCameraEpsilon && g_fCameraEpsilon != camera->targetX &&
          camera->targetY <= g_fCameraEpsilon && g_fCameraEpsilon != camera->targetY &&
          camera->targetZ <= g_fCameraEpsilon && g_fCameraEpsilon != camera->targetZ)))
    {
        effectPosX = 0.0f;
        effectPosY = 0.0f;
        effectPosZ = 0.0f;
    }
    else
    {
        effectPosX = camera->targetX;
        effectPosY = camera->targetY;
        effectPosZ = camera->targetZ;
    }
    applyCameraTargetEffects();

    // Compute camera target values from FOV and scale
    g_cameraTargetX = camera->fov * g_fGlobalScale;  // actually DAT_01218e44 * scale
    g_cameraTargetY = camera->fov * g_fGlobalScale;  // DAT_01218e48 * scale
    g_cameraTargetZ = 0.0f;                          // local_20
    g_cameraTargetW = playerCameraFlags;             // uStack_14

    // If default camera target matches another pointer, transform
    if ((g_cameraTargetPtr == g_cameraDefaultPtr) &&
        (*(uint32_t*)(&g_cameraDefaultPtr[0x14]) == *(uint32_t*)0x0121bbb0) &&
        (*(uint32_t*)0x0121b99c != 0))
    {
        transformCameraSpace(*(void**)0x0121bbb0, *(void**)0x0121b99c, &g_cameraTargetX);
    }

    // Allocate a float array (8 floats) and set values from globals
    float* matrix = allocateFloatArray(0xd, 4, 0, 1, 0);
    if (matrix != 0)
    {
        matrix[0] = *(float*)&g_fCameraEpsilon; // DAT_00e2eff4 (some constant)
        matrix[1] = *(float*)&g_fCameraEpsilon;
        matrix[2] = g_fDefaultZoom;
        matrix[3] = *(float*)&g_fCameraEpsilon;
        matrix[4] = g_fDefaultZoom;
        matrix[5] = g_fDefaultZoom;
        matrix[6] = *(float*)&g_fCameraEpsilon;
        matrix[7] = g_fDefaultZoom;
        releaseFloatArray();
    }

    // Final updates
    updateCameraState();
    setViewportEnabled(1);
    selectPlayerCamera(currentCamID, 0);

    // Now do another lookup for the player's camera ID and clear its flag
    uint32_t newPlayerID = g_playerCameraID;
    if (g_playerStatePtr != 0)
        newPlayerID = *(uint32_t*)(g_playerStatePtr + 0x16c);

    for (idx = 0; idx < 0x14; idx++)
    {
        if (g_cameraSlotIDs[idx * 2] == newPlayerID)
        {
            g_cameraSlotFlags[idx * 2] &= 0xfffffffc;
            break;
        }
    }

    // Swap previous camera IDs and retarget
    uint32_t prevA = g_prevCameraID;
    uint32_t prevB = g_prevCameraID2;
    g_prevCameraID2 = 0;
    g_prevCameraID = newPlayerID;
    setCameraTarget(0, prevA, prevB);
    setViewportRect(0, 0, 0, 1.0f, 1.0f);

    // Update entity flags for the new player camera slot
    newPlayerID = g_playerCameraID;
    if (g_playerStatePtr != 0)
        newPlayerID = *(uint32_t*)(g_playerStatePtr + 0x16c);

    if (newPlayerID != 0xffffffff && newPlayerID < 0x1000)
    {
        uint32_t slotOffset = newPlayerID * 0x38;
        if (g_cameraSlotData[slotOffset] < 4)
        {
            if (*(int32_t*)(&g_cameraSlotData[slotOffset + 0x1c]) != 0)
            {
                setEntityFlags((void*)*(int32_t*)(&g_cameraSlotData[slotOffset + 0x1c]), 0x210000);
            }
            *(uint32_t*)(&g_cameraSlotData[slotOffset + 0x0c]) = 
                (*(uint32_t*)(&g_cameraSlotData[slotOffset + 0x0c]) & 0xfcad8fff) | 0x210000;
            notifyEntityChange();
        }
    }

    // Update entity flags for the previous camera
    if (currentCamID != 0xffffffff && currentCamID < 0x1000)
    {
        uint32_t slotOffset = currentCamID * 0x38;
        if (g_cameraSlotData[slotOffset] < 4)
        {
            if (*(int32_t*)(&g_cameraSlotData[slotOffset + 0x1c]) != 0)
            {
                setEntityFlags((void*)*(int32_t*)(&g_cameraSlotData[slotOffset + 0x1c]), 0x200000);
            }
            *(uint32_t*)(&g_cameraSlotData[slotOffset + 0x0c]) = 
                (*(uint32_t*)(&g_cameraSlotData[slotOffset + 0x0c]) & 0xfcac8fff) | 0x200000;
            notifyEntityChange();
        }
    }

    // Second set of FOV clamping and effect presets (likely for "transition" or "aim" mode)
    if (g_cameraFOV < 0x16) g_cameraFOV = 0x16;
    if (g_maxCameraFOV > 0x16) g_maxCameraFOV = 0x16;
    g_cameraEffect1 = 1;
    if (g_cameraFOV < 7) g_cameraFOV = 7;
    if (g_maxCameraFOV > 7) g_maxCameraFOV = 7;
    g_cameraEffect2 = 1;
    if (g_cameraFOV < 0xe) g_cameraFOV = 0xe;
    if (g_maxCameraFOV > 0xe) g_maxCameraFOV = 0xe;
    g_cameraEffect3 = 1;
    if (g_cameraFOV < 0x19) g_cameraFOV = 0x19;
    if (g_maxCameraFOV > 0x19) g_maxCameraFOV = 0x19;
    g_cameraEffect4 = 7;
    if (g_cameraFOV < 0x18) g_cameraFOV = 0x18;
    if (g_maxCameraFOV > 0x18) g_maxCameraFOV = 0x18;
    g_cameraEffect5 = 0;
    if (g_cameraFOV < 0xf) g_cameraFOV = 0xf;
    if (g_maxCameraFOV > 0xf) g_maxCameraFOV = 0xf;
    g_cameraEffect6 = 0;
    if (g_cameraFOV < 0x1b) g_cameraFOV = 0x1b;
    if (g_maxCameraFOV > 0x1b) g_maxCameraFOV = 0x1b;
    g_cameraEffect7 = 0;

    // Play sound effect for final transition (group 1, index 5, subIndex 6)
    playSoundEffect(1, 5, 6);

    // If the initial player camera ID matches the current one, decrement the switch counter
    if (savedPlayerID == newPlayerID)
    {
        g_cameraSwitchCounter--;
    }

    return 1;
}