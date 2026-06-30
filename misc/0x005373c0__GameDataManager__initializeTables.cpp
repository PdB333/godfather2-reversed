// FUNC_NAME: GameDataManager::initializeTables
void __fastcall GameDataManager::initializeTables(int this_)
{
    // pre-initialization setup
    FUN_00537150(); // Likely clears tables or sets default values

    // Generate 6 unique IDs at offset 0x12C0 (tableA)
    uint32_t* tableA = (uint32_t*)(this_ + 0x12C0);
    for (int i = 0; i < 6; i++) {
        *tableA = FUN_0060a380(); // generateUniqueId
        tableA++;
    }

    // Generate 24 unique IDs at offset 0x12D8 (tableB)
    uint32_t* tableB = (uint32_t*)(this_ + 0x12D8);
    for (int i = 0; i < 24; i++) {
        *tableB = FUN_0060a380(); // generateUniqueId
        tableB++;
    }

    // Generate 32 hashed IDs from global string table at offset 0x1338 (tableC)
    // The global pointer array PTR_PTR_01128200 has 32 entries (0x80/4)
    uint32_t* tableC = (uint32_t*)(this_ + 0x1338);
    for (int i = 0; i < 32; i++) {
        // Each global pointer points to a string or resource
        *tableC = FUN_0060a2e0(*(uint32_t*)((int)&PTR_PTR_01128200 + i * 4)); // getStringHash
        tableC++;
    }

    // Fill tableD (offset 0xE38) with 24 rows of 12 columns
    // Uses tableA and a global data array (PTR_DAT_010bdfc0)
    uint32_t* rowD = (uint32_t*)(this_ + 0xE38);
    uint32_t* tableA_ptr = (uint32_t*)(this_ + 0x12C0);
    int globalOffset = (int)&PTR_DAT_010bdfc0 - this_; // offset from this to global data
    for (int row = 0; row < 24; row++) {
        for (int col = 0; col < 12; col++) {
            uint32_t globalVal = *(uint32_t*)(globalOffset + (uint32_t)rowD);
            *rowD = FUN_0060a580(*tableA_ptr, globalVal); // combine IDs
            rowD++;
        }
        tableA_ptr++;
        globalOffset -= 0x30; // move to next row in global data (12*4=0x30? but -0x30 makes sense across rows in opposite direction)
    }

    // Fill tableE (offset 0xD30) with 6 rows of 11 columns
    // Uses tableA (again starting from first ID) and another global array (PTR_DAT_010be054)
    uint32_t* rowE = (uint32_t*)(this_ + 0xD30);
    tableA_ptr = (uint32_t*)(this_ + 0x12C0);
    globalOffset = (int)&PTR_DAT_010be054 - this_;
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 11; col++) {
            uint32_t globalVal = *(uint32_t*)(globalOffset + (uint32_t)rowE);
            *rowE = FUN_0060a580(*tableA_ptr, globalVal);
            rowE++;
        }
        tableA_ptr++;
        globalOffset -= 0x2C; // move to next row (11*4 = 0x2C)
    }

    // Fill tableF (offset 0x7A4) with 32 rows of 11 columns
    // Uses tableC and global array (PTR_DAT_010be684)
    uint32_t* rowF = (uint32_t*)(this_ + 0x7A4);
    uint32_t* tableC_ptr = (uint32_t*)(this_ + 0x1338);
    globalOffset = (int)&PTR_DAT_010be684 - this_;
    for (int row = 0; row < 32; row++) {
        for (int col = 0; col < 11; col++) {
            uint32_t globalVal = *(uint32_t*)((uint32_t)rowF + globalOffset);
            *rowF = FUN_0060a580(*tableC_ptr, globalVal);
            rowF++;
        }
        tableC_ptr++;
        globalOffset -= 0x2C;
    }

    // Fill tableG (offset 0x664) with 8 rows of 5 columns and call virtual function
    // Uses tableC (points to pairs? Since row step is 2 elements in tableC)
    uint32_t* vtableArray = (uint32_t*)(this_ + 0xA4); // array of vtable pointers? offset 0xA4
    uint32_t* rowG = (uint32_t*)(this_ + 0x664);
    uint32_t* tableC_pair = (uint32_t*)(this_ + 0x1378); // each row uses two consecutive tableC entries? (offset 0x1378)
    globalOffset = (int)&PTR_DAT_010be7f0 - this_;
    for (int row = 0; row < 8; row++) {
        uint32_t* rowStart = rowG;
        for (int col = 0; col < 5; col++) {
            uint32_t globalVal = *(uint32_t*)(globalOffset + (uint32_t)rowStart);
            *rowStart = FUN_0060a580(*tableC_pair, globalVal); // uses first element of the pair
            rowStart++;
        }
        // Call virtual function on the second element of the pair (index 1? Actually *tableC_pair is used, then tableC_pair points to next element? Wait: at end of row, line: (**(code**)(*vtableArray + 4))(*tableC_pair); 
        // vtableArray is incremented by 0x2e*4 = 0xB8 each row? piVar5 += 0x2e (in int units) but that's huge. Actually piVar5 = (int*)(this_+0xA4) and then piVar5 = piVar5 + 0x2e; that steps by 0x2e*4 bytes. Might be a pointer to some object array.
        // For simplicity, we'll represent as:
        void (**vtable)(void*) = *(void (***)(void*))(this_ + 0xA4 + row * 0xB8); // assuming vtable array with stride 0xB8
        if (vtable) {
            vtable[1]( (void*)*tableC_pair ); // call second virtual function on the pointer
        }
        rowG += 10; // next row offset by 10*4 = 40 bytes
        tableC_pair += 2; // move to next pair in tableC
        globalOffset -= 0x28; // adjust for next row's global data stride
    }
}