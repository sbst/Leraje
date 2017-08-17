#include "pch.h"
#include "Component.h"

using namespace Leraje::Components;

Component::Component(fastcgi::ComponentContext *context)
  : fastcgi::Component(context)
{}

Component::~Component()
{}

void Component::onLoad()
{
  db = Database::Database::GetDatabase();
  loadDatabase();
}

void Component::onUnload()
{}
