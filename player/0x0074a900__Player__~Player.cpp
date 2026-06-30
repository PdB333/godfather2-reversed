// FUNC_NAME: Player::~Player
void __thiscall Player::~Player(void)
{
  // +0x00: vtable pointer, set to derived class vtable initially
  *(int **)this = &PTR_LAB_00d644d4;

  // Debug log with ID 0x46 (e.g., "Player destroyed")
  debugPrint(0x46);

  char isInGame = isGameplayActive();       // FUN_0072d630
  char isPlaying = isMissionActive();       // FUN_00717c70

  if (isPlaying == '\0') {
    uint soundId = 0;
    uint missionHash = getCurrentMissionHash(0, 0); // FUN_006fbc40
    uint soundEvent;
    if (isInGame == '\0') {
      soundEvent = this->field_0xC0;       // +0x30*4 = 0xC0, e.g. currentAreaSound
    } else {
      soundEvent = this->field_0xC4;       // +0x31*4 = 0xC4, e.g. currentMusic
    }
    playSoundEvent(soundEvent, 0, missionHash, soundId); // FUN_007f96a0
  } else {
    // Playing mission: check flag bit 3 at +0x70 (0x1c*4)
    if (((this->field_0x70 >> 3) & 1) == 0) {
      goto cleanup;
    }
    uint soundId = 0;
    uint missionHash = getCurrentMissionHash(0, 0);
    uint soundEvent;
    if (isInGame == '\0') {
      soundEvent = 0x90fd9d7; // hash for "mission ending" sound
    } else {
      soundEvent = 0x74fcaade; // hash for "mission failed" sound
    }
    playSoundEvent(soundEvent, 0, missionHash, soundId);
  }
  stopAllSounds(); // FUN_006fbc70

cleanup:
  if (this->field_0x84 != 0) { // +0x21*4 = 0x84, e.g. hudPointer
    releaseUIElement(this->field_0x84); // FUN_009c8f10
  }

  // Switch vtable to base class (release derived part)
  *(int **)this = &PTR_LAB_00d63090;

  if (this->field_0x68 != 0) { // +0x1A*4 = 0x68, e.g. crewList
    clearContainer(this + 0x1A); // FUN_004daf90, likely a vector/array
  }

  finalizeDestruction(); // FUN_0080ea60
}