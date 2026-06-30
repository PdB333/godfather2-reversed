// FUNC_NAME: BaseVehicle::constructor
undefined4 __thiscall BaseVehicle::constructor(undefined4 this, byte flags)
{
  FUN_00503af0(); // Call parent class constructor (likely Vehicle::constructor or similar)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // EARS object allocation/initialization
  }
  return this;
}