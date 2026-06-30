// FUNC_NAME: EntityAnimationComponent::SetPlaybackSpeed
void __thiscall EntityAnimationComponent::SetPlaybackSpeed(float speed)
{
    // Pointer to a sub-object (e.g., animation state) at +0x218 from this
    int* subObject = *(int**)((char*)this + 0x218);
    if (subObject != nullptr)
    {
        // +0x104: playback rate/duration
        *(float*)(subObject + 0x104 / 4) = speed;
        // +0x108: inverse rate (computed from global constant DAT_00e2b1a4)
        *(float*)(subObject + 0x108 / 4) = DAT_00e2b1a4 / speed;
    }
}