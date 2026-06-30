// FUNC_NAME: EntityManager::findEntityByTypeId
int EntityManager::findEntityByTypeId(int typeId)
{
  // this pointer is in EAX, stored in in_EAX
  // +0x28: pointer to linked list head (iterator start)
  // The linked list is a standard intrusive doubly-linked list
  // Each node has: [prev, next, data] at offsets 0, 4, 8
  // data is a pointer to an Entity object
  
  undefined4 *currentNode = *(undefined4 **)(*(int *)(this + 0x28)); // dereference head pointer to get first node
  
  while (true) {
    // Check if we've reached the end of the list (back to head)
    if (currentNode == *(undefined4 **)(this + 0x28)) {
      return 0; // not found
    }
    
    // Safety check (redundant in release, but present in debug)
    if (currentNode == *(undefined4 **)(this + 0x28)) {
      FUN_00b97aea(); // likely an assertion failure handler
    }
    
    // Check if the entity's type ID matches
    // +0x88 is the typeId field in the Entity class
    if (*(int *)(currentNode[2] + 0x88) == typeId) break;
    
    // Safety check again
    if (currentNode == *(undefined4 **)(this + 0x28)) {
      FUN_00b97aea();
    }
    
    // Move to next node in the linked list
    currentNode = (undefined4 *)*currentNode;
  }
  
  // Return the entity pointer (stored at offset +8 in the node)
  return currentNode[2];
}