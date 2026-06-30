// FUNC_NAME: CharacterAppearance::updateTeamColor
void __thiscall CharacterAppearance::updateTeamColor(int this, void* colorOutput) {
    // Local color arrays (8 fields, likely two RGBA colors)
    int colorA[4]; // local_30, local_2c, local_28, local_24
    int colorB[4]; // local_20, local_1c, local_18, local_14

    // Initialize default values
    colorA[0] = 0;
    colorA[1] = 0;
    colorA[2] = 0;
    colorA[3] = DAT_00e2b1a4; // Global default alpha/color component

    colorB[0] = 0;
    colorB[1] = 0;
    colorB[2] = 0;
    colorB[3] = DAT_00e2b1a4;

    // Call some color calculation/setup function (likely blends or sets defaults)
    FUN_00593210(colorA, in_EAX); // in_EAX might be a hidden parameter (e.g., ID)

    // Get the appearance data pointer (stored at this+0x04)
    int* appearanceData = *(int**)(this + 4);

    // Determine if the character is "young" (age/variant < 10) or "adult"
    int* selectedColor;
    if ((*(unsigned char*)(appearanceData + 1) & 0xFF) < 10) { // (byte)(*(int*)(appearanceData+4)) & 0xFF
        selectedColor = (int*)(appearanceData + 3); // +0x0c
    } else {
        selectedColor = (int*)(appearanceData + 8); // +0x20
    }

    // Apply the selected color to the output
    FUN_00586df0(colorOutput, selectedColor);
}