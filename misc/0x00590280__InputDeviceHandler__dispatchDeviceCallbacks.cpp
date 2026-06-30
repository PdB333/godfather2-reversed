// FUNC_NAME: InputDeviceHandler::dispatchDeviceCallbacks

void InputDeviceHandler::dispatchDeviceCallbacks(InputDevice* device, int arg3, int arg4, int arg5, uint flags, int arg7)
{
    // Check if flags have bits 0x14 set (bits 2 and 4): if so, skip direct dispatch
    if ((flags & 0x14) == 0) {
        // At device+0x4, there is a pointer to two input indices
        int* indices = *(int**)((char*)device + 4);
        int index0 = indices[0];
        int index1 = indices[1];

        // Global callback table: array of 0xC-byte slots, number of slots at DAT_01205574
        // Each slot: [4 bytes unused?, callback1 at +4, callback2 at +8]
        int slotCount = DAT_01205574;

        // Dispatch first callback if index is valid
        if (index0 >= 0 && index0 < slotCount) {
            void (*callback)(void*, int, uint*) = *(void(***)(void*, int, uint*))(DAT_01205570 + 4 + index0 * 0xC);
            if (callback != nullptr) {
                callback(this, index0, &flags);
            }
        }

        // Dispatch second callback if index is valid
        if (index1 >= 0 && index1 < slotCount) {
            void (*callback)(void*, int, uint*) = *(void(***)(void*, int, uint*))(DAT_01205570 + 8 + index1 * 0xC);
            if (callback != nullptr) {
                callback(this, index1, &flags);
            }
        }
    }

    // Call base class processing (FUN_0058afb0) with all original parameters
    FUN_0058afb0(this, device, arg3, arg4, arg5, flags, arg7);
}