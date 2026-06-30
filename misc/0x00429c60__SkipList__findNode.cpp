// FUNC_NAME: SkipList::findNode
uint * __thiscall SkipList::findNode(uint *key)
{
  // this->header: pointer to header node (first uint* in struct)
  // this->maxLevel: current maximum level (signed int, second field)
  uint *current;         // puVar4, initially *this
  uint *next;            // puVar1
  uint *prev;            // puVar2
  int level;             // iVar3, loop counter

  current = (uint *)*this;
  for (level = this->maxLevel; level >= 0; level--) {
    next = *(uint **)(current[2] + level * 4); // current->next[level]
    while (next != nullptr) {
      if (*key <= *next) break;
      prev = next;
      next = *(uint **)(prev[2] + level * 4); // prev->next[level]
      current = prev;
    }
    // At end of level, move to next node at level 0
    next = *(uint **)current[2]; // current->next[0]
    if (next == nullptr) break;
    if (*next == *key) {
      return next;
    }
  }
  return nullptr;
}