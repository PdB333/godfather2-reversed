// FUNC_NAME: ResourceHashManager::registerDefaults

void ResourceHashManager::registerDefaults(uint param_1) {
    // Register three hash IDs with the manager (likely triggers some initialization)
    FUN_00690530(0x64ce24d7, param_1);
    FUN_00690530(0x657a83a5, param_1);
    FUN_00690530(0xa08a43df, param_1);

    // Look up a data table by two hash keys (0xa7879506, 0xf0c639eb)
    int* dataTable = nullptr;
    FUN_004979c0(&dataTable, 0xa7879506, 0xf0c639eb);
    if (dataTable != nullptr) {
        // Set string data for command 0x1f (string at offset +0x90c10, length 0x41)
        char* str1 = FUN_0049a700(nullptr, &LAB_00690c10, 0x41, 1);
        ((void (*)(int, char*))(*dataTable + 4))(0x1f, str1);  // vtable call: set(0x1f, str1)
        FUN_00497960(0x776def75, dataTable, 0x1f);  // store this assignment

        // Set string data for command 0x21
        char* str2 = FUN_0049a700(nullptr, &LAB_00690c60, 0x23, 1);
        ((void (*)(int, char*))(*dataTable + 4))(0x21, str2);
        FUN_00497960(0xf0c639eb, dataTable, 0x21);

        // Set integer data for commands 0x28, 0x29, 0xd, 0xc
        int val1 = FUN_0049a640(nullptr);
        ((void (*)(int, int))(*dataTable + 4))(0x28, val1);
        FUN_00497960(0x776def75, dataTable, 0x28);

        int val2 = FUN_0049a640(nullptr);
        ((void (*)(int, int))(*dataTable + 4))(0x29, val2);
        FUN_00497960(0x78467823, dataTable, 0x29);

        int val3 = FUN_0049a640(nullptr);
        ((void (*)(int, int))(*dataTable + 4))(0xd, val3);
        FUN_00497960(0x1d8e854d, dataTable, 0xd);

        int val4 = FUN_0049a640(nullptr);
        ((void (*)(int, int))(*dataTable + 4))(0xc, val4);
        FUN_00497960(0xc1e9c75, dataTable, 0xc);
    }

    // Register three more hash IDs
    FUN_00690530(0x17a26743, param_1);
    FUN_00690530(0x6ef11ea8, param_1);
    FUN_00690530(0xbe16155b, param_1);

    if (dataTable != nullptr) {
        // Register string data for commands 0x15..0x1e using a fixed data buffer DAT_00691950
        // Each entry has a different length (8,5,9,1,2,4,3,0,6,7)
        static const char* dataBuffer = &DAT_00691950;  // base address of buffer
        int lenTable[] = {8,5,9,1,2,4,3,0,6,7};
        for (int i = 0; i < 10; i++) {
            char* str = FUN_0049a700(nullptr, dataBuffer + (i * ???), lenTable[i], 1);
            // The actual offset in the buffer is not explicitly computed; it seems to be sequential per allocation.
            // Each call returns a pointer to the allocated substring.
            // For simplicity, we perform the calls as in original: separate calls with same base but different length.
            // TODO: The exact buffer offsets are not reconstructed; this loop is conceptual.
        }
        // The original code called FUN_0049a700 10 separate times with varying lengths.
        // We'll reconstruct each call individually for fidelity.
        {
            char* s = FUN_0049a700(nullptr, &DAT_00691950, 8, 1);
            ((void (*)(int, char*))(*dataTable + 4))(0x15, s);
            FUN_00497960(0xc4aacd36, dataTable, 0x15);
        }
        {
            char* s = FUN_0049a700(nullptr, &DAT_00691950, 5, 1);
            ((void (*)(int, char*))(*dataTable + 4))(0x16, s);
            FUN_00497960(0xc4aacd37, dataTable, 0x16);
        }
        {
            char* s = FUN_0049a700(nullptr, &DAT_00691950, 9, 1);
            ((void (*)(int, char*))(*dataTable + 4))(0x17, s);
            FUN_00497960(0xc4aacd38, dataTable, 0x17);
        }
        {
            char* s = FUN_0049a700(nullptr, &DAT_00691950, 1, 1);
            ((void (*)(int, char*))(*dataTable + 4))(0x18, s);
            FUN_00497960(0xc4aacd39, dataTable, 0x18);
        }
        {
            char* s = FUN_0049a700(nullptr, &DAT_00691950, 2, 1);
            ((void (*)(int, char*))(*dataTable + 4))(0x19, s);
            FUN_00497960(0xc4aacd3a, dataTable, 0x19);
        }
        {
            char* s = FUN_0049a700(nullptr, &DAT_00691950, 4, 1);
            ((void (*)(int, char*))(*dataTable + 4))(0x1a, s);
            FUN_00497960(0xc4aacd3b, dataTable, 0x1a);
        }
        {
            char* s = FUN_0049a700(nullptr, &DAT_00691950, 3, 1);
            ((void (*)(int, char*))(*dataTable + 4))(0x1b, s);
            FUN_00497960(0xc4aacd3c, dataTable, 0x1b);
        }
        {
            char* s = FUN_0049a700(nullptr, &DAT_00691950, 0, 1);
            ((void (*)(int, char*))(*dataTable + 4))(0x1c, s);
            FUN_00497960(0xc4aacd3d, dataTable, 0x1c);
        }
        {
            char* s = FUN_0049a700(nullptr, &DAT_00691950, 6, 1);
            ((void (*)(int, char*))(*dataTable + 4))(0x1d, s);
            FUN_00497960(0xc4aacd3e, dataTable, 0x1d);
        }
        {
            char* s = FUN_0049a700(nullptr, &DAT_00691950, 7, 1);
            ((void (*)(int, char*))(*dataTable + 4))(0x1e, s);
            FUN_00497960(0xc4aacd3f, dataTable, 0x1e);
        }
    }

    // Register final hash ID
    FUN_00690530(0xebc77d43, param_1);
}