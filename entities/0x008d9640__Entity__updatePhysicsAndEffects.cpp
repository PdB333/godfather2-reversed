// FUNC_NAME: Entity::updatePhysicsAndEffects
void __fastcall Entity::updatePhysicsAndEffects(int *this)
{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  float fVar4;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float fStack_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  undefined4 local_54;
  undefined1 local_50 [12];
  undefined4 local_44;
  undefined4 local_34;
  undefined4 local_24;
  undefined4 local_14;
  
  // Check if entity has a valid physics object (not null and not a specific type 0x48)
  if ((this[0x6c] != 0) && (this[0x6c] != 0x48)) {
    local_44 = 0;
    local_34 = 0;
    local_24 = 0;
    local_14 = _DAT_00d5780c; // Some global constant
    
    // Calculate velocity magnitude from velocity components at +0x208, +0x20c, +0x210
    fVar4 = (float)this[0x82];
    fVar4 = SQRT((float)this[0x84] * (float)this[0x84] +
                 (float)this[0x83] * (float)this[0x83] + fVar4 * fVar4);
    
    FUN_00470f80(local_50); // Get some transform/rotation matrix
    FUN_006cb9d0(&local_78, this + 0x82, local_50); // Transform velocity by rotation
    
    local_60 = local_78;
    local_5c = local_74;
    local_58 = local_70;
    local_54 = 0;
    FUN_0056afa0(&local_60, &local_60); // Normalize the transformed velocity
    
    // Scale normalized direction by velocity magnitude
    local_78 = local_60 * fVar4;
    local_74 = local_5c * fVar4;
    local_70 = local_58 * fVar4;
    
    iVar1 = FUN_00471610(); // Get current frame time or some time value
    local_6c = (float)*(undefined8 *)(iVar1 + 0x30);
    fStack_68 = (float)((ulonglong)*(undefined8 *)(iVar1 + 0x30) >> 0x20);
    _local_6c = CONCAT44(fStack_68 + local_74, local_6c + local_78);
    local_64 = *(float *)(iVar1 + 0x38) + local_70;
    
    // Get physics object pointer (offset -0x48 from the physics handle)
    if (this[0x6c] == 0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)(this[0x6c] + -0x48);
    }
    // Call physics object's setPosition (vtable+0x1c)
    (**(code **)(*piVar3 + 0x1c))(&local_6c);
    
    // Get physics object pointer again
    if (this[0x6c] == 0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)(this[0x6c] + -0x48);
    }
    // Call physics object's setRotation (vtable+0x20)
    (**(code **)(*piVar3 + 0x20))(&local_54);
    
    // Get physics object pointer again
    if (this[0x6c] == 0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)(this[0x6c] + -0x48);
    }
    iVar1 = *piVar3;
    uVar2 = (**(code **)(*this + 0x58))(0xffffffff); // Get some ID from entity
    (**(code **)(iVar1 + 0x5c))(uVar2); // Set physics object's ID
  }
  
  // Clean up attached effect/particle if present (+0x19c)
  if (this[0x67] != 0) {
    FUN_005e6660(this[0x67]); // Destroy/remove the effect
    this[0x67] = 0;
  }
  
  return;
}