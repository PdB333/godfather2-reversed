// FUNC_NAME: DataParser::parseStream
void __thiscall DataParser::parseStream(void *this, uint streamHandle)
{
    char isDone;
    uint tokenType;
    int dataPtr;
    int value;

    // Initialize stream and check magic
    FUN_0046c710(streamHandle);
    FUN_0043aff0(streamHandle, 0xe801bfe5); // Magic number check

    // Main parse loop
    isDone = FUN_0043b120(); // Check if end of stream?
    while (isDone == '\0') {
        FUN_0043b210(); // Advance to next token?
        tokenType = FUN_0043ab70(); // Get token type
        switch (tokenType) {
        case 0:
            // Token type 0: possibly a string or resource reference
            dataPtr = FUN_0043b210();
            if (*(int *)(dataPtr + 8) != 0) {
                FUN_00408680(&DAT_0120e93c); // Log or handle error?
            }
            break;
        case 1:
            // Token type 1: set string at offset +0x50
            FUN_0043b210();
            value = FUN_0043ab90(); // Get integer value
            FUN_004089b0((int)this + 0x50, value); // Set string/ID
            break;
        case 2:
            // Token type 2: set string at offset +0x58
            FUN_0043b210();
            value = FUN_0043ab90();
            FUN_004089b0((int)this + 0x58, value);
            break;
        case 3:
            // Token type 3: handle callback or object creation
            FUN_0043b210();
            value = FUN_0043ab90(); // Get a value (maybe object ID)
            if (value == 0) {
                // Clear callback if value is zero
                if (*(int *)((int)this + 0x6c) != 0) {
                    // Call destructor or cleanup function at +0x78
                    (*(code **)((int)this + 0x78))(*(int *)((int)this + 0x6c));
                }
                *(int *)((int)this + 0x6c) = 0;
                *(int *)((int)this + 0x74) = 0;
                *(int *)((int)this + 0x70) = 0;
            } else {
                FUN_004d3d90(value); // Create or initialize object
            }
            break;
        case 4:
            // Token type 4: set value at offset +0x60
            dataPtr = FUN_0043b210();
            *(int *)((int)this + 0x60) = *(int *)(dataPtr + 8);
            break;
        case 5:
            // Token type 5: set value at offset +0x64 (100 decimal)
            dataPtr = FUN_0043b210();
            *(int *)((int)this + 100) = *(int *)(dataPtr + 8);
            break;
        case 6:
            // Token type 6: set value at offset +0x68
            dataPtr = FUN_0043b210();
            *(int *)((int)this + 0x68) = *(int *)(dataPtr + 8);
            break;
        }
        FUN_0043b1a0(); // Advance to next token?
        isDone = FUN_0043b120(); // Check if end of stream
    }
    return;
}