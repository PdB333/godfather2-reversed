// FUNC_NAME: AudioDataManager::initializeAudioData
undefined * FUN_004f6de0(void)

{
  // Initialize audio data manager globals
  // +0x00: pointer to audio data table (DAT_00e3781c)
  // +0x04: audio format identifier (0x2e62656d = ".bem" string)
  // +0x08: sample rate (4 = 44100Hz? or 4kHz?)
  // +0x0c: buffer size (0x800 = 2048 bytes)
  // +0x10: flags (0 = initialized)
  // +0x14: more flags (0 = not ready)
  // +0x18: stream offset (0)
  // +0x1c: stream size (0)
  // +0x20: audio data pointer (DAT_00e3781c)
  // +0x24: audio format string (".bem")
  // +0x28: sample rate value (4)
  // +0x2c: buffer size (0x800)
  // +0x30: pointer to audio data table (DAT_00e37870)
  
  _DAT_01218fe4 = 0;  // +0x04: flags = 0
  _DAT_01218fec = 0;  // +0x0c: stream offset = 0
  _DAT_01218ff4 = 0;  // +0x14: stream size = 0
  _DAT_01218ff8 = 0;  // +0x18: more flags = 0
  _DAT_01218ffc = 0;  // +0x1c: unknown = 0
  _DAT_01218fdc = &DAT_00e3781c;  // +0x04: audio data pointer
  _DAT_01218fe0 = 0x2e62656d;    // +0x08: ".bem" string
  _DAT_01218fe8 = 4;             // +0x10: sample rate
  _DAT_01218ff0 = 0x800;         // +0x18: buffer size
  _DAT_01218fd8 = &PTR_LAB_00e37870;  // +0x00: pointer to audio data table
  return &DAT_01218fd8;  // Return pointer to initialized audio data manager
}