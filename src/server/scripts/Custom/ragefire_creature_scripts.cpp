/*
* 
///*    Name                  SpellID   CAST-TIME      DAMAGE */
/*SPELL_FIREBALL             = 70282, // 3 sec       ,  6198-7202*/
/*SPELL_FIRE_SPIT            = 66796, // 1 sec       ,  5088-5912*/
/*SPELL_BLAST_NOVA           = 74392, // 2 sec       ,  5688-7312*/
/*SPELL_CLEAVE				 = 74524,  
/SPELL_WARSTOMP				 = 24375,
/SPELL_FIREBALLVOLLEY		 = 22425,
/SPELL_CONFLAGRATION		 = 23023,
/SPELL_STOMP                 = 58663,
/SPELL_FLAME_BUFFET          = 34121, // Flame Buffet - every 1, 5 secs in phase 1 if there is no victim in melee range and after Dive Bomb in phase 2 with same conditions
/SPELL_FLAME_QUILLS          = 34229, // Randomly after changing position in phase after watching tons of movies, set probability 20%
/SPELL_REBIRTH               = 34342, // Rebirth - beginning of second phase(after losing all health in phase 1)
/SPELL_REBIRTH_2             = 35369, // Rebirth(another, without healing to full HP) - after Dive Bomb in phase 2
/SPELL_MELT_ARMOR            = 35410, // Melt Armor - every 60 
/SPELL_CHARGE                = 35412, // Charge - 30 sec cooldown
/SPELL_SUPERCHARGE           = 61920,
/SPELL_DIVE_BOMB_VISUAL      = 35367, // Bosskillers says 30 sec cooldown, wowwiki says 30 sec colldown, DBM and BigWigs addons says ~47 sec
/SPELL_DIVE_BOMB             = 35181, // after watching tonns of movies, set cooldown to 40+rand()%5.
/SPELL_BERSERK = 45078, // 10 minutes after phase 2 starts(id is wrong, but proper id is unknown)
/SPELL_CARRION_SWARM		 = 31306,
/SPELL_SLEEP				 = 31298,
/SPELL_VAMPIRIC_AURA	     = 38196,
/SPELL_INFERNO				 = 31299,
/SPELL_IMMOLATION			 = 31303,
/SPELL_INFERNO_EFFECT	     = 31302,
/SPELL_IMPALE                = 28783,
/SPELL_CAUTERIZING_FLAMES    = 59466, //Only in heroic
/SPELL_FIREBOLT              = 54235,
/H_SPELL_FIREBOLT            = 59468,
/SPELL_FLAME_BREATH          = 54282,
/H_SPELL_FLAME_BREATH        = 59469,
/SPELL_LAVA_BURN             = 54249,
/H_SPELL_LAVA_BURN           = 59594
/SPELL_FIREBALL              = 14034
/CREATURE_EMBER_OF_ALAR      = 19551, // Al'ar summons one Ember of Al'ar every position change in phase 1 and two after Dive Bomb. Also in phase 2 when Ember of Al'ar dies, boss loses 3% health.
/SPELL_EMBER_BLAST           = 34133, // When Ember of Al'ar dies, it casts Ember Blast
/SPELL_SHADOWBOLT            = 17393,
CREATURE_FLAME_PATCH_ALAR    = 20602, // Flame Patch - every 30 sec in phase 2
SPELL_FLAME_PATCH            = 35380, //
/
/
/
//EVENT_CONFLAGRATION,
//EVENT_CLEAVE,
//EVENT_BLAST_NOVA,

enum AssemblyActions
{
ACTION_SUPERCHARGE                           = 1,
};


///Charge timer////
if (Charge_Timer <= diff)
{
Unit* target= SelectTarget(SELECT_TARGET_RANDOM, 1, 100, true);
if (target)
DoCast(target, SPELL_CHARGE);
Charge_Timer = 30000;
}
else
Charge_Timer -= diff;
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum YELLS
{
	SAY_AGGRO = 0
};

enum Spells
{
	//taragaman_the_hungerer
	SPELL_CHARGE		= 33709,
	SPELL_CONFLAGRATION = 23023,
	SPELL_CLEAVE		= 74524, 
	SPELL_WAR_STOMP	    = 24375,
	SPELL_IMPALE		= 28783,
	SPELL_WHIRLWIND		= 13736,
	SPELL_MORTAL_STRIKE = 16856,
	SPELL_FRENZY		= 28131,
	H_SPELL_FLAME_BREATH = 59469,

	// harrowing_of_hell
	SPELL_FW_METEOR_FISTS        = 66808,
	SPELL_FW_METEOR_FISTS_DAMAGE = 66809,
	SPELL_RAIN_OF_FIRE			 = 33617,
	SPELL_FLAME_CINDER_A		 = 66684,

	//Molten Hound
	SPELL_LAVA_BURN				 = 54249,
	SPELL_FLAME_BREATH			 = 54282,

	//Molten Imp
	SPELL_FIRE_NOVA				 = 20203,

	//Apocalyptic
	SPELL_HAND_OF_RAGNAROS		 = 19780,
	SPELL_WRATH_OF_RAGNAROS		 = 20566,
	SPELL_LAVA_BURST			 = 21158,
	SPELL_MAGMA_BLAST			 = 20565,              
	SPELL_MELT_WEAPON			 = 21388,
	SPELL_ELEMENTAL_FIRE		 = 20564,
	SPELL_ERRUPTION				 = 17731
};

enum Events
{

	//taragaman_the_hungerer
	EVENT_CHARGE_ATTACK	= 1,
	EVENT_CONFLAGRATION = 2,
	EVENT_CLEAVE		= 3,
	EVENT_WAR_STOMP		= 4,
	EVENT_IMPALE		= 5,
	EVENT_MORTAL_STRIKE = 6,
	EVENT_WHIRLWIND		= 7,
	EVENT_FLAME_BREATH  = 8,

	// harrowing_of_hell
	EVENT_FW_METEOR_FISTS = 9,
	EVENT_SUMMON_SPIRITS = 10,
	EVENT_RAIN_OF_FIRE   = 11,
	EVENT_FLAME_CINDER_A = 12,

	//Molten Hound
	EVENT_LAVA_BURN		= 13,

	//Molten Imp
	EVENT_FIRE_NOVA = 14,

	//Apocalyptic
	EVENT_ERUPTION = 15,
	EVENT_WRATH_OF_RAGNAROS = 16,
	EVENT_HAND_OF_RAGNAROS = 17,
	EVENT_LAVA_BURST = 18,
	EVENT_ELEMENTAL_FIRE = 19,
	EVENT_MAGMA_BLAST = 20
};


//taragaman_the_hungerer
Position const positions[4] =
{
	{ -247.465f, 138.866f, -18.545f, 1.210f },
	{ -259.750f, 151.071f, -18.848f, 0.137f },
	{ -240.001f, 168.152f, -18.467f, 4.465f },
	{ -229.170f, 151.676f, -18.925f, 3.230f }
};

class boss_taragaman_the_hungerer : public CreatureScript
{
public:
	boss_taragaman_the_hungerer() : CreatureScript("boss_taragaman_the_hungerer") { }

	struct boss_taragaman_the_hungererAI : public ScriptedAI
	{
		boss_taragaman_the_hungererAI(Creature* creature) : ScriptedAI(creature) { }

		void Reset() override
		{
			_events.Reset();
		}

		void EnterCombat(Unit* /*who*/) override
		{
			
			Talk(SAY_AGGRO);
			_events.ScheduleEvent(EVENT_CHARGE_ATTACK, 1000);
			_events.ScheduleEvent(EVENT_CONFLAGRATION, urand(10000, 30000));
			_events.ScheduleEvent(EVENT_CLEAVE, 10000);
			_events.ScheduleEvent(EVENT_WAR_STOMP, 20000);
			_events.ScheduleEvent(EVENT_IMPALE, urand(35000, 60000));
			_events.ScheduleEvent(EVENT_MORTAL_STRIKE, urand(2000, 5000));
			_events.ScheduleEvent(EVENT_WHIRLWIND, urand(24000, 30000));
			_events.ScheduleEvent(EVENT_FLAME_BREATH, urand(25000, 35000));

			
		}

		void UpdateAI(uint32 diff) override
		{
			if (!UpdateVictim())
				return;

			_events.Update(diff);

			while (uint32 eventId = _events.ExecuteEvent())
			{
				switch (eventId)
				{

				case EVENT_CHARGE_ATTACK:
					DoCastVictim(SPELL_CHARGE);
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
						DoCast(target, SPELL_CHARGE);
					_events.ScheduleEvent(EVENT_CHARGE, urand(5000, 15000));
					break;
				case EVENT_CONFLAGRATION:
					DoCastVictim(SPELL_CONFLAGRATION);
					if (me->GetVictim() && me->EnsureVictim()->HasAura(SPELL_CONFLAGRATION))
						if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 100, true))
							me->TauntApply(target);
					_events.ScheduleEvent(EVENT_CONFLAGRATION, 30000);
					break;
				case EVENT_CLEAVE:
					DoCastVictim(SPELL_CLEAVE);
					_events.ScheduleEvent(EVENT_CLEAVE, 10000);
					break;
				case EVENT_WAR_STOMP:
					DoCast(me, SPELL_WAR_STOMP);
					_events.ScheduleEvent(EVENT_WAR_STOMP, urand(18000, 24000));
					break;
				case EVENT_IMPALE:
					//Cast Impale on a random target
					//Do NOT cast it when we are afflicted by CONFLAGRATION
					if (!me->HasAura(sSpellMgr->GetSpellIdForDifficulty(SPELL_CONFLAGRATION, me)))
						if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
							DoCast(target, SPELL_IMPALE);
					_events.ScheduleEvent(EVENT_IMPALE, urand(20000, 40000));
					break;
				case EVENT_MORTAL_STRIKE:
					DoCastVictim(SPELL_MORTAL_STRIKE);
					_events.ScheduleEvent(EVENT_MORTAL_STRIKE, 8000);
					break;
				case EVENT_WHIRLWIND:
					DoCastVictim(SPELL_WHIRLWIND);
					_events.ScheduleEvent(EVENT_WHIRLWIND, 15000);
				case EVENT_FLAME_BREATH:
					DoCastVictim(H_SPELL_FLAME_BREATH);
					_events.ScheduleEvent(EVENT_FLAME_BREATH, 30000);
					break;
				default:
					break;
				}
			}

			DoMeleeAttackIfReady();
		}

	private:
		EventMap _events;
	};

	CreatureAI* GetAI(Creature* creature) const override
	{
		return new boss_taragaman_the_hungererAI(creature);
	}
};

void AddSC_boss_taragaman_the_hungerer()
{
	new boss_taragaman_the_hungerer();
}


/*######
## harrowing_of_hell
######*/
class harrowing_of_hell : public CreatureScript
{
public:
	harrowing_of_hell() : CreatureScript("harrowing_of_hell") { }

	struct harrowing_of_hellAI : public ScriptedAI
	{
		harrowing_of_hellAI(Creature* creature) : ScriptedAI(creature)
		{
		}

		void Reset() override
		{
			events.Reset();
		}

		void EnterCombat(Unit* /*who*/) override
		{
			DoZoneInCombat();

			events.ScheduleEvent(EVENT_FW_METEOR_FISTS, 10000);
			events.ScheduleEvent(EVENT_SUMMON_SPIRITS, 45000);
			events.ScheduleEvent(EVENT_FIRE_NOVA, urand(2000, 10000));
			events.ScheduleEvent(EVENT_FLAME_CINDER_A, 20000);
		}
		void SummonSpirit(Unit* victim)
		{
			if (Creature* spirit = DoSpawnCreature(900006, 0, 0, 0, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 60000))
				spirit->AI()->AttackStart(victim);
		}

		void UpdateAI(uint32 diff) override
		{
			if (!UpdateVictim())
				return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_FW_METEOR_FISTS:
					DoCast(me, SPELL_FW_METEOR_FISTS);
					events.ScheduleEvent(EVENT_FW_METEOR_FISTS, 20000);
					break;
				case EVENT_SUMMON_SPIRITS:
					me->SetReactState(REACT_AGGRESSIVE);
					me->SummonCreature(900006, positions[0], TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 5000);
					me->SummonCreature(900006, positions[1], TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 5000);
					me->SummonCreature(900006, positions[2], TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 5000);
					me->SummonCreature(900006, positions[3], TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 5000);
					break;
				case EVENT_RAIN_OF_FIRE:
					DoCast(me, SPELL_FIRE_NOVA);
					events.ScheduleEvent(EVENT_FIRE_NOVA, urand(2000, 10000));
					break;
				case EVENT_FLAME_CINDER_A:
					DoCast(me, SPELL_FLAME_CINDER_A);
					events.ScheduleEvent(EVENT_FLAME_CINDER_A, 30000);
					break;
				default:
					break;
				}
			}

			DoMeleeAttackIfReady();
		}

	private:
		EventMap events;
	};

	CreatureAI* GetAI(Creature* creature) const override
	{
		return new harrowing_of_hellAI(creature);
	}
};
void AddSC_harrowing_of_hell()
{
	new harrowing_of_hell();
}

/*######
## Molten Hound
######*/

class molten_hound : public CreatureScript
{
public:
	molten_hound() : CreatureScript("molten_hound") { }

	struct molten_houndAI : public ScriptedAI
	{
		molten_houndAI(Creature* creature) : ScriptedAI(creature) { }

		void Reset() override
		{
			events.Reset();
		}

		void EnterCombat(Unit* /*who*/) override
		{

			events.ScheduleEvent(EVENT_FLAME_BREATH, 15000);
			events.ScheduleEvent(EVENT_LAVA_BURN, 5000);

		}

		void UpdateAI(uint32 diff) override
		{
			if (!UpdateVictim())
				return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{

				case EVENT_FLAME_BREATH:
					DoCastVictim(SPELL_FLAME_BREATH);
					if (me->GetVictim() && me->EnsureVictim()->HasAura(SPELL_FLAME_BREATH))
						if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 100, true))
							me->TauntApply(target);
					events.ScheduleEvent(EVENT_FLAME_BREATH, 30000);
					break;
				case EVENT_LAVA_BURN:
					DoCastVictim(SPELL_LAVA_BURN);
					events.ScheduleEvent(EVENT_LAVA_BURN, 10000);
					break;
				default:
					break;
				}
			}

			DoMeleeAttackIfReady();
		}

	private:
		EventMap events;
	};

	CreatureAI* GetAI(Creature* creature) const override
	{
		return new molten_houndAI(creature);
	}
};

void AddSC_molten_hound()
{
	new molten_hound();
}

/*######
## Molten Imp
######*/

class molten_imp : public CreatureScript
{
public:
	molten_imp() : CreatureScript("molten_imp") { }

	struct molten_impAI : public ScriptedAI
	{
		molten_impAI(Creature* creature) : ScriptedAI(creature) { }

		void Reset() override
		{
			events.Reset();
		}

		void EnterCombat(Unit* /*who*/) override
		{

			events.ScheduleEvent(EVENT_FIRE_NOVA, 5000);
			events.ScheduleEvent(EVENT_LAVA_BURN, 10000);

		}

		void UpdateAI(uint32 diff) override
		{
			if (!UpdateVictim())
				return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{

				case EVENT_FIRE_NOVA:
					DoCastVictim(SPELL_FIRE_NOVA);
					events.ScheduleEvent(EVENT_FIRE_NOVA, 10000);
					break;
				case EVENT_LAVA_BURN:
					DoCastVictim(SPELL_LAVA_BURN);
					events.ScheduleEvent(EVENT_LAVA_BURN, 10000);
					break;
				default:
					break;
				}
			}

			DoMeleeAttackIfReady();
		}

	private:
		EventMap events;
	};

	CreatureAI* GetAI(Creature* creature) const override
	{
		return new molten_impAI(creature);
	}
};

void AddSC_molten_imp()
{
	new molten_imp();
}

//Apocalyptic

class apocalyptic : public CreatureScript
{
public:
	apocalyptic() : CreatureScript("apocalyptic") { }

	struct apocalypticAI : public ScriptedAI
	{
		apocalypticAI(Creature* creature) : ScriptedAI(creature) { }

		void Reset() override
		{
			events.Reset();
		}

		void EnterCombat(Unit* /*who*/) override
		{

			events.ScheduleEvent(EVENT_ERUPTION, 15000);
			events.ScheduleEvent(EVENT_WRATH_OF_RAGNAROS, 30000);
			events.ScheduleEvent(EVENT_HAND_OF_RAGNAROS, 25000);
			events.ScheduleEvent(EVENT_LAVA_BURST, 10000);
			events.ScheduleEvent(EVENT_ELEMENTAL_FIRE, 3000);
			events.ScheduleEvent(EVENT_MAGMA_BLAST, 2000);
		
		}

		void UpdateAI(uint32 diff) override
		{
			if (!UpdateVictim())
				return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{

				case EVENT_ERUPTION:
					DoCastVictim(SPELL_ERRUPTION);
					events.ScheduleEvent(EVENT_ERUPTION, urand(20000, 45000));
					break;
				case EVENT_WRATH_OF_RAGNAROS:
					DoCastVictim(SPELL_WRATH_OF_RAGNAROS);
					if (urand(0, 1))
					events.ScheduleEvent(EVENT_WRATH_OF_RAGNAROS, 25000);
					break;
				case EVENT_HAND_OF_RAGNAROS:
					DoCast(me, SPELL_HAND_OF_RAGNAROS);
					if (urand(0, 1))
					events.ScheduleEvent(EVENT_HAND_OF_RAGNAROS, 20000);
					break;
				case EVENT_LAVA_BURST:
					DoCastVictim(SPELL_LAVA_BURST);
					events.ScheduleEvent(EVENT_LAVA_BURST, 10000);
					break;
				case EVENT_ELEMENTAL_FIRE:
					DoCastVictim(SPELL_ELEMENTAL_FIRE);
					events.ScheduleEvent(EVENT_ELEMENTAL_FIRE, urand(10000, 14000));
					break;
				case EVENT_MAGMA_BLAST:
					if (!me->IsWithinMeleeRange(me->GetVictim()))
						DoCastVictim(SPELL_MAGMA_BLAST);
					events.ScheduleEvent(EVENT_MAGMA_BLAST, 2500);
				default:
					break;
				}
			}

			DoMeleeAttackIfReady();
		}

	private:
		EventMap events;
	};

	CreatureAI* GetAI(Creature* creature) const override
	{
		return new apocalypticAI(creature);
	}
};

void AddSC_apocalyptic()
{
	new apocalyptic();
}


