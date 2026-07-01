// FUNC_NAME: BaseVehicle::destructor
int __thiscall BaseVehicle::destructor(int this, byte flags)
{
  // Call sub-function on some member at offset +0x8
  FUN_009c8f10(*(undefined4 *)(this + 8));
  // If flags has bit 0 set, call operator delete on this
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}