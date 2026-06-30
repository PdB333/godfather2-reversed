// FUNC_NAME: AimStateComponent::update
// Address: 0x00594aa0
// Role: Updates aiming state based on target distance and flags. Handles transitions between aim sub-states.

class AimStateComponent {
public:
    // Vtable offsets (used in this function):
    // +0x10: getTargetPosition (or computePosition)
    // +0x14: updateAim (inside close range)
    // +0x2c: aimAtTarget (with debug)
    // +0x38: isTargetValid?
    // +0x5c: aimUpdateFallback

    // Offsets in this object:
    // +0x04: int mFlags2 (bit0-1 used for state flags)
    // +0x05: Entity* mpTargetEntity    // [actually pointer sized, but offset 0x05 is odd; likely 0x14?]
    // Actually offsets from decompiled: unaff_ESI[5] means +0x14 (since int* index)
    // I'll correct: unaff_ESI[5] => this->mpTargetEntity at offset 0x14
    // Similarly:
    // +0x1f: unsigned char mFlags  (bit4: 0x10, bit5: 0x20, bit6: 0x40, bit7: 0x80)
    // +0x24: float mOwnerX
    // +0x25: float mOwnerYaw
    // +0x26: float mOwnerZ
    // +0x28: float mSomeAngleOffset
    // +0x2c: float mDistSqThreshold  (squared distance)
    // +0x2d: float mMinDistForStateChange
    // +0x2e: void* mpTargetOrEntity
    // +0x44: float mAimStateStartTime
    // +0x45: float mAimTargetX
    // +0x46: float mAimTargetY
    // +0x47: float mAimTargetZ
    // +0x48: float mAimCurrentProgress
    // +0x49: float mAimSomeFloat1
    // +0x4a: float mAimSomeFloat2
    // +0x4b: float mAimSomeFloat3
    // +0x4f: int mAimStateCounter1
    // +0x50: int mAimStateCounter2
    // +0x51: int mAimStateCounter3
    // +0x52: int mAimStateCounter4

    // External transform/math utility (DAT_012055a8)
    struct TransformMath {
        // vtable: 0x04: setIdentity, 0x10: invert, 0x18: add, 0x1c: setLookAt, 0x24: multiply, 0x28: dot, 0x2c: transformPoint, 0x40: getTranslation, 0x48: cross, 0x68: rotateByQuaternion
    };
    static TransformMath* gTransformMath; // DAT_012055a8

    // Debug/log utility (DAT_01205590)
    struct DebugLog {
        // vtable: 0x28: logMessage
    };
    static DebugLog* gDebugLog; // DAT_01205590

    // Constants:
    static constexpr float kAngleOffset1 = 0.0f; // DAT_00e2b04c
    static constexpr float kAngleOffset2 = 0.0f; // DAT_00e2afb8
    static constexpr float kMinDistForStateChange = 0.0f; // DAT_00e2b05c

    void update(float targetX, float targetZ) __thiscall {
        // Compute squared distance from owner to target
        float dx = targetX - this->mOwnerX;
        float dz = targetZ - this->mOwnerZ;
        float distSq = dx*dx + dz*dz;

        if (this->mDistSqThreshold <= distSq) {
            // Target at or beyond threshold: update aim with full transform math
            // [Simplified: Set up a look-at matrix, compute rotation, set flags]
            // This block ends by setting mFlags bit 6 (0x40)
            // ... (complex transform operations omitted for brevity)
            this->mFlags |= 0x40;
        } else {
            // Target within threshold
            this->mFlags &= ~0x20;  // clear bit 5

            if (this->mpTargetOrEntity != nullptr) {
                // Check if debug log is present
                if (gDebugLog && gDebugLog->logMessage("aiming", 0)) {
                    // Log and call vtable method
                    this->aimAtTarget(this->mpTargetOrEntity);
                }
            }

            if (this->mFlags & 0x80) {
                // Enter new aim state: set state variables
                this->mAimStateStartTime = this->mDistSqThreshold; // placeholder
                this->mAimTargetX = (float)this->mDistSqThreshold;
                this->mAimTargetY = (float)this->mOwnerYaw + kAngleOffset1;
                this->mAimTargetZ = (float)this->mOwnerZ;
                // More state setup...
                this->mAimCurrentProgress = 0.0f;
                this->mpStateNext = (void*)&this->mAimTargetX;
                this->mStateCounter = 1;
                this->mSubState = 2;
                this->mStatePtr = &this->mAimTargetX;
                this->mOtherStateCounter = 1;
                this->mFlags2 &= ~3;
                return;
            }

            if (this->mMinDistForStateChange < this->mDistSqThreshold) {
                // Update aim within close range
                this->updateAim(); // call vtable+0x14
                return;
            }

            if (this->mpTargetEntity != nullptr && (*(byte*)this->mpTargetEntity & 4)) {
                // Additional transform math for entity target
                // ... (cross product, dot product, etc.)
            }

            this->updateAim(); // fallback call vtable+0x14
            return;
        }
    }

private:
    void aimAtTarget(void* target) __thiscall;
    void updateAim() __thiscall;
};