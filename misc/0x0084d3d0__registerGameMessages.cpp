// FUNC_NAME: registerGameMessages
void registerGameMessages(void)
{
    // Register message types for damage and explosion knowledge
    FUN_00408240(&DAT_0112dd94, "iMsgDamage");
    FUN_00408240(&DAT_0112dd8c, "iMsgExplosionKnowledge");
    return;
}