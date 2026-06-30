// FUNC_NAME: Sentient::isTargetFacingAway
// Address: 0x0054f4a0
// Checks if the target entity (stored at this+0x14) is facing away from this entity's forward direction.
// Returns true if the dot product of this entity's forward vector (at this+0x90,0x94,0x98) 
// with the target's forward vector (at target+0x10,0x14,0x18) is negative.
// This indicates the target is generally facing away (angle > 90 degrees).

bool __thiscall Sentient::isTargetFacingAway(void* this) {
    // Dereference pointer to target entity at offset +0x14
    int targetEntity = *(int*)((char*)this + 0x14);
    
    // Compute dot product of this->forward (x,y,z) with target->forward (x,y,z)
    float dot = (*(float*)((char*)this + 0x90) * *(float*)(targetEntity + 0x10)) +
                (*(float*)((char*)this + 0x94) * *(float*)(targetEntity + 0x14)) +
                (*(float*)((char*)this + 0x98) * *(float*)(targetEntity + 0x18));
    
    return dot < 0.0f;
}