// Xbox PDB: EARS_Apt_UIHudEventQueue_AddCrewRecruitedMessage
// FUNC_NAME: FamilyManager::onNewFamilyMemberAdded
// Address: 0x0093ee00
// Role: Handles fanfare/notification when a new family member is added to the family.
// Calls: AudioManager::playSoundEvent, FamilyManager::getFamilyMemberID, StringBufferManager utilities

#include <alloca.h> // for __alloca_probe

void FamilyManager::onNewFamilyMemberAdded(Entity* pNewMember)
{
    // Global flags: (DAT_01129904 + 0x3c) -> g_bFanfareEnabled
    // (DAT_012234a4) -> g_pFanfareFormatString (e.g. "fanfare_new_name_format")
    // (DAT_0120546e) -> empty string placeholder

    if (pNewMember != nullptr && *(char*)(DAT_01129904 + 0x3c) != '\0')
    {
        AudioManager::playSoundEvent("$fanfare_new_family_member_added");

        int memberIndex = FamilyManager::getFamilyMemberID(pNewMember); // Returns -1 if invalid

        // local_1020: likely a global flag or status from SoundManager
        // Assuming it's always true when the first condition passes
        if (g_bFanfareCanPlay && memberIndex != -1)
        {
            StringBufferManager::pushBufferContext();
            char* pBuffer = StringBufferManager::getCurrentBuffer();
            if (pBuffer == nullptr)
                pBuffer = &g_emptyString; // DAT_0120546e

            StringBufferManager::setBufferSize(0x72, pBuffer); // Possibly 114 bytes

            // Locals used for sprintf parameters
            int charsWritten = 0;
            int unknownArg2 = 0;
            int unknownArg3 = 0;
            code* pCallback = nullptr;

            char* pNameArg = pFamilyMemberName; // local_1024, source of name string
            if (pNameArg == nullptr)
                pNameArg = &g_emptyString;

            StringBufferManager::formatString(
                g_pFanfareFormatString, // uVar1
                (char*)alloca(4112),    // local_1014 large buffer
                &charsWritten,
                pNameArg
            );

            if (unknownArg2 != 0)
            {
                // Process fanfare with the formatted string
                FamilyManager::triggerFanfare(&charsWritten, memberIndex);
            }

            if (charsWritten != 0 && pCallback != nullptr)
            {
                pCallback(charsWritten);
            }

            StringBufferManager::popBufferContext();
        }

        // If pFamilyMemberName (local_1024) was dynamically allocated, free it
        if (local_1024 != nullptr)
        {
            unknownFreeFunc(local_1024);
        }
    }
}