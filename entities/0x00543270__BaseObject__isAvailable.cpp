// FUNC_NAME: BaseObject::isAvailable
// Address: 0x00543270 - Wrapper that calls a virtual function (vtable+500) to check a condition and returns true if result is zero.
bool __thiscall BaseObject::isAvailable(int *this, uint param_2)
{
    // Call virtual function at vtable offset 500 (index 125).
    // Returns true if the virtual function returns 0, indicating availability.
    int result = (*(code (__thiscall**) (int *))(*(int *)this + 500))(this, param_2);
    return result == 0;
}