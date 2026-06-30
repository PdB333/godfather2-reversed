// FUNC_NAME: SimManager::spawnSimEntity
int __thiscall SimManager::spawnSimEntity(void *this, int param2)
{
  int allocResult;
  int *stackStruct;
  int local_c;
  int local_8;
  int local_4;

  // Stack structure passed to allocator: type=2, flags=0x10, unknown=0
  local_c = 2;
  local_8 = 0x10;
  local_4 = 0;

  // Allocate 0xC4 bytes (196 bytes) for a new sim entity
  allocResult = MemoryManager::allocate(0xC4, &stackStruct, param2);
  if (allocResult != 0) {
    // Initialize the newly allocated object (this is the resulting pointer)
    return EntityInitializer::initSimEntity(this, allocResult);
  }
  return 0;
}