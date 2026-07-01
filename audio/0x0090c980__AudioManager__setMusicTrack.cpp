// FUNC_NAME: AudioManager::setMusicTrack
void __thiscall AudioManager::setMusicTrack(int this, undefined4 trackId)
{
  // Set the music track - likely plays/queues a music track
  FUN_005dd9f0("MUSIC",trackId);
  // Store the track ID at offset +0x18 (current music track)
  *(undefined4 *)(this + 0x18) = trackId;
  // Notify the audio system about the music track change
  FUN_0069c010("Audio.Music",trackId);
  return;
}