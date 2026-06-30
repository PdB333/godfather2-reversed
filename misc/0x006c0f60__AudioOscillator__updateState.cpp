// FUNC_NAME: AudioOscillator::updateState
void __thiscall AudioOscillator::updateState(AudioOscillator* this, float param2, float param3, float param4)
{
    // param2: likely phase/frequency index
    // param3: amplitude/gain
    // param4: additional mod factor

    float fVar1;
    float fVar2;
    uint uVar3;
    float10 fVar4;
    float fVar5;
    float fVar6;

    // Compute envelope or waveform sample from external function
    fVar4 = (float10)FUN_006c91c0(param2, 
                                  _DAT_00e50e70,   // unknown constants
                                  _DAT_00e50e74,
                                  _DAT_0112a780,
                                  _DAT_00e50f50);

    fVar2 = DAT_00d5eee4;          // some base coefficient
    fVar1 = _DAT_00d5780c;         // often 1.0
    fVar6 = (DAT_00e50f4c * param2 + _DAT_00e50f48) * param2 * DAT_00e445a4; // quadratic in param2

    // Update output at +0x50 (e.g., channel 0 or main output)
    this->field_0x50 = (float)((fVar4 * (float10)param3 + (float10)_DAT_00d5780c) *
                               (float10)this->field_0x50);

    uVar3 = DAT_010c2678 & DAT_012054b4;  // bitmask to index a table
    // Lookup next table entry and compute fVar5 (sawtooth or sine derivative)
    fVar5 = (*(float*)(&DAT_010c2680 + (DAT_010c2678 & (DAT_012054b4 + 1)) * 4) * fVar2 - fVar1) *
            _DAT_00e50f40;

    DAT_012054b4 = DAT_012054b4 + 2; // advance phase by 2

    // Update +0x40 (left channel) and +0x44 (right channel) using table and envelope
    this->field_0x40 = ((*(float*)(&DAT_010c2680 + uVar3 * 4) * fVar2 - fVar1) *
                        _DAT_00e50f44 * fVar6 * param4 + fVar1) * this->field_0x40;
    this->field_0x44 = (fVar5 * fVar6 * param4 + fVar1) * this->field_0x44;
}