// FUNC_NAME: Entity::checkLineOfSight
// Function at 0x007afbc0: Checks line of sight between two entities, using camera position or entity positions, and two threshold values from virtual functions.

int Entity::checkLineOfSight(void* entity1, void* entity2) {
    // Variables for source vector
    double sourceVec[3]; // 2 floats packed in 8 bytes? Actually local_c is 2 floats, local_4 is third.
    // Note: In Ghidra's decomp, local_c is undefined8 (two floats), local_4 is float. We'll treat as float[3].
    
    // Check entity2's state (offset 0x6e3 * 4 = 0x1B8C) - likely a state enum
    char entityState = *(char*)((int)entity2 + 0x1B8C);
    if (entityState == 2 || entityState == 3) {
        // Use camera-relative position
        float* cameraPos = (float*)getCurrentCamera(); // FUN_00471610 returns float* (camera world pos)
        sourceVec[0] = g_targetHeight - cameraPos[0]; // DAT_00e44564 is some target height
        sourceVec[1] = g_targetHeight - cameraPos[1];
        sourceVec[2] = g_targetHeight - cameraPos[2];
    } else {
        // Use entity2's body position at offset +0x20 (3 floats)
        int* entityData = (int*)getCurrentCamera(); // Same function returns different singleton? Actually it's the same call but interpreted differently.
        // In the else branch, the function returns int* that is then dereferenced for vector at +0x20.
        // Let's treat it as some object with position at offset 0x20.
        sourceVec[0] = *(float*)(entityData + 0x20); // first two floats at 0x20 and 0x24? Actually local_c is CONCAT44 which reads 8 bytes at 0x20.
        sourceVec[1] = *(float*)((int)entityData + 0x24);
        sourceVec[2] = *(float*)((int)entityData + 0x28);
    }

    // Get threshold values from virtual functions at vtable index 0x214 (div/4 = 0x85)
    float threshold1 = getVirtualFloat(entity2, 0x214); // (**(code **)(*param_2 + 0x214))()
    float threshold2 = getVirtualFloat(entity1, 0x214); // (**(code **)(*param_1 + 0x214))()

    // Check global overrides (debug/cheats)
    if (isCheatsEnabled() || isDebugMode2()) {
        // Override thresholds with global value (possibly infinite)
        threshold1 = *(float*)&g_debugThreshold;
        threshold2 = *(float*)&g_debugThreshold;
    }

    // Perform intersection test from entity2's shape (offset +0x30) to source vector with threshold1
    bool hit1 = testIntersection(
        (void*)((int)getSomeSingleton() + 0x30), // iVar4+0x30 (first call: iVar4 = result of FUN_00471610)
        (void*)((int)getCurrentCamera() + 0x30), // iVar2+0x30
        &sourceVec,
        threshold1
    );

    if (hit1) {
        // Second intersection test from entity1's shape (offset +0x30) to entity2->+0x20 vector with threshold2
        bool hit2 = testIntersection(
            (void*)((int)getSomeSingletonAgain() + 0x30), // iVar5+0x30
            (void*)((int)getSomeSingleton()+ 0x30), // iVar4+0x30
            (void*)((int)getCurrentCamera() + 0x20),// iVar2+0x20 (source vector? but different offset)
            threshold2
        );
        if (hit2) {
            return 1;
        }
    }
    return 0;
}

// Stub functions (assume these exist in the codebase)
extern float g_targetHeight; // DAT_00e44564
extern float g_debugThreshold; // DAT_00d6bf98 (global float)

// Forward declarations for helper functions
extern void* getCurrentCamera(); // FUN_00471610: returns pointer to camera or some singleton
extern void* getSomeSingleton(); // Another call to same function, but we treat it as different for clarity
extern void* getSomeSingletonAgain(); // Third call
extern bool isCheatsEnabled(); // FUN_00481640
extern bool isDebugMode2(); // FUN_00481660
extern float getVirtualFloat(void* obj, int vtableOffset); // Virtual function call
extern bool testIntersection(void* shapeA, void* shapeB, void* vector, float threshold); // FUN_007f7f30