
#include "ScriptPCH.h"
 
class Level_item : public ItemScript
{
        public: Level_item() : ItemScript("Level_item") { }
       
				bool OnUse(Player* player, Item* item, const SpellCastTargets &)
                {
					if (player->InBattleground() || player->InArena() || player->IsInCombat() || player->IsInFlight())
					{
						player->GetSession()->SendAreaTriggerMessage("You Don't Want To Use This Right Now!");
						return false;
					}
					if (player->getLevel() == MAX_LEVEL)
					{
						player->GetSession()->SendAreaTriggerMessage("You are already max level! Suppose you just had to temp fate, Didn't you? Was it really worth the trouble?");
						return false;
					}
					player->SetLevel(MAX_LEVEL);
					player->SetHealth(player->GetMaxHealth());
					player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
					player->DestroyItemCount(item->GetEntry(),1,true,false);
					player->GetSession()->SendAreaTriggerMessage("You have redeemed your soul this time.");

					return true;
					}
};
 
void AddSC_Level_item()
{
        new Level_item();
}
