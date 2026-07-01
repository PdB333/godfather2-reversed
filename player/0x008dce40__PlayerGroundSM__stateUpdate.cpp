// FUNC_NAME: PlayerGroundSM::stateUpdate

void __thiscall PlayerGroundSM::stateUpdate(PlayerGroundSM* this, int updateFlags)
{
    // Update the movement component (e.g., ground physics) at offset 0x1C8
    void* movementComponent = *(void**)((char*)this + 0x1C8);
    if (movementComponent)
    {
        ComponentUpdate(movementComponent);
    }

    // Process the input or update flags
    ProcessUpdateFlags(updateFlags);

    // If the low byte of updateFlags is zero (e.g., no directional input), reset the target direction
    if ((char)updateFlags == 0)
    {
        // Read the current target x from offset 0x1AC, and zero out y and z
        float target[3];
        target[0] = *(float*)((char*)this + 0x1AC);  // +0x1AC: target.x
        target[1] = 0.0f;                             // target.y = 0
        target[2] = 0.0f;                             // target.z = 0
        SetInputVector(target, 0);
    }
}