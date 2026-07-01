// FUNC_NAME: Player::updateProximityTriggers
void __fastcall Player::updateProximityTriggers(int this)
{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  uint local_4;
  
  // First pass: clear all proximity trigger flags (bit 0 of +0x2c)
  uVar7 = 0;
  if (*(int *)(this + 0x1a3c) != 0) {
    piVar8 = (int *)(this + 0x193c);
    do {
      *(uint *)(*piVar8 + 0x2c) = *(uint *)(*piVar8 + 0x2c) & 0xfffffffe;
      uVar7 = uVar7 + 1;
      piVar8 = piVar8 + 1;
    } while (uVar7 < *(uint *)(this + 0x1a3c));
  }
  
  // Get the game object manager / entity list
  uVar3 = FUN_008c6d20(2);
  puVar4 = (undefined4 *)FUN_0043c2c0(uVar3);
  puVar4 = (undefined4 *)*puVar4;
  
  do {
    if (puVar4 == (undefined4 *)0x0) {
      return;
    }
    
    piVar8 = (int *)*puVar4;
    local_4 = 0;
    
    // Check if this entity is a proximity trigger (vtable check with magic ID)
    cVar2 = (**(code **)(*piVar8 + 0x10))(0x55859efa, &local_4);
    piVar5 = (int *)(-(uint)(cVar2 != '\0') & local_4);
    
    // Check if the trigger is active and has positive range
    cVar2 = FUN_007f4800();
    if (((cVar2 != '\0') && (fVar9 = (float10)(**(code **)(*piVar5 + 0xc0))(), (float10)0 < fVar9))
       && (uVar7 = 0, *(int *)(this + 0x1a3c) != 0)) {
      
      // Iterate through proximity trigger slots
      piVar5 = (int *)(this + 0x193c);
      do {
        iVar1 = *piVar5;
        iVar6 = FUN_00471610(); // Get player position
        fVar10 = *(float *)(iVar6 + 0x30) - *(float *)(iVar1 + 0x10); // dx
        fVar11 = *(float *)(iVar6 + 0x34) - *(float *)(iVar1 + 0x14); // dy
        fVar12 = *(float *)(iVar6 + 0x38) - *(float *)(iVar1 + 0x18); // dz
        
        // Check distance squared against trigger radius squared
        if (fVar12 * fVar12 + fVar11 * fVar11 + fVar10 * fVar10 <=
            *(float *)(iVar1 + 0x1c) * *(float *)(iVar1 + 0x1c)) {
          // Player is within range, set trigger flag and call activation
          *(uint *)(iVar1 + 0x2c) = *(uint *)(iVar1 + 0x2c) | 1;
          FUN_00788580(piVar8);
          break;
        }
        uVar7 = uVar7 + 1;
        piVar5 = piVar5 + 1;
      } while (uVar7 < *(uint *)(this + 0x1a3c));
    }
    puVar4 = (undefined4 *)puVar4[1]; // Next entity in linked list
  } while( true );
}