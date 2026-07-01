// FUNC_NAME: Sentient::Sentient

Sentient* __thiscall Sentient::Sentient(Sentient* this, byte aFlag)
{
    // Call base class constructor (likely Entity or SimBase)
    FUN_00816660(); // +0x0 base initialization
    // Optional extra initialization for derived types (e.g., enable senses)
    if (aFlag & 1)
    {
        FUN_009c8eb0(this); // additional setup
    }
    return this;
}