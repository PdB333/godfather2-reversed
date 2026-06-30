// FUNC_NAME: ChaseCamera::getTargetPositionAndVelocity
void __thiscall ChaseCamera::getTargetPositionAndVelocity(int this, Vector3 *outPosition, Vector3 *outVelocity)
{
    // +0x260: pointer to target entity (likely a Sentient or Vehicle)
    int *targetEntity = *(int **)(this + 0x260);
    
    if (targetEntity != 0) {
        // Get the vtable from the target entity's data at +0x10
        // Call a method at vtable offset 0x1c (likely getPositionAndVelocity or similar)
        // The method takes: this + 0xe0 (some offset), 0 (some flag), and a local buffer
        int *vtable = *(int **)(targetEntity + 0x10);
        int entityData = targetEntity + 0xe0;
        Vector3 localPos; // local_30 is the position buffer
        (**(code **)(vtable + 0x1c))(entityData, 0, &localPos);
        
        // Copy the results to output parameters
        *outPosition = *(Vector3 *)&localPos;
        *outVelocity = *(Vector3 *)((int)&localPos + 0x10); // uStack_2c is velocity
        return;
    }
    
    // No target, zero out outputs
    *outPosition = Vector3(0, 0, 0);
    *outVelocity = Vector3(0, 0, 0);
}