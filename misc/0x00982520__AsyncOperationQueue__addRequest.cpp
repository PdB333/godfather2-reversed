// FUNC_NAME: AsyncOperationQueue::addRequest
void __thiscall AsyncOperationQueue::addRequest(int *this, int requestObject) {
    // this[0x1b] = queued count (max 6)
    // this[0x24] = enabled flag (char)
    // this[0x12] = flushImmediately flag (char)
    // this[0x49] = flags (byte, bit 1 and 3 control behavior)
    // this+0x14 = array of request pointers (size 6)

    if ((uint)this[0x1b] < 6 && (char)this[0x24] != '\0') {
        // Add request to slot
        this[this[0x1b] + 0x14] = requestObject;
        this[0x1b] = (int)((char *)this + 0x1b) + 1; // increment count
        if (this[0x1b] == 1) {
            // First request: start processing timer/callback? LAB_00982270 is likely a callback address
            FUN_005c0260(this + 4, &LAB_00982270, 1);
        }
        if ((char)this[0x12] == '\0') {
            // Flush immediately: call virtual function at vtable+0x28 (likely processPending)
            (**(code **)(*this + 0x28))();
            return;
        }
        if ((*(byte *)((int)this + 0x49) & 10) == 0) {
            // No flags preventing direct processing: call the request handler
            FUN_00981f50(requestObject);
        }
    } else {
        // Cannot queue: if request has a failure callback, call it immediately
        if (*(code **)(requestObject + 0x14) != (code *)0x0) {
            (**(code **)(requestObject + 0x14))(0xffffffff, requestObject, 1);
            return;
        }
    }
    return;
}