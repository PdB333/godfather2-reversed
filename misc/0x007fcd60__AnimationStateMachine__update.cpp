// FUNC_NAME: AnimationStateMachine::update

// Function at 0x007fcd60: Base update method for animation state machines.
// Handles parent state machine propagation, time-based state transitions,
// and clearing of entry/exit flags.

// Offset constants (in bytes, relative to 'this')
#define OFFSET_FLAGS      0x970   // param_1[0x25c] - bit5 = entering, bit6 = exiting
#define OFFSET_PARENT     0xFFC   // param_1[0x3ff] - pointer to parent's field at +0x48 (or sentinel 0x48)

class AnimationStateMachine
{
public:
    // Vtable entries (index = offset / 4)
    // vtable[0x198>>2] => update()  (likely call to per-class tick)
    // vtable[0x0c0>>2] => getTimeUntilTransition()  (returns float)

    virtual void update();
    virtual float getTimeUntilTransition();

    // Helper to get parent pointer from the stored field value
    AnimationStateMachine* getParent()
    {
        int stored = *(int*)((char*)this + OFFSET_PARENT);
        if (stored != 0 && stored != 0x48)  // 0x48 is a sentinel for "no parent"
        {
            return reinterpret_cast<AnimationStateMachine*>(stored - 0x48);
        }
        return nullptr;
    }

    uint32_t& flags() { return *(uint32_t*)((char*)this + OFFSET_FLAGS); }

    // External functions (likely engine globals)
    void updateFrameTime();
    void transitionState();
};

// invocations of external helpers (names guessed)
void updateFrameTime() {}
void transitionState() {}

// The reconstructed method
void AnimationStateMachine::update()
{
    // Ensure extra checks are inline (__fastcall in original)
    AnimationStateMachine* parent = getParent();

    if (parent != nullptr)
    {
        updateFrameTime();
        parent->update();        // virtual call at vtable+0x198
    }

    updateFrameTime();
    this->update();              // virtual call at vtable+0x198

    // Check own "entering" flag (bit5)
    if (flags() & (1 << 5))
    {
        float time = getTimeUntilTransition(); // vtable+0xc0
        if (time > 0.0f)
        {
            flags() &= ~(1 << 5);
            transitionState();
        }
    }

    // Check own "exiting" flag (bit6)
    if (flags() & (1 << 6))
    {
        float time = getTimeUntilTransition();
        if (time > 0.0f)
        {
            flags() &= ~(1 << 6);
            transitionState();
        }
    }

    // Do the same for the parent if it exists
    if (parent != nullptr)
    {
        if (parent->flags() & (1 << 5))
        {
            float time = parent->getTimeUntilTransition();
            if (time > 0.0f)
            {
                parent->flags() &= ~(1 << 5);
                transitionState();
            }
        }

        if (parent->flags() & (1 << 6))
        {
            float time = parent->getTimeUntilTransition();
            if (time > 0.0f)
            {
                parent->flags() &= ~(1 << 6);
                transitionState();
                return;   // early return after parent's "exiting" transition
            }
        }
    }

    return;
}