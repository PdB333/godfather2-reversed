// FUNC_NAME: MenuScreen::processInput
// Address: 0x00731050
// Purpose: Process input for a menu screen, checking enabled actions and dispatching sound/event hashes.
// Flags at this+0x2188 determine which actions are currently active.

void __fastcall MenuScreen::processInput(int this)
{
    uint flags = *(uint *)(this + 0x2188); // m_flags
    char eventBuffer[20];                  // local_1c
    int unkBuffer[2];                      // local_8 (may be set by sound system; unused here)

    // Reset input state and set context
    FUN_00892af0(0);
    FUN_00892ce0(this, 0);

    // Big chain of action checks; each branch corresponds to a specific user action
    if ((flags >> 9 & 1) == 0)
    {
        if ((flags >> 3 & 1) == 0)
        {
            if ((flags >> 4 & 1) == 0)
            {
                if ((flags >> 5 & 1) == 0)
                {
                    if ((flags >> 6 & 1) == 0)
                    {
                        // Series of action IDs (likely gamepad/keyboard mappings)
                        if (!FUN_0072c080(0x3e))
                        {
                            if (!FUN_0072c080(0x38))
                            {
                                if (!FUN_0072c080(0x10))
                                {
                                    if (!FUN_0072c080(0x11))
                                    {
                                        if (!FUN_0072c080(0x1d))
                                        {
                                            if (!FUN_0072c080(0x1e))
                                            {
                                                if (!FUN_0072c080(0x1f))
                                                {
                                                    if (!FUN_0072c080(0x20))
                                                    {
                                                        if (!FUN_0072c080(0x21))
                                                        {
                                                            if (!FUN_0072c080(0x22))
                                                            {
                                                                if (!FUN_0072c080(0x23))
                                                                {
                                                                    if (!FUN_0072c080(0x24))
                                                                    {
                                                                        if (!FUN_0072c080(0x25))
                                                                        {
                                                                            if (!FUN_0072c080(0x26))
                                                                            {
                                                                                if (!FUN_0072c080(0x19))
                                                                                {
                                                                                    if (!FUN_0072c080(0x1a))
                                                                                    {
                                                                                        if (!FUN_0072c080(0x27))
                                                                                        {
                                                                                            if (!FUN_0072c080(0x28))
                                                                                            {
                                                                                                if (!FUN_0072c080(0x2b))
                                                                                                {
                                                                                                    if (!FUN_0072c080(0x2c))
                                                                                                    {
                                                                                                        if (!FUN_0072c080(0x29))
                                                                                                        {
                                                                                                            if (!FUN_0072c080(0x2a))
                                                                                                            {
                                                                                                                if (!FUN_0072c080(0x2d))
                                                                                                                {
                                                                                                                    if (!FUN_0072c080(0x2e))
                                                                                                                    {
                                                                                                                        if (!FUN_0072c080(0x2f))
                                                                                                                        {
                                                                                                                            if (!FUN_0072c080(0x30))
                                                                                                                            {
                                                                                                                                if (!FUN_0072c080(0x31))
                                                                                                                                {
                                                                                                                                    if (!FUN_0072c080(0x32))
                                                                                                                                    {
                                                                                                                                        if (!FUN_0072c080(0x1b))
                                                                                                                                        {
                                                                                                                                            if (!FUN_0072c080(0x1c))
                                                                                                                                            {
                                                                                                                                                if (!FUN_0072c080(0xc))
                                                                                                                                                {
                                                                                                                                                    if (!FUN_0072c080(0xa))
                                                                                                                                                    {
                                                                                                                                                        if (!FUN_0072c080(0xb))
                                                                                                                                                        {
                                                                                                                                                            if (!FUN_0072c080(0x37))
                                                                                                                                                            {
                                                                                                                                                                if (!FUN_0072c080(0x39))
                                                                                                                                                                {
                                                                                                                                                                    if (!FUN_0072c080(0x33))
                                                                                                                                                                    {
                                                                                                                                                                        if (!FUN_0072c080(0x34) && !FUN_0072c080(0x35) && !FUN_0072c080(0x36))
                                                                                                                                                                        {
                                                                                                                                                                            if (!FUN_0072c080(7))
                                                                                                                                                                            {
                                                                                                                                                                                if (!FUN_0072c080(8))
                                                                                                                                                                                {
                                                                                                                                                                                    if (!FUN_0072c080(0xd))
                                                                                                                                                                                    {
                                                                                                                                                                                        if (!FUN_0072c080(0xf))
                                                                                                                                                                                        {
                                                                                                                                                                                            if (!FUN_0072c080(0x18))
                                                                                                                                                                                            {
                                                                                                                                                                                                if (!FUN_0072c080(0xe))
                                                                                                                                                                                                    goto LAB_007315f2;
                                                                                                                                                                                                hash = 0x45295ae5;
                                                                                                                                                                                            }
                                                                                                                                                                                            else
                                                                                                                                                                                                hash = 0x8597d73a;
                                                                                                                                                                                        }
                                                                                                                                                                                        else
                                                                                                                                                                                            hash = 0x1dd8ad9d;
                                                                                                                                                                                    }
                                                                                                                                                                                    else
                                                                                                                                                                                        hash = 0xe014442d;
                                                                                                                                                                                }
                                                                                                                                                                                else
                                                                                                                                                                                    hash = 0x98ff9545;
                                                                                                                                                                            }
                                                                                                                                                                        }
                                                                                                                                                                        else
                                                                                                                                                                        {
                                                                                                                                                                            FUN_00894c40(0x7363762, eventBuffer);
                                                                                                                                                                            hash = 0xe06f665;
                                                                                                                                                                        }
                                                                                                                                                                    }
                                                                                                                                                                    else
                                                                                                                                                                        hash = 0x9d407218;
                                                                                                                                                                }
                                                                                                                                                                else
                                                                                                                                                                {
                                                                                                                                                                    FUN_00892b40(this, 1);
                                                                                                                                                                    hash = 0x5bf55321;
                                                                                                                                                                }
                                                                                                                                                            }
                                                                                                                                                            else
                                                                                                                                                                hash = 0xfdbf89be;
                                                                                                                                                        }
                                                                                                                                                        else
                                                                                                                                                            hash = 0x1b1ae31d;
                                                                                                                                                    }
                                                                                                                                                    else
                                                                                                                                                        hash = 0x8d7aa0de;
                                                                                                                                                }
                                                                                                                                                else
                                                                                                                                                    hash = 0x5586f79b;
                                                                                                                                            }
                                                                                                                                            else
                                                                                                                                                hash = 0x1148fe48;
                                                                                                                                        }
                                                                                                                                        else
                                                                                                                                            hash = 0xb81bea9d;
                                                                                                                                    }
                                                                                                                                    else
                                                                                                                                        hash = 0x73ddf14a;
                                                                                                                                }
                                                                                                                                else
                                                                                                                                    hash = 0xb81bea9d;
                                                                                                                            }
                                                                                                                            else
                                                                                                                                hash = 0x73ddf14a;
                                                                                                                        }
                                                                                                                        else
                                                                                                                            hash = 0xfd2a13f8;
                                                                                                                    }
                                                                                                                    else
                                                                                                                        hash = 0xb8ec1aa5;
                                                                                                                }
                                                                                                                else
                                                                                                                    hash = 0xa6f6de39;
                                                                                                            }
                                                                                                            else
                                                                                                                hash = 0x62b8e4e6;
                                                                                                        }
                                                                                                        else
                                                                                                            hash = 0xb837b0ae;
                                                                                                    }
                                                                                                    else
                                                                                                        hash = 0x73f9b75b;
                                                                                                }
                                                                                                else
                                                                                                    hash = 0xc8d48bb7;
                                                                                            }
                                                                                            else
                                                                                                hash = 0x84969264;
                                                                                        }
                                                                                        else
                                                                                            hash = 0xd76a7f03;
                                                                                    }
                                                                                    else
                                                                                        hash = 0x932c85b0;
                                                                                }
                                                                                else
                                                                                    hash = 0x4db76b7d;
                                                                            }
                                                                            else
                                                                                hash = 0x979722a;
                                                                        }
                                                                        else
                                                                            hash = 0x889f1de6;
                                                                    }
                                                                    else
                                                                        hash = 0x44612493;
                                                                }
                                                                else
                                                                    hash = 0x8d12e583;
                                                            }
                                                            else
                                                                hash = 0x48d4ec30;
                                                        }
                                                        else
                                                            hash = 0x4cd6deb;
                                                    }
                                                    else
                                                        hash = 0xc08f7498;
                                                }
                                                else
                                                    hash = 0xb9cd50a5;
                                            }
                                            else
                                                hash = 0x758f5752;
                                        }
                                        else
                                            hash = 0x8fe94b0c;
                                    }
                                    else
                                        hash = 0x7803b606;
                                }
                                else
                                {
                                    FUN_00892b40(this, 1);
                                    hash = 0xc68907bc;
                                }
                            }
                            else
                                hash = 0x6d94a4f6;
                        }
                        else
                            hash = 0x3a6a97b1;
                    }
                    else
                        hash = 0xd59da5f8;
                }
                else
                {
                    FUN_00892b40(this, 1);
                    hash = 0x9c7db296;
                }
            }
            else
            {
                FUN_00892b40(this, 1);
                hash = 0x776289d7;
            }
        }
        else
            hash = 0x19f260ba;
    }

LAB_007315eb:
    FUN_00894c40(hash, eventBuffer);

LAB_007315f2:
    // Additional sound/event triggers based on higher flags
    if ((flags >> 0x12 & 1) != 0) // bit 18
        FUN_00894c40(0x478c35d9, eventBuffer);
    if ((flags >> 0x13 & 1) != 0) // bit 19
        FUN_00894c40(0xef11a82b, eventBuffer);
    if ((flags >> 0x14 & 1) != 0) // bit 20
        FUN_00894c40(0x2b9b3c30, eventBuffer);
    if ((flags >> 0x15 & 1) != 0) // bit 21
        FUN_00894c40(0xd0a9a774, eventBuffer);
    if ((flags >> 0x16 & 1) != 0) // bit 22
        FUN_00894c40(0xd43fe3c5, eventBuffer);
    if ((flags >> 0x17 & 1) != 0) // bit 23
        FUN_00894c40(0xdad0382d, eventBuffer);

    if (unkBuffer[0] != 0)
        FUN_004daf90(unkBuffer);

    return;
}