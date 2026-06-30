// FUNC_NAME: SequenceManager::initSequenceSlots
void __fastcall SequenceManager::initSequenceSlots(SequenceManager* this)
{
    // Calls base initializer or general reset function
    BaseClass::reset();

    // Global static value used for initializing sequence slot fields
    uint32_t initialSeqValue = DAT_00e2b1a4;

    // Initialize the main sequence slot (index 0)
    this->mainSequence = initialSeqValue;

    // Initialize the secondary sequence slots at offsets 5 and 10 (each slot is 4 bytes)
    // These likely represent separate sequence counters for different message types
    this->ackedSequence = initialSeqValue;  // +20 (slot 5)
    this->sentSequence  = initialSeqValue;  // +40 (slot 10)
}