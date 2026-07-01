// Xbox PDB: EARS_Apt_UIPlayerFamilyTree_StrategyGame_DeselectMemberForAction
// FUNC_NAME: PlayerCrewLeaderComponent::deselectMember

void __fastcall PlayerCrewLeaderComponent::deselectMember(PlayerCrewLeaderComponent* this)
{
    // Base pointer for crew member data array (global)
    // +0x18 offset to skip some header, + memberIndex * 0x24 (size of member struct)
    uint* memberFlags = (uint*)(gMemberArrayBase + 0x18 + *(int*)(this + 0x6c) * 0x24);

    if (memberFlags != nullptr)
    {
        // Clear the "selected" flag (bit 2 – 0xfffffffb clears bit 2)
        *memberFlags = *memberFlags & 0xfffffffb;

        // Mark this member as not selected (byte at +0x128 in this component)
        *(byte*)(this + 0x128) = 0;

        // Broadcast "MemberDeselected" event (likely through EventScheduler or similar)
        FUN_005a04a0("MemberDeselected", 0, &DAT_00d8fe44, 0);

        // Update UI or state after deselect
        FUN_00981060();
    }
}