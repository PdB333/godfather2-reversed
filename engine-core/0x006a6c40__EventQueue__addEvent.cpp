// FUNC_NAME: EventQueue::addEvent
void __thiscall EventQueue::addEvent(int eventType, int* eventNode)
{
  int slotIndex = *(int *)(this + 0x678) + 1; // +0x678: slot count/next free index
  if (slotIndex < 8) {
    *(int *)(this + 0x678) = slotIndex; // update count
    *(int *)(this + 0x538 + slotIndex * 0x28) = eventType; // +0x538: slot array base, store event type (0x0 in slot)
    // +0x53c: pointer field at offset 0x4 in slot (linked list node)
    int **slotPtrPtr = (int **)(this + 0x53c + slotIndex * 0x28);
    if (*slotPtrPtr != eventNode) {
      int oldNode = *eventNode; // *eventNode is the value (data) of the node pointed to by eventNode
      if (**slotPtrPtr != oldNode) { // if the stored node's data differs
        if (**slotPtrPtr != 0) {
          removeLinkedListNode(*slotPtrPtr); // FUN_004daf90 - free/remove old node
        }
        **slotPtrPtr = oldNode; // copy node data to slot
        if (oldNode != 0) {
          // adjust next pointer of the new node (node[1]) to point to slot
          (*slotPtrPtr)[1] = *(int *)(oldNode + 4);
          // adjust previous pointer of the next node to point to slot
          *(int **)(oldNode + 4) = *slotPtrPtr;
        }
      }
    }
    // Zero out two fields at offsets 0x20 and 0x24 in the slot
    *(int *)(this + 0x558 + slotIndex * 0x28) = 0;
    *(int *)(this + 0x55c + slotIndex * 0x28) = 0;
    notifyEventAdded(); // FUN_006a6980 - post-event processing
  }
  return;
}