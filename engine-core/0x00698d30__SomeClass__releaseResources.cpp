// FUNC_NAME: SomeClass::releaseResources
void __fastcall releaseResources(int this)
{
  // +0x20: pointer to first resource (e.g., texture/sound handle)
  if (*(int *)(this + 0x20) != 0) {
    // +0x2c: function pointer to release/destroy the resource (e.g., Release, Delete)
    (**(code **)(this + 0x2c))(*(int *)(this + 0x20));
  }
  // +0x10: pointer to second resource
  if (*(int *)(this + 0x10) != 0) {
    // +0x1c: function pointer to release/destroy the second resource
    (**(code **)(this + 0x1c))(*(int *)(this + 0x10));
  }
  return;
}