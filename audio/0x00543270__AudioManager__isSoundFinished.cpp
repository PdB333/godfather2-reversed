// FUNC_NAME: AudioManager::isSoundFinished
// Address: 0x00543270
// Role: Checks if a sound identified by soundId has finished playing.
//       Calls virtual method at vtable offset 500 (index 125).
//       Returns true if the method returned 0 (i.e., sound is finished).
bool __thiscall AudioManager::isSoundFinished(int *this, unsigned int soundId)
{
    // vtable +0x1F4 method: returns 0 if still playing, non-zero otherwise.
    int result = (*(code **)(*this + 500))(soundId);
    return result == 0;
}