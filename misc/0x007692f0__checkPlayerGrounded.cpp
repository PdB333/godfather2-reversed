// FUNC_NAME: checkPlayerGrounded
// This function checks if the player is grounded by predicting the next position based on velocity and time delta,
// then testing for collisions at that predicted position. If the first collision test fails (returns 0), it is considered grounded.
// Otherwise, it adds a small downward offset (ground check epsilon) and tests again via a physics point query.

// External function: returns pointer to player object (or game manager) with relevant fields at offsets:
// +0x20: velocity packed as 64-bit (low 32 bits: x, high 32 bits: y) ? 
// +0x28: z velocity (float)
// +0x30, +0x34, +0x38: player position (x, y, z) floats
extern void* getPlayerObject(); // 0x00471610

// External function: collision/path check. Returns 0 if clear, non-zero if blocked.
// Parameters: pointer to current position (float3), pointer to target position (float3), flags (3 ints=0)
extern int checkCollisionWithMove(void* currentPos, float* targetPos, int, int, int); // 0x0054eb70

// External function: returns pointer to collision/physics world object with vtable.
extern void* getPhysicsWorld(); // 0x00716430

// Global scaling factor (time delta? gravity?)
static const float s_timeDeltaScale = *(float*)0x00d65c68; // DAT_00d65c68

// Small downward offset for ground check (e.g., -0.1f)
static const float s_groundCheckOffset = *(float*)0x00d5c454; // DAT_00d5c454

bool checkPlayerGrounded()
{
    void* player = getPlayerObject();
    
    // Extract velocity components from packed 64-bit at +0x20
    // Low 32 bits as float (likely x velocity)
    float velX = (float)(*(uint64_t*)((char*)player + 0x20) & 0xFFFFFFFF);
    // High 32 bits as float (likely y velocity)
    float velY = (float)(*(uint64_t*)((char*)player + 0x20) >> 32);
    // Z velocity at +0x28
    float velZ = *(float*)((char*)player + 0x28);
    
    // Compute predicted displacement using time scale
    float dispX = velX * s_timeDeltaScale;
    float dispY = velY * s_timeDeltaScale;
    float dispZ = velZ * s_timeDeltaScale;
    
    // Get current position
    float curX = *(float*)((char*)player + 0x30);
    float curY = *(float*)((char*)player + 0x34);
    float curZ = *(float*)((char*)player + 0x38);
    
    // Predicted position
    float predX = curX + dispX;
    float predY = curY + dispY;
    float predZ = curZ + dispZ;
    
    // Check collision from current to predicted position
    int result = checkCollisionWithMove((char*)player + 0x30, &predX, 0, 0, 0);
    if (result == 0)
    {
        // No collision – assume grounded
        return true;
    }
    
    // Collision detected: try with a slight downward offset (ground check epsilon)
    predY += s_groundCheckOffset;
    
    // Use a physics world point query to see if the new position is on solid ground
    void* physicsWorld = getPhysicsWorld();
    // vtable method at offset 0x1c: likely a point/ground check function
    typedef int (*GroundCheckFunc)(void*, float*);
    GroundCheckFunc groundCheck = *(GroundCheckFunc*)(*(void**)physicsWorld + 0x1c);
    int groundResult = groundCheck(physicsWorld, &predX);
    
    return (groundResult == 0);
}