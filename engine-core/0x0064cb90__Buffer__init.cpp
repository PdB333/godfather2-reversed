// FUNC_NAME: Buffer::init
int __thiscall Buffer::init(void *this, int param_1)
{
  int uVar1;
  int local_4;
  
  uVar1 = FUN_00658390(param_1, (int)this + 0x138, &local_4);
  if (*(char *)((int)this + 0x14) != '\0') {
    *(undefined1 *)((int)this + 0x14) = 0;
    (*(code *)PTR__free_00f0cd8c)(*(undefined4 *)((int)this + 0xc));
  }
  *(int *)((int)this + 0x10) = local_4;
  *(int *)((int)this + 0xc) = (int)this + 0x138;
  *(int *)((int)this + 0x2c) = local_4 * 8;
  *(undefined4 *)((int)this + 0x30) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined1 *)((int)this + 0x1c) = 0;
  *(undefined1 *)((int)this + 0x1d) = 0;
  *(undefined1 *)((int)this + 0x38) = 0;
  *(undefined4 *)((int)this + 0x34) = 0;
  return uVar1;
}