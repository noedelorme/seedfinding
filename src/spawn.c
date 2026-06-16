#include "finders.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int version = MC_1_21;

    Generator g;
    setupGenerator(&g, version, 0);

    uint64_t seed;
    for (seed = 0; ; seed++) {
        applySeed(&g, DIM_OVERWORLD, seed);

        Pos spawn_pos = getSpawn(&g);
        Pos est_spawn_pos = estimateSpawn(&g, NULL);

        printf("Seed %" PRId64 " has spawnpoint at (%d, %d) and estimatated spawnpoint at (%d, %d).\n", (int64_t) seed, spawn_pos.x, spawn_pos.z, est_spawn_pos.x, est_spawn_pos.z);
    }

    return 0;
}