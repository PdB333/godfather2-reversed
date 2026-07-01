// FUNC_NAME: Entity::getTransform
void __thiscall Entity::getTransform(int *this, undefined8 *outTransform)
{
  undefined4 vftableResult;
  int entityData;
  
  vftableResult = (**(code **)(*this + 0x1c))(outTransform);
  entityData = FUN_006b0ee0(vftableResult);
  if (entityData != 0) {
    *outTransform = *(undefined8 *)(entityData + 0x1c);
    *(undefined4 *)(outTransform + 1) = *(undefined4 *)(entityData + 0x24);
    return;
  }
  *(undefined4 *)(outTransform + 1) = 0;
  *(undefined4 *)((int)outTransform + 4) = 0;
  *(undefined4 *)outTransform = 0;
  return;
}