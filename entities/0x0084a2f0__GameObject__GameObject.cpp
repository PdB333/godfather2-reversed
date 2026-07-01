// FUNC_NAME: GameObject::GameObject
undefined4 * __thiscall GameObject::GameObject(undefined4 *this, undefined4 initialValue)
{
  // +0x00: first member, set to the provided value (e.g., an ID or pointer)
  *this = initialValue;
  
  // +0x04 through +0x38: next 14 members zeroed (total 60 bytes)
  this[1] = 0;
  this[2] = 0;
  this[3] = 0;
  this[4] = 0;
  this[5] = 0;
  this[6] = 0;
  this[7] = 0;
  this[8] = 0;
  this[9] = 0;
  this[10] = 0;
  this[11] = 0;
  this[12] = 0;
  this[13] = 0;
  this[14] = 0;
  
  // Call secondary initialization function (likely sets up additional state)
  FUN_0084af30(this);
  
  return this;
}