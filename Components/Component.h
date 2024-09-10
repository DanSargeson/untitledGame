#ifndef COMPONENT_H
#define COMPONENT_H

#include "Engine.h"

class Component : public enable_shared_from_this<Component>{

public:

	Component(std::shared_ptr<class Entity> owner, int updateOrder = 100);
	~Component();

	virtual void update();
	virtual void processInput();

	std::shared_ptr<Component> getPtr() {

		return shared_from_this();
	}

	virtual void render(SDL_Renderer* target);

	void addOwner();

	int getUpdateOrder() { return mUpdateOrder; }

protected:

	std::shared_ptr<class Entity> mOwner;
	int mUpdateOrder;
};

#endif
