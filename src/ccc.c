// find a seed with a certain structure at the origin chunk
#include "finders.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int version = MC_1_21;

    Generator g;
    setupGenerator(&g, version, 0);

    uint64_t lower48;
    for (lower48 = 0; ; lower48++)
    {
        Pos bt_pos;
        if (!getStructurePos(Treasure, version, lower48, 0, 0, &bt_pos))
            continue;

        Pos v_pos;
        if (!getStructurePos(Village, version, lower48, 0, 0, &v_pos))
            continue;

        if (abs(bt_pos.x-v_pos.x) >= 16 || abs(bt_pos.z-v_pos.z) >= 16)
            continue;

        uint64_t upper16;
        for (upper16 = 0; upper16 < 0x10000; upper16++)
        {
            uint64_t seed = lower48 | (upper16 << 48);
            applySeed(&g, DIM_OVERWORLD, seed);

            Pos spawn_pos = getSpawn(&g);
            if (abs(bt_pos.x-spawn_pos.x) >= 16 || abs(bt_pos.z-spawn_pos.z) >= 16)
                continue;
            
            if (!isViableStructurePos(Treasure, &g, bt_pos.x, bt_pos.z, 0))
                continue;

            if (!isViableStructurePos(Village, &g, v_pos.x, v_pos.z, 0))
                continue;

            printf("Seed %" PRId64 " has a Treasure at (%d, %d) and a Village (%d, %d).\n", (int64_t) seed, bt_pos.x, bt_pos.z, v_pos.x, v_pos.z);
        }

        printf("------------------------");
    }

    return 0;
}