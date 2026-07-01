// FUNC_NAME: Player::handleExplosionProximity
void __thiscall Player::handleExplosionProximity(int this, int explosionData, int explosionOwner)
{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  char local_b8[4]; // buffer for some operation
  int local_b4; // linked list node
  int local_ac; // linked list node
  undefined4 local_b0;
  undefined4 local_a8;
  undefined8 local_a4;
  undefined4 local_9c;
  undefined8 local_98;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_80;
  undefined4 local_78;
  uint local_74;
  float local_70;
  float fStack_6c;
  float fStack_68;
  undefined4 uStack_64;
  char local_58[84]; // buffer for some operation
  
  // Get current player position
  iVar1 = FUN_00471610(); // likely getPlayerTransform or similar
  local_70 = *(float *)(iVar1 + 0x30); // position x
  fStack_6c = *(float *)(iVar1 + 0x34); // position y
  fStack_68 = *(float *)(iVar1 + 0x38); // position z
  uStack_64 = _DAT_00d5780c; // some global constant
  
  // Get explosion position
  iVar1 = FUN_00471610(); // likely getExplosionTransform
  fVar2 = local_70 - *(float *)(iVar1 + 0x30); // delta x
  fVar3 = fStack_6c - *(float *)(iVar1 + 0x34); // delta y
  fVar4 = fStack_68 - *(float *)(iVar1 + 0x38); // delta z
  
  // Check if distance squared is within explosion radius (stored at +0x184)
  if (fVar3 * fVar3 + fVar4 * fVar4 + fVar2 * fVar2 <
      *(float *)(this + 0x184) * *(float *)(this + 0x184)) {
    // Player is within explosion radius
    FUN_0084dd20(); // likely beginExplosionEffect or similar
    
    // Handle linked list for explosion owner (param_3)
    if (explosionOwner == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = explosionOwner + 0x48; // offset to some linked list node
    }
    if (local_b4 != iVar1) {
      if (local_b4 != 0) {
        FUN_004daf90(&local_b4); // likely removeFromLinkedList
      }
      local_b4 = iVar1;
      if (iVar1 != 0) {
        local_b0 = *(undefined4 *)(iVar1 + 4);
        *(int **)(iVar1 + 4) = &local_b4; // insert into linked list
      }
    }
    
    // Handle linked list for explosion data (param_3)
    if (explosionOwner == 0) {
      explosionOwner = 0;
    }
    else {
      explosionOwner = explosionOwner + 0x48;
    }
    if (local_ac != explosionOwner) {
      if (local_ac != 0) {
        FUN_004daf90(&local_ac); // remove from linked list
      }
      local_ac = explosionOwner;
      if (explosionOwner != 0) {
        local_a8 = *(undefined4 *)(explosionOwner + 4);
        *(int **)(explosionOwner + 4) = &local_ac; // insert into linked list
      }
    }
    
    // Get current and previous positions for velocity calculation
    iVar1 = FUN_00471610(); // get current transform
    local_98 = *(undefined8 *)(iVar1 + 0x30); // current position (x,y)
    local_90 = *(undefined4 *)(iVar1 + 0x38); // current position z
    iVar1 = FUN_00471610(); // get previous transform
    local_a4 = *(undefined8 *)(iVar1 + 0x30); // previous position (x,y)
    local_9c = *(undefined4 *)(iVar1 + 0x38); // previous position z
    
    local_74 = local_74 | 0x40; // set some flag
    local_8c = *(undefined4 *)(this + 0x198); // some value from player
    local_88 = 4; // some constant
    local_80 = 6; // some constant
    local_78 = DAT_01205224; // some global
    
    // Handle explosion data (param_2)
    if (explosionData == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = explosionData + 0x3c; // offset to some data
    }
    FUN_00408bb0(&DAT_0112dd94, iVar1, local_b8, 0); // likely some data copy or setup
    FUN_0084d330(); // likely applyExplosionForce
    FUN_0084dda0(local_b8); // likely finalizeExplosionEffect
    
    // Handle explosion data for damage
    if (explosionData == 0) {
      explosionData = 0;
    }
    else {
      explosionData = explosionData + 0x58; // offset to damage data
    }
    FUN_0070b6a0(local_58); // likely setupDamageBuffer
    FUN_004a8ec0(explosionData); // likely applyExplosionDamage
    FUN_0084e1c0(); // likely cleanupExplosionEffect
    
    // Cleanup linked lists
    if (local_ac != 0) {
      FUN_004daf90(&local_ac);
    }
    if (local_b4 != 0) {
      FUN_004daf90(&local_b4);
    }
  }
  return;
}