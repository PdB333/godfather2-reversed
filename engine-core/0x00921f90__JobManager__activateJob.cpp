// FUNC_NAME: JobManager::activateJob
// Address: 0x00921f90
// This function inserts a job into a sorted list and optionally plays a fanfare.

class JobManager {
public:
    struct JobNode {
        JobNode* next; // +0x00
        JobNode* prev; // +0x04
    };

    struct Job {
        // ... (other fields)
        JobNode node;          // +0x48
        int sortKey;           // +0x54
        void* callback;        // +0x70 (usage unclear)
        const char* stringId;  // +0xb4 (string identifier)
    };

    JobNode** jobList; // +0x5c (array of 8-byte entries: first 4 bytes are JobNode pointer, second 4 unused?)
    int jobCount;     // +0x60
};

void __thiscall JobManager::activateJob(int thisPtr, int jobPtr, char playFanfare)
{
    // local sentinel node for safe list insertion
    JobNode sentinelNode;
    int savedPrev;
    JobNode** entryPtr;
    int sortKey;
    int jobBase;

    sentinelNode.next = (JobNode*)(jobPtr + 0x48); // Actually the sentinel's next is set to the job's node address
    savedPrev = *(int*)(jobPtr + 0x4c); // save previous prev pointer from job node
    *(int**)(jobPtr + 0x4c) = &sentinelNode; // set job's prev to sentinel (temporarily)

    sortKey = *(int*)(jobPtr + 0x54);

    // Find insertion point in sorted list
    int index = 0;
    if (*(uint*)(thisPtr + 0x60) != 0) {
        JobNode** iter = *(JobNode***)(thisPtr + 0x5c);
        do {
            Job* existingJob = nullptr;
            if (*iter != nullptr) {
                existingJob = (Job*)((int)*iter - 0x48);
            }
            if (existingJob != nullptr && sortKey < existingJob->sortKey) break;
            index++;
            iter += 2;
        } while (index < *(uint*)(thisPtr + 0x60));
    }

    entryPtr = (JobNode**)findInsertPosition(thisPtr, index); // returns pointer to the next entry slot
    int nodeAddr = (int)&sentinelNode;
    if (entryPtr != &sentinelNode && *entryPtr != (JobNode*)&sentinelNode) {
        if (*entryPtr != nullptr) {
            removeNodeEntry(entryPtr); // possibly remove a previous entry
        }
        *entryPtr = (JobNode*)nodeAddr;
        if (nodeAddr != 0) {
            entryPtr[1] = (JobNode*)(*(int*)(nodeAddr + 4)); // set sentinel's prev pointer?
            *(int**)(nodeAddr + 4) = entryPtr;
        }
    }

    if (playFanfare) {
        beginAudioEvent();
        int globalHandle = *DAT_012234a4; // global audio handle?

        // Resolve and play fanfare strings
        const char* name1 = resolveAudioName(*(int*)(jobPtr + 0xb4));
        int playerHandle = 0;
        int result = getCurrentPlayer();
        if (result != 0) {
            result = getPlayerObject(result);
            if (result != 0) {
                playerHandle = *(int*)(result + 0x80);
            }
        }
        const char* name2 = resolveAudioName(playerHandle);
        const char* name1Safe = (name1 != nullptr) ? name1 : "null";
        const char* name2Safe = (name2 != nullptr) ? name2 : "null";
        logAudioEvent(0x6a, name1Safe);
        logAudioEvent(0x72, name2Safe);

        // Format the fanfare string
        char buffer[4096];
        formatAudioString(globalHandle, buffer, "fanfare_dynamic_job_accepted");

        // Play the fanfare
        const char* fanfareString = (buffer[0] != 0) ? buffer : "null";
        playFanfareWithCallback(fanfareString, (void*)(jobPtr + 0x70), &callbackLabel, jobPtr, 0);

        // Clean up allocated strings
        if (name2 != nullptr) freeString(name2);
        if (name1 != nullptr) freeString(name1);
        if (buffer[0] != 0) freeString(buffer);
        endAudioEvent();
    }

    // Clean up sentinel node
    if (&sentinelNode != nullptr) {
        removeNodeEntry(&sentinelNode);
    }
}