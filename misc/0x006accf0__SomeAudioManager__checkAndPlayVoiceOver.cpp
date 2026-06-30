// FUNC_NAME: SomeAudioManager::checkAndPlayVoiceOver
undefined4 FUN_006accf0(uint param_1)

{
  param_1 = FUN_006ac320(param_1);  // Likely resolveSoundBankIndex
  if (param_1 < 0x14) {            // Valid range check (20 sounds)
    FUN_006aca10(&param_1);        // StartVoiceOver playback
    FUN_006acb10();                // PlayVoiceOver now
    return 1;                      // Success
  }
  return 0;                        // Invalid sound index
}