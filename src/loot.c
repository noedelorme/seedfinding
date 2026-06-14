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

    uint64_t seed = 821343982041746931;
    applySeed(&g, DIM_OVERWORLD, seed);

    Pos bt_pos;
    getStructurePos(Treasure, version, seed, 0, 0, &bt_pos);

    LootTableContext* ctx;
    init_buried_treasure(&ctx, version);
    set_loot_seed(ctx, 2); // it reamins to understand how to compute the lootseed as a function of worldseed and pos of bt
    generate_loot(ctx);

    for (int i = 0; i < ctx->generated_item_count; i++) {
        ItemStack item = ctx->generated_items[i];
        printf("%d x %s\n", item.count,ctx->item_names[item.item]);
    }

    return 0;
}