// FUNC_NAME: StreamPlayer::startPlayback
void __thiscall StreamPlayer::startPlayback(bool startImmediate)
{
  AudioSource* source = *(AudioSource**)(this + 0x58); // owner audio source
  *(uint32*)(this + 0x1d8) = 0x18; // initial playback flags (bits 3 and 4)

  if (source == nullptr) {
    return;
  }

  // If source's stream is active (bit21 = 0x200000), stop it
  if ((*(uint32*)(source + 0x8e8) >> 0x15 & 1) != 0) {
    playSoundEffect(0x55); // maybe stop/event ID
    stopStream(this + 0x168); // stop the stream object
  }

  // Determine if any audio channel is unmuted
  VolumeControl* master = getVolumeControl(0x47); // 'G' = master
  bool isUnmuted = false;
  if (isVolumeMuted(master) == 0) {
    isUnmuted = true;
    *(uint32*)(this + 0x1d8) |= 0x1; // bit0: master active
  } else {
    VolumeControl* sfx = getVolumeControl(0x48); // 'H' = sfx
    if (isVolumeMuted(sfx) == 0) {
      isUnmuted = true;
      *(uint32*)(this + 0x1d8) |= 0x2; // bit1: sfx active
    } else {
      VolumeControl* music = getVolumeControl(0x49); // 'I' = music
      if (isVolumeMuted(music) != 0) {
        goto playLabel;
      }
      isUnmuted = true;
      *(uint32*)(this + 0x1d8) |= 0x4; // bit2: music active
    }
  }

  // If any channel is unmuted, force immediate playback
  startImmediate = true;

playLabel:
  Stream* stream = (Stream*)(this + 0x168);
  // Copy some state from source (e.g., playback time offset?)
  *(uint32*)(this + 0x258) = *(uint32*)(source + 0x3184);

  attachStreamToSource(source, stream, true); // link stream to source
  prepareStream(stream); // prepare for playback

  if (startImmediate) {
    playStreamImmediate(stream); // start playing now
  }

  updateAudioSystem();
}