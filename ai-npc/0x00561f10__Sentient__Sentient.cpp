// FUNC_NAME: Sentient::Sentient
// Function address: 0x00561f10
// Role: Constructor for Sentient class (base entity) - initializes vtable and default member values
// Note: Uses global constants from data segments; offsets documented in comments.

#pragma once

void __thiscall Sentient::Sentient()
{
    // Global constants (placeholder names - rename if symbols become available)
    void* gSomeFuncTable = (void*)0x00e3a428; // &PTR_FUN_00e3a428
    int gSomeConstant1 = DAT_00e39f98;        // uVar2
    int gSomeConstant2 = DAT_00e2b1a4;        // uVar1
    int gSomeConstant3 = DAT_00e446bc;        // used multiple times
    int gSomeConstant4 = DAT_00e2b334;        // offset 0x18 value
    int gSomeConstant5 = DAT_00e2cd54;        // offset 0x1C/0x20 value

    // Offset 0x00: vtable pointer
    this->vtable = gSomeFuncTable;

    // Offsets 0x3C, 0x40, 0x44: state machine counters
    this->stateMax = 4;      // +0x3C
    this->stateCurrent = 2;  // +0x40
    this->statePrevious = 0; // +0x44

    // Offset 0x60, 0x80, 0x84, 0x88: timers/flags
    this->timerA = 0;        // +0x60
    this->flagA = 0;         // +0x80
    this->flagB = 0;         // +0x84
    this->flagC = 0;         // +0x88

    // Offsets 0x8C, 0x90: behavior function pointers (overridden later)
    this->behaviorFunc1 = (void*)0x00dc3dd4; // &PTR_LAB_00dc3dd4 (temporary)
    this->someParamA = gSomeConstant2;       // +0x94
    this->someParamB = gSomeConstant2;       // +0x98
    this->someParamC = gSomeConstant3;       // +0x9C
    this->someParamD = gSomeConstant2;       // +0xA0 (note: originally uVar1)
    this->someParamE = gSomeConstant2;       // +0xA4
    this->someParamF = 0;                    // +0xA8
    this->someParamG = 0;                    // +0xAC

    // Overwrite final function pointers (behavior functions)
    this->behaviorFunc2 = (void*)0x00e3a038; // +0x8C: &PTR_FUN_00e3a038
    this->behaviorFunc1 = (void*)0x00e3a054; // +0x90: &PTR_LAB_00e3a054 (final)

    // Offset 0xC0, 0xB0-0xBC: zero fields
    this->field0xC0 = 0; // +0xC0
    this->field0xB0 = 0; // +0xB0
    this->field0xB4 = 0; // +0xB4
    this->field0xB8 = 0; // +0xB8
    this->field0xBC = 0; // +0xBC

    // Offset 0x14, 0x18: size/resource fields
    this->field0x14 = 0;              // +0x14
    this->field0x18 = gSomeConstant4; // +0x18

    // Offset 0x24-0x38: zero fields (counters/pointers)
    this->field0x24 = 0; // +0x24
    this->field0x28 = 0; // +0x28
    this->field0x2C = 0; // +0x2C
    this->field0x30 = 0; // +0x30
    this->field0x34 = 0; // +0x34
    this->field0x38 = 0; // +0x38

    // Offset 0x10: another constant
    this->field0x10 = gSomeConstant1; // +0x10

    // Offset 0x1C, 0x20: same constant
    this->field0x1C = gSomeConstant5; // +0x1C
    this->field0x20 = gSomeConstant5; // +0x20
}