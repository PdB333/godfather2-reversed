// FUNC_NAME: PlayerSoundManager::resetSoundStates
void __fastcall PlayerSoundManager::resetSoundStates(int thisPtr)
{
  // Stop (release?) various sound events/anchor points
  FUN_00408680(&DAT_0112ecfc); // wwise event stop or release
  FUN_00408680(&DAT_012069c4);
  FUN_00408680(&DAT_0112edf4);
  FUN_00408680(&DAT_0112ef7c);
  FUN_00408680(&DAT_01218068);

  // Reset driver ambient sound (param_1+0xa0)
  int ambientSoundId = *(int *)(thisPtr + 0xa0); // +0xa0: active ambient sound id
  int nullParam = 0;
  char nullByte = 0;
  FUN_00408a00(&ambientSoundId, 0); // possibly stop/remove sound reference

  // Reset secondary ambient
  ambientSoundId = DAT_0112ee84; // global ambient sound id
  FUN_00408a00(&ambientSoundId, 0);

  // Set state to 2 (probably "idle" or "stopped" state)
  *(int *)(thisPtr + 0xd8) = 2; // +0xd8: sound state enum

  // Update some global sound state
  FUN_0094e640(); // possibly update environment/ambient state

  // Reset another global sound anchor
  ambientSoundId = DAT_0112b214;
  FUN_00408a00(&ambientSoundId, 0);

  // Update sound system
  FUN_0093a2f0(); // refresh sound context

  // Reset music state
  ambientSoundId = DAT_0112b534;
  FUN_00408a00(&ambientSoundId, 0);

  // Sync current sound position with previous
  *(int *)(thisPtr + 0x124) = *(int *)(thisPtr + 0x120); // +0x120=current position, +0x124=previous position

  // Clear bit 3 in flags (allow new sounds to play?)
  *(unsigned int *)(thisPtr + 0x7c) &= 0xfffffff7; // +0x7c: flags bitfield

  // If there's an active sound to stop (+0x90 != 0)
  if (*(int *)(thisPtr + 0x90) != 0) {
    int stopResult = FUN_0090e2d0(*(int *)(thisPtr + 0x10c), *(int *)(thisPtr + 0x90), 0x1a, 0, 0, 0);
    // 0x1a = likely stop action ID
    *(int *)(thisPtr + 0x110) = stopResult; // +0x110: result of stop action
    FUN_009847c0(0xffffffff); // probably unregister sound instance
  }

  // Reset footstep surface sound (param_1+0xa8)
  ambientSoundId = *(int *)(thisPtr + 0xa8); // +0xa8: current footstep surface sound id
  FUN_00408a00(&ambientSoundId, 0);
}