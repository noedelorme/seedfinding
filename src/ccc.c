// find a seed with a certain structure at the origin chunk
#include "finders.h"
#include "loot/loot_table_context.h"
#include "loot/items.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int version = MC_1_21;

    Generator g;
    setupGenerator(&g, version, 0);

    int bt_v_dist = 16*3;

    uint64_t lower48;
    for (lower48 = 0; ; lower48++) {
        Pos bt_pos;
        if (!getStructurePos(Treasure, version, lower48, 0, 0, &bt_pos))
            continue;

        Pos v_pos;
        if (!getStructurePos(Village, version, lower48, 0, 0, &v_pos))
            continue;

        if (abs(bt_pos.x-v_pos.x) >= bt_v_dist || abs(bt_pos.z-v_pos.z) >= bt_v_dist)
            continue;

        printf("... start testing lower48=%" PRId64 " ...\n", (int64_t) lower48);

        uint64_t upper16;
        for (upper16 = 0; upper16 < 0x10000; upper16++)
        {
            uint64_t seed = lower48 | (upper16 << 48);
            applySeed(&g, DIM_OVERWORLD, seed);

            int biome = getBiomeAt(&g, 1, v_pos.x, 63, v_pos.z);
            if (biome != plains && biome !=taiga)
                continue;

            StructureSaltConfig salt_config;
            getStructureSaltConfig(Treasure, version, -1, &salt_config);
            StructureVariant structure_variant;
            getVariant(&structure_variant, Treasure, version, seed, bt_pos.x, bt_pos.z, -1);
            Piece piece;
            getStructurePieces(&piece, 1, Treasure, salt_config, &structure_variant, version, seed, bt_pos.x, bt_pos.z);

            LootTableContext* ctx;
            init_loot_table_name(&ctx, piece.lootTables[0], version);
            set_loot_seed(ctx, piece.lootSeeds[0]);
            generate_loot(ctx);

            int iron_count = 0;
            int gold_count = 0;
            int emerald_count = 0;
            int tnt_count = 0;
            for (int i = 0; i < ctx->generated_item_count; i++) {
                ItemStack item = ctx->generated_items[i];
                if (ctx->global_item_ids[item.item] == ITEM_IRON_INGOT) { iron_count += item.count; }
                if (ctx->global_item_ids[item.item] == ITEM_GOLD_INGOT) { gold_count += item.count; }
                if (ctx->global_item_ids[item.item] == ITEM_EMERALD) { emerald_count += item.count; }
                if (ctx->global_item_ids[item.item] == ITEM_TNT) { tnt_count += item.count; }
            }

            int cond = tnt_count >= 1 && emerald_count >= 3 && (iron_count >= 12 || (iron_count >= 10 && gold_count >= 2));

            if (!cond)
                continue;

            Pos spawn_pos = getSpawn(&g);
            if (spawn_pos.x >= 16 || spawn_pos.z >= 16)
                continue;
            
            if (!isViableStructurePos(Treasure, &g, bt_pos.x, bt_pos.z, 0))
                continue;

            if (!isViableStructurePos(Village, &g, v_pos.x, v_pos.z, 0))
                continue;

            // printf("Seed %" PRId64 " bt at (%d, %d) and village at (%d, %d).\n", (int64_t) seed, bt_pos.x, bt_pos.z, v_pos.x, v_pos.z);
            printf("%" PRId64 "\n", (int64_t) seed);
        }
    }

    return 0;
}


// stdbuf -oL -eL ./build/ccc > seed/ccc.txt 2>&1