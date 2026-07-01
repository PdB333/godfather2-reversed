// FUNC_NAME: GodfatherGameManager::update
void __fastcall GodfatherGameManager::update(undefined4 *this)
{
  char cVar1;
  
  *this = &PTR_LAB_00d67ac8; // vtable setup
  FUN_00460340(0,0x3f800000); // setTimeScale(0, 1.0f)
  FUN_0045f250(0); // resetGameClock(0)
  FUN_007f6420(0x10); // playSound(0x10)
  FUN_007f6420(0x66); // playSound(0x66)
  
  // Clear flags at offset +0x1b94 in the object at this[0x14]
  *(uint *)(this[0x14] + 0x1b94) = *(uint *)(this[0x14] + 0x1b94) & 0xffffffef;
  *(uint *)(this[0x14] + 0x1b94) = *(uint *)(this[0x14] + 0x1b94) & 0xfffffffb;
  
  FUN_007fbe90(); // updateAudio()
  FUN_007fbe50(); // updateAudioStreams()
  
  // Call virtual function at vtable+0x290 on the object at this[0x14]
  (**(code **)(*(int *)this[0x14] + 0x290))(1,2);
  
  if ((*(byte *)(this + 0x15) & 8) != 0) {
    FUN_007f4490(0,0,DAT_00d5ef90); // playDialog(0, 0, dialogID)
    *(byte *)(this + 0x15) = *(byte *)(this + 0x15) & 0xf7; // Clear flag
  }
  
  // Clear flag at offset +0x1f5c
  *(uint *)(this[0x14] + 0x1f5c) = *(uint *)(this[0x14] + 0x1f5c) & 0xffffbfff;
  
  if (((*(uint *)(this[0x14] + 0x8e0) >> 1 & 1) != 0) &&
     ((*(byte *)(this + 0x15) & 0x80) != 0)) {
    FUN_0072cb10(0); // triggerMissionEvent(0)
  }
  
  cVar1 = (**(code **)(*(int *)this[0x14] + 0x1bc))(); // Call virtual function at vtable+0x1bc
  if (cVar1 != '\0') {
    if (*(int *)(this[0x14] + 0x1e70) != 0) {
      FUN_004df600(); // deleteObject()
    }
    if (*(int *)(this[0x14] + 0x1e84) != 0) {
      FUN_004df600(); // deleteObject()
    }
  }
  
  FUN_00716310(); // updateCamera()
  
  if (this[0x19] != 0) {
    FUN_004daf90(this + 0x19); // releaseResource(this + 0x19)
  }
  if (this[0x17] != 0) {
    FUN_004daf90(this + 0x17); // releaseResource(this + 0x17)
  }
  
  this[0x16] = &PTR_LAB_00e2f0c0; // Set pointer to some global
  FUN_004ac1e0(); // updateUI()
  return;
}