// FUNC_NAME: IsControllerActive
bool __cdecl IsControllerActive(int controllerIndex) {
    char result = (**(char (__thiscall**)(int))(*DAT_01223510 + 0x38))(controllerIndex);
    return result != 0;
}