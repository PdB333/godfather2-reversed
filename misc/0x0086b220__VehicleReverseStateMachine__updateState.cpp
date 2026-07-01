// FUNC_NAME: VehicleReverseStateMachine::updateState

// Function address: 0x0086b220
// Role: Update logic for vehicle reverse state machine (likely part of AI or player vehicle control)
// Calls sub-functions for throttle, braking, steering, and virtual speed/angle check (VTBL +0x1b0)

#include <cmath>

// Forward declarations of class methods (callees)
// These are member functions of the same class or related class.
// Assume they are defined elsewhere.
void setThrottle(float value);          // 0x0086b830
void setBrake(bool on);                 // 0x0086b7f0
void setHandbrake(bool on);             // 0x0086b810
void setSteering(float value);          // 0x0086b7b0
void setSomeFlag(float value);          // 0x0086b7d0 (could be reverse direction or turn signal)
float getSomeComponentValue();          // 0x00872180 takes param+0x60

// Global constants (from decompiled data references)
extern const float DAT_00e44680;        // Mask for truncation/bit operation
extern const float DAT_00d58cbc;        // Speed threshold for reverse state
extern const float DAT_00d5ef88;        // Minimum speed/angle threshold for settling
extern const float DAT_00d75d84;        // Time threshold for reverse condition
extern const float DAT_00d5ca64;        // Another time threshold (probably max time)
extern const float DAT_00d5f18c;        // Another speed threshold
extern const float DAT_00d5c458;        // Parameter passed to setSomeFlag (maybe 0.0f or 1.0f)
extern const float REVERSE_SPEED_THRESHOLD; // At s__43S_VehicleReverseStateMachine+4 (0x00d75d87+1)

// Class definition (inferred)
class VehicleReverseStateMachine {
public:
    // Offsets from this pointer:
    // +0x30: float timeInReverse (or speed? compared to constants)
    // +0x5C: pointer to some component (vtable at +0x1b0)
    // +0x60: passed to getSomeComponentValue
    // +0x6C: byte flag (set to 1 when settled)

    void updateState() { // __fastcall with this in ecx, no explicit params
        float fVar1 = static_cast<float>(getSomeComponentValue()); // cast to float (was float10)
        float fVar2 = static_cast<float>(static_cast<unsigned int>(fVar1) & static_cast<unsigned int>(DAT_00e44680)); // bitwise AND with mask, then float
        setThrottle(-fVar1); // negate throttle for reverse
        setBrake(false);
        setHandbrake(true);

        // Outer condition: if reverse speed is high enough OR time in reverse is small
        if (DAT_00d58cbc <= fVar2 || this->timeInReverse <= REVERSE_SPEED_THRESHOLD) {
            // Inside: check if time is within limits and either time is short or speed is high enough
            if (this->timeInReverse <= DAT_00d75d84 &&
                (this->timeInReverse <= DAT_00d5ca64 || DAT_00d5f18c <= fVar2)) {
                setSteering(1.0f); // full steer
                setSomeFlag(0.0f);
                return;
            }
            // else: moderate reverse
            setSteering(0.0f);
            setSomeFlag(DAT_00d5c458); // unknown constant
        } else {
            // Low speed or high time: decelerate/coast
            setSteering(0.0f);
            setSomeFlag(1.0f);
            // Virtual function call on component at +0x5C (index +0x1b0 in vtable)
            // Probably returns current speed relative to direction
            // Assume component type has virtual method float getSpeed();
            float speed = (*(float (__fastcall *)(void*))(*static_cast<int*>(this->component) + 0x1b0))();
            if (std::abs(speed) < DAT_00d5ef88) {
                this->settledFlag = 1; // mark as settled
                return;
            }
        }
        // implicit return for other cases
    }

    // Member variables (guessed)
    float timeInReverse;   // +0x30
    void* component;       // +0x5C (pointer to some object with vtable)
    // +0x60 is also part of object, passed to getSomeComponentValue (maybe another variable)
    unsigned char settledFlag; // +0x6C
};

// Note: actual layout may differ; offsets are from decompiled param_1.
// The getSomeComponentValue function is called on param_1+0x60 implying a member at that offset.
// The constant REVERSE_SPEED_THRESHOLD is taken from string "43S_VehicleReverseStateMachine" offset 1.
// Use with caution.