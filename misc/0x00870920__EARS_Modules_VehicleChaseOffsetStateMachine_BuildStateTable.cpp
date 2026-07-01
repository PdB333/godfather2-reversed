// Xbox PDB: EARS_Modules_VehicleChaseOffsetStateMachine_BuildStateTable
//FUNC_NAME: VehicleChaseOffsetStateMachine::initializeStateMachine
void VehicleChaseOffsetStateMachine::initializeStateMachine(void)
{
    // Check if the state machine table already exists
    void* tableHandle = getTable("vehicleChaseOffsetTable");
    if (isTableNull(tableHandle) == 0) {
        // Table doesn't exist, create and populate it
        tableHandle = createTable();
        registerTable("vehicleChaseOffsetTable", tableHandle);

        // --- Block state group ---
        addState("block", 0xffffffff);           // +0x00: state "block" (placeholder)
        setInitialState(10);                      // +0x04: initial state = 10 (unknown)
        addState("followEntity", 0xc);            // +0x08: state 0xc = followEntity
        addState("block", 0x14);                  // +0x0c: state 0x14 = block
        addState("teleport", 0xd);                // +0x10: state 0xd = teleport
        addState("followEntity", 0xb);            // +0x14: state 0xb = followEntity (duplicate?)
        setTransition("followEntity", 0xffffffff); // +0x18: clear transitions from followEntity
        setInitialState(0xb);                     // +0x1c: initial state = 0xb
        addTransitionFromCurrent(0xd);            // +0x20: transition from 0xb -> 0xd
        addTransitionFromCurrent(0xc);            // +0x24: transition from 0xb -> 0xc
        addTransitionFromCurrent(0x1d);           // +0x28: transition from 0xb -> 0x1d
        addTransitionFromCurrent(0x14);           // +0x2c: transition from 0xb -> 0x14

        // --- Teleport state group ---
        addState("teleport", 0x12);               // +0x30: state 0x12 = teleport
        addState("teleport", 0x13);               // +0x34: state 0x13 = teleport (duplicate?)
        addState("reverse", 10);                  // +0x38: state 10 = reverse (note: 10 is decimal)
        addState("slow_then_reverse", 0x1c);      // +0x3c: state 0x1c = slow_then_reverse
        addState("maneuver", 0x19);               // +0x40: state 0x19 = maneuver
        setTransition("teleport", 0xffffffff);    // +0x44: clear transitions from teleport
        setInitialState(0xe);                     // +0x48: initial state = 0xe
        addTransitionFromCurrent(0xd);            // +0x4c: transition from 0xe -> 0xd
        addTransitionFromCurrent(0xf);            // +0x50: transition from 0xe -> 0xf
        addTransitionFromCurrent(0x14);           // +0x54: transition from 0xe -> 0x14
        addTransitionFromCurrent(0x1d);           // +0x58: transition from 0xe -> 0x1d

        // --- FollowEntity state group ---
        addState("followEntity", 0xe);            // +0x5c: state 0xe = followEntity
        addState("followEntity", 0x10);           // +0x60: state 0x10 = followEntity (duplicate?)
        addState("teleport", 0x12);               // +0x64: state 0x12 = teleport (again)
        addState("reverse", 10);                  // +0x68: state 10 = reverse (again)
        addState("slow_then_reverse", 0x1c);      // +0x6c: state 0x1c = slow_then_reverse (again)
        addState("maneuver", 0xf);                // +0x70: state 0xf = maneuver
        setTransition("maneuver", 0xffffffff);    // +0x74: clear transitions from maneuver
        setInitialState(0x15);                    // +0x78: initial state = 0x15
        addTransitionFromCurrent(0x16);           // +0x7c: transition from 0x15 -> 0x16
        addTransitionFromCurrent(0x1d);           // +0x80: transition from 0x15 -> 0x1d
        addState("teleport", 0x16);               // +0x84: state 0x16 = teleport
        addState("followEntity", 0x17);           // +0x88: state 0x17 = followEntity
        addState("slow_then_reverse", 0x1c);      // +0x8c: state 0x1c = slow_then_reverse (again)
        addState("followEntity", 0x18);           // +0x90: state 0x18 = followEntity
        setTransition("teleport", 0xffffffff);    // +0x94: clear transitions from teleport
        setInitialState(0x10);                    // +0x98: initial state = 0x10
        setStateAsTerminal(0x11);                 // +0x9c: state 0x11 is terminal
        addState("block", 0x15);                  // +0xa0: state 0x15 = block (overwrites previous?)
        addState("block", 4);                     // +0xa4: state 4 = block

        // --- SlowThenReverse state group ---
        setTransition("slow_then_reverse", 0xffffffff); // +0xa8: clear transitions from slow_then_reverse
        setInitialState(0x19);                    // +0xac: initial state = 0x19
        setInitialState(0x18);                    // +0xb0: initial state = 0x18 (overwrites)
        addTransitionFromCurrent(0x14);           // +0xb4: transition from 0x18 -> 0x14
        addTransitionFromCurrent(0xd);            // +0xb8: transition from 0x18 -> 0xd
        addTransitionFromCurrent(0x1a);           // +0xbc: transition from 0x18 -> 0x1a
        addTransitionFromCurrent(0x1d);           // +0xc0: transition from 0x18 -> 0x1d
        addState("teleport", 0x12);               // +0xc4: state 0x12 = teleport
        addState("reverse", 0x1a);                // +0xc8: state 0x1a = reverse
        setTransition("reverse", 0xffffffff);     // +0xcc: clear transitions from reverse
        createSubTable("vehicleReverseTable", 1); // +0xd0: create sub-table for reverse
        setInitialState(0x18);                    // +0xd4: initial state = 0x18
        addTransitionFromCurrent(0x14);           // +0xd8: transition from 0x18 -> 0x14
        addTransitionFromCurrent(0xd);            // +0xdc: transition from 0x18 -> 0xd
        addTransitionFromCurrent(0x1d);           // +0xe0: transition from 0x18 -> 0x1d
        addState("teleport", 0x12);               // +0xe4: state 0x12 = teleport
        addState("slow_then_reverse", 0x1c);      // +0xe8: state 0x1c = slow_then_reverse
        addState("block", 1);                     // +0xec: state 1 = block
        setTransition("block", 0xffffffff);       // +0xf0: clear transitions from block
        addTransitionFromCurrent(0x17);           // +0xf4: transition from ??? (current state?) -> 0x17
        addTransitionFromCurrent(0x14);           // +0xf8: transition from ??? -> 0x14
        addTransitionFromCurrent(0xd);            // +0xfc: transition from ??? -> 0xd
        addTransitionFromCurrent(0x1d);           // +0x100: transition from ??? -> 0x1d
        addState("teleport", 0x12);               // +0x104: state 0x12 = teleport
        setTransition("slow_then_reverse", 0xffffffff); // +0x108: clear transitions from slow_then_reverse
        setInitialState(0x1a);                    // +0x10c: initial state = 0x1a
        addTransitionFromCurrent(0x1a);           // +0x110: transition from 0x1a -> 0x1a (self-loop?)
        addState("exitOccupants", 0x1d);          // +0x114: state 0x1d = exitOccupants
        addState("block", 0x1e);                  // +0x118: state 0x1e = block
        setTransition("exitOccupants", 0xffffffff); // +0x11c: clear transitions from exitOccupants
        setInitialState(0x1b);                    // +0x120: initial state = 0x1b
        addTransitionFromCurrent(0x1c);           // +0x124: transition from 0x1b -> 0x1c
        addState("teleport", 0x12);               // +0x128: state 0x12 = teleport
        setTransition("block", 0xffffffff);       // +0x12c: clear transitions from block
        setStateAsTerminal(0x13);                 // +0x130: state 0x13 is terminal
        addState("followEntity", 0x1b);           // +0x134: state 0x1b = followEntity
        setTransition("followEntity", 0xffffffff); // +0x138: clear transitions from followEntity
        setInitialState(0x12);                    // +0x13c: initial state = 0x12

        // Register the state machine with a hash and label
        registerStateMachine(0xdfd3c4cb, &LAB_00870540, "VehicleChaseOffsetStateMachine");
        finalizeStateMachine();
    }
    return;
}