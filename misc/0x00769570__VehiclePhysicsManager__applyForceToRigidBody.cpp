// FUNC_NAME: VehiclePhysicsManager::applyForceToRigidBody
void __thiscall applyForceToRigidBody(int thisPtr) {
    int* manager;
    int* rigidBody;
    
    // Dereference offset 0x5c to get a manager pointer (e.g., HavokPhysicsManager)
    manager = *(int**)(thisPtr + 0x5c);
    if (manager != (int*)0) {
        // Offset 0x24c4 likely holds a pointer to a rigid body or collision node
        rigidBody = *(int**)(manager + 0x24c4);
        if (rigidBody != (int*)0) {
            // Subtract 0x48 to get base of rigid body structure (member offset)
            rigidBody = (int*)((char*)rigidBody - 0x48);
            if (rigidBody != (int*)0) {
                // Apply physics force scaled by global time and multiplier
                // DAT_01206800 likely = global time step, DAT_00d636b8 = force scalar
                float force = *(float*)0x01206800 * *(float*)0x00d636b8;
                FUN_00470230(rigidBody, force, 0);
            }
        }
    }
}