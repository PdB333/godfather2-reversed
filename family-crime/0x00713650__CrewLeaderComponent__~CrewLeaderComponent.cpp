// FUNC_NAME: CrewLeaderComponent::~CrewLeaderComponent
// Address: 0x00713650
// Role: Destructor for CrewLeaderComponent, cleans up crew member pointers array and other resources.

void __fastcall CrewLeaderComponent::~CrewLeaderComponent(CrewLeaderComponent* this)
{
    // Set vtable to base class pointer to prevent virtual calls during destruction
    this->vtable = &PTR_FUN_00d61a40; // +0x00: base vtable

    // Release synchronization objects (mutexes)
    FUN_004086d0(&DAT_0112dd08); // release global lock 1
    FUN_004086d0(&DAT_0112ac90); // release global lock 2

    // Clean up array of 8 crew member pointers at offset 0x134-0x150
    int* pSlot = reinterpret_cast<int*>(&this->m_crewMembers) + 7; // start at last slot (offset 0x150)
    int count = 7;
    do {
        int* pPrev = pSlot - 1; // offset 0x14C, etc.
        pSlot = pSlot - 1;      // move to previous slot
        if (*pPrev != 0) {
            FUN_004daf90(pSlot); // release the object pointed to by pSlot
        }
        count = count - 1;
    } while (count >= 0);

    // Release optional additional pointer at offset 0x18
    if (this->m_pExtraData != 0) { // +0x18
        FUN_004daf90(&this->m_pExtraData);
    }

    // Set another resource pointer to a sentinel value
    this->m_pSomeData = &PTR_LAB_00e2f0c0; // +0x14

    // Set vtable to final base class (likely root class)
    this->vtable = &PTR_FUN_00d61a08; // +0x00

    // Perform final cleanup (e.g., destroy base class)
    FUN_004083d0();
}