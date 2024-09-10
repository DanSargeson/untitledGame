#include "stdafx.h"
#include "Component.h"
#include "Entity.h"

Component::Component(std::shared_ptr<Entity> owner, int updateOrder) : mOwner(owner), mUpdateOrder(updateOrder) {

	//mOwner->addComponent(getPtr());
	mOwner = owner;
}

Component::~Component(){

//	if (mOwner != nullptr) {
//	if (mOwner) {
//
//		mOwner->removeComponent(this);
//	}
//}
}

void Component::addOwner() {

	mOwner->addComponent(getPtr());
}

void Component::update()
{
}

void Component::processInput()
{
}

void Component::render(SDL_Renderer * target)
{
}
