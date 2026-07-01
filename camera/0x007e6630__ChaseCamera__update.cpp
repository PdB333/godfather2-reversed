// FUNC_NAME: ChaseCamera::update

// Function address: 0x007e6630
// Role: Per-frame update for the chase camera: manages camera stack transitions, plays camera effects, handles interaction queries, and computes final camera position.

class ChaseCamera {
public:
    void update(); // __thiscall
};

// Forward declarations for structures (offsets approximate)
struct CameraStackNode {
    // +0x00 vtable
    // +0x10 virtual function (query)
    // +0x12 next/prev pointers? (offset 0x48 from container)
};

struct CameraManager {
    // +0x34 camera mode (0=follow,1=chase,2=something)
    // +0x58 base? Actually used as pointer to this
    // +0x31a8 camera stack head pointer
    // +0x31ac camera stack next? 
    // +0x8e0 flags (bit 10 pause-related)
    // +0x30c0 some state (0 or 0x48 when not free)
};

struct PlayerManager {
    // +0x35c player pointer?
};

struct Player {
    // ...
};

struct InteractionManager {
    // ...
};

// Global data (likely singletons)
extern CameraManager* gCameraManager; // DAT_01129938
extern float gCameraSpeed;           // DAT_00d6fa90
extern float gCameraDamping;         // DAT_00d6fa94

// Forward declarations of helper functions (names guessed from context)
bool isCutsceneActive();            // FUN_00410de0
bool isDialogueActive();            // FUN_00410e10
void linkedListRemove(void* list);  // FUN_004daf90
PlayerManager* getPlayerManager();  // FUN_00800a90
void setCameraTarget(void* player); // FUN_00702e90
void playCameraEffect(int effectId, int param); // FUN_0079f100
InteractionManager* getInteractionManager(); // FUN_007ab1f0
bool canInteract(uint queryResult); // FUN_00798eb0
uint beginInteraction();            // FUN_006fbc40
void showInteractionPrompt(void* prompt, uint typeAndId); // FUN_007f96a0
void endInteraction();              // FUN_006fbc70
void handleInteraction(uint queryResult); // FUN_007e60b0

void computeTargetOffset(Vec3* outOffset, Vec3* cameraPos, Vec3* velocity, CameraManager* mgr); // FUN_007e4e00
bool isGamePaused();                // FUN_00800b10
void calculateFinalCameraPosition(Vec3* outPos, Vec3* newPos, Vec3* targetOffset, CameraManager* mgr); // FUN_007e59a0
void setCameraTransform(Vec3* pos); // FUN_0072a0b0

void ChaseCamera::update()
{
    // Camera stack node management
    CameraStackNode* pDesiredNode = nullptr;
    CameraStackNode* pCurrentNode = nullptr;

    if (*(int*)(this + 0x1e4) != 0) {
        pDesiredNode = (CameraStackNode*)(*(int*)(this + 0x1e4) - 0x48);
    }

    CameraManager* pCamMgr = *(CameraManager**)(this + 0x58);
    uint queryResult = 0;

    // Determine camera mode from global manager
    int camMode;
    if (gCameraManager->field_0x34 == 0) {
        camMode = 2;
    } else if (gCameraManager->field_0x34 == 1) {
        camMode = 0;
    } else {
        camMode = 1;
    }

    // In chase mode (1) check for cutscene/dialogue; in mode 2 force null
    if (camMode == 1) {
        if (isCutsceneActive() || isDialogueActive()) {
            pDesiredNode = nullptr;
        }
    } else if (camMode == 2) {
        pDesiredNode = nullptr;
    }

    // Get current stack node from camera manager
    CameraStackNode** pStackHead = (CameraStackNode**)((int*)pCamMgr + 0x31a8); // offset 0xC6A0? Actually 0x31a8/sizeof(int)
    CameraStackNode* pStackHeadNode = *pStackHead;
    CameraStackNode* pCurrentFromStack = nullptr;
    if (pStackHeadNode != nullptr) {
        pCurrentFromStack = (CameraStackNode*)((int)pStackHeadNode - 0x48);
    }

    // Compute desired node's 'list entry' offset
    CameraStackNode* pNodeToSet = nullptr;
    if (pDesiredNode != nullptr) {
        pNodeToSet = (CameraStackNode*)((int*)(pDesiredNode) + 0x12); // +0x48 bytes
    }

    // Update camera stack if needed
    if (*pStackHead != pNodeToSet) {
        if (*pStackHead != nullptr) {
            linkedListRemove(pStackHead);
        }
        *pStackHead = (int)pNodeToSet;
        if (pNodeToSet != nullptr) {
            *(int*)((int*)pCamMgr + 0x31ac) = *(int*)((int*)pNodeToSet + 1);
            *(int*)((int*)pNodeToSet + 1) = (int)pStackHead;
        }
    }

    // Query the desired node for permissions (virtual, hash 0x369ac561)
    queryResult = 0;
    if (pDesiredNode != nullptr) {
        bool canQuery = ((int (__thiscall*)(CameraStackNode*, uint, uint*))(*(int**)pDesiredNode)[4])(pDesiredNode, 0x369ac561, &queryResult);
        if (canQuery) {
            queryResult = queryResult; // (actual result)
        } else {
            queryResult = 0;
        }
    }

    // If the desired node is already current, skip effects
    if (pDesiredNode == pCurrentFromStack) {
        goto LAB_007e67c8;
    }

    // Get player manager and set camera target
    PlayerManager* pPlayerMgr = getPlayerManager();
    if (pPlayerMgr != nullptr) {
        setCameraTarget(*(void**)((int*)pPlayerMgr + 0x35c));
    }

    // Play camera effects based on flags at +0x1d8
    uint flags = *(uint*)(this + 0x1d8);
    if ((flags & 1) == 0) {
        if ((flags & 2) != 0) {
            playCameraEffect(0x12, 0); // e.g., zoom in
        } else if ((flags & 4) != 0) {
            playCameraEffect(0x13, 0); // e.g., zoom out
        }
    } else {
        playCameraEffect(0x11, 0); // e.g., shake
    }
    playCameraEffect(0, 0); // reset effects

    // Handle interaction query result
    if (queryResult != 0) {
        InteractionManager* pIntMgr = getInteractionManager();
        if (pIntMgr != nullptr && canInteract(queryResult)) {
            uint interactionId = beginInteraction();
            showInteractionPrompt(nullptr, interactionId | 0x40); // prompt
            endInteraction();
        }
        handleInteraction(queryResult);
    }

LAB_007e67c8:
    // Compute target position offset from current camera data
    Vec3 targetOffset;
    Vec3 targetVelocity = *(Vec3*)(this + 0x180); // velocity
    computeTargetOffset(&targetOffset, (Vec3*)(this + 0x174), &targetVelocity, pCamMgr);

    // Get global damping and speed
    float damping = gCameraDamping; // DAT_00d6fa94
    float speed = gCameraSpeed;     // DAT_00d6fa90

    // Adjust speed if game is not paused or camera state indicates free movement
    if (!isGamePaused() || ((*(uint*)((int*)pCamMgr + 0x8e0) >> 10 & 1) == 0)) {
        if (*(int*)((int*)pCamMgr + 0x30c0) == 0 || *(int*)((int*)pCamMgr + 0x30c0) == 0x48) {
            speed = damping; // use damping when state is free
        }
    }

    // Compute new camera position = velocity * speed + offset
    Vec3 newPos;
    newPos.x = targetVelocity.x * speed + targetOffset.x;
    newPos.y = targetVelocity.y * speed + targetOffset.y;
    newPos.z = targetVelocity.z * speed + targetOffset.z;

    // Final camera position calculation and apply
    Vec3 finalPos;
    calculateFinalCameraPosition(&finalPos, &newPos, &targetOffset, pCamMgr);
    setCameraTransform(&finalPos);
}