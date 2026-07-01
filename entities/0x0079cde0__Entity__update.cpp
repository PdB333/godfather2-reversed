// FUNC_NAME: Entity::update

// Reconstructed from 0x0079cde0
// Role: Main update tick for Entity objects, calls virtual update and handles state transitions

class Entity {
public:
    // VTable entry at offset 0x6c: virtual method for specific update logic
    virtual void vfunc0x6c();

    // Offset +0x74C: state/type identifier (int)
    // 0x48 (72) likely represents an inactive or default state
    int m_nState;

    // Constructor and other members omitted
};

// External functions (actual addresses in binary)
extern void __cdecl handleActiveState(void); // FUN_00707610 – processes active state (state != 0 && state != 0x48)
extern void __cdecl finalizeUpdate(void);    // FUN_007ff030 – common post-update tasks

void Entity::update() {
    // Invoke virtual specific update (e.g., behavior tree, animation tick)
    this->vfunc0x6c();

    // Check if state is active and not a known default value
    if (this->m_nState != 0 && this->m_nState != 0x48) {
        handleActiveState();
    }

    // Perform generic post-update processing (e.g., timer decrement, cleanup)
    finalizeUpdate();
}