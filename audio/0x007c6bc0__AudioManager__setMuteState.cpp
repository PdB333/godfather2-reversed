// FUNC_NAME: AudioManager::setMuteState
void AudioManager::setMuteState(bool isMuted)
{
  if (isMuted) {
    // Mute: stop all sounds (0x19 = 25, likely a "stop all" command)
    FUN_007f63e0(0x19);
    // Mute: set master volume to 0 (0x1c = 28, likely master volume control)
    FUN_007f6420(0x1c);
    return;
  }
  // Unmute: restore volume for both channels
  FUN_007f6420(0x19);
  FUN_007f6420(0x1c);
  return;
}