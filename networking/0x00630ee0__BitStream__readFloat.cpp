// FUNC_NAME: BitStream::readFloat
undefined4 __thiscall BitStream::readFloat(int this)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  double dVar4;
  float local_14;
  int local_10;
  float local_c;
  
  piVar3 = *(int **)(this + 0xc); // +0xC: current read position pointer
  if (*(int **)(this + 8) <= piVar3) goto LAB_00630f9b; // +0x8: end of buffer
  if (piVar3 == (int *)0x0) goto LAB_00630f9b;
  if (*piVar3 != 3) { // Check if current tag is not a float (tag 3)
    if (*piVar3 != 4) goto LAB_00630f9b; // Check if current tag is not a double (tag 4)
    iVar2 = FUN_00636850(&local_14); // Read double value
    if (iVar2 == 0) goto LAB_00630f9b;
    local_10 = 3; // Convert to float tag
    local_c = local_14;
    piVar3 = &local_10;
  }
  local_14 = (float)piVar3[1]; // Read float value from tag data
  if (local_14 == DAT_00e2b05c) { // Check for sentinel value (NaN or special)
    while (((piVar3 = *(int **)(this + 0xc), *(int **)(this + 8) <= piVar3 ||
            (piVar3 == (int *)0x0)) ||
           ((*piVar3 != 3 && ((*piVar3 != 4 || (iVar2 = FUN_00636850(&local_10), iVar2 == 0))))))) {
      FUN_00627ac0(PTR_s_number_00e2a8a8); // Log error "number"
LAB_00630f9b:
      local_14 = 0.0;
    }
  }
  puVar1 = *(undefined4 **)(this + 8); // Get write position
  *puVar1 = 3; // Write float tag
  dVar4 = (double)local_14;
  FUN_00b9c041(); // Possibly convert float to network byte order
  puVar1[1] = (float)dVar4; // Write float value
  *(int *)(this + 8) = *(int *)(this + 8) + 8; // Advance write position by 8 bytes
  return 1;
}