// FUNC_NAME: DebugMenuSystem::createVenueSelectJobTask

#include <cstdint>

// Forward declarations of external functions (EA EARS engine internal)
void debugPushContext(int contextId);
void* getPlayerTransform();  // returns pointer to a float[3] + quat? Actually we see three floats: position, one more float, maybe rotation? Let's keep as generic.
void debugPopContext();
void vectorClear(float* vec);
void matrixMultiply(const float* a, const float* b, float* result);  // dimensions assume 4x4? local_50 is 76 bytes = 19 floats? but not typical.
void debugPrintString(const char* str);
int* debugCreateTaskNode(const float* transform1, const float* transform2, int parentId, int taskType, int flags, int unk1, int unk2);  // returns pointer to new node

// Global constant for identity quaternion or zero vector
extern const float g_identityQuat[4];  // _DAT_00d5780c appears multiple times, likely all zeros? Actually it's used as a constant float, maybe 1.0? We'll treat as identity.
extern const float g_positionOffset;  // DAT_00d8bbc8, maybe offset for something

void __fastcall DebugMenuSystem::createVenueSelectJobTask(int thisPtr)
{
    float playerTransform[3];  // from getPlayerTransform: position (x,y,z) and rotation? Actually we have *puVar1, puVar1[1], puVar1[2] - three floats? But code uses fStack_ac = offset + puVar1[1] as y? Let's rearrange.
    float playerRot;  // from puVar1[2]? Actually uStack_a8 = puVar1[2]; That might be rotation component.
    float playerPos[2];  // only x and z? local_b0 = *puVar1 (x), fStack_ac = offset + puVar1[1] (y?), uStack_a8 = puVar1[2] (z?)
    // Actually we have three floats: x, y, z. The offset added to second element suggests y-axis offset.

    void* playerData = getPlayerTransform();
    if (!playerData)
    {
        debugPopContext();
        return;
    }

    // Extract player transform components
    playerPos[0] = *(float*)playerData;            // +0x00: x
    playerPos[1] = *(float*)((char*)playerData + 4); // +0x04: y (to which offset added)
    playerRot = *(float*)((char*)playerData + 8);   // +0x08: rotation (yaw?) or z?

    float localTransform[4]; // actually local_b0, fStack_ac, uStack_a8, uStack_a4: this is a 3D point + identity quat? uStack_a4 = g_identityQuat (constant)
    localTransform[0] = playerPos[0];
    localTransform[1] = playerPos[1] + g_positionOffset;  // fStack_ac
    localTransform[2] = playerRot;
    localTransform[3] = g_identityQuat; // maybe w component? Actually uStack_a4 = _DAT_00d5780c, which might be 0.0 or 1.0. Since used as quaternion identity (1,0,0,0) but often stored as w? For simplicity treat as scalar.

    debugPopContext();

    // Build a working transform matrix or structure
    float workMatrix[16]; // local_9c..local_94? Actually there are many undefined4 locals that form a matrix? Let's use local names.
    float matrixResult[19]; // local_50 is 76 bytes = 19 floats; possibly a 4x4 matrix with extra?
    // Actually the code does FUN_00425060(&local_9c,0) -> zero out a vector? Then FUN_0056b8a0(local_98,local_9c,local_94,local_50) -> copy/transform?
    // Hard to reconstruct exactly. Simplify: assume we have a function that creates a transform from player position.

    // The next block sets up a "finalTransform" (local_90..local_60) with identity rotation and player position:
    // local_90 = g_identityQuat; uStack_8c = 0; uStack_88 = 0; uStack_84 = 0; local_80 = 0; uStack_7c = g_identityQuat; ...
    // This is messy. Probably constructing a 4x4 transformation matrix.
    // We'll skip the exact matrix math and assume debugCreateTaskNode takes the transform.

    // Simulate the transform construction (simplified)
    float finalTransform[16];
    // Assume identity rotation and player position
    // For brevity, we'll just use localTransform array.

    debugPrintString("dv_venue_select_jobtask");

    int* newTask = debugCreateTaskNode(&localTransform[0], &finalTransform[0], 0xFFFFFFFF, 4, 0, 0xFFFFFFFF, 0);
    if (!newTask)
    {
        // cleanup? Already popped.
        return;
    }

    // Link into a singly linked list at thisPtr+0xAC
    int* taskListPtr = *(int**)(thisPtr + 0xAC);  // +0xAC: pointer to head of task list
    if (taskListPtr != nullptr)
    {
        taskListPtr[2] = 0;  // clear next field? Actually *(undefined4 *)(*piVar2 + 8) = 0; That's offset 8.
        *taskListPtr = 0;   // dereference? Wait: *piVar2 = 0; Actually code: if (*piVar2 != 0) { *(undefined4 *)(*piVar2 + 8) = 0; *piVar2 = 0; }
        // So it clears the head pointer and also sets the previous node's next to null? This looks like it might be a stack (prev pointer at +8). But then the new node's back pointer is set to piVar2.
        // So likely a reverse linked list where offset 8 points back to the previous node.
    }

    // Store new task at thisPtr+0xAC
    *(int**)(thisPtr + 0xAC) = newTask;  // *piVar2 = local_b4;

    // Double-link: set new node's back pointer to point to the head pointer itself? Actually: *(int **)(local_b4 + 8) = piVar2; where piVar2 = thisPtr+0xAC
    // So new node's offset 8 holds address of the head pointer. That's unusual but possible for a doubly linked list with sentinel.
    // This is how the engine sometimes implements linked lists where head is stored as a pointer and each node has a pointer to the head pointer.
    *(int**)(newTask + 8) = (int*)(thisPtr + 0xAC);  // back link to the head location
}