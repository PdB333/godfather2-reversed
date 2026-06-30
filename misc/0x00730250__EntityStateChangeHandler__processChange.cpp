// FUNC_NAME: EntityStateChangeHandler::processChange
void __thiscall EntityStateChangeHandler::processChange(int this, int source, char changeType)
{
    int iVar1;
    // Local structures for event message construction
    struct {
        undefined4 field0;   // +0x00: possibly something
        undefined*** field4; // +0x04: vtable pointer?
        undefined1 field8;   // +0x08: padding?
        undefined4 fieldC;   // +0x0C: some id
        // ... offsets follow as they are placed on stack
    } localEvent1;
    struct {
        undefined4 field0;
        undefined*** field4;
        undefined1 field8;
        undefined4 fieldC;
        // ... etc.
    } localEvent2;
    // More local variables ...
    undefined4 local_60;
    undefined ***local_5c;
    undefined1 local_58;
    undefined4 local_54;
    undefined ***local_50;
    undefined1 local_4c;
    undefined **local_48;
    undefined4 local_44;
    int local_40;
    undefined4 local_3c;
    undefined4 local_38;
    undefined4 local_34;
    undefined4 local_30;
    undefined1 local_2c;
    undefined4 local_28;
    undefined **local_24;
    undefined4 local_20;
    int local_1c;
    undefined4 local_18;
    undefined4 local_14;
    undefined4 local_10;
    undefined4 local_c;
    undefined1 local_8;
    undefined4 local_4;

    // Check if version numbers match; if so, no change to process
    if (*(int *)(this + 0x2138) == *(int *)(source + 0x1ed4)) {
        return;
    }

    // Determine if source owns this (i.e., this is the child at offset 0x24c4 - 0x48)
    if (*(int *)(source + 0x24c4) == 0) {
        iVar1 = 0;
    } else {
        iVar1 = *(int *)(source + 0x24c4) + -0x48;  // Adjust pointer back to container
    }
    if (iVar1 == this) {
        // Set up first event structure (type 0xa6888fdc)
        local_c = 0;
        local_10 = 0;
        local_14 = 0;
        local_24 = &PTR_FUN_00d5dbbc;   // vtable for event message
        local_1c = 0;
        local_18 = 0;
        local_8 = 0;
        local_4 = DAT_01205228;         // some global
        local_20 = 0xa6888fdc;         // event type hash

        // Insert this local event into source's linked list (if list head exists)
        if (source + 0x48 != 0) {
            local_18 = *(undefined4 *)(source + 0x4c);  // save old tail next
            *(int **)(source + 0x4c) = &local_1c;       // set new tail next to our local node
            local_1c = source + 0x48;                  // set our node's next to head (circular?)
        }

        local_60 = DAT_0112ad8c;       // another global (maybe message queue)
        local_5c = &local_24;
        local_58 = 0;
        FUN_00408bf0(&local_60, this + 0x3c, 0); // send event to this+0x3c (event receiver)

        if (local_1c != 0) {
            FUN_004daf90(&local_1c);   // cleanup/remove from list
        }
    }

    // Build second event structure based on changeType
    local_30 = 0;
    local_34 = 0;
    local_38 = 0;
    local_48 = &PTR_FUN_00d5dbbc;
    local_40 = 0;
    local_3c = 0;
    local_2c = 0;
    local_28 = DAT_01205228;

    // Select event type based on changeType
    if (changeType != '\x01') {
        if (changeType == '\x02') {
            local_44 = 0x23f3d3fd;   // change type 2 event hash
            goto LAB_00730381;
        }
        if (changeType == '\x05') {
            local_44 = 0x7b35500e;   // change type 5 event hash
            goto LAB_00730381;
        }
    }
    local_44 = 0xb6988728;           // default event hash (likely type 1 or unknown)

LAB_00730381:
    // Insert this second event into source's list (same pattern)
    if (source + 0x48 != 0) {
        local_3c = *(undefined4 *)(source + 0x4c);
        *(int **)(source + 0x4c) = &local_40;
        local_40 = source + 0x48;
    }

    local_54 = DAT_0112ad8c;
    local_50 = &local_48;
    local_4c = 0;
    FUN_00408bf0(&local_54, this + 0x3c, 0);  // send second event

    if (local_40 != 0) {
        FUN_004daf90(&local_40);
    }

    return;
}