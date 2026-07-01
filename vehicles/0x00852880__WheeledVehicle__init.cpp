// FUNC_NAME: WheeledVehicle::init
// Function at 0x00852880: Initializes a WheeledVehicle from a large set of parameters, likely a constructor or setup routine.
// Calls a base class initializer (FUN_008522d0) for common vehicle fields, then fills in wheeled-specific properties.
int __thiscall WheeledVehicle::init(WheeledVehicle *this, int arg0, int arg1, int arg2, int arg3, int arg4,
                                    int arg5, int arg6, int arg7, int arg8, int arg9,
                                    int arg10, int arg11, int arg12, int arg13, int arg14,
                                    int arg15, int arg16, int arg17, int arg18, int arg19,
                                    int arg20, int arg21, int arg22, int arg23, int arg24,
                                    int arg25, int arg26, int arg27)
{
    // Base vehicle initialization (handles fields common to all vehicles)
    // Parameters passed: arg0-arg4, arg8, arg10-arg16 (matches param_2-6, param_10, param_12-18)
    FUN_008522d0(arg0, arg1, arg2, arg3, arg4, arg8, arg10, arg11, arg12, arg13, arg14, arg15, arg16);

    // Wheeled-specific field assignments (offsets relative to this)
    this->field_0x40 = arg6;      // +0x40 (e.g., throttle input)
    this->field_0x4c = arg5;      // +0x4c (e.g., brake input)
    this->field_0x50 = arg17;     // +0x50 (e.g., steering input)
    this->field_0x3c = arg9;      // +0x3c (e.g., suspension parameters)
    this->field_0x54 = arg18;     // +0x54
    this->field_0x58 = arg19;     // +0x58
    this->field_0x5c = arg20;     // +0x5c
    this->field_0x68 = arg24;     // +0x68
    this->field_0x74 = arg27;     // +0x74
    this->field_0x44 = arg7;      // +0x44
    this->field_0x48 = arg21;     // +0x48
    this->field_0x6c = arg25;     // +0x6c
    this->field_0x90 = 0;         // +0x90 – cleared (flags/pointers)
    this->field_0x60 = arg22;     // +0x60
    this->field_0x64 = arg23;     // +0x64 (100 decimal)
    this->field_0x70 = arg26;     // +0x70
    this->field_0x94 = 0;         // +0x94 – cleared
    this->field_0x98 = 0;         // +0x98 – cleared
    this->field_0x9c = 0;         // +0x9c – cleared
    this->field_0xa0 = 0;         // +0xa0 – cleared
    this->field_0xa4 = 0;         // +0xa4 – cleared

    return (int)this;
}