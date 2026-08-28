#include "tracker.h"
#include <stddef.h>

/* Placeholder tuning values -- finalize in docs/design.md */
#define GATE_DISTANCE_MM   300  /* 30cm: max jump to still count as same target */
#define MAX_MISSES         3    /* FR-8: consecutive misses before deleting a track */
#define ALPHA_NUM          5    /* alpha-beta filter gains, alpha = 0.5 */
#define ALPHA_DEN          10
#define BETA_NUM           2    /* beta = 0.2 */
#define BETA_DEN           10

static track_t tracks[TRACKER_MAX_TRACKS];
static uint8_t next_track_id = 1;

/* Array to track whether each track has been updated this pass 
   Reset to false by tracker_end_of_sweep()
   at the start of each pass (after aging is applied (FR-8)).*/
static bool updated_this_pass[TRACKER_MAX_TRACKS];

static int16_t abs16(int16_t v)
{
    return (v < 0) ? (int16_t)(-v) : v;
}

void tracker_init(void)
{
    for(uint8_t i = 0; i < TRACKER_MAX_TRACKS; i++)
    {
        tracks[i].active =false;
        tracks[i].id = 0;
        tracks[i].bearingInDegrees = 0;
        tracks[i].rangeInMillimetres = 0;
        tracks[i].velocityInMillimetresPerSweep = 0;
        tracks[i].missedSweeps = 0;
        updated_this_pass[i] = false;
    }
    next_track_id = 1;
}

static int8_t findAssociatedTrack(int16_t range_mm)
{
    int8_t best_index = -1;
    int16_t best_distance = GATE_DISTANCE_MM + 1; // Start with a value larger than the gate distance

    for(uint8_t i = 0; i < TRACKER_MAX_TRACKS; i++)
    {
        if(!tracks[i].active)
        {
            continue; // Skip inactive tracks
        }   // Linux kernel style, MISRA-adjacent practices, and embedded systems often favor guard clauses for cleaner diffs and readability

        int16_t diff = abs16(tracks[i].rangeInMillimetres - range_mm);
        if(diff < best_distance && diff <= GATE_DISTANCE_MM)
        {
            best_distance = diff;
            best_index = (int8_t)i;
        }
    }
    return best_index;
}

static int8_t find_free_slot(void)
{
    for (uint8_t i = 0; i < TRACKER_MAX_TRACKS; i++) {
        if (!tracks[i].active) {
            return (int8_t)i;
        }
    }
    return -1; /* table full: new detection dropped until a slot ages out */
}

const track_t *tracker_process(uint8_t bearing_deg, bool has_detecction, int16_t range_mm)
{
    if (!has_detecction)
    {
        return NULL; // No detection to process
    }

    // Try to find new tracks
    int8_t associated_index = findAssociatedTrack(range_mm);
    if(associated_index < 0)
    {
        // No associated track found, try to create a new one
        associated_index = find_free_slot();
        if(associated_index < 0)
        {
            return NULL; // No free slot available, drop this detection
        }
        tracks[associated_index].active                         = true;
        tracks[associated_index].id                             = next_track_id++;
        tracks[associated_index].bearingInDegrees               = bearing_deg;
        tracks[associated_index].rangeInMillimetres             = range_mm;
        tracks[associated_index].velocityInMillimetresPerSweep  = 0;
        tracks[associated_index].missedSweeps                   = 0;
        updated_this_pass[associated_index]                     = true;
        return &tracks[associated_index];
    }

    // Update the associated track using alpha-beta filtering
    int16_t predicted_range = (int16_t)(tracks[associated_index].rangeInMillimetres 
                                      + tracks[associated_index].velocityInMillimetresPerSweep);  
    int16_t residual = range_mm - predicted_range;

    tracks[associated_index].rangeInMillimetres = (int16_t)(predicted_range + (ALPHA_NUM * residual) / ALPHA_DEN);
    tracks[associated_index].velocityInMillimetresPerSweep = (int16_t)(tracks[associated_index].velocityInMillimetresPerSweep + (BETA_NUM * residual) / BETA_DEN);
    tracks[associated_index].bearingInDegrees = bearing_deg;
    tracks[associated_index].missedSweeps = 0; // Reset missed sweeps
    updated_this_pass[associated_index] = true;

    return &tracks[associated_index];
}

const track_t *tracker_get_track(uint8_t index)
{
    if(index >= TRACKER_MAX_TRACKS)
    {
        return NULL; // Invalid index
    }
    return &tracks[index];
}

void tracker_end_of_sweep(void)
{
    for(uint8_t i = 0; i < TRACKER_MAX_TRACKS; i++)
    {
        if(!tracks[i].active)
        {
            continue; // Skip inactive tracks
        }

        if(!updated_this_pass[i])
        {
            tracks[i].missedSweeps++;
            if(tracks[i].missedSweeps > MAX_MISSES)
            {
                tracks[i].active = false;
            }
        }
        updated_this_pass[i] = false; // Reset for the next sweep
    }
}