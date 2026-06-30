// FUNC_NAME: Entity::~Entity (destructor)
void __thiscall Entity::~Entity(void)
{
  int iVar1;
  
  if ((*(byte *)(this + 0x3c) & 1) != 0) {
    if (*(code **)(DAT_012234c4 + 0x2c) != (code *)0x0) {
      (**(code **)(DAT_012234c4 + 0x2c))(*(undefined4 *)(this + 0x28),*(undefined1 *)(this + 0x44));
    }
    *(uint *)(this + 0x3c) = *(uint *)(this + 0x3c) & 0xfffffffe;
  }
  iVar1 = *(int *)(this + 0x28);
  if (iVar1 != 0) {
    *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + -1;
    if (*(int *)(iVar1 + 0x14) == 0) {
      FUN_0044f130(DAT_012233a4,0);
    }
    DAT_012054f4 = DAT_012054f4 + -1;
  }
  *(undefined4 *)(this + 0x28) = 0;
  return;
}