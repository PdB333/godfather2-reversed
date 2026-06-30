// FUNC_NAME: PlayerReputationTracker::updateReputation
void __fastcall PlayerReputationTracker::updateReputation(int this)
{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined1 *puVar4;
  float local_18;
  float local_14;
  undefined1 *local_10 [3];
  code *local_4;
  
  iVar3 = *(int *)(this + 0x3d0) * 0x30; // +0x3d0: current crime type index
  iVar1 = *(int *)(iVar3 + this + 0x34); // +0x34: crime state array, offset by type*0x30
  uVar2 = *(int *)(iVar3 + 0x20 + this) / 10; // +0x20: reputation points for this crime type, divided by 10
  
  if (iVar1 == 1) { // CrimeState::InProgress
    FUN_00894e50(0xc5d9c585,(float)(int)uVar2,0); // Add reputation - criminal
    *(int *)(this + 0x3d8) = *(int *)(this + 0x3d8) + 1; // +0x3d8: crimes completed count
    local_14 = (float)*(int *)(this + 0x3d8);
    *(int *)(this + 0x3e0) = *(int *)(this + 0x3e0) + uVar2; // +0x3e0: total rep accumulated this session
    
    if (*(int *)(this + 0x3d8) < 0) {
      local_14 = local_14 + DAT_00e44578; // Handle underflow (add frame time?)
    }
    local_18 = 0.0;
    FUN_008934e0(0x6c725335,&local_18); // Get elapsed time since last check
    if (local_18 < local_14) {
      FUN_00894ea0(0x6c725335,local_14,0); // Schedule next rep increase
    }
  }
  else if (iVar1 == 3) { // CrimeState::Failed
    *(int *)(this + 0x3e4) = *(int *)(this + 0x3e4) + uVar2; // +0x3e4: failed rep sum
  }
  else if (iVar1 == 0) { // CrimeState::Completed
    FUN_00894e50(0xa25662c2,(float)(int)uVar2,0); // Add reputation - completion bonus
    *(int *)(this + 0x3e4) = *(int *)(this + 0x3e4) + uVar2;
  }
  else if (iVar1 == 2) { // CrimeState::Cancelled
    FUN_00894e50(0x354e832f,(float)(int)uVar2,0); // Add reputation - negative
    FUN_00894e50(0xbcbcc88d,0x3f800000,0); // Reset timer?
    *(int *)(this + 1000) = *(int *)(this + 1000) + uVar2; // +0x3e8: cancelled rep total
    *(int *)(this + 0x3ec) = *(int *)(this + 0x3ec) + 1; // +0x3ec: cancelled count
  }
  
  iVar1 = *(int *)(*(int *)(this + 0x3d0) * 0x30 + 0x34 + this); // Re-read current crime state
  if (((iVar1 == 2) || (iVar1 == 0)) || (iVar1 == 3)) { // If completed/failed/cancelled
    FUN_0093b340(*(int *)(this + 1000) + *(int *)(this + 0x3e4)); // Update total rep display
    FUN_004d4a60(local_10,1,"%06X.%06X", // Format truncated crime data as hex string
                 *(uint *)((*(int *)(this + 0x3d0) + 1) * 0x30 + this) & 0xffffff,
                 uVar2 & 0xffff);
    puVar4 = local_10[0];
    if (local_10[0] == (undefined1 *)0x0) {
      puVar4 = &DAT_0120546e; // Default empty string
    }
    FUN_009085a0(0x53504750,0x53574747,puVar4); // Send debug/log message (SPGP:SWGG)
    if (local_10[0] != (undefined1 *)0x0) {
      (*local_4)(local_10[0]); // Free string memory
    }
  }
  return;
}