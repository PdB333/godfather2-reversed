// FUNC_NAME: UnknownClass::Constructor

void __thiscall UnknownClass::Constructor(UnknownClass *this)
{
  // Set primary virtual table pointer (offset +0x00)
  *(int **)this = (int *)&PTR_FUN_00d5eb60;

  // Set secondary vtable pointer at offset +0x3C (0xF * 4)
  *(int **)((char *)this + 0x3C) = (int *)&PTR_LAB_00d5eb50;

  // Set another vtable/interface pointer at offset +0x48 (0x12 * 4)
  *(int **)((char *)this + 0x48) = (int *)&PTR_LAB_00d5eb4c;

  // Initialize sub-object at offset +0x58 (0x16 * 4)
  FUN_004086d0((UnknownClass *)((char *)this + 0x58));

  // Initialize three sub-structures (likely arrays or iterators) at offsets +0x58, +0x60, +0x68
  FUN_00408310((UnknownClass *)((char *)this + 0x58));
  FUN_00408310((UnknownClass *)((char *)this + 0x60));
  FUN_00408310((UnknownClass *)((char *)this + 0x68));

  // Global game manager initialization
  FUN_0046c640();
}