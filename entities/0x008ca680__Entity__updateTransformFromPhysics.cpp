// FUNC_NAME: Entity::updateTransformFromPhysics
void __fastcall Entity::updateTransformFromPhysics(int this)
{
  int physicsBody;
  int transform;
  undefined4 rotationStack[4]; // 16 bytes for quaternion
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;

  // Check if physics body exists (offset +0x0C)
  physicsBody = *(int *)(this + 0xc);
  if (physicsBody != 0) {
    // Get the physics body's transform
    FUN_009e7450(physicsBody);
    
    // Get the entity's transform component (offset +0x08)
    transform = (**(code **)(**(int **)(*(int *)(this + 8) + 8) + 4))();
    
    // Copy rotation quaternion from transform (offset +0x30 to +0x3C)
    rotationStack[0] = *(undefined4 *)(transform + 0x30);
    rotationStack[1] = *(undefined4 *)(transform + 0x34);
    rotationStack[2] = *(undefined4 *)(transform + 0x38);
    rotationStack[3] = *(undefined4 *)(transform + 0x3c);
    
    // Convert transform to matrix and apply
    FUN_004b59d0(transform, rotationStack);
    FUN_009f17c0(rotationStack);
  }
}