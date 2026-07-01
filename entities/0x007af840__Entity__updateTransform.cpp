// FUNC_NAME: Entity::updateTransform
void __fastcall Entity::updateTransform(int this)
{
  undefined4 transformData;
  undefined4 newTransform;
  
  transformData = *(undefined4 *)(this + 0x58); // +0x58: transform data pointer
  newTransform = FUN_007ab170(); // Get current world transform
  FUN_007c09a0(transformData, newTransform); // Apply transform to entity
  return;
}