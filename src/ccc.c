// find a seed with a certain structure at the origin chunk
#include "finders.h"
#include <stdio.h>

int main()
{
    int structType = Treasure;
    int mc = MC_1_21;

    Generator g;
    setupGenerator(&g, mc, 0);

    uint64_t lower48;
    for (lower48 = 0; ; lower48++)
    {
        // The structure position depends only on the region coordinates and
        // the lower 48-bits of the world seed.
        Pos p;
        if (!getStructurePos(structType, mc, lower48, 0, 0, &p))
            continue;

        Pos vp;
        if (!getStructurePos(Village, mc, lower48, 0, 0, &vp))
            continue;

        // Look for a seed with the structure at the origin chunk.
        if (p.x >= 16 || p.z >= 16)
            continue;

        if (vp.x >= 16 || vp.z >= 16)
            continue;

        // Look for a full 64-bit seed with viable biomes.
        int stop = 0;
        uint64_t upper16;
        for (upper16 = 0; upper16 < 0x10000; upper16++)
        {
            uint64_t seed = lower48 | (upper16 << 48);
            applySeed(&g, DIM_OVERWORLD, seed);
            if (isViableStructurePos(structType, &g, p.x, p.z, 0) && isViableStructurePos(Village, &g, vp.x, vp.z, 0))
            {
                printf("Seed %" PRId64 " has a Treasure with close Village at (%d, %d) and (%d, %d).\n",
                    (int64_t) seed, p.x, p.z, vp.x, vp.z);
                // return 0;
                stop = 1;
            }
        }
        if(stop==1){return 0;}
    }
}