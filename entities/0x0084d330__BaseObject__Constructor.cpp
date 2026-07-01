// FUNC_NAME: BaseObject::Constructor
// Function at 0x0084d330: Constructor for a base game object, initializes many fields to 0 and sets a flag at +0x40 to 1.
// Called from multiple places, likely part of Entity or Sentient hierarchy.

int __thiscall BaseObject::Constructor(BaseObject* thisPtr)
{
    // Likely clears some internal buffers or resets subsystems (e.g., audio, scripting)
    someClearFunction(0);
    someClearFunction(0);

    // Zero out a block of fields (offsets from 0x28 to 0x3c)
    thisPtr->m_field28 = 0;    // +0x28
    thisPtr->m_field2C = 0;    // +0x2c
    thisPtr->m_field30 = 0;    // +0x30
    thisPtr->m_field34 = 0;    // +0x34
    thisPtr->m_field38 = 0;    // +0x38
    thisPtr->m_field3C = 0;    // +0x3c

    // Set a flag to true (e.g., isActive, isEnabled)
    thisPtr->m_flag40 = 1;     // +0x40

    // Zero out another block (offsets 0x10–0x24)
    thisPtr->m_field10 = 0;    // +0x10
    thisPtr->m_field14 = 0;    // +0x14
    thisPtr->m_field18 = 0;    // +0x18
    thisPtr->m_field1C = 0;    // +0x1c
    thisPtr->m_field20 = 0;    // +0x20
    thisPtr->m_field24 = 0;    // +0x24

    return (int)thisPtr;
}