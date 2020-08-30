
/*Basic Spells For Boss Fights*/

///*    Name                  SpellID   CAST-TIME      DAMAGE */
/*SPELL_FIREBALL             = 70282, // 3 sec       ,  6198-7202*/
/*SPELL_FIRE_SPIT            = 66796, // 1 sec       ,  5088-5912*/
/*SPELL_BLAST_NOVA           = 74392, // 2 sec       ,  5688-7312*/
/*SPELL_CLEAVE = 22540,
/SPELL_WARSTOMP = 24375,
/SPELL_FIREBALLVOLLEY = 22425,
/SPELL_CONFLAGRATION = 23023*/
//};
//
//enum EventIds
//{
//EVENT_NONE,
//EVENT_CONFLAGRATION,
//EVENT_CLEAVE,
//EVENT_BLAST_NOVA,
//EVENT_SPAWN_FIRE,
//EVENT_SPAWN_FIRE_CLEANUP
//};
//
//class npc_battle : public CreatureScript
//{
//public:
//  npc_battle() : CreatureScript("npc_battle") {}
//
//   struct npc_battleAI : public ScriptedAI
//   {
//       npc_battleAI(creature* creature) : ScriptedAI(creature) {}
//
//       void Reset()
//       {
//          events.Rest();
//          events.ScheduleEvent(EVENT_CONFLAGRATION, urand(6000, 11000));
//			events.ScheduleEvent(EVENT_CLEAVE, urand(4000, 16000));






/*Basic Boss Fight*/

enum SpellIds
{
	SPELL_CLEAVE = 22540,
	SPELL_WARSTOMP = 24375,
	SPELL_FIREBALLVOLLEY = 22425,
	SPELL_CONFLAGRATION = 23023
};

class npc_new_boss : public CreatureScript
{
public:
		npc_new_boss() : CreatureScript("npc_new_boss") { }

		struct npc_new_bossAI : public ScriptedAI
		{
			npc_new_bossAI(Creature* creature) : ScriptedAI(creature), summons(me) { }

			uint32 conflagrationTimer;
			uint32 cleaveTimer;
			uint32 WarstompTimer;
			uint32 FireballvolleyTimer;
			uint32 spawnMinionTimer;

		void Reset()
		{
			conflagrationTimer = urand(6000, 12000);
			cleaveTimer = urand(4000, 10000);
			WarstompTimer = urand(8000, 15000);
			FireballvolleyTimer = urand(60000, 90000);
			spawnMinionTimer = urand(20000, 30000);
			summons.DespawnAll();
		}

		void UpdateAI(UINT32 diff)
		{
			if (cleaveTimer <= diff)
			{
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
					DoCast(target, SPELL_CONFLAGRATION, true);
				conflagrationTimer = urand(6000, 12000);
				
			}
			else
				conflagrationTimer -= diff;

			if (spawnMinionTimer <= diff)
			{
				me->SummonCreature(48, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 9000);
				spawnMinionTimer = urand(40000, 60000);
			}
			else spawnMinionTimer -= diff;
			DoMeleeAttackIfReady();
		}

		void EnterCombat(Unit* /* target*/)
		{

		}

		void JustSummoned(Creature* summoned)
		{
			if (me->GetVictim())
				summoned->GetMotionMaster()->MoveChase(me->GetVictim(), 100.0f);
			summons.Summon(summoned);
		}

		void JustDied(Unit* /* killer */)
		{
			summons.DespawnAll();
		}
	private:
		SummonList summons;
	};

	CreatureAI* GetAI(Creature* creature)const
	{
		return new npc_new_bossAI(creature);
	}
};

void AddSC_New_Boss()
{
	new npc_new_boss;
}