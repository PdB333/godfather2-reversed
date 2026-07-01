// FUNC_NAME: GameObject::update
// Address: 0x0080b670
// Role: Performs per-frame update, conditionally calling a sub-update if a flag at +0x1bc8 is set.
class GameObject {
public:
    // +0x1bc8: flag indicating whether a subsystem update is required (treated as boolean)
    int m_bUpdateSubsystem;

    // __thiscall
    void update();
};

// External helper (likely a global or static function)
void FUN_0080ad60(); // TODO: rename to baseUpdate or similar

void GameObject::update() {
    // Call base-class or global update logic
    FUN_0080ad60();

    // Check if subsystem needs processing
    if (this->m_bUpdateSubsystem) {
        // Calls another member function on this object (conditional update logic)
        FUN_007f0500(this); // TODO: rename to processSubsystem or similar
    }
}