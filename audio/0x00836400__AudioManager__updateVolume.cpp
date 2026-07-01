// FUNC_NAME: AudioManager::updateVolume
void __thiscall AudioManager::updateVolume(int this, int *param_2)

{
  float local_c8;
  undefined1 local_c0 [188];
  
  if (DAT_0112dbc0 != 0) {
    if (param_2 == (int *)0x0) {
      FUN_00836330(this + 0x30);  // stopChannel(this + 0x30)
      return;
    }
    local_c8 = _DAT_00d5780c;  // currentTime
    FUN_008297a0();  // getMasterVolume()
    FUN_0081f830();  // getChannelVolume()
    if (*(int *)(*param_2 + 0xc) == *(int *)(this + 0xc)) {  // compare channel IDs
      local_c8 = (float)param_2[1];  // target volume
      FUN_0081f8c0(*param_2 + 0x30,local_c8);  // setChannelVolume(channel, volume)
      local_c8 = _DAT_00d5780c - local_c8;  // time delta
    }
    FUN_0081f8c0(this + 0x30,local_c8);  // setChannelVolume(this + 0x30, volume)
    FUN_00836330(local_c0);  // stopChannel(local_c0)
  }
  return;
}