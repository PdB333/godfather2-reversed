// FUNC_NAME: SomethingHandler::init
void __thiscall SomethingHandler::init(void *this, void *parentObj)
{
  // Initialize vtable
  *(void ***)this = (void **)&PTR_LAB_00e39c3c; // +0x00: vtable pointer

  // Store parent object reference
  *(void **)((int)this + 4) = 0;                 // +0x04: unknown field
  *(void **)((int)this + 8) = parentObj;         // +0x08: parent object pointer
  *(int *)((int)this + 12) = 0;                  // +0x0C: field3
  *(int *)((int)this + 16) = 0;                  // +0x10: field4
  *(int *)((int)this + 20) = 0;                  // +0x14: field5

  // Call virtual function at offset 8 on parent object (likely addRef or registerChild)
  (**(void (__thiscall **)(void *))(*(int *)parentObj + 8))(parentObj);

  // Initialize static data handlers (likely registering with subsystems)
  FUN_0049c6e0(&PTR_LAB_00e39bd8, 1); // PTR_LAB_00e39bd8 - some static table/function
  FUN_0049c6e0(&DAT_00e39bdc, 1);    // DAT_00e39bdc - some global data
  FUN_0049c6e0(&DAT_00e39be0, 1);    // DAT_00e39be0 - another global
  FUN_0049c6e0(&DAT_00e39be4, 1);    // DAT_00e39be4 - another global
}