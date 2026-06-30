// FUNC_NAME: SlotManager::addSlot
void __thiscall SlotManager::addSlot(uint32 slotValue, Node* node)
{
  int newIndex = this->slotCount + 1;
  if (newIndex < 8) {
    this->slotCount = newIndex;
    Slot* slot = &this->slots[newIndex]; // +0x538 offset in this
    slot->value = slotValue; // +0x00
    Node** slotNodePtr = &slot->node; // +0x04 (pointer to node)
    if (slotNodePtr != node) {
      int nodeValue = node->value; // first field of node (+0x00)
      if (*slotNodePtr != nodeValue) {
        if (*slotNodePtr != 0) {
          FUN_004daf90(slotNodePtr); // likely remove old node from list
        }
        *slotNodePtr = nodeValue;
        if (nodeValue != 0) {
          // Insert slot as node in list after the node pointed to by nodeValue
          slot->next = node->next; // +0x08
          node->next = slotNodePtr; // node is actually nodeValue? The decompiled uses iVar2+4
        }
      }
    }
    slot->field_0x20 = 0; // +0x20
    slot->field_0x24 = 0; // +0x24
    FUN_006a6980(); // post-add callback
  }
}