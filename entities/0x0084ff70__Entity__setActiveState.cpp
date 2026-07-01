// FUNC_NAME: Entity::setActiveState
void __fastcall Entity::setActiveState(void* this) // __thiscall, this in ecx
{
    // Set state to 2 (e.g., STATE_ACTIVE or STATE_RUNNING)
    *(int*)((char*)this + 0x84) = 2;

    // Debug log – likely prints a string from DAT_0120685c
    debugPrint(&DAT_0120685c);

    // Play sound or effect: using global audio manager, sound ID from +0xa8, with flags 1 and 0x10
    audioPlay(gAudioManager, *(int*)((char*)this + 0xa8), 1, 0x10);

    // Mark object as dirty or needs update: set bit 0 at +0x90
    *(unsigned int*)((char*)this + 0x90) |= 1;
}