// FUNC_NAME: EventManager::dispatchEvent
void __thiscall EventManager::dispatchEvent(void* this, int param2, char param3, int param4)
{
  // Check if param4 is zero and param3 is null character (i.e., empty/clear action)
  if (param4 == 0 && param3 == '\0') {
    // Validate the second parameter using a helper function
    int isValid = FUN_0071ce70(param2);
    if (isValid != 0) {
      // Generate a random value via a virtual function at vtable offset 0x30 (likely returns float)
      // The vtable pointer is stored at offset 0x1bc from 'this'
      float randomVal = (**(code (__thiscall *)(void*))(*((int*)this + 0x6f) + 0x30))(this); // offset 0x1bc/4 = 0x6f
      FUN_0071c320(randomVal); // Apply the random value (e.g., set duration, amplitude, etc.)
      return;
    }
  }
  // Default: call the standard handler at vtable offset 0x10
  // This passes the original parameters through
  (**(code (__thiscall *)(void*, int, char, int))(*((int*)this + 0x6f) + 0x10))(this, param2, param3, param4);
}