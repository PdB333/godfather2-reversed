// FUNC_NAME: Player::initializePlayerState
void __fastcall Player::initializePlayerState(int *thisPtr)
{
  undefined4 uVar1;
  byte bVar2;
  uint uVar3;
  
  // Get some global value from DAT_01223480 + 0x54 -> +0x48
  uVar1 = *(undefined4 *)(*(int *)(DAT_01223480 + 0x54) + 0x48);
  
  // Call virtual function at vtable offset 0x22c (likely getPlayerIndex or similar)
  bVar2 = (**(code **)(*thisPtr + 0x22c))();
  
  // Get a random or time-based value
  uVar3 = FUN_0043b490();
  
  // Build a 64-bit state value: combine uVar1 with (uVar3 & 0xfff) << 0x10, OR with 0x3e5
  // +0xcf: playerStateFlags (64-bit)
  *(ulonglong *)(thisPtr + 0xcf) = CONCAT44(uVar1,(uVar3 & 0xfff) << 0x10) | 0x3e5;
  
  // +0xd1: playerStateFlags2 (64-bit) - set a bit based on bVar2
  *(ulonglong *)(thisPtr + 0xd1) = (ulonglong)(uint)(1 << (bVar2 & 0x1f));
  
  // +0xd3: some counter or state (32-bit)
  thisPtr[0xd3] = 0;
  
  // Clear or reset something at thisPtr[0xd8] (likely a pointer)
  FUN_009eace0(thisPtr[0xd8]);
  
  // Reset various subsystems
  FUN_0055d970(); // likely resetCombatState
  FUN_0055d870(); // likely resetMovementState
  FUN_0055dbd0(); // likely resetAnimationState
  
  return;
}