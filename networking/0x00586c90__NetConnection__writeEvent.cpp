// FUNC_NAME: NetConnection::writeEvent
uint __thiscall NetConnection::writeEvent(int this, int event, int extraData)
{
    uint retVal;
    int local_74;
    uint* local_70;
    uint local_6c;
    uint local_68;
    uint local_64;
    byte local_60;
    uint local_5c;
    uint local_58;
    int local_54;
    uint local_50;
    uint local_4c;
    uint local_48;
    uint local_44;
    uint local_40;
    uint local_3c;
    uint local_38;
    uint local_34;
    uint local_30;
    uint local_2c;
    uint local_28;
    uint local_24;
    uint local_20;
    uint local_1c;
    uint local_18;
    uint local_14;
    uint local_10;
    uint local_c;

    // Check event type ID matches connection's ID? +0x14 in event, +0x04 in connection
    local_54 = *(int *)(this + 4);
    if (*(int *)(event + 0x14) != local_54) {
        return in_EAX & 0xffffff00;
    }

    // Build local packet structure (BitStream container?)
    local_68 = *(uint *)(this + 8);            // connection: some ID or timestamp
    local_28 = *(uint *)(extraData + 0x30);    // extra data field

    // Zero initialize many locals (likely padding/fields)
    local_50 = 0;
    local_40 = 0;
    local_38 = 0;
    local_24 = 0;
    local_20 = 0;
    local_1c = 0;
    local_18 = 0;
    local_14 = 0;
    local_10 = 0;
    local_c = 0;
    local_60 = 0;
    local_5c = 0;

    // Structure for writing: pointer to itself? 
    local_70 = &local_58;                       // pointer to the local struct
    local_6c = *(uint *)(event + 0x18);         // event field offset

    local_4c = 0;
    local_48 = 0;
    local_30 = 0;

    local_58 = 4;                               // packet type ID? (4 = Reliable/Ghost?)
    local_44 = 0xffffffff;                      // mask
    local_2c = 0x23;                            // 35 decimal – some flag
    local_34 = DAT_00e2b1a4;                    // global constant
    local_74 = event;                           // store event pointer
    local_64 = 0xffffffff;                      // additional mask
    local_3c = local_68;                        // copy connection field

    // Actually write/send the event using the built structure
    retVal = FUN_00579450(event, &local_74);
    return retVal;
}