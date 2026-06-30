// FUNC_NAME: MissionStateMachine::updateState

// Address: 0x006fca90
// Updates mission state machine; returns 1 if state changed, 0 otherwise

struct MissionStateMachine {
    int state;           // +0x00: 3=ready? 4=running? 6=completed?
    int timer;           // +0x04: countdown or sub-state
    int unk_0x08;        // +0x08
    int unk_0x0C;        // +0x0C
    int unk_0x10;        // +0x10
    int someTargetId;    // +0x14: ID or index used for completion event
    int* ownerSubobject; // +0x18: pointer to an embedded subobject (offset 0x48 from actual owner)
};

int __fastcall MissionStateMachine::updateState(MissionStateMachine* this) {
    char cVar1;
    uint uVar2;
    int* piVar3;
    int unaff_ESI;  // external register/global (e.g., debug mode flag)
    int* local_4;

    // Step 1: Check if ownerSubobject is null or sentinel (0x48 = embedded object offset)
    if ((this->ownerSubobject == (int*)0) || (this->ownerSubobject == (int*)0x48)) {
        uVar2 = 0;
        local_4 = (int*)this;
    } else {
        // ownerSubobject points 0x48 into the real owner; get base object
        piVar3 = this->ownerSubobject - 0x48;
        local_4 = (int*)0;
        // Virtual call: is this owner of type 0x55859efa? (likely "Mission" class ID)
        cVar1 = (*(char (__fastcall**)(int*, int**))(*piVar3 + 0x10))(0x55859efa, &local_4);
        uVar2 = -(uint)(cVar1 != '\0') & (uint)local_4;
    }

    // If type matched and local_4 set, do something (e.g., log or alter state)
    if (uVar2 != 0) {
        FUN_007f97a0(0);  // Possibly debug message or notification
    }

    // State machine transition
    if (this->state == 3) {
        // Need to check another condition before transitioning out of state 3
        if ((this->ownerSubobject != (int*)0) && (this->ownerSubobject != (int*)0x48)) {
            piVar3 = this->ownerSubobject - 0x48;
            local_4 = (int*)0;
            // Virtual call: is owner of type 0xae986323? (e.g., "Player" class)
            cVar1 = (*(char (__fastcall**)(int*, int**))(*piVar3 + 0x10))(0xae986323, &local_4);
            if ((cVar1 != '\0') && (unaff_ESI != 0)) {
                // Trigger completion handler with stored target ID
                FUN_0045f2a0(this->someTargetId);
            }
            // Move to state 4 (active/running)
            this->state = 4;
            this->timer = 0;
            return 1;
        }
        // If no valid owner subobject, jump directly to state 6 (final)
        this->state = 6;
        this->timer = 0;
        return 1;
    }
    return 0;
}