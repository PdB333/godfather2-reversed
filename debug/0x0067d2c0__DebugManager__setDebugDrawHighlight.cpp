// FUNC_NAME: DebugManager::setDebugDrawHighlight
void DebugManager::setDebugDrawHighlight(void* entity)
{
    DebugManager* debugMgr = (DebugManager*)GetDebugManager(); // FUN_009c8f80 - returns singleton
    DebugDrawParams params;
    params.type = 2;     // e.g., DRAW_RECT
    params.param1 = 16;  // size or thickness
    params.param2 = 0;   // color or flags
    debugMgr->VTable_SetDrawParams(entity, &params); // call via vtable
}