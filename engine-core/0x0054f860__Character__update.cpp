// FUNC_NAME: Character::update
void __thiscall Character::update(int thisPtr, undefined4 param2)
{
  undefined4 *profileSlot;
  undefined8 timestamp;
  LPVOID tlsData;

  // Profile marker: start of "TtCharacter Update"
  tlsData = TlsGetValue(DAT_01139830);
  profileSlot = *(undefined4 **)((int)tlsData + 4);
  if (profileSlot < *(undefined4 **)((int)tlsData + 0xc)) {
    *profileSlot = "TtCharacter Update";
    timestamp = rdtsc();
    profileSlot[1] = (int)timestamp;
    *(undefined4 **)((int)tlsData + 4) = profileSlot + 3;
  }

  // Check bit 4 of flags at offset 0xe4 (maybe e.g. kFlagSomeSubsystem)
  if ((*(uint *)(thisPtr + 0xe4) >> 4 & 1) != 0) {
    FUN_00550a70(); // Possibly update some subsystem
  }

  // Branch based on bit 6: if clear, call normal update; if set, call alternate
  if ((*(uint *)(thisPtr + 0xe4) >> 6 & 1) == 0) {
    FUN_0054ff90(thisPtr, param2); // Normal character update
  } else {
    FUN_0054f910(param2); // Alternate path (maybe different mode)
  }

  // Profile marker: end (string at DAT_00e39c6c likely "TtCharacter Update End")
  tlsData = TlsGetValue(DAT_01139830);
  profileSlot = *(undefined4 **)((int)tlsData + 4);
  if (profileSlot < *(undefined4 **)((int)tlsData + 0xc)) {
    *profileSlot = &DAT_00e39c6c;
    timestamp = rdtsc();
    profileSlot[1] = (int)timestamp;
    *(undefined4 **)((int)tlsData + 4) = profileSlot + 3;
  }
  return;
}