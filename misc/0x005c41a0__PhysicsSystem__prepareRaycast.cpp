// FUNC_NAME: PhysicsSystem::prepareRaycast
void PhysicsSystem::prepareRaycast(void* this) // __thiscall
{
    // Query request parameters; type=2 likely indicates raycast, maxDistance=16, flags=0
    struct RaycastRequest {
        int type;          // +0x00
        int maxDistance;   // +0x04 (16 units)
        int flags;         // +0x08
    };
    RaycastRequest request;
    request.type = 2;
    request.maxDistance = 0x10; // 16
    request.flags = 0;

    // Call through global handler table at DAT_012234ec, offset +4 (function index 1)
    (*(void (**)(void*, RaycastRequest*))((uintptr_t)DAT_012234ec + 4))(this, &request);
}