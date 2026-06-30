// FUNC_NAME: EARSCharacter::computeDesiredMovement

#include <cstdint>

// Constants from globals (addresses in comments)
const float kOne               = 1.0f;                     // DAT_00e2b1a4
const float kTimeWrapAdjust    = 1.0f;                     // DAT_00e44578
const float kSpeedFactor       = 1.0f;                     // DAT_00e2e210 (maybe reciprocal of time?)
const float kMinTimeThreshold  = 0.001f;                   // DAT_00e44598
const float kForceScale        = 1.0f;                     // DAT_00e32850
const float kMinDistanceSq     = 0.01f;                    // _DAT_0110a6ac

// Forward declaration of helper function (reads controller data)
void getControllerData(void* pController, void* pOut);     // FUN_0056cef0

// Structure of the controller array entries (0x30 bytes each)
struct ControllerData {
    char pad_0x00[0x10];
    float posX;               // +0x10
    float posY;               // +0x14
    float posZ;               // +0x18
    int32_t timestamp;        // +0x20
    char pad_0x24[0x0C];      // to 0x30
};

// Main class (this)
class EARSCharacter {
public:
    void* getController() const;  // returns pointer at +0x168
    bool computeDesiredMovement(float* outForce); // this function
};

// Implementation
bool __thiscall EARSCharacter::computeDesiredMovement(float* outForce) {
    // Get the controller object from this
    uint8_t* pController = *(uint8_t**)(this + 0x168);
    if (!pController) return false;

    // Check if controller has enough data
    if (pController[0x60] <= 1 || pController[0x62] == 0) {
        outForce[0] = 0.0f;
        outForce[1] = 0.0f;
        outForce[2] = 0.0f;
        return false;
    }

    // Read first controller entry (index based on bit 0 of byte at 0x61)
    int32_t idx0 = (pController[0x61] & 1);
    ControllerData cd0;
    // The helper function reads from pController + idx0 * 0x30 and writes to cd0
    getControllerData(pController + idx0 * 0x30, &cd0);

    // Extract position and timestamp from first entry
    float posX0 = cd0.posX;
    float posY0 = cd0.posY;
    float posZ0 = cd0.posZ;
    int32_t time0 = cd0.timestamp;

    // Read second controller entry (index = (byte at 0x61 - 1) & 1)
    int32_t idx1 = (pController[0x61] - 1) & 1;
    ControllerData cd1;
    getControllerData(pController + idx1 * 0x30, &cd1);

    // Compute time difference
    int32_t deltaTime = time0 - cd1.timestamp;
    float fDelta = (float)deltaTime;
    if (deltaTime < 0) {
        fDelta += kTimeWrapAdjust;
    }

    // Check if time difference is too small
    float scaledDelta = fDelta * kSpeedFactor;
    if (kMinTimeThreshold >= scaledDelta) {
        outForce[0] = 0.0f;
        outForce[1] = 0.0f;
        outForce[2] = 0.0f;
        return false;
    }

    // Compute velocity from position difference scaled by inverse time
    float invDelta = kOne / scaledDelta;
    float velX = invDelta * (posX0 - cd1.posX);
    float velY = invDelta * (posY0 - cd1.posY);
    float velZ = invDelta * (posZ0 - cd1.posZ);

    // Check if velocity magnitude is above threshold
    float magSq = velX * velX + velY * velY + velZ * velZ;
    if (magSq <= kMinDistanceSq) {
        outForce[0] = 0.0f;
        outForce[1] = 0.0f;
        outForce[2] = 0.0f;
        return false;
    }

    // Scale force vector and store result (fourth component is scaled invDelta)
    outForce[0] = kForceScale * velX;
    outForce[1] = kForceScale * velY;
    outForce[2] = kForceScale * velZ;
    outForce[3] = kForceScale * invDelta;

    return true;
}