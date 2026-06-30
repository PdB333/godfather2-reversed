// FUNC_NAME: GenericGameObject::constructor
undefined4 * __thiscall GenericGameObject::constructor(undefined4 *this, byte allocFlag)
{
  // Initialize vtable pointers at various offsets:
  // this+0x00: primary vtable
  // this+0x3C: secondary vtable (likely interface)
  // this+0x48: tertiary vtable or static data
  *this = &GENERIC_OBJECT_VTABLE;           // +0x00
  this[0xf] = &INTERFACE_VTABLE;            // +0x3C = 15*4
  this[0x12] = &STATIC_DATA_PTR;            // +0x48 = 18*4

  // Call global static initialization and base class init
  EARS_STATIC_INITIALIZER(&g_someGlobal);   // FUN_004086d0
  BASE_CLASS_INIT();                         // FUN_0046c640

  // If allocFlag has bit 0 set, delete the object with size 0xB0
  if ((allocFlag & 1) != 0) {
    OPERATOR_DELETE(this, 0xb0);             // FUN_0043b960 (likely delete)
  }

  return this;
}