/* Tutorial -
NPC Fight
EmuDevs (http://emudevs.com)
*/

enum SpellIds
{
	SPELL_FIREBALL = 70282,
};

class npc_tutorial_fighting : public CreatureScript
{
public:
	npc_tutorial_fighting() : CreatureScript("npc_tutorial_fighting") { }

	struct npc_tutorial_fightingAI : public ScriptedAI
	{
		npc_tutorial_fightingAI(Creature* creature) : ScriptedAI(creature), summons(me) { }

		uint32 fireBallTimer;
		uint32 spawnMinionTimer;

		void Reset()
		{
			fireBallTimer = urand(6000, 13000);
			spawnMinionTimer = urand(20000, 30000);
			summons.DespawnAll();
		}

		void UpdateAI(uint32 diff)
		{
			if (fireBallTimer <= diff)
			{
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
					DoCast(target, SPELL_FIREBALL, true);
				fireBallTimer = urand(6000, 13000);
			}
			else
				fireBallTimer -= diff;

			if (spawnMinionTimer <= diff)
			{
				me->SummonCreature(90000, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0);
				spawnMinionTimer = urand(20000, 30000);
			}
			else
				spawnMinionTimer -= diff;
			DoMeleeAttackIfReady();
		}

		void EnterCombat(Unit* /* target */)
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

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_tutorial_fightingAI(creature);
	}
};

void AddSC_fighting()
{
	new npc_tutorial_fighting;
}