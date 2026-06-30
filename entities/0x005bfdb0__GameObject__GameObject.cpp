// FUNC_NAME: GameObject::GameObject
// Address: 0x005bfdb0
// Role: Constructor/initializer for GameObject, called with an initialization flag.
// The flag (param_2) bit 0 controls whether additional initialization is performed.

undefined4 __thiscall GameObject::GameObject(GameObject* this, byte initFlags)
{
  // Call base class or common initialization routine (0x005c16e0)
  FUN_005c16e0();

  // If bit 0 of initFlags is set, perform additional initialization
  if ((initFlags & 1) != 0) {
    char result = FUN_005c43d0(this);
    if (result == '\0') {
      // Call virtual function at vtable offset 4 (likely a reset or clear function)
      // DAT_012234ec appears to be a global pointer to a vtable or manager structure
      // *(int *)DAT_012234ec + 4 -> gets base vtable pointer, then +4 gives index 1 (offset 4 bytes)
      (**(code **)(**(int **)(DAT_012234ec + 4) + 4))(this, 0);
    }
  }
  return this;
}