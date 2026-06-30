// FUN_004934f0: GameObject::update
// This function likely performs per-frame update logic for a game object.
// Offsets:
//   +0x14: pointer to some component (e.g., transform or animation state)
//   +0x1f0: pointer or flag for conditional processing (maybe network or input)
//   +0x1f8: integer parameter (e.g., slot index or type)
//   +0x200: buffer for data (e.g., animation keyframes)
void __thiscall GameObject::update(GameObject *thisPtr)
{
  // Call base engine update (likely parent class or global system tick)
  FUN_00492b70();
  
  // If a non-null pointer exists at offset +0x1f0, perform additional processing
  if (*(int *)((char *)thisPtr + 0x1f0) != 0) {
    FUN_006063b0();
  }
  
  // Dispatch a three-argument operation: pointer from +0x14, integer from +0x1f8, buffer at +0x200
  FUN_0060b020(
    *(void **)((char *)thisPtr + 0x14),
    *(int *)((char *)thisPtr + 0x1f8),
    (char *)thisPtr + 0x200
  );
}