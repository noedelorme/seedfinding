#include "finders.h"
#include "loot/loot_table_context.h"
#include "loot/items.h"
#include <stdio.h>
#include <stdlib.h>

void printPiece(Piece *p)
{
    printf("name: %s\n", p->name);

    printf("pos: (%d, %d, %d)\n",
           p->pos.x, p->pos.y, p->pos.z);

    printf("bb0: (%d, %d, %d)\n",
           p->bb0.x, p->bb0.y, p->bb0.z);

    printf("bb1: (%d, %d, %d)\n",
           p->bb1.x, p->bb1.y, p->bb1.z);

    printf("rot: %u\n", p->rot);
    printf("depth: %d\n", p->depth);
    printf("type: %d\n", p->type);

    printf("chestCount: %d\n", p->chestCount);

    for (int i = 0; i < p->chestCount; i++)
    {
        printf("chest %d:\n", i);

        printf("  pos = (%d, %d)\n",
               p->chestPoses[i].x,
               p->chestPoses[i].z);

        printf("  lootSeed = %llu\n",
               (unsigned long long)p->lootSeeds[i]);

        printf("  lootTable = %s\n",
               p->lootTables[i]);
    }

    printf("additionalData: %d\n", p->additionalData);
}

int main()
{
    int version = MC_1_21;

    Generator g;
    setupGenerator(&g, version, 0);

    uint64_t seed = 821343982041746931;
    applySeed(&g, DIM_OVERWORLD, seed);

    Pos bt_pos;
    getStructurePos(Treasure, version, seed, 0, 0, &bt_pos);

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
        if (ctx->global_item_ids[item.item] == ITEM_IRON_INGOT) {
            iron_count += item.count;
        }
        if (ctx->global_item_ids[item.item] == ITEM_GOLD_INGOT) {
            gold_count += item.count;
        }
        if (ctx->global_item_ids[item.item] == ITEM_EMERALD) {
            emerald_count += item.count;
        }
        if (ctx->global_item_ids[item.item] == ITEM_TNT) {
            tnt_count += item.count;
        }
    }

    printf("iron: %d\n", iron_count);
    printf("gold: %d\n", gold_count);
    printf("emerald: %d\n", emerald_count);
    printf("tnt: %d\n", tnt_count);

    return 0;
}