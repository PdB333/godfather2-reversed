// FUNC_NAME: ExampleClass::ConstructorWithFlag
// Function address: 0x004fe890
// Role: Class constructor or initializer with optional cleanup/initialization based on a flag.
// Calls baseInit (0x004fe1f0) and conditionally calls conditionalFunc (0x009c8eb0) if flag bit 0 is set.

// Note: This is a __thiscall member function. The decompiled signature shows param_1 (this) and param_2 (flag).
// The function returns the this pointer.

void __thiscall ExampleClass::ConstructorWithFlag(ExampleClass *this, byte flag)
{
  // Call base class initialization or another member function (likely a constructor).
  baseInit(this);  // 0x004fe1f0

  // If the lowest bit of flag is set, perform additional setup/cleanup.
  if ((flag & 1) != 0) {
    conditionalFunc(this);  // 0x009c8eb0
  }

  return; // Return type is undefined4, but __thiscall constructors often return this implicitly. The decompiler shows return param_1.
}