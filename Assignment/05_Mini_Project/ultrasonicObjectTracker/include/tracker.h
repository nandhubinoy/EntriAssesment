#ifndef TRACKER_H
#define TRACKER_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Hardware-independent detection/association/filtering core.
 * No AVR register access here (NFR-4) -- this file is compiled both into
 * the AVR firmware AND into host-side unit tests (see tests/).
 *
 * Fixed-point: range in millimetres (int16_t), velocity in mm per sweep
 * cycle (int16_t). Alpha-beta filter gains and gate distance are placeholder
 * values -- to be finalized in docs/design.md (see SRS open design decisions).
 */

#define TRACKER_MAX_TRACKS 4

typedef struct
{
    bool active; // Is this track currently active?
    uint8_t id; // Unique identifier for the track
    uint8_t bearingInDegrees; // Bearing in degrees
    int16_t rangeInMillimetres; // Range in millimetres
    int16_t velocityInMillimetresPerSweep; // Velocity in mm per sweep cycle    
    uint8_t missedSweeps; // Number of consecutive sweeps where the track was not detected
} track_t;

/** @brief Reset all track slots to inactive. Call once at startup. */
void tracker_init(void);

/**
 * @brief Feed one sweep step's result into the tracker.
 * @param bearingInDegrees   Servo bearing this detection/non-detection occurred at.
 * @param has_detection false if no valid echo at this bearing (FR-5 filtered).
 * @param rangeInMillimetres      Measured range in mm (ignored if has_detection is false).
 * @return Pointer to the track updated/created this call, or NULL if the
 *         call only aged out a miss with no association.
 */
const track_t *tracker_process(uint8_t bearingInDegrees, bool has_detection, int16_t rangeInMillimetres);

/** @brief Direct read access, for telemetry emission and unit tests. */
const track_t *tracker_get_track(uint8_t index);

/**
 * @brief Call once per completed sweep pass (FR-8). Any active track that
 *        was not updated during the pass has its miss_count incremented;
 *        tracks exceeding MAX_MISSES are deleted (deactivated).
 */
void tracker_end_of_sweep(void);


#endif // TRACKER_H