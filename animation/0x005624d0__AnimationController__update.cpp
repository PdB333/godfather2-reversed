// FUNC_NAME: AnimationController::update
// Address: 0x005624d0
// Role: Updates animation blending, target transform, and state transitions

struct AnimationData; // forward declaration

class AnimationController {
public:
    // +0x00: vtable?
    // +0x10: float someScaleFactor
    // +0x14: float someValue1
    // +0x18: float someValue2
    // +0x1c: float someValue3
    // +0x20: float someValue4
    // +0x24: int flag1
    // +0x28: int flag2
    // +0x2c: int flag3
    // +0x30: int flag4
    // +0x34: int flag5
    // +0x38: int flag6
    // +0x3c: int someHandle
    // +0x40: int blendWeightID
    // +0x44: int pointer1
    // +0x50: float[?] someArray (used with virtual call)
    // +0x60: int pointer2
    // +0x70: float[?] someArray2
    // +0x80: AnimationData* animationData1
    // +0x84: int someState
    // +0x88: AnimationData* animationData2 (main animation data)
    // ... more fields

    void update(float* targetTransform); // param_1 may be a 4-float quaternion or position
};

struct AnimationData {
    // +0x00: vtable?
    // +0xd0: virtual table for animation methods
    // +0xd8: char state (6=idle, 7=some other?)
    // +0x160: float transformX
    // +0x164: float transformY
    // +0x168: float transformZ
    // +0x16c: float transformW
    // +0x184: float someCopyTarget1
    // +0x188: float someCopyTarget2
    // +0x19c: float someScale
    // ... more

    // Virtual methods accessed via vtable at +0xd0:
    // offset 0x14: getCurrentTransform(float* out) -> void
    // offset 0x40: someMethod1(float* arg) -> void
    // offset 0x44: someMethod2(float* arg) -> void
};

// External functions (likely in EARS engine):
extern void FUN_009f4240(int handle, int arg1, int arg2); // maybe setBlendState?
extern int FUN_009f3d50(); // getSomeBlendID?
extern void FUN_009f3cc0(int id); // setSomeBlendID?
extern void FUN_00561e70(); // some update/prep?
extern float FUN_009efd10(float* transform); // getMagnitude or something?
extern void FUN_00aa5040(float scale); // applyScale?
extern void FUN_009f3d60(float value); // setBlendWeight?
extern void FUN_009f3dc0(float* transform); // finalizeTransform?
extern void FUN_009df220(float* diff, float factor); // lerp/blend?
extern void FUN_009f4400(float* target); // copyTransform?
extern void FUN_009f2000(); // beginBlend? or clear?

void AnimationController::update(float* targetTransform) {
    AnimationData* animData = (AnimationData*)this->animationData2; // +0x88
    AnimationData* animData1 = (AnimationData*)this->animationData1; // +0x80

    if (animData != nullptr && animData1 != nullptr) {
        // Check if flag1 is set and state is zero
        if (this->flag1 != 0 && this->someState == 0) { // +0x24 and +0x84
            FUN_009f4240(this->someHandle, 1, 0); // +0x3c
        }

        int currentBlendID = this->blendWeightID; // +0x40
        int currentBlendIDEngine = FUN_009f3d50();
        if (currentBlendIDEngine != currentBlendID) {
            FUN_009f3cc0(currentBlendID); // restore old blend ID?
        }

        if (this->flag4 != 0) { // +0x30
            char state = *(char*)((int)animData + 0xd8); // animation state
            if (state != 6 && state != 7) {
                FUN_00561e70();
                float fVar4 = FUN_009efd10(nullptr); // get some global time?
                float local_5c = fVar4;

                // Call virtual method at vtable+0x14 to get current transform
                void* vtable = *(void**)((int)animData + 0xd0);
                void (*getTransform)(float* out) = (void (*)(float*))((int*)vtable)[0x14 / 4];
                float local_40[15]; // stored in local_40 (size 60 bytes?, but only first used)
                getTransform(local_40);

                float fVar5 = *(float*)((int)animData + 0x19c) * *(float*)((int)this + 0x10); // +0x10 for this
                float local_60; // reused variable
                local_60 = fVar5 * local_40[0]; // use first element? Actually they assign local_60 = fVar5 * local_60, but local_60 uninitialized? Bug in decompilation? Likely local_60 was used earlier as a scalar.
                // Probably: local_60 = fVar5 * someValue from local_40? Actually the decompiler mishandled stack reuse.
                // Let's re-examine: local_60 is declared as float, and then later assigned. The original code might have been: float blendFactor = fVar5 * someInitialValue; or something.
                // We'll assume a simple operation: set blend weight.
                FUN_00aa5040(fVar5);
                FUN_009f3d60(local_60);
                float auStack_44[1]; // stack temp
                FUN_009f3dc0(auStack_44);
            }
        }

        if (targetTransform != nullptr) {
            char state = *(char*)((int)animData + 0xd8);
            if (state != 6 && state != 7) {
                // Call virtual method to get target transform into local_60
                void* vtable = *(void**)((int)animData + 0xd0);
                void (*getTransform)(float* out) = (void (*)(float*))((int*)vtable)[0x14 / 4];
                float local_60[4]; // actually stack reuse, but we treat as 4-float
                getTransform((float*)&local_60);

                if (this->flag5 != 0) { // +0x34
                    AnimationData* animDataRef = (AnimationData*)this->animationData2;
                    float diffX = targetTransform[0] - *(float*)((int)animDataRef + 0x160);
                    float diffY = targetTransform[1] - *(float*)((int)animDataRef + 0x164);
                    float diffZ = targetTransform[2] - *(float*)((int)animDataRef + 0x168);
                    float diffW = targetTransform[3] - *(float*)((int)animDataRef + 0x16c);
                    float diff[4] = { diffX, diffY, diffZ, diffW };

                    float fVar4 = FUN_009efd10((float*)&local_60); // pass local_60 as arg?
                    FUN_009df220(diff, fVar4);
                    FUN_009f3dc0((float*)&local_60);
                    FUN_009f4400(targetTransform);
                }
            }
        }

        if (this->flag2 != 0) { // +0x28
            if (this->pointer1 != 0) { // +0x44
                FUN_009f2000();
                void* vtable = *(void**)((int)animData + 0xd0);
                void (*method40)(float* arg) = (void (*)(float*))((int*)vtable)[0x40 / 4];
                float argArray[4]; // offset from this +0x50, size? assume 4 floats
                method40((float*)((int)this + 0x50));
                this->pointer1 = 0;
            }
            if (this->pointer2 != 0) { // +0x60
                FUN_009f2000();
                void* vtable = *(void**)((int)animData + 0xd0);
                void (*method44)(float* arg) = (void (*)(float*))((int*)vtable)[0x44 / 4];
                float argArray2[4]; // offset from this +0x70?
                method44((float*)((int)this + 0x70));
                this->pointer2 = 0;
            }
        }

        if (this->flag3 != 0) { // +0x2c
            // Copy two floats from this to animation data
            *(float*)((int)animData + 0x184) = *(float*)((int)this + 0x14);
            *(float*)((int)animData + 0x188) = *(float*)((int)this + 0x18);
        }

        if (this->flag6 != 0) { // +0x38
            // Copy two floats from this to animation data
            *(float*)((int)animData + 0x84) = *(float*)((int)this + 0x1c);
            *(float*)((int)animData + 0x88) = *(float*)((int)this + 0x20);
        }
    }
}