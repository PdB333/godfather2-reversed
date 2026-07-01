// FUNC_NAME: Entity::Entity
undefined4 * __thiscall Entity::Entity(Entity *this, undefined4 arg1, undefined4 arg2)
{
  int *globalListHead;
  int listHead;
  Entity *pEntity;

  // Call base class constructor with arguments
  SimObject::SimObject(arg1, arg2);  // FUN_007ab5e0

  // Set vtable pointer
  *this = &g_EntityVTable;  // PTR_LAB_00d6e2b0

  // Initialize flags field at +0x74
  this->flags = 0;  // +0x74

  // Initialize next pointer at +0x78 (linked list node)
  pEntity = this + 0x1e;
  pEntity->next = 0;  // +0x78

  // Initialize previous pointer at +0x7C and some ID at +0x80
  this->prev = 0;      // +0x7C
  this->id = 0xffffffff; // +0x80

  // Get global linked list head
  globalListHead = getGlobalEntityList();  // FUN_007ab390

  // Determine list head pointer (possibly offset 0x48 from the returned object)
  if (globalListHead == 0) {
    listHead = 0;
  }
  else {
    listHead = globalListHead + 0x48;
  }

  // Insert this entity into the doubly linked list if different from current next
  if (pEntity->next != listHead) {
    if (pEntity->next != 0) {
      removeFromList(pEntity);  // FUN_004daf90
    }
    pEntity->next = listHead;  // +0x78
    if (listHead != 0) {
      this->prev = *(undefined4 *)(listHead + 4);  // +0x7C = listHead->prev
      *(int **)(listHead + 4) = pEntity;            // listHead->prev = pEntity
    }
  }

  // Handle component at +0x48 (param_1[0x12])
  if ((this->component1 != 0) && (this->component1 != 0x48)) {
    unknownComponentHandler();  // FUN_00461290
  }

  // Check component at +0x58 (param_1[0x16]) for a flag at offset 0x8e0
  if ((this->component2 != 0) && ((*(uint *)(this->component2 + 0x8e0) >> 10 & 1) != 0)) {
    // Set bit 1 in flags (+0x74)
    this->flags = this->flags | 2;
    // Call virtual function at index 0x98 (vtable+0x260) on component2
    (*(void (__thiscall **)(void))(*(int *)this->component2 + 0x260))();
  }

  return this;
}