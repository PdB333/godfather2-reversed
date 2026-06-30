// FUNC_NAME: ObjectReferenceManager::removeAllReferencesTo

void __thiscall ObjectReferenceManager::removeAllReferencesTo(void* this, void* removalInfo)
{
  // removalInfo + 0x8 holds the target object pointer
  Object* pTarget = *(Object**)((char*)removalInfo + 8);
  
  // Debug string init (likely unused in release)
  char debugString[20] = "01222220"; // placeholder for DAT_01222220
  debugString[0] = 0; // local_c = 0, not sure if actually used
  
  // Possibly a string conversion/initialization call
  FUN_00408a00(debugString, 0);
  
  // First pass: remove from linked list at this+0x28 (main object list)
  // List node structure: [next(4), prev(4), data(4)] = 12 bytes
  ListNode* pNode = *(ListNode**)(*(int**)this[0x28]);
  ListNode* head = *(ListNode**)((char*)this + 0x28);
  
  while (true) {
    if (pNode == head) {
      break; // Reached end of list
    }
    // Check if node's data field matches target
    if ((void*)pNode->data == pTarget) {
      // Remove node from list
      pNode->prev->next = pNode->next;
      pNode->next->prev = pNode->prev;
      
      // Free node memory via virtual function
      (**(void(__thiscall**)(void*, int))**(int**)((char*)this + 0x10))(pNode, 12);
      
      // Decrement count
      *(int*)((char*)this + 0x2c) -= 1;
      
      break; // Found and removed, move to second pass
    }
    pNode = pNode->next;
  }
  
  // Second pass: iterate over second list at this+0x48
  // This list contains nodes that each have a data pointer to an array of reference entries
  ListNode* pListNode = *(ListNode**)((char*)this + 0x48);
  ListNode* listHead = pListNode;
  
  while (true) {
    // Access the node's data (offset 8), which is a pointer to a structure with a vtable
    void* pArrayHolder = *(void**)((char*)pListNode + 8);
    // Call virtual function at vtable+8 to get a pointer to an array of 16-byte entries
    int* pArray = (*(int*(__thiscall**)(void*))(*(int*)pArrayHolder + 8))(pArrayHolder);
    
    if (pArray[1] != 0) {
      int arrayStart = pArray[0];
      int arrayEnd = arrayStart + pArray[1] * 16;
      
      for (int i = arrayStart; i < arrayEnd; i += 16) {
        // Check if entry's second field (offset 4) equals target
        if (*(void**)(i + 4) == pTarget) {
          FUN_005fc5f0(0); // Likely removes this reference entry
          break;
        }
      }
    }
    
    pListNode = pListNode->next;
    if (pListNode == listHead) {
      break;
    }
  }
  
  // Finally, call destroy on the target object itself (virtual function on vtable[0])
  (**(void(__thiscall**)(void*, int))(*(int*)pTarget))(pTarget, 0);
}