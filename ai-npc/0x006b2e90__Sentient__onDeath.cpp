// FUNC_NAME: Sentient::onDeath
void __fastcall Sentient::onDeath(int this)
{
    // +0xd8: pointer to a death handler or corpse manager (only active if not null)
    if (*(int *)(this + 0xd8) != 0) {
        // Check if the game is still active (DAT_0112afb8 likely the global game state)
        if (sub_43b870(DAT_0112afb8) != 0) {
            // Stop input vibration or sounds for this character (DAT_00d5e288 = controller/audio manager)
            sub_78b4b0(DAT_00d5e288, 0, 1);
        }
    }
    // Set the "dead" flag in the object's state flags (+0x34)
    *(unsigned int *)(this + 0x34) |= 0x2000000;
}