// FUNC_NAME: PlayerSM::handleInput
undefined1 __fastcall PlayerSM::handleInput(int this)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  char *pcVar5;
  undefined4 local_1c;
  uint uStack_10;
  undefined8 local_c;
  undefined4 local_4;
  
  uVar4 = 0;
  // Check if input is enabled (bit 5 of flags at +0x74->+4)
  if ((((*(byte *)(*(int *)(this + 0x74) + 4) & 0x20) != 0) &&
      // Check if game is not paused (bit 2 of global pause flags)
      (iVar2 = FUN_007ab160(), (*(byte *)(iVar2 + 4) & 4) != 0)) &&
     // Check if no cutscene is playing (DAT_0112a838 == 0 or cutscene handle is 0)
     ((DAT_0112a838 == 0 || (*(int *)(DAT_0112a838 + 0x5c) == 0)))) {
    // Check if player is alive and can accept input (bit 10 of player state flags at +0x58->+0x8e0)
    iVar2 = FUN_00800b10();
    if ((iVar2 != 0) && ((*(uint *)(*(int *)(this + 0x58) + 0x8e0) >> 10 & 1) != 0)) {
      // Allocate a new input event (size 0x38)
      uVar3 = FUN_00798f50(0x38);
      cVar1 = FUN_0079e920(uVar3);
      if (cVar1 != '\0') {
        uVar4 = 1;
        // Check if there's pending input to process
        cVar1 = FUN_00481620();
        if (cVar1 != '\0') {
          local_1c = CONCAT31(local_1c._1_3_,1);
          // Queue the input event (type 0xc, with parameters)
          FUN_0079fb90(0xc,CONCAT44(3,local_1c),(ulonglong)uStack_10 << 0x20,local_c,local_4);
          return 1;
        }
      }
    }
    // Check for alternative input (e.g., menu/back button)
    cVar1 = FUN_00481640();
    if ((cVar1 != '\0') && (pcVar5 = (char *)(*(int *)(this + 0x58) + 0x22e8), *pcVar5 == '\0'))
    {
      // Set flag at +0x22e8 to indicate menu input received
      *pcVar5 = '\x01';
      return 1;
    }
  }
  return uVar4;
}