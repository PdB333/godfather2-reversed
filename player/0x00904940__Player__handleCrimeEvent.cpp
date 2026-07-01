// FUNC_NAME: Player::handleCrimeEvent
void __thiscall Player::handleCrimeEvent(int thisPtr, int *eventData)
{
  int iVar1;
  char cVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  undefined1 auStack_48 [20];
  undefined8 uStack_34;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_10;
  undefined4 uStack_8;
  uint uStack_4;
  
  // Check event type matches expected crime event signature (DAT_012180f8)
  if (((*eventData == DAT_012180f8) && (iVar1 = *(int *)(eventData[1] + 4), iVar1 != 0)) &&
     (iVar1 + -0x48 != 0)) {
    // If player is dead (bit 0 of flags at +0x200), handle death cleanup
    if ((*(byte *)(thisPtr + 0x200) & 1) != 0) {
      FUN_004088c0(iVar1 + -0xc);  // Some cleanup function
      FUN_004c1260(eventData);      // Release event data
      return;
    }
    // Get crime scene object from event data offset
    piVar3 = (int *)FUN_0046a1f0(iVar1 + -0x48,0x38523fc3);
    if ((piVar3 != (int *)0x0) && (cVar2 = (**(code **)(*piVar3 + 0x78))(), cVar2 != '\\0')) {
      FUN_0084dd20();  // Some initialization
      uVar4 = FUN_0044b210(thisPtr + -0x3c);  // Get player component
      FUN_006bf990(uVar4);  // Process crime event
      iVar5 = FUN_00471610();  // Get some manager
      uStack_34 = *(undefined8 *)(iVar5 + 0x30);
      uStack_18 = *(undefined4 *)(thisPtr + 0x1f8);  // +0x1F8: some player state
      uStack_2c = *(undefined4 *)(iVar5 + 0x38);
      uStack_10 = *(undefined4 *)(thisPtr + 0x1fc);  // +0x1FC: more player state
      uStack_1c = *(undefined4 *)(thisPtr + 500);     // +0x1F4: player state
      uStack_8 = DAT_01205224;
      iVar5 = FUN_00471610();  // Get manager again
      uStack_28 = *(undefined8 *)(iVar5 + 0x30);
      uStack_20 = *(undefined4 *)(iVar5 + 0x38);
      // Check additional flags at +0x200
      if ((*(uint *)(thisPtr + 0x200) & 2) != 0) {
        uStack_4 = uStack_4 | 2;
      }
      if ((*(uint *)(thisPtr + 0x200) & 4) != 0) {
        uStack_4 = uStack_4 | 4;
      }
      // Send crime event to UI/logging system
      FUN_00408bb0(&DAT_0112dd94,iVar1 + -0xc,auStack_48,0);
      FUN_0070aaf0();  // Update crime tracking
    }
  }
  FUN_004c1260(eventData);  // Release event data
  return;
}