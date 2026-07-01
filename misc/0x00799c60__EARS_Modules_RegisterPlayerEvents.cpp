// Xbox PDB: EARS_Modules_RegisterPlayerEvents
// FUNC_NAME: registerPlayerMessages

void registerPlayerMessages(void)
{
    // Register player-related internal messages for the messaging system.
    FUN_00408240(&DAT_0112b53c, "iMsgPlayerInitialized");
    FUN_00408240(&DAT_0112b394, "iMsgPlayerMovedInsideToOutside");
    FUN_00408240(&DAT_0112b8fc, "iMsgPlayerMovedOutsideToInside");
    FUN_00408240(&DAT_0112b344, "iMsgPlayerTeleportDoneExceptFade");
    FUN_00408240(&DAT_0112b38c, "iMsgPlayerPhoneStart");
    FUN_00408240(&DAT_0112b574, "iMsgPlayerPhoneEnd");
    FUN_00408240(&DAT_0112b2ac, PTR_s_vibration__play_00e527f4);        // "vibration__play"
    FUN_00408240(&DAT_0112b2bc, PTR_s_item_switch_00e527f8);            // "item_switch"
    FUN_00408240(&DAT_0112b354, PTR_s_execution_end_00e527fc);          // "execution_end"
    FUN_00408240(&DAT_0112b514, PTR_s_special_tommygun_use_00e52800);   // "special_tommygun_use"
    FUN_00408240(&DAT_0112b35c, PTR_s_paired_player_detach_00e52804);   // "paired_player_detach"
    FUN_00408240(&DAT_0112b55c, PTR_s_paired_player_unlock_00e52808);   // "paired_player_unlock"
}