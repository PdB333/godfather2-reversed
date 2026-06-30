// FUNC_NAME: PlayerMovementController::update
// Address: 0x006c7e60
// This function updates the player movement state, handling various movement modes,
// blending, and interaction with external components (e.g., cover, vehicle).
// It uses a state field at +0xe8 (0 = none, 0x48 = some specific state) and a flag at +0x2bc.

#include <cmath>

// Forward declarations of called functions (assumed to be in the same module)
void baseUpdate(int playerIndex, int someFlag);
void someInit(int stateIndex);
void someCleanup(int stateIndex);
float getTimeOrSpeed(int playerIndex);
void handleSpecialState(int playerIndex);
void* getGlobalFrameInfo();
float getRandomOffset();
void startMovementModeA(int playerIndex);
void startMovementModeB(int playerIndex, int flag);
void startDefaultMovement();
void computeTargetVector(float* src, float* dst, float* result);
void logDistance(float dist);
void updateCameraOrSomething(void* frameInfo);

// Global constants (inferred from usage)
extern const float ZERO_FLOAT;          // _DAT_00d5780c
extern const float SPEED_MULTIPLIER;    // _DAT_00d5c458
extern const float SOME_CONSTANT;       // _DAT_00d577a0
extern const float MAX_SPEED;           // _DAT_00d5eff8
extern const float SPEED_SCALE;         // _DAT_00e445c8
extern const int SOME_VALUE;            // _DAT_00e50e64
extern void** gEntityManager;           // _DAT_012233a0
extern const int SOME_FLAG;             // _DAT_00e44854
extern const unsigned int SOME_THRESHOLD; // _DAT_01205224
extern const int SOME_OTHER;            // _DAT_00e50e78

class PlayerMovementController {
public:
    // Offsets (relative to this):
    // +0x20: position (x)
    // +0x24: position (y)
    // +0x28: position (z)
    // +0x2c: position (w?) or padding
    // +0x40: velocity (x)
    // +0x44: velocity (y)
    // +0x48: velocity (z)
    // +0x4c: velocity (w?) or padding
    // +0x50: speed * scale
    // +0x60: some float (initialized to ZERO_FLOAT)
    // +0x70: distance
    // +0x80: interpolation factor
    // +0x88: state index (derived from +0xe8)
    // +0xe8: state enum (0, 0x48, or other)
    // +0x104: some float (e.g., acceleration)
    // +0x108: another float (e.g., max speed)
    // +0x110: another float
    // +0x118: start speed
    // +0x11c: end speed
    // +0x13c: some value (used for +0x2a8)
    // +0x140: another value
    // +0x14c: some value (copied to +0x2ac)
    // +0x1b8: some value (copied to +0x2f4)
    // +0x1c0: float
    // +0x1c4: float
    // +0x1d0: float
    // +0x1d4: float
    // +0x1e8: some value (copied to +0x284)
    // +0x1ec: some value (copied to +0x294)
    // +0x1f0: some value (copied to +0x2ec)
    // +0x204: unsigned int (used for threshold)
    // +0x214: target position x
    // +0x218: target position y
    // +0x21c: target position z
    // +0x220: current position x
    // +0x224: current position y
    // +0x228: current position z
    // +0x22c: velocity x
    // +0x230: velocity y
    // +0x234: velocity z
    // +0x238: target position x (from some component)
    // +0x23c: target position y
    // +0x240: target position z
    // +0x244: speed (clamped)
    // +0x24c: copied from position
    // +0x254: copied from position y
    // +0x268: zero
    // +0x26c: zero
    // +0x270: zero
    // +0x274: zero
    // +0x278: zero
    // +0x27c: zero
    // +0x280: zero
    // +0x284: copied from +0x1e8
    // +0x288: zero
    // +0x28c: ZERO_FLOAT
    // +0x290: zero
    // +0x294: copied from +0x1ec
    // +0x298: some float (initialized to ZERO_FLOAT or from state)
    // +0x2a8: selected value from +0x13c or +0x140
    // +0x2ac: copied from +0x14c
    // +0x2b0: copied from +0x108
    // +0x2b4: copied from +0x108
    // +0x2b8: zero
    // +0x2bc: flag (char) - indicates special state (e.g., in cover)
    // +0x2c0: zero
    // +0x2c4: SOME_VALUE
    // +0x2c8: pointer to some entity (from global array)
    // +0x2cc: DAT_00e44940
    // +0x2d0: SOME_FLAG
    // +0x2d4: ZERO_FLOAT
    // +0x2d8: SOME_OTHER
    // +0x2e0: computed float (speed * multiplier)
    // +0x2e4: zero
    // +0x2e8: zero
    // +0x2ec: copied from +0x1f0
    // +0x2f0: zero
    // +0x2f4: copied from +0x1b8
    // +0x2f8: unsigned int (threshold adjusted)
    // +0x2fc: delta x (target - current)
    // +0x300: delta y
    // +0x304: delta z
    // +0x308: zero
    // +0x30c: zero

    void update(int playerIndex, int someFlag);
};

void PlayerMovementController::update(int playerIndex, int someFlag) {
    float local_4; // used for query results

    // Base class update
    baseUpdate(playerIndex, someFlag);

    // Initialize some fields
    *(float*)((int)this + 0x60) = ZERO_FLOAT;
    *(int*)((int)this + 0x2cc) = DAT_00e44940;
    *(int*)((int)this + 0x2e4) = 0;
    *(int*)((int)this + 0x2e8) = 0;

    int state = *(int*)((int)this + 0xe8);
    if (state == 0 || state == 0x48) {
        // Simple state: compute speed from acceleration and max speed
        *(float*)((int)this + 0x2e0) = (*(float*)((int)this + 0x108) + *(float*)((int)this + 0x104)) * SPEED_MULTIPLIER;
    } else {
        // Complex state: handle component interaction
        int stateIndex = (state == 0) ? 0 : (state - 0x48);
        *(int*)((int)this + 0x88) = stateIndex;
        someInit(stateIndex);

        // Get pointer to component (state object)
        int* componentPtr = (state == 0) ? nullptr : (int*)(state - 0x48);
        if (componentPtr) {
            // Query component for a float value by hash (0xf8b45dfb)
            local_4 = 0.0f;
            char result = (**(code**)(*componentPtr + 0x10))(0xf8b45dfb, &local_4);
            bool flag = (result != 0 && local_4 != 0.0f);
            *(char*)((int)this + 0x2bc) = flag ? 1 : 0;

            if (flag) {
                // Query another value (0x10e5319e)
                local_4 = 0.0f;
                result = (**(code**)(*componentPtr + 0x10))(0x10e5319e, &local_4);
                if (result != 0 && local_4 != 0.0f) {
                    // Add component's offsets to movement parameters
                    float* componentData = (float*)(int)local_4;
                    *(float*)((int)this + 0x110) += componentData[0xaa8 / 4];
                    float addVal = componentData[0xaac / 4];
                    *(float*)((int)this + 0x104) += addVal;
                    *(float*)((int)this + 0x108) += addVal;
                    *(float*)((int)this + 0x1c0) += addVal;
                    *(float*)((int)this + 0x1c4) += addVal;
                    *(float*)((int)this + 0x1d0) += addVal;
                    *(float*)((int)this + 0x1d4) += addVal;
                }
            }
        }

        // Recompute speed
        *(float*)((int)this + 0x2e0) = (*(float*)((int)this + 0x104) + *(float*)((int)this + 0x108)) * SPEED_MULTIPLIER;

        someCleanup(stateIndex);

        // Get time or speed from player index
        float timeOrSpeed = getTimeOrSpeed(playerIndex);
        local_4 = timeOrSpeed;

        if (someFlag == 0 || timeOrSpeed == SOME_CONSTANT) {
            *(float*)((int)this + 0x298) = ZERO_FLOAT;
        } else {
            handleSpecialState(playerIndex);
        }

        // Copy global frame info to position
        int frameInfo = (int)getGlobalFrameInfo();
        *(float*)((int)this + 0x220) = *(float*)(frameInfo + 0x30);
        *(float*)((int)this + 0x224) = *(float*)(frameInfo + 0x34);
        *(float*)((int)this + 0x228) = *(float*)(frameInfo + 0x38);

        // Add random offset to Y position
        *(float*)((int)this + 0x224) += getRandomOffset();

        // Zero out many fields
        *(int*)((int)this + 0x27c) = 0;
        *(int*)((int)this + 0x268) = 0;
        *(int*)((int)this + 0x284) = *(int*)((int)this + 0x1e8);
        *(int*)((int)this + 0x294) = *(int*)((int)this + 0x1ec);
        *(int*)((int)this + 0x2b0) = *(int*)((int)this + 0x108);
        *(float*)((int)this + 0x24c) = *(float*)((int)this + 0x220);
        *(float*)((int)this + 0x250) = *(float*)((int)this + 0x224);
        *(float*)((int)this + 0x254) = *(float*)((int)this + 0x228);
        *(int*)((int)this + 0x2ec) = *(int*)((int)this + 0x1f0);

        // Choose movement mode based on flag and time
        bool flag = *(char*)((int)this + 0x2bc) != 0;
        if (!flag && timeOrSpeed != 0.0f) {
            if (someFlag == 0) {
                startMovementModeB(playerIndex, 0);
            } else {
                startMovementModeA(playerIndex);
            }
        } else {
            startDefaultMovement();
        }

        // Select value for +0x2a8 based on comparison
        float val298 = *(float*)((int)this + 0x298);
        if (ZERO_FLOAT <= val298) {
            *(int*)((int)this + 0x2a8) = *(int*)((int)this + 0x13c);
        } else {
            *(int*)((int)this + 0x2a8) = *(int*)((int)this + 0x140);
        }

        // Compute speed with interpolation
        float startSpeed = *(float*)((int)this + 0x118);
        float endSpeed = *(float*)((int)this + 0x11c);
        float interpFactor = *(float*)((int)this + 0x80);
        float speed = (endSpeed - startSpeed) * val298 + startSpeed;
        speed = (speed - startSpeed) * interpFactor + startSpeed;
        *(float*)((int)this + 0x244) = speed;

        // Clamp speed if not in special state
        if (!flag) {
            if (speed > 0.0f) {
                if (speed > MAX_SPEED) speed = MAX_SPEED;
            } else {
                speed = 0.0f;
            }
            *(float*)((int)this + 0x244) = speed;
        }

        // Zero out more fields
        *(int*)((int)this + 0x26c) = 0;
        *(char*)((int)this + 0x270) = 0;
        *(int*)((int)this + 0x274) = 0;
        *(char*)((int)this + 0x278) = 0;
        *(int*)((int)this + 0x280) = 0;
        *(int*)((int)this + 0x288) = 0;
        *(float*)((int)this + 0x28c) = ZERO_FLOAT;
        *(int*)((int)this + 0x290) = 0;
        *(int*)((int)this + 0x2ac) = *(int*)((int)this + 0x14c);

        // If in special state or time is zero, compute target vector and set position/velocity
        if (flag || timeOrSpeed == 0.0f) {
            float* targetPos = (float*)((int)this + 0x238);
            float* currentPos = (float*)((int)this + 0x220);
            computeTargetVector(currentPos, targetPos, targetPos);
            *(float*)((int)this + 0x20) = targetPos[0];
            *(float*)((int)this + 0x24) = targetPos[1];
            *(float*)((int)this + 0x2c) = ZERO_FLOAT;
            *(float*)((int)this + 0x28) = targetPos[2];
            *(float*)((int)this + 0x40) = *(float*)((int)this + 0x22c);
            *(float*)((int)this + 0x44) = *(float*)((int)this + 0x230);
            *(float*)((int)this + 0x4c) = ZERO_FLOAT;
            *(float*)((int)this + 0x48) = *(float*)((int)this + 0x234);
            *(float*)((int)this + 0x50) = speed * SPEED_SCALE;
        }

        // Compute distance between current and target positions
        float dx = *(float*)((int)this + 0x238) - *(float*)((int)this + 0x220);
        float dy = *(float*)((int)this + 0x23c) - *(float*)((int)this + 0x224);
        float dz = *(float*)((int)this + 0x240) - *(float*)((int)this + 0x228);
        float dist = sqrtf(dx*dx + dy*dy + dz*dz);
        *(float*)((int)this + 0x70) = dist;
        logDistance(dist);

        // Copy more values
        *(int*)((int)this + 0x2b4) = *(int*)((int)this + 0x108);
        *(int*)((int)this + 0x2b8) = 0;
        *(int*)((int)this + 0x2c0) = 0;
        *(int*)((int)this + 0x2c4) = SOME_VALUE;
    }

    // Common finalization
    *(int*)((int)this + 0x2f4) = *(int*)((int)this + 0x1b8);

    // Get entity pointer from global manager
    int* entityArray = *(int**)(gEntityManager + 4);
    int* entity = entityArray[playerIndex];
    if (entity != nullptr) {
        entity = (int*)((int)entity - 0x1f30);
    }
    *(int*)((int)this + 0x2c8) = (int)entity;
    if (entity != nullptr) {
        // Clear a bit in the entity's flags
        *(unsigned int*)((int)entity + 0x249c) &= 0xffbfffff;
    }

    *(int*)((int)this + 0x2d0) = SOME_FLAG;
    *(float*)((int)this + 0x2d4) = ZERO_FLOAT;
    *(int*)((int)this + 0x2f0) = 0;

    // Compute delta vectors (target - current)
    *(float*)((int)this + 0x2fc) = *(float*)((int)this + 0x214) - *(float*)((int)this + 0x220);
    *(float*)((int)this + 0x300) = *(float*)((int)this + 0x218) - *(float*)((int)this + 0x224);
    *(float*)((int)this + 0x304) = *(float*)((int)this + 0x21c) - *(float*)((int)this + 0x228);

    unsigned int threshold = SOME_THRESHOLD;
    *(unsigned int*)((int)this + 0x2f8) = threshold;
    if (*(unsigned int*)((int)this + 0x204) < threshold) {
        *(unsigned int*)((int)this + 0x2f8) = threshold - *(unsigned int*)((int)this + 0x204);
    }

    *(int*)((int)this + 0x2d8) = SOME_OTHER;

    // If in special state and state is not 0 or 0x48, update camera or something
    bool flag = *(char*)((int)this + 0x2bc) != 0;
    int state = *(int*)((int)this + 0xe8);
    if (flag && state != 0 && state != 0x48) {
        int frameInfo = (int)getGlobalFrameInfo();
        updateCameraOrSomething((void*)(frameInfo + 0x20));
    }

    *(char*)((int)this + 0x308) = 0;
    *(int*)((int)this + 0x30c) = 0;
}