// FUNC_NAME: GameObject::getActiveValue
undefined4 __thiscall GameObject::getActiveValue(GameObject *this, int flag)
{
  if (flag != 0) {
    return getInternalValue(this);  // calls FUN_004ffbf0 with this
  }
  return 0;
}