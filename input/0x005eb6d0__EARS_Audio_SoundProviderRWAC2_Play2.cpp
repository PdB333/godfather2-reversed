// Xbox PDB: EARS::Audio::SoundProviderRWAC2::Play2
// FUNC_NAME: ControllerManager::applyVibration

// Address: 0x005eb6d0
// Role: Applies rumble/vibration configuration to a controller slot based on parameters from an animation or input event.
// The function validates controller connectivity, clamps speeds, wraps angles, and updates internal controller state with motor speeds and optional transformation data.

#include <cstdint>

class ControllerManager {
public:
    // Controller state structure (size 0xF8)
    struct ControllerSlot {
        float speed;             // +0x04  (param_5)
        float angle;             // +0x08 (wrapped fVar14)
        // padding at +0x0C?
        float leftMotor;         // +0x10 (param_7)
        float rightMotor;        // +0x14 (param_8)
        void* dataPtr;           // +0x18 (from param_3+8)
        // unknown up to +0xAC
        int32_t zeroFlag;        // +0xAC (set to 0)
        double transformValue;   // +0xB0
        // some buffer at +0xBC used by commit
        int32_t dcFlag;          // +0xDC (must be non-zero)
        int32_t e0Flag;          // +0xE0 (must be zero)
        int32_t patternIndex;    // +0xEC (param_10)
        uint32_t extraParam;     // +0xF0 (param_11)
    };

    // Constants (likely defined elsewhere in the engine)
    static constexpr float kTwoPi = 6.2831855f;                     // DAT_00e2af34
    static constexpr float kMaxRumbleSpeed = 1.0f;                  // DAT_00e2b1a4
    static constexpr float kMaxMagnitude = 1.0f;                    // DAT_00e2b04c
    static constexpr float kAngleScale = 0.017453292f;              // DAT_011274f0 (degrees to radians?)
    static constexpr float kIntToFloatOffset = 256.0f;              // DAT_00e44578 (for negative conversion)

    // Offset to the bool at +0x588
    bool isRumbleEnabled() const { return *(char*)((uintptr_t)this + 0x588) != 0; }
    // Offset to the controller array at +0x5A0
    ControllerSlot* getControllerSlot(uint32_t index) {
        return reinterpret_cast<ControllerSlot*>((uintptr_t)this + 0x5A0 + (index & 0xFFFF) * sizeof(ControllerSlot));
    }

    // Internal functions (stubs for calls)
    bool isControllerValid(int32_t index);
    bool isLeftMotorValid();
    bool isRightMotorValid();
    bool isBothMotorsValid();
    void beginRumbleUpdate();
    void endRumbleUpdate();
    void prepareRumbleFrame();
    void setMotorSpeed(int32_t motorIndex, float speed);
    void getTransform(uint32_t source, uint32_t target, float* out);
    bool commitRumble(uint32_t extra, uint32_t buffer);
};

// __thiscall function
uint32_t __thiscall ControllerManager::applyVibration(uint32_t controllerIndex, void* sourceData,
    int32_t slotIndex, float magnitude, float angleDeg, float leftMotorSpeed, float rightMotorSpeed,
    float* motionData, int32_t patternIndex, uint32_t extraParam)
{
    uint32_t result = 1;
    if (!this->isRumbleEnabled() || sourceData == nullptr || slotIndex < 0)
        return result;

    // Wrap angleAng into [0, 2*PI)
    float wrappedAngle = kAngleScale * angleDeg * kTwoPi;
    while (wrappedAngle < 0.0f)
        wrappedAngle += kTwoPi;
    while (wrappedAngle >= kTwoPi)
        wrappedAngle -= kTwoPi;

    // Clamp motor speeds
    if (leftMotorSpeed > kMaxRumbleSpeed)
        leftMotorSpeed = kMaxRumbleSpeed;
    else if (leftMotorSpeed < 0.0f)
        leftMotorSpeed = 0.0f;

    if (rightMotorSpeed > kMaxRumbleSpeed)
        rightMotorSpeed = kMaxRumbleSpeed;
    else if (rightMotorSpeed < 0.0f)
        rightMotorSpeed = 0.0f;

    // Clamp magnitude
    if (magnitude > kMaxMagnitude)
        magnitude = kMaxMagnitude;
    else if (magnitude < 0.0f)
        magnitude = 0.0f;

    // Get controller slot
    ControllerSlot* slot = this->getControllerSlot(controllerIndex);
    if (slot->dcFlag == 0 || slot->e0Flag != 0 || !this->isControllerValid(slotIndex))
        return result;

    // Begin rumble processing
    this->beginRumbleUpdate();
    this->setMotorSpeed(1, 0); // some reset?
    this->endRumbleUpdate();
    this->prepareRumbleFrame();

    // Update slot data
    slot->leftMotor = leftMotorSpeed;
    slot->speed = magnitude;
    slot->angle = wrappedAngle;
    slot->rightMotor = rightMotorSpeed;
    slot->dataPtr = *(void**)((uintptr_t)sourceData + 8);
    slot->patternIndex = patternIndex;
    slot->extraParam = extraParam;

    // Validate animation data
    void* animData = slot->dataPtr;
    if (animData != nullptr && slotIndex < *(int32_t*)animData + 4) {
        int32_t animIndex = slotIndex + 1;
        if (*(int32_t*)(animIndex * 16 + (uintptr_t)animData) != 0) {
            // Check compatibility
            if (this->isControllerValid(/*?*/)) {  // FUN_005ee610 (likely another check)
                float motorProduct = slot->leftMotor * slot->rightMotor;

                // Check which motors are valid
                bool leftValid = this->isLeftMotorValid();
                bool rightValid = this->isRightMotorValid();
                bool leftValid2 = this->isLeftMotorValid();
                bool rightValid2 = this->isRightMotorValid();
                bool bothValid = this->isBothMotorsValid();
                // ... repeated pattern

                this->beginRumbleUpdate();

                if (leftValid) {
                    float speed = motorProduct;
                    if (*(char*)((uintptr_t)this + 0x9089) == '\0') {
                        speed = 0.0f;
                    }
                    this->setMotorSpeed(0, speed);
                }
                if (rightValid) {
                    this->setMotorSpeed(0, 0.0f);
                }
                if (leftValid2) {
                    this->setMotorSpeed(0, motorProduct);
                }
                if (rightValid2) {
                    this->setMotorSpeed(0, slot->leftMotor);
                }
                if (bothValid) {
                    // Transform calculation
                    float transformOut[3];
                    this->getTransform(*(uint32_t*)((uintptr_t)this + 0x580), *(uint32_t*)((uintptr_t)this + 0x580), &transformOut);
                    // Prepare transform data
                    float x = 0.0f;
                    float y = motionData[0];
                    float z = 0.0f;
                    if (y > 0.0f) {
                        if (y >= kMaxRumbleSpeed)
                            y = kMaxRumbleSpeed;
                    } else {
                        y = 0.0f;
                    }
                    this->setMotorSpeed(0, &transformOut);  // note: signature mismatch, but preserved

                    if (motionData[0x23] != 0.0f) {
                        double d = *(double*)(*(uint32_t*)((uintptr_t)this + 0x580) + 8) + 0.0; // _DAT_00e44860 likely 0.0
                        float f1 = motionData[2];
                        float f2 = motionData[1];
                        if (f2 > 0.0f) {
                            if (f2 >= kMaxRumbleSpeed)
                                f2 = kMaxRumbleSpeed;
                        } else {
                            f2 = 0.0f;
                        }
                        this->setMotorSpeed(0, &d); // buffer
                        slot->transformValue = d;
                        slot->zeroFlag = 0;
                    }
                }
                // For patternIndex conversion
                if (this->isBothMotorsValid()) {
                    float fPattern = (float)patternIndex;
                    if (patternIndex < 0)
                        fPattern += kIntToFloatOffset;
                    this->setMotorSpeed(0, fPattern);
                }

                this->endRumbleUpdate();

                // Commit rumble changes
                if (!this->commitRumble(slot->extraParam, (uint32_t)&slot->dataPtr + 0xBC)) {
                    result = 0;
                }
            }
        }
    }
    return result;
}