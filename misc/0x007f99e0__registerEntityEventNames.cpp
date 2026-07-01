// FUNC_NAME: registerEntityEventNames
void registerEntityEventNames(void)
{
    // Register event names for entity-related events
    registerEventName(&gEventPairedAnimationChange, "Sent to an entity when paired animation change required");
    registerEventName(&gEventFalling, "Sent to an entity to commence falling");
    registerEventName(&gEventClearFalling, "Sent to an entity to clear falling flag");
    registerEventName(&gEventStopBurning, "Sent to a sentient to stop them from burning");
    registerEventName(&gEventCollisionOn, "collision_on");
    registerEventName(&gEventCollisionOff, "collision_off");
    registerEventName(&gEventBreakableCollisionOn, "breakable_collision_on");
    registerEventName(&gEventBreakableCollisionOff, "breakable_collision_off");
    registerEventName(&gEventDeathsprayOn, "deathspray_on");
    registerEventName(&gEventDeathsprayOff, "deathspray_off");
    registerEventName(&gEventFootstep, "footstep");
    registerEventName(&gEventFootstepL1, "footstepl_1");
    registerEventName(&gEventFootstepL2, "footstepl_2");
    registerEventName(&gEventFootstepR1, "footstepr_1");
    registerEventName(&gEventFootstepR2, "footstepr_2");
    registerEventName(&gEventFootstepL3, "footstepl_3");
    registerEventName(&gEventFootstepL4, "footstepl_4");
    registerEventName(&gEventFootstepR3, "footstepr_3");
    registerEventName(&gEventFootstepR4, "footstepr_4");
    registerEventName(&gEventCreateImpactExc1, "createimpactexc1");
    registerEventName(&gEventCreateImpactExc2, "createimpactexc2");
    registerEventName(&gEventBodyFall, "bodyfall");
    registerEventName(&gEventHitReactLight, "hit_react_light");
    registerEventName(&gEventHitReactHeavy, "hit_react_heavy");
    registerEventName(&gEventChangePosture, "change_posture");
    registerEventName(&gEventTakeDamagePoint, "take_damage_point");
    registerEventName(&gEventItemAttach, "item_attach");
    registerEventName(&gEventItemDetach, "item_detach");
    registerEventName(&gEventItemUse, "item_use");
    registerEventName(&gEventItemThrow, "item_throw");
    registerEventName(&gEventPropAttach, "prop_attach");
    registerEventName(&gEventPropDetach, "prop_detach");
    registerEventName(&gEventLivingWorldPropAttach, "living_world_prop_attach");
    registerEventName(&gEventLivingWorldPropDetach, "living_world_prop_detach");
    registerEventName(&gEventLivingWorldPropPlant, "living_world_prop_plant");
    registerEventName(&gEventLivingWorldPropDrop, "living_world_prop_drop");
    registerEventName(&gEventEnablePA, "enable_PA");
    registerEventName(&gEventAmbientStretch, "ambient_stretch");
    registerEventName(&gEventAmbientCheckTime, "ambient_check_time");
    registerEventName(&gEventAmbientSmoke, "ambient_smoke");
    registerEventName(&gEventAmbientCough, "ambient_cough");
    registerEventName(&gEventAmbientBrushShoulders, "ambient_brush_shoulders");
    registerEventName(&gEventAmbientOgleLady, "ambient_ogle_lady");
    registerEventName(&gEventAmbientBrandishFist, "ambient_brandish_fist");
    registerEventName(&gEventUsePhone, "use_phone");
    registerEventName(&gEventVoxPlay, "vox__play");
    registerEventName(&gEventSetExpression, "set_expression");
    registerEventName(&gEventVfxStartPropUseVfx, "vfx__start_prop_use_vfx");
    registerEventName(&gEventVfxStopPropUseVfx, "vfx__stop_prop_use_vfx");
    registerEventName(&gEventPairedSentientDetach, "paired_sentient_detach");
    registerEventName(&gEventPairedSentientResume, "paired_sentient_resume");
}