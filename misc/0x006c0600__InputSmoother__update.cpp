// FUNC_NAME: InputSmoother::update

// Reconstructed C++ for InputSmoother::update (address 0x006c0600)
// This function updates a smoothed input value with a rate, and handles
// returning to zero after a timeout when input is idle.

// Known fields (offsets in bytes from this pointer):
// +0x00 : mIsZero (uint, treated as bool)
// +0x20 : mSavedValue (float) - saved when transitioning to zero
// +0x24 : mZeroCounter1 (uint) - zeroed on reset
// +0x28 : mZeroCounter2 (uint) - zeroed on reset
// +0x2c : mZeroCounter3 (uint) - zeroed on reset
// +0x40 : mCurrentValue (float) - the smoothed output
// +0x44 : mRate (float) - multiplier applied to inputDelta when not zero
// +0x48 : mTimer (float) - countdown timer before snap to zero
// +0x4c : mMaxValue (float) - upper clamp bound
// +0x50 : mTimeoutDuration (float) - initial timer value set on transition
// +0x54 : mDeadzoneSquared (float) - squared threshold for snap decision

// External globals referenced:
// DAT_00e44564 : likely a minimum clamp value or offset (e.g., 0.0 or -1.0)
// External functions:
// void resetSmoother();       // FUN_006daa50
// void setSmootherToZero(uint* out, float delta); // FUN_006daac0

#include <cmath> // for float operations

class InputSmoother {
public:
    uint mIsZero;                // +0x00
    // padding up to +0x20?
    float mSavedValue;           // +0x20 (offset 8 words)
    uint mZeroCounter1;          // +0x24
    uint mZeroCounter2;          // +0x28
    uint mZeroCounter3;          // +0x2c
    float mCurrentValue;         // +0x40 (offset 0x10 words)
    float mRate;                 // +0x44
    float mTimer;                // +0x48
    float mMaxValue;             // +0x4c
    float mTimeoutDuration;      // +0x50
    float mDeadzoneSquared;      // +0x54

    // Returns the updated mCurrentValue as extended precision float (here as float)
    float __thiscall update(float deltaTime, float inputDelta)
    {
        // Determine if inputDelta is zero (within tolerance, but here exact zero check)
        uint newIsZero = (uint)(inputDelta * inputDelta <= 0.0f); // 1 if zero, 0 otherwise

        // If the zero state changed, handle transition
        if (newIsZero != mIsZero) {
            if (newIsZero == 1) {
                // Transitioning to zero state: reset internal state
                resetSmoother(); // FUN_006daa50
                mSavedValue = mCurrentValue;
                mZeroCounter1 = 0;
                mZeroCounter2 = 0;
                mZeroCounter3 = 0;
            }
            mIsZero = newIsZero;
        }

        if (mIsZero == 0) {
            // Input is not zero: move current value toward inputDelta with rate
            float newValue = mRate * inputDelta + mCurrentValue;
            float minValue = DAT_00e44564 - mMaxValue; // global constant minus max
            mCurrentValue = (uint)newValue; // intentional? Should be float cast? Probably a bug in decompiler

            // Clamp new value to [minValue, mMaxValue] 
            if (newValue < minValue) {
                mCurrentValue = (uint)minValue;
            } else if (mMaxValue < newValue) {
                mCurrentValue = (uint)mMaxValue;
            } else {
                mCurrentValue = (uint)newValue;
            }
            // Reset timer to stored duration
            mTimer = mTimeoutDuration;
        } else {
            // Input is zero: decrement timer by deltaTime
            mTimer = mTimer - deltaTime;
            if ((mTimer <= 0.0f) && 
                (mCurrentValue * mCurrentValue <= mDeadzoneSquared * mDeadzoneSquared)) {
                // Timer expired and current value is within deadzone: snap to zero
                uint zeroOut[7] = {}; // local_20
                setSmootherToZero(zeroOut, deltaTime); // FUN_006daac0
                mCurrentValue = (float)zeroOut[0]; // first element is new value
            }
        }

        // Return current value (as float, but decompiler shows float10)
        return mCurrentValue;
    }

    // Global constant (likely defined elsewhere)
    static const float DAT_00e44564; // example: 1.0f or 0.0f
};