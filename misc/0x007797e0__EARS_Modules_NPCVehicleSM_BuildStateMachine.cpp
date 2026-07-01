// Xbox PDB: EARS_Modules_NPCVehicleSM_BuildStateMachine
// FUNC_NAME: NPCVehicleStateMachine::buildStateMachine

void NPCVehicleStateMachine::buildStateMachine(void)
{
    // Build the NPC vehicle state table (state machine definition)
    statemachine::StateTable* stateTable = statemachine::createStateTable(); // FUN_009c8f80
    statemachine::registerStateTable("NPCVehicleST", stateTable); // FUN_004ad9d0

    // Define states and transitions for the NPC vehicle AI

    // Generic state - "driver" (state 0xffffffff = no transition?)
    statemachine::setTransition(&DAT_00d63420, 0xffffffff); // FUN_004adae0
    statemachine::enableState(0x27); // FUN_004acf70
    statemachine::setStateFlags(3, 0x80001, 1); // FUN_004ad0f0

    // Add states with actions
    statemachine::addState("terminate", 0x12); // FUN_004acc70
    statemachine::addState("death", 0xc);
    statemachine::addState("chooseSeat", 4);
    statemachine::setTransition("chooseSeat", 0xffffffff);
    statemachine::addState("driver", 0x15);
    statemachine::addState("passenger", 4);
    statemachine::setTransition("driver", 0xffffffff);

    statemachine::enableState(0x23);
    statemachine::enableState(0x29);
    statemachine::enableState(0x2a);
    statemachine::disableState(0x29); // FUN_004acff0
    statemachine::disableState(0x2a);

    statemachine::addState("terminate", 0x12);
    statemachine::addState("terminate", 0x13);
    statemachine::addState("death", 0xc);
    statemachine::addState("highTension", 0x17);
    statemachine::addState("vehicleDamage", 0x1c);

    statemachine::addStateCondition(&DAT_00d63370, 6, 1, 1); // FUN_004acd20
    statemachine::setTransition("passenger", 0xffffffff);
    statemachine::enableState(0x23);
    statemachine::enableState(0x29);
    statemachine::enableState(0x2a);
    statemachine::disableState(0x29);
    statemachine::disableState(0x2a);

    statemachine::addState("terminate", 0x12);
    statemachine::addState("shooter", 0x14);
    statemachine::addState("terminate", 0x13);
    statemachine::addState("death", 0xc);
    statemachine::addState("highTension", 0x17);
    statemachine::addState("vehicleDamage", 0x1c);

    statemachine::addStateCondition(&DAT_00d63370, 6, 1, 1);
    statemachine::addStateCondition("changeSeat", 6, 0x80000, 1); // DAT_00d63370?
    statemachine::setTransition("changeSeat", 0xffffffff);
    statemachine::enableState(0x26);
    statemachine::enableState(0x29);
    statemachine::disableState(0x29);

    statemachine::addState("terminate", 0x12);
    statemachine::addState("passenger", 7);
    statemachine::setTransition("shooter", 0xffffffff);

    // Create sub-state machine for rail shooter
    statemachine::createSubStateMachine("NPCRailShooterStateTable", 1); // FUN_004acf10
    statemachine::enableState(0x2b);
    statemachine::enableState(0x29);
    statemachine::disableState(0x29);

    statemachine::addState("terminate", 0x12);
    statemachine::addState("terminate", 0x13);
    statemachine::addState("passenger", 1);
    statemachine::setTransition("highTension", 0xffffffff);
    statemachine::enableState(0x2c);

    statemachine::addState("terminate", 0x12);
    statemachine::addState("cower", 0x1a);
    statemachine::addState(&DAT_00d68408, 0x1b);
    statemachine::addState("chooseSeat", 4);
    statemachine::setTransition("vehicleDamage", 0xffffffff);
    statemachine::enableState(0x2d);

    statemachine::addState("terminate", 0x12);
    statemachine::addState("cower", 0x1a);
    statemachine::addState(&DAT_00d68408, 0x1b);
    statemachine::addState("chooseSeat", 4);
    statemachine::setTransition("cower", 0xffffffff);
    statemachine::enableState(0x2e);
    statemachine::enableState(0x2f);
    statemachine::enableState(0x29);
    statemachine::enableState(0x2a);
    statemachine::disableState(0x29);
    statemachine::disableState(0x2a);

    statemachine::addState("terminate", 0x12);
    statemachine::addState("death", 0xc);
    statemachine::addState("cowerExitVehicle", 0x1c);
    statemachine::addStateCondition("cowerExitVehicle", 6, 1, 1);
    statemachine::addState("tensionLowered", 0x19);
    statemachine::setTransition("tensionLowered", 0xffffffff);
    statemachine::enableState(0x30);
    statemachine::enableState(0x32);

    statemachine::addState("chooseSeat", 4);
    statemachine::setTransition("cowerExitVehicle", 0xffffffff);
    statemachine::enableState(0x34);
    statemachine::enableState(0x33);

    statemachine::addState("chooseSeat", 4);
    statemachine::setTransition(&DAT_00d68408, 0xffffffff);
    statemachine::enableState(0x31);
    statemachine::enableState(0x29);
    statemachine::enableState(0x2a);
    statemachine::disableState(0x29);
    statemachine::disableState(0x2a);

    statemachine::addState("death", 0xc);
    statemachine::addState("terminate", 0x12);
    statemachine::setTransition(&DAT_00d63370, 0xffffffff);
    statemachine::enableState(0x28);
    statemachine::enableState(0x29);
    statemachine::disableState(0x29);

    statemachine::addState("terminate", 0x12);
    statemachine::addState("death", 0xc);
    statemachine::addState(&DAT_00d63420, 0x16);
    statemachine::setTransition("death", 0xffffffff);
    statemachine::enableState(0x25);
    statemachine::enableState(0x2f);
    statemachine::addStateWithClass(0x24); // FUN_004ad070

    statemachine::addState("corpse", 7);
    statemachine::setTransition("corpse", 0xffffffff);
    statemachine::enableState(0x13);
    statemachine::disableState(0x14);
    statemachine::setTransition("terminate", 0xffffffff);
    statemachine::setStateFlags(4, 0x80001, 1);
    statemachine::enableState(2);

    // Register the state machine with a timeout and label
    statemachine::registerStateMachine(-4.0e7f, &LAB_007797b0, "NPCVehicleSM"); // FUN_004adc90
    statemachine::finalize(); // FUN_004ada40
}