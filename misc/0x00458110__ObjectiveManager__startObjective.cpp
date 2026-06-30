// FUNC_NAME: ObjectiveManager::startObjective
void __thiscall ObjectiveManager::startObjective(int thisPtr, int objectiveId, double time, char isCutscene, int param5)
{
  // Lock critical section for this function
  criticalSectionEnter(&g_criticalSection);

  // Clear flag at +0x208
  *(char *)(thisPtr + 0x208) = 0;

  if (*(int *)(thisPtr + 0x170) == 0)  // state: 0 = not started
  {
    if (*(int *)(thisPtr + 0x16c) == 1)  // cutscene status: 1 = playing?
    {
      bool cutsceneFinished = checkCutsceneFinished(); // returns char (0 = not finished)
      if (cutsceneFinished)
      {
        // Cutscene ended, reset timers and state
        *(int *)(thisPtr + 0x164) = 0;   // +0x164: cutscene timer start
        *(int *)(thisPtr + 0x168) = 0;   // +0x168: cutscene duration
        *(int *)(thisPtr + 0x16c) = 0;   // +0x16c: cutscene state = idle
      }
      else
      {
        // Still playing, handle movie progress
        moviePlayStart();
        movieSetTrack(1, 0);
        int movieDuration = movieGetDuration();
        *(int *)(thisPtr + 0x168) = movieDuration;   // store duration
        moviePlayEnd();
        *(int *)(thisPtr + 0x16c) = 2;  // cutscene state = done playing
      }
      // Update global timer reference?
      *(int *)(thisPtr + 0x158) = g_currentTime;  // +0x158: global time snapshot
    }

    // Handle time parameter (param_3)
    if (time == 0.0)
    {
      *(double *)(thisPtr + 0x100) = 0.0;   // +0x100: objective expiry time
    }
    else
    {
      double newTime = g_timeDelta + time;   // +8 offset in g_timeStruct?
      if (newTime < 0.0)
        newTime = 0.0;
      else if (newTime > g_maxTime)          // DAT_00e44900
        newTime = g_maxTime;
      *(double *)(thisPtr + 0x100) = newTime;
    }

    // Store flags and additional parameter
    *(char *)(thisPtr + 0x15c) = isCutscene;   // +0x15c: cutscene flag
    *(int *)(thisPtr + 0x160) = param5;        // +0x160: extra objective parameter

    // Call setObjectiveTrigger with the objectiveId
    setObjectiveTrigger(objectiveId);

    // Clear UI-related flags and pointer
    *(char *)(thisPtr + 0xe0) = 0;          // +0xe0: UI flag
    *(int *)(thisPtr + 0x14c) = 0;          // +0x14c: UI state
    if (*(char **)(thisPtr + 0x148) != nullptr)
    {
      **(char **)(thisPtr + 0x148) = 0;      // +0x148: pointer to UI text, nullify
    }

    // Mark objective as started
    *(int *)(thisPtr + 0x170) = 1;          // state = 1 (started)

    // Load objective UI (find UI path, callback)
    char *uiPath = *(char **)(thisPtr + 0x138);
    if (uiPath == nullptr)
    {
      uiPath = "DefaultObjectiveUI";         // DAT_0120546e
    }
    loadObjectiveUI(uiPath, 0, onObjectiveUICallback, thisPtr, 0);
  }
  else
  {
    // Already started, just update trigger and mark as finished?
    setObjectiveTrigger(objectiveId);
    *(int *)(thisPtr + 0x170) = 2;          // state = 2 (finished)
  }

  // If not already flagged, set flag and call event handler
  if (*(char *)(thisPtr + 0xf8) == '\0')
  {
    *(char *)(thisPtr + 0xf8) = 1;
    if (g_objectiveEventHandler != 0)
    {
      callEventHandler(thisPtr, g_objectiveEventHandler);
    }
  }

  // Leave critical section
  criticalSectionLeave();
}