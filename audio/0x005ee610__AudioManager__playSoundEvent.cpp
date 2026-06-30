// FUNC_NAME: AudioManager::playSoundEvent
// Address: 0x005ee610
// Handles playing a sound event with a single parameter.
// Uses EARS audio system (streaming audio engine).
// param_1 likely points to AudioManager (+0x580 is pointer to SoundSystem)
// param_2 is the sound event ID/resource identifier

undefined4 __cdecl AudioManager::playSoundEvent(int this, int eventId)
{
  int soundSystem;
  int iVar2;
  undefined4 result;

  result = 0;
  if ((eventId != 0) && (soundSystem = *(int *)(this + 0x580), soundSystem != 0)) // +0x580: pointer to SoundSystem
  {
    iVar2 = FUN_005e9d10(); // Get sound event manager or bank reference
    if (iVar2 != 0)
    {
      // Initialize event parameter structure (5 = event type param index?)
      FUN_00c9cbe0(soundSystem, *(undefined4 *)(iVar2 + 0x10), 5, &eventParams);
      // Zero out the event parameter buffer (size ~28 bytes)
      eventParams = 0; // local_4c
      eventParams.field_0x8 = 0; // local_44
      eventParams.field_0x10 = 0; // local_34
      eventParams.field_0x14 = eventId; // local_2c (the actual parameter value)
      eventParams.field_0x1c = 0; // local_1c
      eventParams.field_0x24 = 0; // local_14 (not shown in ordering due to stack layout)
      FUN_00c9eac0(); // Start sound event setup
      FUN_00c9cd40(1, 0); // Set parameter index 1 to 0 (e.g., volume/pan?)
      FUN_00c9cd40(5, &eventParams); // Set parameter index 5 to the event parameters struct
      result = FUN_00c9eb20(); // Execute/play the event
      *(undefined4 *)(in_EAX + 0x20) = result; // Store result in sound state (+0x20)
      FUN_00c9eae0(); // End event configuration
      *(undefined4 *)(in_EAX + 0x28) = local_1c; // Store another field (+0x28)
    }
    result = 1; // Success
  }
  return result;
}