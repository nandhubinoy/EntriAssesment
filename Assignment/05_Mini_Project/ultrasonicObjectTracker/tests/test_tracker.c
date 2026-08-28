/*
 * Host-side unit tests for src/tracker.c (NFR-4).
 * No hardware, no AVR headers -- runs natively on the dev machine.
 * Minimal hand-rolled assertions; no external test framework dependency.
 */
#include "tracker.h"
#include <stdio.h>
#include <assert.h>

static int tests_run = 0;

#define RUN(test_fn) do { \
    printf("  running %s...\n", #test_fn); \
    test_fn(); \
    tests_run++; \
} while (0)

static void test_first_detection_creates_track(void)
{
    tracker_init();
    const track_t *t = tracker_process(90, true, 1000); /* 1m away, bearing 90 */

    assert(t != NULL);
    assert(t->active == true);
    assert(t->rangeInMillimetres == 1000);
    assert(t->bearingInDegrees == 90);
    assert(t->velocityInMillimetresPerSweep == 0);
    assert(t->id != 0);
}

static void test_close_detection_associates_same_track(void)
{
    tracker_init();
    const track_t *t1 = tracker_process(90, true, 1000);
    uint8_t id1 = t1->id;

    /* Next sweep pass, target moved slightly closer -- within gate (30cm) */
    const track_t *t2 = tracker_process(90, true, 980);

    assert(t2->id == id1);            /* same track, not a new one */
    assert(t2->rangeInMillimetres < 1000);      /* filtered range should move toward 980 */
    assert(t2->velocityInMillimetresPerSweep < 0); /* closing target -> negative velocity */
}

static void test_far_detection_creates_new_track(void)
{
    tracker_init();
    const track_t *t1 = tracker_process(90, true, 500);   /* target A, 50cm */
    const track_t *t2 = tracker_process(120, true, 2000); /* target B, 200cm, far outside gate */

    assert(t1->id != t2->id);
    assert(tracker_get_track(0)->active && tracker_get_track(1)->active);
}

static void test_track_ages_out_after_max_misses(void)
{
    tracker_init();
    tracker_process(90, true, 1000);

    /* The sweep pass a track is CREATED on already counts as "updated," so
     * the first end_of_sweep call after creation costs zero misses -- it
     * just clears that flag for the next pass. Misses only start accruing
     * from the second call onward. MAX_MISSES = 3, deletion on exceeding it. */
    tracker_end_of_sweep(); /* clears creation-pass flag, miss_count stays 0 */
    assert(tracker_get_track(0)->missedSweeps == 0);

    tracker_end_of_sweep(); /* miss_count = 1 */
    tracker_end_of_sweep(); /* miss_count = 2 */
    tracker_end_of_sweep(); /* miss_count = 3 -- still <= MAX_MISSES, stays active */
    assert(tracker_get_track(0)->active == true);
    assert(tracker_get_track(0)->missedSweeps == 3);

    tracker_end_of_sweep(); /* miss_count = 4 > MAX_MISSES(3) -> deleted */
    assert(tracker_get_track(0)->active == false);
}

static void test_track_survives_if_reacquired_before_ageout(void)
{
    tracker_init();
    tracker_process(90, true, 1000);

    tracker_end_of_sweep(); /* creation-pass flag clear, miss_count stays 0 */
    tracker_end_of_sweep(); /* miss_count = 1 */
    tracker_end_of_sweep(); /* miss_count = 2 */

    tracker_process(90, true, 1010); /* reacquired -- resets miss_count */
    assert(tracker_get_track(0)->missedSweeps == 0);
    assert(tracker_get_track(0)->active == true);
}

static void test_track_table_full_drops_new_detection(void)
{
    tracker_init();
    /* Fill all 4 slots with widely separated targets (each > gate apart) */
    tracker_process(10, true, 100);
    tracker_process(30, true, 900);
    tracker_process(50, true, 1700);
    tracker_process(70, true, 2500);

    /* 5th, unrelated target -- table is full, should be dropped, not crash */
    const track_t *t5 = tracker_process(90, true, 3300);
    assert(t5 == NULL);
}

int main(void)
{
    printf("radar_tracker host unit tests\n");

    RUN(test_first_detection_creates_track);
    RUN(test_close_detection_associates_same_track);
    RUN(test_far_detection_creates_new_track);
    RUN(test_track_ages_out_after_max_misses);
    RUN(test_track_survives_if_reacquired_before_ageout);
    RUN(test_track_table_full_drops_new_detection);

    printf("All %d test cases passed.\n", tests_run);
    return 0;
}
