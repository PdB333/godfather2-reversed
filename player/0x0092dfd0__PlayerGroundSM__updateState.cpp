// FUNC_NAME: PlayerGroundSM::updateState
void __thiscall PlayerGroundSM::updateState(int this) {
    // +0xe8: current state enum (2 = MoveDown, 3 = some other state)
    if (*(int *)(this + 0xe8) == 2) {
        // Debug/log call: "MoveDown" string, 0, some global, 0
        debugPrint("MoveDown", 0, &DAT_00d88e88, 0);
    } else if (*(int *)(this + 0xe8) == 3) {
        // +0x84: pointer to vtable (base class or interface)
        // vtable+0x68: virtual function (likely a movement/action method)
        // Arguments:
        //   this+0x128: some object (e.g., position or target)
        //   this+0x154: some value (e.g., speed or duration)
        //   this+0xe0 + this+0xd4: sum of two fields (e.g., velocity components)
        //   last arg: computed flag (7 if byte at +0x124 is non-zero, else 10)
        int flag = (-(uint)(*(char *)(this + 0x124) != '\0') & 0xfffffffd) + 10;
        (*(void (__thiscall **)(int, int, int, int))(*(int *)(this + 0x84) + 0x68))
            (this + 0x128, *(int *)(this + 0x154), *(int *)(this + 0xe0) + *(int *)(this + 0xd4), flag);
    }
}