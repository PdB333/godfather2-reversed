// FUNC_NAME: CrewLeaderComponent::processNextCrewMember
void __fastcall CrewLeaderComponent::processNextCrewMember(CrewLeaderComponent* this)
{
    // Iterator structure (size 0x1C)
    struct CrewMemberIterator {
        void* vtable;          // +0x00
        int field_4;           // +0x04
        CrewMember* found;     // +0x08 - set by initializeIterator if a member is found
        int field_C;           // +0x0C
        void* toFree;          // +0x10 - pointer to be freed later
        int field_14;          // +0x14
        int field_18;          // +0x18
    } iter;

    // Initialize iterator with global vtable
    iter.vtable = (void*)DAT_00e44758;
    iter.field_4 = 0;
    iter.found = nullptr;
    iter.field_C = 0;
    iter.toFree = nullptr;
    iter.field_14 = 0;
    iter.field_18 = 0;

    // Release global resource (null check)
    FUN_009c8f10(nullptr);

    iter.toFree = nullptr;
    iter.field_18 = 0;

    // Initialize iterator to find the next crew member
    FUN_008c59e0(&iter, 1, 0);

    if (iter.found != nullptr) {
        // Process the found crew member
        FUN_008c4190(&iter);

        // Access the crew member at index (this->crewMemberIndex - 1)
        // this+0x130: base pointer to crew member array (each 0x1C bytes)
        // this+0x134: current index (1-based)
        int* base = *(int**)((char*)this + 0x130);
        int index = *(int*)((char*)this + 0x134);
        int* memberAddr = base + (index - 1) * 0x1C; // equivalent to base - 0x1C + index * 0x1C
        FUN_008c62e0(memberAddr);
    }

    if (iter.toFree != nullptr) {
        FUN_009c8f10(iter.toFree);
    }
}