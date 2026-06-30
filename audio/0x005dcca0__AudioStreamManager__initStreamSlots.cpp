// FUNC_NAME: AudioStreamManager::initStreamSlots
// Function at 0x005dcca0 initializes 5 stream slot structures with fixed magic values,
// default sample rate (96000), and other fields. It then calls three initialization functions.
// The object is likely part of EARS audio stream management, handling up to 5 concurrent streams.

void AudioStreamManager::initStreamSlots(void)
{
    uint32_t globalVal1 = DAT_00e2b1a4; // likely some global config value (e.g., buffer size)
    uint32_t globalVal2 = DAT_00e2b118; // another global config
    StreamSlot* slot;
    int i;

    i = 4; // iterate 5 times (slots 0..4)
    slot = &this->streamSlots[0]; // +0x18: slot base pointer (first slot starts at offset 0x18 from this)
    do {
        // Initialize fields relative to current slot
        slot->field0x18 = 0xeac15a55;              // +0x18: first dword of slot
        slot->field0x00 = globalVal1;              // -0x18 -> offset 0
        slot->field0x04 = globalVal1;              // -0x14 -> offset 4
        slot->field0x28 = globalVal1;              // +0x28
        slot->field0x2C = globalVal1;              // +0x2C
        slot->field0x44 = 96000;                   // +0x44: likely sample rate
        slot->field0x4C = 96000;                   // +0x4C: another sample rate
        slot->byte0x21 = 0;                        // byte at +0x21
        slot->byte0x22 = 0;                        // byte at +0x22
        slot->field0x08 = 0;                       // +0x08
        slot->field0x24 = 0;                       // +0x24
        slot->field0x30 = 0;                       // +0x30
        slot->field0x34 = 0;                       // +0x34
        slot->field0x48 = 0;                       // +0x48
        slot->byte0x23 = 0;                        // byte at +0x23
        slot->field0x0C = 1;                       // +0x0C: likely some flag or counter
        slot->field0x10 = 0xbadbadba;              // +0x10: sentinel
        slot->field0x14 = 0xbeefbeef;              // +0x14: sentinel
        slot->field0x18 = 0xeac15a55;              // +0x18: re-written (first dword again)
        slot->field0x1C = 0x91100911;              // +0x1C: sentinel
        slot->field0x38 = globalVal2;              // +0x38: from globalVal2
        slot->field0x3C = globalVal1;              // +0x3C: from globalVal1
        slot->field0x50 = 0;                       // +0x50
        slot->field0x54 = 0;                       // +0x54
        slot->field0x58 = 0;                       // +0x58
        slot->field0x5C = 0;                       // +0x5C
        slot->field0x60 = 0;                       // +0x60
        slot->field0x64 = 0;                       // +0x64

        // Advance to next slot (0x1a dwords = 0x68 bytes per slot)
        slot = (StreamSlot*)((uint8_t*)slot + 0x68);
        i--;
    } while (i >= 0);

    // Initialize additional fields after the 5 slots
    this->field0x218 = 0xbadbadba; // sentinel
    this->field0x21C = 0xbeefbeef; // sentinel
    this->field0x220 = 0xeac15a55; // sentinel
    this->field0x224 = 0x91100911; // sentinel

    // Call initialization functions
    uint32_t retVal = FUN_005dd030(); // returns a value (likely a handle or manager address)
    this->field0x270 = retVal;
    this->field0x274 = retVal;
    this->field0x278 = retVal;
    this->field0x2A0 = retVal;
    this->field0x2A4 = retVal;
    this->field0x2A8 = retVal;
    this->field0x2AC = retVal;

    FUN_005dce60(); // subsequent initialization
    FUN_005e18b0(); // final setup

    return;
}