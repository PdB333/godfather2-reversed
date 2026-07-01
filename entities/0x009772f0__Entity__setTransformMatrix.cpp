// FUNC_NAME: Entity::setTransformMatrix
void __thiscall Entity::setTransformMatrix(int this, undefined4 *matrix)
{
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  
  // Validate matrix pointer
  FUN_00990a80(matrix);
  
  // Check if entity has a physics body (likely a Havok hkpRigidBody pointer at +0x108)
  if (*(int *)(this + 0x108) != 0) {
    // Copy matrix to local stack for physics update
    FUN_004df780(&local_50);
    local_50 = *matrix;
    uStack_4c = matrix[1];
    uStack_48 = matrix[2];
    uStack_44 = matrix[3];
    local_40 = matrix[4];
    uStack_3c = matrix[5];
    uStack_38 = matrix[6];
    uStack_34 = matrix[7];
    local_30 = matrix[8];
    uStack_2c = matrix[9];
    uStack_28 = matrix[10];
    uStack_24 = matrix[0xb];
    
    // Apply transform to physics body (likely hkpRigidBody::setTransform)
    FUN_004df720(&local_50);
  }
  return;
}