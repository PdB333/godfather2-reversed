// FUNC_NAME: Entity::firstFrameTrigger
// Function address: 0x004719e0
// Increments a frame deferral counter. When the counter transitions from 0 to 1 (i.e., first call after reset),
// it invokes two virtual methods: one at vtable offset 0xc and another at vtable offset 0x6c.
// This is used to trigger one-time actions on the first frame after a state change.

void __thiscall Entity::firstFrameTrigger(void)
{
    // +0x162: m_frameDelayCounter (byte) - incremented each frame; triggers on transition from 0
    char previousCounter = *(char *)((int)this + 0x162);
    *(char *)((int)this + 0x162) = previousCounter + 1;
    if (previousCounter == 0) {
        // Virtual call at vtable+0xc (method index 3) - likely a general update/notify
        (*(void (__thiscall **)(Entity *))(*(int *)this + 0xc))(this);
        // Virtual call at vtable+0x6c (method index 27) - likely the specific deferred action
        (*(void (__thiscall **)(Entity *))(*(int *)this + 0x6c))(this);
    }
}