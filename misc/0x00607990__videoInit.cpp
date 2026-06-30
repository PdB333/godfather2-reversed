// FUNC_NAME: videoInit
void videoInit(void)
{
    // Initialize resolution globals from stored values
    DAT_0120587c = DAT_012058b8;   // +0x7c: width
    DAT_01205878 = (float)DAT_012058b8 / (float)DAT_012058bc; // +0x78: aspect ratio
    DAT_01205880 = DAT_012058bc;   // +0x80: height
    DAT_01205884 = 0;
    DAT_01205888 = 0;
    _DAT_01205890 = 0x411a;       // some constant
    _DAT_01205894 = 0;
    
    // Store a byte from AL
    DAT_01205762 = in_AL;         // possibly window mode flag?

    // Query something; if not equal to 9, call error handler via function pointer
    if (FUN_0060f390() != 9) {
        (*(code *)PTR_FUN_00f15a3c)();
        return;
    }

    // Validate resolution settings; if fails, run error routine
    if (!FUN_006073e0(&DAT_0120587c, &DAT_01205880)) {
        FUN_00608b50();
    }

    // Copy resolved resolution
    DAT_0120588c = DAT_0120587c;
    DAT_01205898 = DAT_01205880;

    // Create Direct3D9 interface if not already created
    if (DAT_012058cc == 0) {
        DAT_012058cc = Direct3DCreate9(0x20); // D3D_SDK_VERSION
    }

    // Attempt to create a device with specific parameters
    int result = (**(code **)(*DAT_012058cc + 0x40))(DAT_012058cc, DAT_0120575c, 1, DAT_012058b4);
    if ((result >= 0) && (DAT_01205750 != 0)) {
        // Device created successfully
        if (DAT_012058cc == 0) {
            DAT_012058cc = Direct3DCreate9(0x20);
        }
        // Get device capabilities? (offset 0x20 = GetDeviceCaps)
        (**(code **)(*DAT_012058cc + 0x20))(DAT_012058cc, DAT_0120575c, &puStack_34);

        // Determine fullscreen or windowed mode
        if ((DAT_011d91a8 != 0) || (DAT_011d91bc & 2) == 0) {
            DAT_0120575a = 1;   // fullscreen
        } else {
            DAT_0120575a = 0;   // windowed
        }

        if (DAT_012058cc == 0) {
            DAT_012058cc = Direct3DCreate9(0x20);
        }
        // Second device creation attempt with different flags
        int result2 = (**(code **)(*DAT_012058cc + 0x28))
                    (DAT_012058cc, DAT_0120575c, 1, puStack_34, 0x100000, 3, 0x72);
        DAT_0120575b = (result2 >= 0); // success flag

        // Set some engine globals
        DAT_00f15a3b = DAT_00f15a39;
        DAT_00f15a48 = -(uint)(DAT_00f15a39 != 0) & 2;

        // Post-initialization
        FUN_0060f1f0();

        // Set rendering state (likely SetRenderState with D3DRS_FILLMODE=8)
        (**(code **)(*DAT_01205750 + 0x1d8))(DAT_01205750, 8, &DAT_01205754);
    } else {
        // Device creation failed, call error handler
        (*(code *)PTR_FUN_00f15a3c)(1);
    }
}