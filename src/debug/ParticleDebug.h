#ifndef PARTICLE_DEBUG_H
#define PARTICLE_DEBUG_H

#include "DebugInfo.h"

class Simulation;
class GameModel;
class GameController;
class ParticleDebug : public DebugInfo
{
	Simulation * sim;
	GameModel * model;
	GameController * c;
public:
	ParticleDebug(unsigned int id, Simulation * sim, GameModel * model, GameController * c);
	int UpdateSimUpToInterestingChange();
	void Debug(int mode, int x, int y);
	bool KeyPress(int key, int scan, bool shift, bool ctrl, bool alt, ui::Point currentMouse) override;
	virtual ~ParticleDebug();
private:
	void updateSimUpTo(int i);
	int updateSimOneParticle();
};

#endif
