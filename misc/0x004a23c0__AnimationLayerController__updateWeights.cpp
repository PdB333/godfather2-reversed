// FUNC_NAME: AnimationLayerController::updateWeights
// Address: 0x004a23c0
// Role: Updates animation blend weights for 12 slots (layers), with easing and threshold checks.
// Clamps values, handles transitions (current slot ramps up, others ramp down).
// Calls slot function pointers on completion or update.

extern float DAT_01206800;   // Fixed time delta (e.g., 0.0167f)
extern float DAT_00e2b1a4;   // Max blend weight (1.0f)
extern float DAT_00e2b05c;   // Threshold for speed division
extern float DAT_00e2e210;   // Min weight to trigger completion
extern float DAT_00e44854;   // Max weight override threshold

// Forward declaration of easing helper
float10 FUN_004a2210(float t, int type);  // Returns eased delta (extended precision)

struct AnimationSlot {
    void* mCallback;       // +0x00: Callback object (vtable pointer)
    float mValue;          // +0x04: Current blend weight
    float mSpeed;          // +0x08: Blend rate (speed)
};

struct AnimationLayerController { // size >= 0x130
    // Slot array at +0x88
    // Each slot: pointer (4 bytes), value (4), speed (4) => 12 bytes
    // 12 slots => 144 bytes, so slots occupy +0x88 to +0x118? Actually +0x88 + 144 = +0x118
    uint mCurrentSlotIndex; // +0x118: Index of the layer being transitioned to
    float mAccumulator;     // +0x11c: Accumulated time delta
    float mTransitionTime;  // +0x124: Total transition duration
    float mPreviousDelta;   // +0x120: Previous eased delta (for relative change)
    int mTransitionType;    // +0x128: Easing type (4=linear,5=easeIn,6=easeOut,8=easeInOut,9=...)
    // Fields before +0x88 might exist (e.g., vtable, other members)
};

void AnimationLayerController::updateWeights() {
    float delta = DAT_01206800;
    float maxWeight = DAT_00e2b1a4;
    float speedThreshold = DAT_00e2b05c;

    // Accumulate time delta
    mAccumulator += delta;
    float elapsed = mAccumulator;

    // Compute normalized time (t)
    float t = maxWeight; // default 1.0
    if (speedThreshold < mTransitionTime) {
        t = elapsed / mTransitionTime;
    }

    float localDelta = maxWeight; // will hold the change in weight
    if (t < maxWeight) {
        // Compute eased progress using previous delta
        float10 eased = FUN_004a2210(t, mTransitionType); // extended precision
        localDelta = (float)eased - mPreviousDelta;
        mPreviousDelta = (float)eased;
    }

    // Update each slot
    float minWeight = DAT_00e2e210; // threshold to terminate slot
    for (uint i = 0; i < 12; i++) {
        // Pointer to current slot's value (offset +0x8c + i*12)
        float* slotValue = &((float*)(this + 0x8c))[i * 3]; // careful: this is not valid C++ but reconstruct
        // Actually we need to access via struct better.

        // Full slot structure:
        // Slot base = reinterpret_cast<AnimationSlot*>(reinterpret_cast<uint8*>(this) + 0x88 + i * sizeof(AnimationSlot));
        // For clarity, we'll cast properly.

        void* callback = reinterpret_cast<void**>(reinterpret_cast<uint8*>(this) + 0x88 + i * sizeof(AnimationSlot))[0]; // +0x00
        float& value = reinterpret_cast<float*>(reinterpret_cast<uint8*>(this) + 0x8c + i * sizeof(AnimationSlot))[0]; // +0x04
        float& speed = reinterpret_cast<float*>(reinterpret_cast<uint8*>(this) + 0x90 + i * sizeof(AnimationSlot))[0]; // +0x08

        // There's no direct way to do this cleanly without pointer arithmetic.
        // We'll just keep using pointer arithmetic for reconstruction.

        // Equivalent to original: piVar1 = (int*)((float*)(&this->slots[0].value) + i*3 - 1)
        // Initially pfVar6 = &slots[0].value; then pfVar6 += 3 each iteration.
        // Better to write in a style faithful to decompiled logic.

        float* pfVar6 = reinterpret_cast<float*>(reinterpret_cast<uint8*>(this) + 0x8c) + i * 3;
        int* piVar1 = reinterpret_cast<int*>(pfVar6[-1]); // callback pointer as int* for vtable access

        float threshold = DAT_00e2e210; // re-fetched each iteration (might be const)

        if (piVar1 != nullptr) {
            float newValue;
            if (i == mCurrentSlotIndex) {
                // Ramp up
                newValue = pfVar6[1] * localDelta + pfVar6[0];
                if (maxWeight <= newValue)
                    newValue = maxWeight;
            } else {
                // Ramp down
                newValue = pfVar6[0] - pfVar6[1] * localDelta;
                if (newValue <= 0.0f)
                    newValue = 0.0f;
            }
            pfVar6[0] = newValue;

            if (newValue <= threshold) {
                // Weight dropped below threshold
                if (i != mCurrentSlotIndex) {
                    // Call "stop" or "complete" function (vtable entry 0)
                    reinterpret_cast<void (*)(int)>(*piVar1)(1); // first virtual method, arg 1
                    pfVar6[-1] = 0; // clear callback
                }
            } else if ((DAT_00e44854 <= newValue) || (mTransitionType != 9)) {
                // Not a special case where weight must be under DAT_00e44854 and type==9
                // Check if we should call the update function
                int type = mTransitionType;
                if ((type != 4 && type != 6 && type != 5 && type != 8) || (i == mCurrentSlotIndex)) {
                    // Call "update" function (vtable entry 2, i.e., offset 8)
                    reinterpret_cast<void (*)(float)>(reinterpret_cast<int*>(*piVar1)[2])(delta);
                }
            }
        }
    }
}