// FUNC_NAME: shutdownEngineSystems
void shutdownEngineSystems(void)
{
  // Call the shutdown function at vtable offset 0x8 on the engine manager object
  (**(code **)(*DAT_012234e0 + 8))();

  // If the audio manager exists, call its shutdown (vtable[0]) with arg 1
  if (DAT_0112ff6c != (undefined4 *)0x0) {
    (**(code **)*DAT_0112ff6c)(1);
  }

  // If the engine manager exists, call its shutdown (vtable[0]) with arg 1
  if (DAT_012234e0 != (int *)0x0) {
    (**(code **)*DAT_012234e0)(1);
  }

  return;
}