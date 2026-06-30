// FUNC_NAME: NetState::selectState
// Function at 0x00583aa0
// Merges two state buffers (internal and external) into output buffer.
// Internal buffer (this) is used when external has flag=0x02, else external is used.
// When both have flag=0x02, calls combine function (FUN_00582ea0) on output.

struct NetStateData {
    char flag;              // +0x00: state flag (0 or 2)
    char __pad[3];          // +0x01: alignment padding
    uint32_t data[8];       // +0x04: 32 bytes of state data
};

void __thiscall NetState::selectState(NetStateData* this, NetStateData* param_1, NetStateData* param_2)
{
    char internalFlag = this->flag;   // Internal state flag
    char externalFlag = param_1->flag; // External state flag

    if (externalFlag == 0x02) {
        param_2->flag = 2;
        if (internalFlag == 0x02) {
            // Both have flag set: combine via special routine
            FUN_00582ea0(param_2); // Combine function
            return;
        }
        // Only external has flag: copy external data to output
        NetStateData* src = param_1;
        // Fall through to copy
    }
    else {
        if (internalFlag != 0x02) {
            // Neither has flag: clear output and return
            param_2->flag = 0;
            return;
        }
        // Only internal has flag: copy internal data to output
        NetStateData* src = this;
        param_2->flag = 2;
        // Fall through to copy
    }

    // Copy 32 bytes (8 dwords) from source's data to output
    param_2->data[0] = src->data[0];
    param_2->data[1] = src->data[1];
    param_2->data[2] = src->data[2];
    param_2->data[3] = src->data[3];
    param_2->data[4] = src->data[4];
    param_2->data[5] = src->data[5];
    param_2->data[6] = src->data[6];
    param_2->data[7] = src->data[7];
}