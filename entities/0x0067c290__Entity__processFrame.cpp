// FUNC_NAME: Entity::processFrame
// Address: 0x0067c290
// Wrapper that performs pre/post operations around a virtual update call (vtable+0x2c).
// Likely checks if updates are allowed, resets state if not, then locks/unlocks for thread safety.

bool isUpdateEnabled();       // FUN_0069d700
void resetUpdateState();      // FUN_0068ac30
void lockUpdate(int mode);    // FUN_0068baf0
void unlockUpdate(int mode);  // FUN_0068bcd0

int __thiscall Entity::processFrame(Entity *this) {
    if (!isUpdateEnabled()) {
        resetUpdateState();
    }
    lockUpdate(1);
    // vtable+0x2c = virtual update function (e.g., Entity::update)
    int result = (*(int (__thiscall **)(Entity *))(*(int *)this + 0x2c))(this);
    unlockUpdate(1);
    return result;
}