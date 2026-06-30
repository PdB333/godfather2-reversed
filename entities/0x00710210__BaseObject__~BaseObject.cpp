// FUNC_NAME: BaseObject::~BaseObject

int __thiscall BaseObject::~BaseObject(int this, byte deletingFlag)

{
  if (*(int *)(this + 0xb0) != 0) {
    destructorAt0B0(this + 0xb0);
  }
  if (*(int *)(this + 0x9c) != 0) {
    (**(code **)(this + 0xa8))(*(int *)(this + 0x9c)); // virtual destructor via vtable pointer at +0xA8
  }
  if ((deletingFlag & 1) != 0) {
    operatorDelete(this);
  }
  return this;
}