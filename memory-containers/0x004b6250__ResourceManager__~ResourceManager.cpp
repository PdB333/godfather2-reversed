// FUNC_NAME: ResourceManager::~ResourceManager
void __thiscall ResourceManager::~ResourceManager()
{
  uint i;
  RefCountedObject **slotPtr;
  int slotIndex;
  int capacity;
  char *slotBase;
  RefCountedObject *obj;

  // Set vtable for this class
  this->vtable = &PTR_FUN_00e358b8;
  this->field_0C = &PTR_LAB_00e35940;

  // Release all objects referenced by the active slots (m_activeCount)
  if (this->m_activeCount != 0) {
    i = 0;
    do {
      slotPtr = (RefCountedObject **)(this->m_poolBuffer + 0x40 + i * 0x70);
      obj = *slotPtr;
      if (obj != nullptr) {
        if (*(short *)(&obj->field4) != 0) {
          obj->field6_short = obj->field6_short - 1;
          if (obj->field6_short == 0) {
            obj->vtable->Destroy(1);
          }
        }
        *slotPtr = nullptr;
      }
      i = i + 1;
    } while (i < (uint)this->m_activeCount);
  }

  // Release all remaining objects in the pool buffer (capacity from header)
  capacity = *(int *)(this->m_poolBuffer - 0x10);
  slotBase = this->m_poolBuffer + capacity * 0x70;
  while (slotIndex = capacity, capacity = capacity - 1, slotIndex > 0) {
    slotBase = slotBase - 0x70;
    if (*(int *)(slotBase + 0x40) != 0) {
      FUN_00557020();   // some additional cleanup before releasing the object
      obj = *(RefCountedObject **)(slotBase + 0x40);
      if (*(short *)(&obj->field4) != 0) {
        obj->field6_short = obj->field6_short - 1;
        if (obj->field6_short == 0) {
          obj->vtable->Destroy(1);
        }
      }
      *(RefCountedObject **)(slotBase + 0x40) = nullptr;
    }
  }

  // Free the pool buffer (including header)
  FUN_009c8f10(this->m_poolBuffer - 0x10);

  // Global cleanup if flag is set
  if ((*(byte *)(this + 0x28) & 8) != 0) {
    FUN_004086d0(&DAT_012069c4);
  }
  FUN_004083d0();

  // Set vtable to base class
  this->vtable = &PTR_LAB_00e2f638;
  return;
}