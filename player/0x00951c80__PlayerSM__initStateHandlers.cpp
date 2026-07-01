// FUNC_NAME: PlayerSM::initStateHandlers
void __thiscall PlayerSM::initStateHandlers(int this) {
    // Call base class constructor (thunk)
    thunk_FUN_005c1740();

    // Set state handler at offsets from this:
    // +0x70, +0x74, +0x84, +0x88, +0x8c, +0x90, +0x94: setCallbackWithFlags(global, fieldPtr, 0, 0, 1, 1)
    setCallbackWithFlags(&DAT_00d8be5c, this + 0x70, 0, 0, 1, 1);
    setCallbackWithFlags(&DAT_00d8be54, this + 0x74, 0, 0, 1, 1);
    setCallbackWithFlags(&DAT_00d8be3c, this + 0x84, 0, 0, 1, 1);
    setCallbackWithFlags(&DAT_00d8be34, this + 0x88, 0, 0, 1, 1);
    setCallbackWithFlags(&DAT_00d8be2c, this + 0x8c, 0, 0, 1, 1);
    setCallbackWithFlags(&DAT_00d8be24, this + 0x90, 0, 0, 1, 1);
    setCallbackWithFlags(&DAT_00d8be04, this + 0x94, 0, 0, 1, 1);

    // Set state action at offsets +0x7c, +0x80, +0x98, +0x9c, +0xa0:
    // setActionWithTarget(global, fieldPtr, 0, functionPtr, 0) or (global, fieldPtr, functionPtr, 0, 0)
    setActionWithTarget(&DAT_00d8be4c, this + 0x7c, 0, &functionHandler0, 0);
    setActionWithTarget(&DAT_00d8be44, this + 0x80, &functionHandler1, 0, 0);
    setActionWithTarget(&DAT_00d8be1c, this + 0x98, 0, 0, 1);
    setActionWithTarget(&DAT_00d8be14, this + 0x9c, 0, 0, 1);
    setActionWithTarget(&DAT_00d8be0c, this + 0xa0, 0, 0, 1);
}