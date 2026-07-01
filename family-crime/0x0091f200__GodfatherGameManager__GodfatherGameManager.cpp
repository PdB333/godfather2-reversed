// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x0091f200 - Constructor for the main game manager object
// This initializes all sub-systems, sets up vtable pointers, and calls virtual init on each subobject.

int* __thiscall GodfatherGameManager::GodfatherGameManager(int* thisPtr)
{
    // Initialize all sub-system components
    FUN_009122f0(); // SubSystemA::init?
    FUN_00934bc0(); // SubSystemB::init?
    FUN_0095a660(); // SubSystemC::init?
    FUN_00989d20(); // SubSystemD::init?
    FUN_00952c30(); // SubSystemE::init?
    FUN_00986860(); // SubSystemF::init?
    FUN_0096f1a0(); // SubSystemG::init?
    FUN_009621a0(); // SubSystemH::init?
    FUN_0091e4b0(); // SubSystemI::init?
    FUN_0098e840(); // SubSystemJ::init?
    FUN_009831f0(); // SubSystemK::init?
    FUN_00911b30(); // SubSystemL::init?
    FUN_00975c60(); // SubSystemM::init?
    FUN_00926070(); // SubSystemN::init?
    FUN_00990300(); // SubSystemO::init?
    FUN_00993500(); // SubSystemP::init?
    FUN_00924f40(); // SubSystemQ::init?
    FUN_00927460(); // SubSystemR::init?
    FUN_00937630(); // SubSystemS::init?
    FUN_009608f0(); // SubSystemT::init?
    FUN_00961d90(); // SubSystemU::init?
    FUN_00988aa0(); // SubSystemV::init?
    FUN_0098c910(); // SubSystemW::init?

    // Set the vtable pointer for the subobject at offset +0x2E40 (0xb90 * 4)
    thisPtr[0xb90] = (int)&PTR_LAB_00d86068; // +0x2E40 : subobject vtable

    // Call virtual init (vtable offset 0x64) on each subobject
    (**(code **)(*thisPtr + 100))();                                  // Main object vtable at offset 0x64
    (**(code **)(thisPtr[0x18] + 100))();                              // +0x60 subobject
    (**(code **)(thisPtr[0x46] + 100))();                              // +0x118 subobject
    (**(code **)(thisPtr[0x94] + 100))();                              // +0x250 subobject
    (**(code **)(thisPtr[0xd5] + 100))();                              // +0x354 subobject
    (**(code **)(thisPtr[0xef] + 100))();                              // +0x3BC subobject
    (**(code **)(thisPtr[0x134] + 100))();                             // +0x4D0 subobject
    (**(code **)(thisPtr[0x2f6] + 100))();                             // +0xBD8 subobject
    (**(code **)(thisPtr[0x30e] + 100))();                             // +0xC38 subobject
    (**(code **)(thisPtr[0x352] + 100))();                             // +0xD48 subobject
    (**(code **)(thisPtr[0x37a] + 100))();                             // +0xDE8 subobject
    (**(code **)(thisPtr[0x39f] + 100))();                             // +0xE7C subobject
    (**(code **)(thisPtr[0x3b7] + 100))();                             // +0xEDC subobject
    (**(code **)(thisPtr[0x3d8] + 100))();                             // +0xF60 subobject
    (**(code **)(thisPtr[0x8c8] + 100))();                             // +0x2320 subobject
    (**(code **)(thisPtr[0x92a] + 100))();                             // +0x24A8 subobject
    (**(code **)(thisPtr[0x941] + 100))();                             // +0x2504 subobject
    (**(code **)(thisPtr[0x964] + 100))();                             // +0x2590 subobject
    (**(code **)(thisPtr[0xa5c] + 100))();                             // +0x2970 subobject
    (**(code **)(thisPtr[0xa71] + 100))();                             // +0x29C4 subobject
    (**(code **)(thisPtr[0xa85] + 100))();                             // +0x2A14 subobject
    (**(code **)(thisPtr[0xaa7] + 100))();                             // +0x2A9C subobject
    (**(code **)(thisPtr[0xaf0] + 100))();                             // +0x2BC0 subobject

    // Finalize the subobject at offset +0x2E40
    int* subObj = thisPtr + 0xb90;  // +0x2E40
    FUN_005c3960(subObj);           // subObject::func1
    FUN_005c3b10(subObj);           // subObject::func2

    return thisPtr;
}