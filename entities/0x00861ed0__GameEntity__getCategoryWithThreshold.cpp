// FUNC_NAME: GameEntity::getCategoryWithThreshold

uint __fastcall GameEntity::getCategoryWithThreshold(GameEntity* this)
{
    uint category = this->vtable->GetSomeFloatProperty(this); // vtable+0x1a8 returns float, sets FPU ST0
    if ( (float)extraout_ST0 < g_fMaxSomeValue ) // 0x00d75758
    {
        category = g_uDefaultCategory; // 0x012233a0
    }
    return category & 0xffffff00;
}