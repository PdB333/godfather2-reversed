// FUNC_NAME: ChaseCamera::update

// Reconstructed from Ghidra export at 0x006d24d0
// This function updates a ChaseCamera component each frame, handling
// camera position blending, target selection, and transitions between
// player and AI controlled states.

// Known offsets relative to this pointer:
// +0x08: cameraPosition (4 floats, likely x,y,z,w)
// +0x0C: cameraTargetPosition (4 floats)
// +0x2C: currentCameraPosition (4 floats, maybe interpolated)
// +0x34: cameraIndex (used to fetch camera target from manager)
// +0x35: targetIndex (index into an array of game objects)
// +0x36: vtable pointer (points to a camera functions table)
// +0x38: blendFactor (float, used for smoothing)
// +0x39: transitionTimer (float, countdown for camera transitions)
// +0x3A: lifetime (float, accumulated delta time)

// Known global variables (renamed based on usage):
extern float g_cameraDeltaClamp;       // DAT_00e510d0, clamps accumulated delta
extern float g_cameraDeltaMin;         // DAT_00e510cc
extern float *g_objectManagerBase;     // DAT_012233a0 + 4, pointer to object array base
extern float g_transitionTimeMax;      // DAT_00d5c454, max transition time
extern float g_angleThreshold;         // DAT_00d5e288, angle threshold for singleplayer
extern float g_blendDecay;             // DAT_00d5f378, decay factor for blend
extern float g_blendScale;             // _DAT_00d5cf70, scale for blend
extern float g_cameraHeight;           // DAT_00e51104, camera height
extern float g_cameraDistance;         // DAT_00e445c8, base camera distance
extern float g_cameraMinAngle;         // DAT_00e51170, min camera angle
extern float g_cameraMaxAngle;         // DAT_00e51178, max camera angle
extern float g_cameraAngle;            // DAT_00e51174, current angle
extern float g_cameraStrafeFactor;     // DAT_0112a870, strafe factor
extern float g_cameraStrafeFactor2;    // DAT_00e51110, alternate strafe factor
extern float g_lifetimeThreshold;      // DAT_00e5116c, lifetime threshold for transition
extern float g_moveSpeedThreshold;     // DAT_00e51180, movement speed threshold
extern float g_targetDistThreshold;    // DAT_00e44598, distance threshold for target change
extern bool g_isStrafing;              // DAT_0112a863
extern float g_cameraPlayerMode;       // DAT_0112a868, player mode indicator

// External functions (declared with meaningful names)
bool isSinglePlayer();                                                      // FUN_0089c630
bool checkValidity(float *vec);                                             // FUN_006d1b10
float* getPositionData(void *obj);                                          // FUN_006d1ec0 (returns +0x30 offset?)
float getAngle(float *vec);                                                 // FUN_006d0200
void resetCameraTransition(void *p);                                        // FUN_006d52c0
void sendEvent(int eventID, int targetID, float param, int type, int unk1, int unk2); // FUN_00424df0
int* getEntityByID(int id);                                                 // FUN_00410540 (returns entity with flags)
void* getCameraTransform();                                                 // FUN_00471610 (returns 4x4 matrix)
bool checkCameraOverride(float *uVar8);                                     // FUN_006d1e50 (checks if some condition)
void setCameraImmediate();                                                  // FUN_006d1f00
void computeCameraBlend(float *pOutBlendX, float *pOutBlendY, int cameraIndex, float deltaTime); // FUN_006d1c20
bool isGamePaused();                                                        // FUN_00410d80
void computeLookAt(float *pos, float *target, int unk, float *yaw, float *pitch, float *roll); // FUN_00473bc0

// Forward declarations for class methods
class ChaseCamera;

// Class definition (partial)
class ChaseCamera {
public:
    void update(float deltaTime);
private:
    // Fields as per offsets
    float cameraPosition[4];           // +0x08
    float cameraTarget[4];             // +0x0C
    float currentPosition[4];          // +0x2C
    int cameraIndex;                   // +0x34
    int targetIndex;                   // +0x35
    void **vtable;                     // +0x36
    float blendFactor;                 // +0x38
    float transitionTimer;             // +0x39
    float lifetime;                    // +0x3A

    // Additional fields inferred from usage
    float m_unk0x1c[4];                // +0x1C (immediate camera position?)
    float m_unk0x30[4];                // +0x30 (immediate target?)
    float m_unk0x10;                   // +0x10 (maybe yaw)
    float m_unk0x11;                   // +0x11 (pitch)
    float m_unk0x12;                   // +0x12 (roll)
    float m_unk0x14;                   // +0x14 (unknown timer)
};

// Implementation
void ChaseCamera::update(float deltaTime) {
    // Update accumulated lifetime
    this->lifetime += deltaTime;
    g_cameraDeltaClamp += deltaTime;
    // Clamp g_cameraDeltaClamp between 0 and g_cameraDeltaMin
    if (g_cameraDeltaClamp < 0.0f) {
        g_cameraDeltaClamp = 0.0f;
    } else if (g_cameraDeltaClamp > g_cameraDeltaMin) {
        g_cameraDeltaClamp = g_cameraDeltaMin;
    }

    // Fetch target object from global manager array
    int *objectManager = *(int **)(*(int *)(0x012233a0) + 4); // DAT_012233a0+4
    int *targetObject = *(int **)(objectManager + this->targetIndex); // each entry is pointer
    if (targetObject == nullptr) {
        // No target, reset timer and index
        this->transitionTimer = g_transitionTimeMax;
        this->targetIndex = 0;
    } else {
        // Subtract 0x1f30 to get the object's base component
        int *componentBase = targetObject - 0x1f30/4; // offset 0x1f30 in bytes
        if (componentBase == nullptr) {
            this->transitionTimer = g_transitionTimeMax;
            this->targetIndex = 0;
        } else {
            // Check if object is player-controlled and not in certain states
            uint flagsPlayer = *(uint *)(targetObject + 0x56c/4); // +0x56c
            bool isPlayerControlled = (flagsPlayer >> 5) & 1;
            if (!isPlayerControlled &&
                checkValidity(this->cameraPosition) == false &&
                checkValidity(this->cameraTarget) == false) {
                // Get target position
                float *targetPos = getPositionData(this->currentPosition);
                float angleToTarget = getAngle(targetPos + 0x30/4); // +0x30
                if (angleToTarget > g_angleThreshold) {
                    // In player mode, check if we should force transition
                    if (isSinglePlayer()) {
                        // Force immediate transition
                        (*(void (**)(int, int))(*(int *)this->vtable)[1])(this->cameraIndex, 1);
                    }
                }
            } else {
                // Object is not eligible, force transition
                if (isSinglePlayer()) {
                    (*(void (**)(int, int))(*(int *)this->vtable)[1])(this->cameraIndex, 1);
                } else {
                    (*(void (**)(int, int))(*(int *)this->vtable)[1])(this->targetIndex, 1);
                }
            }
        }
    }

    // Get the base object for current camera mode (player/ai)
    int *baseObj = *(int **)(*(int *)(0x012233a0) + 4);
    int *baseComponent;
    if (baseObj == nullptr) {
        baseComponent = nullptr;
    } else {
        baseComponent = baseObj - 0x1f30/4;
    }
    if (isSinglePlayer()) {
        baseComponent = baseObj - 0x1f30/4; // reuse
    }

    // Handle transition timer and camera shake event
    if (this->transitionTimer <= 0.0f) {
        // Camera shake check from component
        uint shakeResult = (**(uint (**)(void))(*(int *)(baseComponent[0x7cc] + 8)))();
        float shakeFactor = (float)shakeResult;
        if (isSinglePlayer()) {
            int *entity = getEntityByID((int)shakeFactor);
            if (entity != nullptr && (*(uint *)(entity + 0x10) & 0x40) != 0 && (*(uint *)(entity + 0x12) & 0x40) == 0) {
                this->transitionTimer = g_transitionTimeMax;
            }
        }
    } else {
        // Decrease transition timer
        this->transitionTimer -= deltaTime;
        if (this->transitionTimer <= 0.0f) {
            if (isSinglePlayer()) {
                resetCameraTransition(this->cameraPosition);
            }
            this->transitionTimer = 0.0f;
            // Send event (camera transition complete?)
            if (this->cameraPosition[3] == 0.0f) {
                // No target? use 0
                sendEvent(0, 0, g_transitionTimeMax, 8, 0, 0);
            } else {
                sendEvent(0, (int)(this->cameraPosition[3] - 0x48), g_transitionTimeMax, 8, 0, 0);
            }
            return;
        }
    }

    // Update some timer field
    this->m_unk0x14 = (int)(g_cameraHeight * g_cameraDistance);

    // Clamp camera angle if needed
    float angle = g_cameraAngle;
    if (angle < g_cameraMinAngle || angle > g_cameraMaxAngle) {
        g_cameraAngle = angle; // clamp? actually set equal
    }

    // Re-fetch base component if needed
    if (baseComponent == nullptr) {
        int *baseObjTemp = *(int **)(*(int *)(0x012233a0) + 4);
        if (baseObjTemp == nullptr) {
            baseComponent = nullptr;
        } else {
            baseComponent = baseObjTemp - 0x1f30/4;
        }
        this->targetIndex = 0;
    }

    // Update blend factor with strafe influence
    float strafeFactor = g_cameraStrafeFactor;
    if ((*(uint *)(baseComponent + 0x238) >> 1) & 1) {
        strafeFactor = g_cameraStrafeFactor2;
    }
    this->blendFactor = this->blendFactor * g_blendDecay + strafeFactor * g_blendScale;

    // Get camera transformation matrix
    float *cameraMatrix = (float *)getCameraTransform();
    float camPos[4] = {cameraMatrix[0], cameraMatrix[1], cameraMatrix[2], cameraMatrix[3]};
    float camTarget[4] = {cameraMatrix[4], cameraMatrix[5], cameraMatrix[6], cameraMatrix[7]}; // Actually, likely the last 4 are position? Need to check matrix layout.
    // But decompiled shows copying 12 floats? Actually local_50 to local_30 are first 12? Hard to tell. We'll treat as 4x4.
    // For simplicity, we'll assume getCameraTransform returns a 4x4 matrix in row-major.
    // The function picks out specific elements: local_20 = puVar7[0xc], fStack_1c = puVar7[0xd] + this->blendFactor, etc.
    float currentCamPos[4] = {0,0,0,0}; // Placeholder
    // In decompilation: local_20 = (float)puVar7[0xc]; fStack_1c = (float)this->blendFactor + (float)puVar7[0xd];
    // fStack_18 = (float)puVar7[0xe]; fStack_14 = (float)puVar7[0xf];
    // So likely matrix[12..15] is position.
    float cameraWorldPos[4] = {cameraMatrix[12], cameraMatrix[13]+this->blendFactor, cameraMatrix[14], cameraMatrix[15]};

    // Compute difference between camera position and target position (this->currentPosition)
    float dx = cameraWorldPos[0] - this->currentPosition[0];
    float dy = cameraWorldPos[1] - this->currentPosition[1];
    float dz = cameraWorldPos[2] - this->currentPosition[2];
    float dw = cameraWorldPos[3] - this->currentPosition[3];

    // Check if we need to update target based on distance or flags
    bool needUpdate = false;
    if (((*(uint *)(baseComponent + 0x23a) >> 9) & 1) != 0) {
        // Force immediate update if flag set
        needUpdate = true;
    } else {
        float distSq = dx*dx + dy*dy + dz*dz;
        float speed = sqrt(distSq) / deltaTime;
        if (speed > g_moveSpeedThreshold) {
            needUpdate = false; // otherwise too fast? Wait, logic: if speed <= threshold then skip?
            // Actually the decompiled: SQRT(...)/param_2 <= _DAT_00e51180 => then bVar3=false, else true.
            // So if speed <= threshold, needUpdate=false; else needUpdate=true.
            // But the code sets bVar3 = false after the check if condition true, else bVar3 = false? Let's re-read.
            // The decompiled: if ( (flag) || (speed <= threshold) ) { bVar3=false; } else { bVar3=true; }
            // So needUpdate is set true only if speed > threshold AND flag not set.
            needUpdate = (speed > g_moveSpeedThreshold);
        }
    }

    // Additional check: if lifetime > threshold and not needUpdate, check component flags
    if ((this->lifetime > g_lifetimeThreshold) && !needUpdate && (((*(uint *)(baseComponent + 0x928) >> 0x14) & 1) == 0)) {
        // Check for camera override
        uint overrideResult = (**(uint (**)(void))(*(int *)(baseComponent[0x7cc] + 8)))();
        if (checkCameraOverride((float *)overrideResult)) {
            needUpdate = true;
        }
    }

    g_isStrafing = (g_cameraPlayerMode != 0.0f);

    if (needUpdate) {
        // Immediate camera set
        setCameraImmediate();
        this->cameraPosition[0] = this->m_unk0x1c[0];
        this->cameraPosition[1] = this->m_unk0x1c[1];
        this->cameraPosition[2] = this->m_unk0x1c[2];
        this->cameraPosition[3] = this->m_unk0x1c[3];
        this->cameraTarget[0] = this->m_unk0x30[0];
        this->cameraTarget[1] = this->m_unk0x30[1];
        this->cameraTarget[2] = this->m_unk0x30[2];
        this->cameraTarget[3] = this->m_unk0x30[3];
        // Call vtable function (index 0? probably "setPositionAndTarget")
        ((void (*)(float*, float*, float*))(*(void **)this->vtable[0]))(this->cameraPosition, this->cameraTarget, &cameraWorldPos[0]);
    } else {
        // Blend camera
        float blendX, blendY;
        computeCameraBlend(&blendX, &blendY, this->cameraIndex, deltaTime);
        if ((this->lifetime <= g_lifetimeThreshold) && (g_lifetimeThreshold != this->lifetime)) {
            blendY = 0.0f;
        }
        if (!isGamePaused() && ((*(int *)(baseComponent + 0x239) < 0) || (((*(uint *)(baseComponent + 0x239) >> 0x1e) & 1) != 0))) {
            blendX = 0.0f;
            blendY = 0.0f;
        }
        // Call vtable function (index 1, maybe "blendCamera")
        ((void (*)(int*, int, float, float, float, float*, int))(*(int *)(this->vtable[0]))[1])(baseComponent, 0, deltaTime, blendX, blendY, cameraMatrix, 0);

        // Get current camera data from vtable functions (indices 4 and 5?)
        float *camDataA = (float*)((*(int (**)(void))(this->vtable[0] + 0x10))());
        float *camDataB = (float*)((*(int (**)(void))(this->vtable[0] + 0x14))());
        float diffX = camDataB[0] - camDataA[0];
        float diffY = camDataB[1] - camDataA[1];
        float diffZ = camDataB[2] - camDataA[2];
        float diffW = camDataB[3] - camDataA[3];
        float dist2D = sqrt(diffX*diffX + diffY*diffY);
        if (dist2D <= g_targetDistThreshold) {
            // Use target from vtable index 3 (maybe "getTarget")
            ((void (*)(float*, float*, float*))(*(int *)(this->vtable[0] + 0xc)))(this->cameraPosition, this->cameraTarget, &cameraMatrix[5]); // &uStack_3c is part of matrix
        } else {
            // Use positions from camDataA and camDataB
            int *posA = (int*)camDataA;
            int *posB = (int*)camDataB;
            this->cameraPosition[0] = posA[0];
            this->cameraPosition[1] = posA[1];
            this->cameraPosition[2] = posA[2];
            this->cameraPosition[3] = posA[3];
            this->cameraTarget[0] = posB[0];
            this->cameraTarget[1] = posB[1];
            this->cameraTarget[2] = posB[2];
            this->cameraTarget[3] = posB[3];
        }
    }

    // Compute lookAt orientation from camera position and target
    float *posPtr = this->cameraPosition;
    computeLookAt(posPtr, this->cameraTarget, 0, &this->m_unk0x11, &this->m_unk0x10, &this->m_unk0x12);

    // Store results into base component? (Actually stores into local_7c which is now baseComponent)
    baseComponent[0] = *(int*)&cameraWorldPos[0]; // uStack_2c? Hard to map.
    baseComponent[1] = *(int*)&cameraWorldPos[1];
    baseComponent[2] = *(int*)&cameraWorldPos[2];
    baseComponent[3] = *(int*)&cameraWorldPos[3];

    // Store into global debug vars for rendering
    g_debugCameraPos[0] = *posPtr;
    g_debugCameraPos[1] = this->cameraPosition[1];
    g_debugCameraPos[2] = this->cameraPosition[2];
    g_debugCameraPos[3] = this->cameraPosition[3];
    g_debugCameraTarget[0] = this->cameraTarget[0];
    g_debugCameraTarget[1] = this->cameraTarget[1];
    g_debugCameraTarget[2] = this->cameraTarget[2];
    g_debugCameraTarget[3] = this->cameraTarget[3];

    if (isSinglePlayer()) {
        int debugData[3] = {*posPtr, this->cameraPosition[1], this->cameraPosition[2]};
        ((void (*)(int*))(*(int *)g_unknownEBX + 0x1c))(&debugData);
    }
    return;
}