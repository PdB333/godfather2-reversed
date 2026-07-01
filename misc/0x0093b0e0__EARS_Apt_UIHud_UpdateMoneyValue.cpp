// Xbox PDB: EARS_Apt_UIHud_UpdateMoneyValue
// FUNC_NAME: Player::updateMoneyValue
void __fastcall Player::updateMoneyValue(int this)
{
  int iVar1;
  undefined1 *puVar2;
  float10 fVar3;
  float local_14;
  undefined1 *local_10;
  undefined4 local_c;
  undefined4 local_8;
  code *local_4;
  
  // Check if bit 0x11 (bit 17) of flags at +0x5c is set
  if ((*(uint *)(this + 0x5c) >> 0x11 & 1) != 0) {
    local_14 = 0.0;
    // Check if global pointer at DAT_01223484 + 0xc is zero (likely some game mode or state)
    if (*(int *)(DAT_01223484 + 0xc) == 0) {
      // Use a constant value from DAT_01129908 + 0x14 (likely a default money value)
      local_14 = *(float *)(DAT_01129908 + 0x14);
    }
    else {
      // Get some object by ID 0x637b907 (likely a player or entity)
      iVar1 = FUN_008c74d0(0x637b907);
      if ((iVar1 != 0) && (*(int *)(iVar1 + 0x230) != 0)) {
        // Get a random or calculated value
        fVar3 = (float10)FUN_00892390();
        local_14 = (float)fVar3;
      }
    }
    local_10 = (undefined1 *)0x0;
    local_c = 0;
    local_8 = 0;
    local_4 = (code *)0x0;
    // Format the money value as a string (likely localized)
    FUN_00604030(local_14,0,&local_10,1);
    puVar2 = local_10;
    if (local_10 == (undefined1 *)0x0) {
      puVar2 = &DAT_0120546e; // Fallback string (empty or default)
    }
    // Update the money value display (HUD element)
    FUN_005a04a0("UpdateMoneyValue",0,&DAT_00d8a64c,1,puVar2);
    if (local_10 != (undefined1 *)0x0) {
      (*local_4)(local_10); // Free the allocated string
    }
  }
  return;
}