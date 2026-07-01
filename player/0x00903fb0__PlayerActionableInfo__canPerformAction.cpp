// FUNC_NAME: PlayerActionableInfo::canPerformAction
// Address: 0x00903fb0
// Role: Checks if an action can be performed based on cooldown timers and entity state flags.
// Uses ActionOptions (param_2) to retrieve interface pointers by hash and query float values.

#include <cstdint>

// Forward declaration of the function used to query interfaces by hash
void* __cdecl getInterface(void* object, uint32_t interfaceHash);

class PlayerActionableInfo {
public:
    // +0x00: vtable pointer (base class)
    // +0x14: state flags (bits: 0x34 = 0b110100 = flags for grappling, cover, etc.)
    uint8_t stateFlags[0x18]; // placeholder for actual struct layout

    // +0x00: vtable
    // +0x14: stateFlags at offset 0x14 (uint8_t)

    // Method at vtable offset 0xc0 in ActionOptions: returns a float (probably cooldown remaining)
    // Method at vtable offset 0x1e4 in another object: returns a pointer to something with a float method at 0xc0
};

class ActionOptions {
public:
    // vtable layout:
    // +0xc0: virtual float getCooldownRemaining() const;
    // +... others
};

class SomeTimerInterface {
public:
    // vtable layout:
    // +0x1e4: virtual SomeOtherObject* getSource() const;
    // +... others
};

class SomeOtherObject {
public:
    // vtable layout:
    // +0xc0: virtual float getDurationRemaining() const;
    // +... others
};

// The function
int __thiscall PlayerActionableInfo::canPerformAction(ActionOptions* actionOptions) {
    if (actionOptions == nullptr) {
        return 0;
    }

    // Check if the entity is not in a disabled state (bit 0 of stateFlags)
    if (!(this->stateFlags[0] & 1)) {
        // Get cooldown from actionOptions
        float cooldown = actionOptions->getCooldownRemaining(); // vtable[0xc0]
        if (cooldown <= 0.0f) {
            return 0;
        }

        // Check some state bits at offset 0x14 (0x34 = flags for grappling/carrying?)
        if ((this->stateFlags[0x14] & 0x34) != 0) {
            // Get a specific interface from actionOptions (hash for timer/cooldown)
            void* timerInterface = getInterface(actionOptions, 0xf8b45dfb);
            if (timerInterface != nullptr) {
                // Get a sub-object from the timer interface
                void* subObject = reinterpret_cast<SomeTimerInterface*>(timerInterface)->getSource(); // vtable[0x1e4]
                if (subObject != nullptr) {
                    // Check another float from the sub-object
                    float subDuration = reinterpret_cast<SomeOtherObject*>(subObject)->getDurationRemaining(); // vtable[0xc0]
                    if (subDuration <= 0.0f) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}