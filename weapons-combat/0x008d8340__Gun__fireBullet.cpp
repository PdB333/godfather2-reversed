// FUNC_NAME: Gun::fireBullet
void __fastcall Gun::fireBullet(Gun* this) {
    char spreadCvar;
    float* pdst;
    float* psrc;
    int allocPtr;
    void* callbackResult;
    int matIdx;

    // Check if projectile has already been spawned
    if (*(int*)((char*)this + 0x184) != 0) {
        return;
    }

    // Get current camera view matrix (4x4)
    float* viewMat = (float*)FUN_00471610();  // MatrixManager::getCurrentViewMatrix
    spreadCvar = *(char*)((char*)this + 0x18c);  // spread flag (0 = no spread, any other = with spread)
    float localMatrix[16];  // We'll use this to hold the matrix copy (loop copies 16 elements)
    float* pLocal = localMatrix;
    float* pView = viewMat;
    for (matIdx = 16; matIdx != 0; matIdx--) {
        *pLocal++ = *pView++;
    }

    // Prepare spawn data structure on stack (position, rotation, velocity)
    struct SpawnData {
        float position[3];    // local_ac, local_a8, local_a4
        float rotation[4];    // local_a0..local_8c? but actually used as a Quaternion or matrix?
        float dummy1[4];      // padding, set to zero
        float forward[3];     // local_70, local_6c, local_68 (from camera)
        float zero;           // local_64
        float velocity[3];    // local_60, local_5c, local_58
        float zero2;
    } spawnData;

    if (spreadCvar == 0) {
        // No spread: use camera forward direction directly
        // Initialize rotation to zero (using global constant)
        spawnData.rotation[0] = _DAT_00d5780c;  // zero vector component
        spawnData.rotation[1] = _DAT_00d5780c;
        spawnData.rotation[2] = _DAT_00d5780c;
        // Set forward direction from camera matrix (last columns)
        spawnData.forward[0] = localMatrix[12]; // local_20
        spawnData.forward[1] = localMatrix[13]; // local_1c
        spawnData.forward[2] = localMatrix[14]; // local_18
        // Zero out remaining rotation fields
        spawnData.rotation[3] = 0;
        spawnData.rotation[4] = 0;
        spawnData.rotation[5] = 0;
        spawnData.rotation[6] = 0;
        spawnData.rotation[7] = 0;
        spawnData.rotation[8] = 0;
        spawnData.rotation[9] = 0;
        spawnData.rotation[10] = 0;
        spawnData.rotation[11] = 0;
        spawnData.zero = 0;

        // Calculate bullet speed: length of camera forward * speed multiplier
        float speed = sqrt(localMatrix[0]*localMatrix[0] + localMatrix[1]*localMatrix[1] + localMatrix[2]*localMatrix[2]);
        float bulletSpeed = speed * *(float*)((char*)this + 0x188);  // projectile speed factor

        // Allocate physics object (type 0x20, size 0x20)
        TlsGetValue(DAT_01139810);  // thread local storage
        allocPtr = FUN_00aa2680(0x20, 0x27);  // MemoryManager::allocate
        *(short*)(allocPtr + 4) = 0x20;

        // Create projectile with speed, returns pointer to newly created object
        void* projectileObj = (void*)FUN_00a64b00(bulletSpeed);  // PhysicsManager::createBullet

        // Allocate event data (type 0x31, size 0x160)
        TlsGetValue(DAT_01139810);
        allocPtr = FUN_00aa2680(0x160, 0x31);
        *(short*)(allocPtr + 4) = 0x160;

        // Schedule spawn callback
        int currentTime = FUN_0043b490();  // TimeManager::getCurrentTime
        callbackResult = (void*)FUN_00540c60(10, 0x1f, currentTime);  // EventScheduler::schedule

        // Actually create the game object (bullet) with the spawn data and callback
        *(int*)((char*)this + 0x184) = FUN_009f0c70(projectileObj, &spawnData, callbackResult);  // EntityFactory::instantiate

        // Send message to notify spawn
        FUN_0043b490();  // get current time again? (unused)
        FUN_009f01f0(0x2001, this, 0);  // send message "Spawn" to self

        // Decrement reference count on the projectile object
        if (*(short*)((char*)projectileObj + 2) != 0) {
            *(short*)((char*)projectileObj + 6) -= 1;
            if (*(short*)((char*)projectileObj + 6) == 0) {
                (*(void(__thiscall**)(ints))projectileObj)(1);  // destructor call via vtable
            }
        }
    } else {
        // With spread: transform a vector from the camera matrix to get direction with randomness
        float spreadVector[3];
        FUN_004bffa0(&spreadVector, localMatrix);  // Transform a random offset? (matrix multiplication)
        // Scale the spread vector by global spread factor
        spreadVector[0] *= _DAT_00d5c458;
        spreadVector[1] *= _DAT_00d5c458;
        spreadVector[2] *= _DAT_00d5c458;

        // Set velocity from the spread vector
        spawnData.velocity[0] = spreadVector[0];
        spawnData.velocity[1] = spreadVector[1];
        spawnData.velocity[2] = spreadVector[2];
        spawnData.zero2 = _DAT_00d5780c;

        // Get camera forward direction again
        float* currentView = (float*)FUN_00471610();
        spawnData.forward[0] = *(currentView + 0x30);  // +0x30 is view matrix column 3? Actually offset 0x30 is 12 floats = 12*4 = 48 bytes, so maybe the 13th element? That seems off. Let's reinterpret: camera matrix likely stored as float[16], offset 0x30 = 48 bytes = 12 floats, so that's element 12 (row 0 col 3? typical matrix indexing). Likely the world view orientation.
        spawnData.forward[1] = *(currentView + 0x34);  // element 13
        spawnData.forward[2] = *(currentView + 0x38);  // element 14
        spawnData.zero = _DAT_00d5780c;

        // Compute rotation from the matrix
        FUN_004b59d0(localMatrix, &spawnData.rotation);  // Matrix4x4 -> Quaternion conversion

        // Allocate physics object (type 0x20 but size 0x30 now)
        TlsGetValue(DAT_01139810);
        allocPtr = FUN_00aa2680(0x30, 0x27);
        *(short*)(allocPtr + 4) = 0x30;

        // Create projectile with velocity
        void* projectileObj = (void*)FUN_00a66df0(&spawnData.velocity, _DAT_00ef3a9c);  // PhysicsManager::createImpulse

        // Same event scheduling
        TlsGetValue(DAT_01139810);
        allocPtr = FUN_00aa2680(0x160, 0x31);
        *(short*)(allocPtr + 4) = 0x160;
        int currentTime = FUN_0043b490();
        callbackResult = (void*)FUN_00540c60(10, 0x1f, currentTime);

        // Create the bullet
        *(int*)((char*)this + 0x184) = FUN_009f0c70(projectileObj, &spawnData, callbackResult);

        // Same messaging
        FUN_0043b490();
        FUN_009f01f0(0x2001, this, 0);

        // Decrement reference
        if (*(short*)((char*)projectileObj + 2) != 0) {
            *(short*)((char*)projectileObj + 6) -= 1;
            if (*(short*)((char*)projectileObj + 6) == 0) {
                (*(void(__thiscall**)(ints))projectileObj)(1);
            }
        }
    }

    return;
}