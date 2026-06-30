// FUNC_NAME: WeatherManager::updateWeatherTransition
void WeatherManager::updateWeatherTransition()
{
    // Check if weather conditions (snow, rain, maybe thunder) are active and if the current time is within transition bounds
    // DAT_01219880, DAT_012198b0, DAT_012198e0 are weather intensity factors (snow, rain, thunder?)
    // DAT_00e2af44 is current time or timer
    // _DAT_0121986c, _DAT_0121989c, _DAT_012198cc are transition thresholds
    if (((DAT_01219880 != 0.0f && DAT_00e2af44 <= _DAT_0121986c) ||
         (DAT_012198b0 != 0.0f && DAT_00e2af44 <= _DAT_0121989c) ||
         (DAT_012198e0 != 0.0f && DAT_00e2af44 <= _DAT_012198cc)) &&
        // Ensure current weather state index is valid
        (DAT_011f38f0 < 0x1000 &&
         (&DAT_011a0f28 + DAT_011f38f0 * 0x38 != nullptr &&
          2 < *(byte *)(&DAT_011a0f28 + DAT_011f38f0 * 0x38)))) {

        // If already in target weather state and no transition in progress
        if (DAT_011f38f0 == DAT_01218e58 && DAT_011f38f4 == 0) {
            FUN_00609890(1); // Set weather state to active
        } else {
            FUN_0060df60(DAT_011f38f0, DAT_01218e58); // Transition between states
        }

        // Adjust various weather parameters to predefined values
        clampMin(&DAT_012058d0, 0x16); // 22
        clampMax(&DAT_00f15988, 0x16);
        _DAT_011f3a30 = 1;

        clampMin(&DAT_012058d0, 7);
        clampMax(&DAT_00f15988, 7);
        _DAT_011f39f4 = 0;

        clampMin(&DAT_012058d0, 0x19); // 25
        clampMax(&DAT_00f15988, 0x19);
        _DAT_011f3a3c = 5;

        clampMin(&DAT_012058d0, 0x18); // 24
        clampMax(&DAT_00f15988, 0x18);
        _DAT_011f3a38 = 0;

        clampMin(&DAT_012058d0, 0xf); // 15
        clampMax(&DAT_00f15988, 0xf);
        _DAT_011f3a14 = 0;

        clampMin(&DAT_012058d0, 0x1b); // 27
        clampMax(&DAT_00f15988, 0x1b);
        _DAT_011f3a44 = 1;

        FUN_00417cf0(1, 2, 1); // Enable post-processing effects (e.g., fog)

        // Update fog shader parameters
        DAT_0121b750 = DAT_01219908;
        DAT_0121b874 = 0;
        DAT_0121b754 = DAT_0121bbcc;

        if (DAT_0121bbcc == DAT_0121bbc0 || DAT_0121bbcc == DAT_0121bbc4 || DAT_0121bbcc == DAT_0121bbc8) {
            // Get fog shader handles
            DAT_0121bb7c = FUN_0060a580(DAT_0121bbcc, "fog_color");
            DAT_0121bb80 = FUN_0060a580(DAT_0121b754, "fog_params");
            DAT_0121bb84 = FUN_0060a580(DAT_0121b754, "depth_texture");
        }

        // Release previous fog shader if still using old one
        if (DAT_012058e8 == &DAT_0121b740) {
            FUN_0060a460(DAT_0121b754);
            FUN_0060a460(DAT_0121b750);
        }

        // Process weather layer updates (rain, snow, etc.)
        FUN_0053a5b0(); // Process rain particles?
        if (DAT_01219880 != DAT_00e2b05c && DAT_00e2af44 <= _DAT_0121986c) {
            float fVar3 = DAT_00e2b1a4 / DAT_01219880;
            _DAT_01219860 = fVar3 * _DAT_01219860;
            _DAT_01219864 = fVar3 * _DAT_01219864;
            _DAT_01219868 = fVar3 * _DAT_01219868;
            _DAT_0121986c = fVar3 * _DAT_0121986c;
            DAT_01219870 = DAT_01219870 * fVar3;
            DAT_01219874 = DAT_01219874 * fVar3;
        }
        FUN_0053a430(); // Process snow particles?
        if (DAT_012198b0 != DAT_00e2b05c && DAT_00e2af44 <= _DAT_0121989c) {
            float fVar3 = DAT_00e2b1a4 / DAT_012198b0;
            _DAT_01219890 = fVar3 * _DAT_01219890;
            _DAT_01219894 = fVar3 * _DAT_01219894;
            _DAT_01219898 = fVar3 * _DAT_01219898;
            _DAT_0121989c = fVar3 * _DAT_0121989c;
            DAT_012198a0 = DAT_012198a0 * fVar3;
            DAT_012198a4 = DAT_012198a4 * fVar3;
        }
        FUN_0053a4b0(); // Process thunder?
        FUN_0053a530(); // Process wind?
        FUN_005388a0(); // Process overall environment effects

        // Allocate and fill effect parameters (maybe for screen effects)
        uint32_t *puVar2 = (uint32_t *)FUN_0060cd00(5, 4, 0, 1, 0);
        if (puVar2 != nullptr) {
            puVar2[0] = DAT_00e2eff4;
            puVar2[1] = DAT_00e2eff4;
            puVar2[2] = DAT_00e2b1a4;
            puVar2[3] = DAT_00e2eff4;
            puVar2[4] = DAT_00e2eff4;
            puVar2[5] = DAT_00e2b1a4;
            puVar2[6] = DAT_00e2b1a4;
            puVar2[7] = DAT_00e2b1a4;
            FUN_0060cde0();
        }

        FUN_00539250(); // Final weather transition update

        // Apply second set of parameter adjustments for the new phase
        clampMin(&DAT_012058d0, 0x16);
        clampMax(&DAT_00f15988, 0x16);
        _DAT_011f3a30 = 1;

        clampMin(&DAT_012058d0, 7);
        clampMax(&DAT_00f15988, 7);
        _DAT_011f39f4 = 1;

        clampMin(&DAT_012058d0, 0x19);
        clampMax(&DAT_00f15988, 0x19);
        _DAT_011f3a3c = 7;

        clampMin(&DAT_012058d0, 0x18);
        clampMax(&DAT_00f15988, 0x18);
        _DAT_011f3a38 = 0;

        clampMin(&DAT_012058d0, 0xf);
        clampMax(&DAT_00f15988, 0xf);
        _DAT_011f3a14 = 0;

        clampMin(&DAT_012058d0, 0x1b);
        clampMax(&DAT_00f15988, 0x1b);
        _DAT_011f3a44 = 0;

        FUN_00417cf0(1, 5, 6); // Disable previous effects

        // Reset weather intensities to zero
        _DAT_01219860 = 0.0f;
        _DAT_01219864 = 0.0f;
        _DAT_01219868 = 0.0f;
        _DAT_0121986c = 0.0f;
        DAT_01219870 = 0.0f;
        DAT_01219874 = 0.0f;
        _DAT_01219890 = 0.0f;
        _DAT_01219894 = 0.0f;
        _DAT_01219898 = 0.0f;
        _DAT_0121989c = 0.0f;
        DAT_012198a0 = 0.0f;
        DAT_012198a4 = 0.0f;
        DAT_01219880 = 0.0f; // Snow intensity
        DAT_012198b0 = 0.0f; // Rain intensity
        DAT_012198e0 = 0.0f; // Thunder intensity
    }
}