// FUN_NAME: GameSystem::GameSystem
void * GameSystem::GameSystem(GameSystem *this, unsigned char deleteFlag)
{
  // Set vtable pointer
  *this = &GAMEsYSTEM_VTABLE; // +0x00 vtable

  // Initialize global mutexes or critical sections
  local_initializeMutex(&DAT_01218040);
  local_initializeMutex(&DAT_01218048);

  // Base class or common initialization
  baseClassInitialize();

  // Class-specific initializers
  initializePart1();
  initializePart2();

  // If deleteFlag is set, call operator delete (likely for placement new / return)
  if ((deleteFlag & 1) != 0) {
    operatorDelete(this);
  }

  return this;
}