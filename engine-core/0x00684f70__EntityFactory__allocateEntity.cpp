// FUNC_NAME: EntityFactory::allocateEntity
undefined4 EntityFactory::allocateEntity(Entity* thisObject, uint allocatorIndex)
{
  uint allocFlags[3];
  int allocationResult;
  undefined4 initializationResult;

  allocFlags[0] = 2;          // size class hint
  allocFlags[1] = 0x10;       // alignment (16 bytes)
  allocFlags[2] = 0;          // flags / padding

  // Allocate memory block of 0x11b0 bytes (4528) – typical size for a game entity
  allocationResult = EA::Allocator::allocate(0x11b0, allocFlags, allocatorIndex);
  if (allocationResult != 0) {
    // Perform class-specific initialization (constructor equivalent)
    initializationResult = thisObject->initialize();
    return initializationResult;
  }
  return 0;
}