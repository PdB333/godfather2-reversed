// FUNC_NAME: HandleWrapper::dispatch
void __thiscall HandleWrapper::dispatch(int param_2, int param_3)
{
    // +0x00: handle (or pointer to inner object)
    if (this->handle != 0) {
        FUN_0051cbc0(this->handle, param_2, param_3);
    }
}