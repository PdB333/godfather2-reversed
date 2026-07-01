// FUNC_NAME: ActionStateController::updateState
void __fastcall ActionStateController::updateState(uint32_t *this) {
    // this is a pointer to a struct with fields:
    // +0x00: flags (uint32, bit3 = some toggle)
    // +0x08: state (uint32, 0 = uninitialized, 0x48 = idle)
    // +0x10: entityId (uint32)
    // +0x14: subData (start of a substructure, accessed via FUN_0090a7e0)

    if (this[2] != 0 && this[2] != 0x48) {
        int32_t entityIndex = FUN_00791300(); // possibly global index or handle
        if (entityIndex != 0) {
            FUN_0090a500(entityIndex); // pre-action setup

            void *manager = FUN_0043b870(DAT_01131040); // likely singleton manager
            if (manager != nullptr) {
                FUN_009b1b80(this[4]); // initialize something using entityId

                int32_t dataOffset = (this[2] == 0) ? 0 : (this[2] - 0x48);
                // check a flag byte in a data table at offset 0x5f from dataOffset
                if ((*(uint8_t *)(dataOffset + 0x5f) & 1) == 0) {
                    FUN_00737940(3, 0); // debug/log routine
                } else {
                    FUN_0090a660(); // alternate path handler

                    if ((this[0] & 8) != 0) { // bit3 of flags
                        // call virtual function at vtable offset 0x1c (index 7)
                        typedef bool (*VirtualFunc)(void *self, uint32_t param);
                        VirtualFunc vfunc = *(VirtualFunc *)(*(uint32_t *)manager + 0x1c);
                        if (vfunc(manager, 0x100)) {
                            thunk_FUN_009b1d10(); // likely sound or animation
                            FUN_0090a7e0(this + 5); // process substructure
                            this[0] &= ~8; // clear bit3
                            return;
                        }
                    }
                }
            }
            FUN_0090a7e0(this + 5); // always called (via fallthrough)
        }
        this[0] &= ~8; // clear bit3 in any case
    }
}