// FUNC_NAME: Entity::destroyAllChildren
void __fastcall Entity::destroyAllChildren(int this)
{
  int childNode;
  
  childNode = *(int *)(this + 0x98); // +0x98: firstChild pointer
  while (childNode != 0) {
    childNode = *(int *)(*(int *)(this + 0x94)); // +0x94: childList head pointer
    if ((childNode != 0) && (childNode != 0x48)) { // 0x48 = sizeof(Entity) or child node offset
      childNode = *(int *)(*(int *)(this + 0x94));
      if (childNode == 0) {
        childNode = 0;
      }
      else {
        childNode = childNode + -0x48; // Adjust pointer to get Entity base
      }
      Entity::destroy(childNode,0); // FUN_0083c260 - destroy entity with flag=0
      *(undefined4 *)(childNode + 0x158) = 0; // +0x158: some ref count or state
      Entity::onDestroy(childNode); // FUN_0083f190
    }
    if (*(int *)(*(int *)(this + 0x94)) == 0) {
      childNode = 0;
    }
    else {
      childNode = *(int *)(*(int *)(this + 0x94)) + -0x48;
    }
    Entity::removeFromParent(childNode); // FUN_0083de30
    childNode = *(int *)(this + 0x98);
  }
  return;
}