// FUNC_NAME: Player::setControllerBinding
void __thiscall Player::setControllerBinding(int this, int newBinding)
{
    // this+0x18: pointer to bound controller object
    int controllerObj = *(int *)(this + 0x18);
    // controllerObj+0x2c: binding slot/player index
    *(int *)(controllerObj + 0x2c) = newBinding;
    // Notify the controller subsystem of the change (maybe mark dirty or apply)
    FUN_009e9c50(controllerObj, 1);
}