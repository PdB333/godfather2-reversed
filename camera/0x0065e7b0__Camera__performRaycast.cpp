// FUNC_NAME: Camera::performRaycast
// Address: 0x0065e7b0
// This function performs a raycast from the camera's position/target into the physics world.
// It uses uninitialized local array sizes based on typical EA EARS structures.

bool Camera::performRaycast(void* thisPtr, /* unaff_ESI: PhysicsWorld* world */ CollisionFilter* filter)
{
    Ray ray;             // +0x00, size 208 bytes (local_d0)
    Ray transformedRay;  // +0x00, size 32 bytes (local_f0)
    int hitResult;       // local_f4
    
    ray.init();          // FUN_006595c0: initializes ray struct
    ray.setFromPoints(*(Vector3*)(thisPtr + 0x0C), // camera position
                      *(Vector3*)(thisPtr + 0x10)); // camera target
    ray.toWorldSpace(&transformedRay); // FUN_00659730: transforms ray to world space
    
    PhysicsWorld* world = (PhysicsWorld*)unaff_ESI; // world pointer from ESI register
    world->raycast(transformedRay, &hitResult, filter->mask); // FUN_00664620
    return hitResult != 0;
}