// FUNC_NAME: Job::Job
void __thiscall Job::Job(Job *this, JobList *list, const JobKey *key, int param4, int param5, bool critical)
{
  // Initialize vtable
  this->vtable = (void**) &PTR_FUN_00d76628;
  // other fields
  this->field_4 = 0;
  // Adjust list pointer: if non-null, add offset 0x48 (likely to get inner list head)
  JobListNode *listNode = (list != 0) ? (JobListNode *)((uint8_t*)list + 0x48) : 0;
  this->listNode = listNode;
  this->next = 0;
  // Insert into doubly linked list at head
  if (listNode != 0) {
    this->next = (JobListNode*)*(uint32_t*)((uint8_t*)listNode + 4); // +0x04: next pointer
    *(uint32_t*)((uint8_t*)listNode + 4) = (uint32_t)&this->listNode; // store address of listNode field as previous next?
  }
  this->prev = 0; // +0x10
  // Copy 8-byte key data
  *(uint64_t*)&this->key = *key;
  // extra int from key +8
  this->keyExtra = *(uint32_t*)((uint8_t*)key + 8); // +0x1c? actually at this[7] = offset 28
  this->param4 = param4; // +0x2c
  this->param5 = param5; // +0x30
  this->flags = 0; // +0x34 (offset 52)
  this->field_40 = 0; // +0x40 (offset 64)
  this->field_38 = 0; // +0x38 (offset 56)
  this->globalTimestamp = _DAT_00d5780c; // +0x3c (offset 60)
  if (critical) {
    this->flags |= 1; // set bit 0
  }
  this->field_28 = 0; // +0x28 (offset 40)
  this->field_24 = 0; // +0x24 (offset 36)
  this->field_20 = 0; // +0x20 (offset 32)
}