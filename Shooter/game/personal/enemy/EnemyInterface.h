#ifndef ENEMYINTERFACE_H
#define ENEMYINTERFACE_H

class EnemyInterface
{
public:
	EnemyInterface() = default;
	~EnemyInterface() = default;

public:
	virtual void IResetEnemy() = 0;
	virtual void IStartEnemy() = 0;
	virtual void IUpdateEnemy() = 0;
	virtual int IGetLayerEnemy() = 0;
};

#endif
