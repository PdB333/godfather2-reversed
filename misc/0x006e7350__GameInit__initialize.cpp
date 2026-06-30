// FUNC_NAME: GameInit::initialize
void __fastcall GameInit::initialize(undefined4* param_1)
{
    // Call to engine initialization routine (0x006e6cf0)
    Sub_006e6cf0();
    // Call to object registration function (0x009c8f10) with value from param_1
    Sub_009c8f10(*param_1);
}