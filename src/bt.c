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

        Pos bt_pos;
        if (!getStructurePos(Treasure, version, seed, spawn_pos.x, spawn_pos.z, &bt_pos))
            continue;

        if (!isViableStructurePos(Treasure, &g, bt_pos.x, bt_pos.z, 0))
            continue;

        printf("Seed %" PRId64 " has a Treasure at (%d, %d).\n", (int64_t) seed, bt_pos.x, bt_pos.z);

        // uint64_t upper16;
        // for (upper16 = 0; upper16 < 0x10000; upper16++) {
        //     uint64_t seed = lower48 | (upper16 << 48);
        //     applySeed(&g, DIM_OVERWORLD, seed);

        //     Pos spawn_pos = getSpawn(&g);
        //     Pos bt_pos;
        //     if (!getStructurePos(Treasure, version, seed, spawn_pos.x, spawn_pos.z, &bt_pos))
        //         continue;
        //     if (!isViableStructurePos(Treasure, &g, bt_pos.x, bt_pos.z, 0))
        //         continue;
            
        //     printf("Seed %" PRId64 "\n", (int64_t) seed);
        // }
    }

    return 0;
}