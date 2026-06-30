// FUNC_NAME: MissionTriggerManager::createTrigger
void MissionTriggerManager::createTrigger(undefined4 *pMissionId, int missionManager, undefined8 *pTransformData)
{
  // TLS handle to get current thread data (EARS engine multitasking)
  TlsGetValue(DAT_01139810);

  // Allocate a 0x160-byte structure (likely a MissionTrigger internal state), tag 0x31
  int triggerState = FUN_00aa2680(0x160, 0x31);
  *(undefined2 *)(triggerState + 4) = 0x160; // store allocation size for validation

  // Look up the trigger definition from missionManager's string table (+0x10) using global string key
  int definitionIndex = FUN_009f0c70(*(undefined4 *)(missionManager + 0x10), &DAT_011397d0, 0);

  // Allocate a data block for the trigger's transform/world-space data
  uint triggerDataBlock = FUN_00559d40(); // returns uint (handle or address)
  undefined4 missionIdValue = *pMissionId;

  // Register the trigger with the mission manager (param_2 is missionManager, third arg 1 = enable/active)
  FUN_00556c80(missionManager, missionIdValue, 1);

  // Set flags in the trigger state: combine with high bits and shift
  *(uint *)(triggerState + 0x2c) = (triggerDataBlock >> 2) | 0xc0000000;

  // Engine-level update (likely flush property changes)
  FUN_0043b490();

  // Send event 0x2001 (e.g., "create trigger") with the mission ID and zero
  FUN_009f01f0(0x2001, missionIdValue, 0);

  // Write transform data into the data block at known offsets
  // Transform appears to be two 64-bit values (e.g., position+quaternion or min/max) and one 32-bit value
  *(undefined8 *)(triggerDataBlock + 0x4c) = *pTransformData;           // first 8 bytes
  *(undefined8 *)(triggerDataBlock + 0x54) = pTransformData[1];          // second 8 bytes
  *(undefined4 *)(triggerDataBlock + 0x5c) = *(undefined4 *)(pTransformData + 2); // last 4 bytes

  // Send event 0x2002 (e.g., "finalize trigger") with the mission ID pointer and zero
  FUN_009f01f0(0x2002, pMissionId, 0);

  // Final engine flush after trigger creation
  FUN_009f01a0();
}