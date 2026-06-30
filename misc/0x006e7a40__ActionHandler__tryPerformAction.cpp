// FUNC_NAME: ActionHandler::tryPerformAction
bool ActionHandler::tryPerformAction(int thisPtr, uint32 param2, uint32 param3)
{
    float gameTime = DAT_01205228;  // global game time
    // Check if action already active and cooldown expired
    if ((*(byte *)(thisPtr + 0x8a) & 0x40) && (gameTime < *(float *)(thisPtr + 0x84) + _DAT_00e514c4))
    {
        return true; // Action not ready yet, but flag says active – treat as success?
    }

    float baseFactor = DAT_00d5fad8;
    if (*(char *)(thisPtr + 0x88) == 1)
    {
        baseFactor = DAT_00d5fad4;
    }

    // Some vector calculation (likely quaternion or euler)
    float scalar = (baseFactor + DAT_00d5faf4) - _DAT_00d5fb44;
    
    // Setup vectors for a possible rotation/interpolation
    Vector4 vecA, vecB;
    vecA.x = 0.0f;
    vecA.y = 0.0f;
    vecA.z = _DAT_00d5780c;  // likely a constant like 0.0f or 1.0f
    vecA.w = 0.0f;
    
    vecB.x = DAT_00d5fb40;   // some angle/offset
    vecB.y = 0.0f;
    vecB.z = _DAT_00d5780c;
    vecB.w = 0.0f;

    // Function performing operation on vectors (e.g., quaternion slerp)
    FUN_00a65bb0(&vecA, &vecB, _DAT_00d5fb44);

    // Logging / event system
    FUN_00549bf0();                 // Begin log context?
    FUN_00549cf0(local_170);        // Initialize some context (260 bytes)
    FUN_00540bc0(0x40136, 0x80000000, param2, param3); // Fire event with ID 0x40136
    uint32 result = FUN_00540cc0(local_29c); // Get result from event? (20 bytes)

    // Setup an "action" task structure
    ActionTask task;
    task.vtable = &PTR_LAB_00e3572c;  // Virtual method table
    task.flags = 0;
    task.someInt = 0;
    task.otherFlags = 0x10;  // -0x7ffffff0
    task.data = local_274;    // buffer for internal data (260 bytes)

    FUN_00549d40(thisPtr + 0x44);  // Add this object's sub-component to task?
    FUN_00549ea0(&task, 0);        // Execute / enqueue the task

    bool success = (task.someInt != 0); // Check execution result
    if (success)
    {
        *(byte *)(thisPtr + 0x8a) |= 0x40;   // Mark action as active
    }
    else
    {
        *(byte *)(thisPtr + 0x8a) &= 0xbf;   // Clear active flag
    }
    *(float *)(thisPtr + 0x84) = gameTime;   // Update last attempt time

    // Cleanup
    task.vtable = &PTR_LAB_00e3572c;  // Restore vtable? (may be unnecessary)
    if (task.otherFlags >= 0)
    {
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(task.data, task.otherFlags << 4, 0x17); // Free allocated memory
    }
    task.vtable = &PTR_LAB_00dcf968;  // Another cleanup vtable?
    FUN_00549cb0();                  // End log context

    return success;
}