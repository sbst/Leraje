#include "pch.h"
#include "LocationsComponent.h"

using namespace Leraje::Components;
using std::cout;
using std::endl;

LocationsComponent::LocationsComponent(fastcgi::ComponentContext *context)
  : fastcgi::Component(context), Leraje::Components::Component(context)
{}

bool LocationsComponent::handleCustomRequest(fastcgi::Request& request)
{
  request.setStatus(404);
  return true;
}

void LocationsComponent::loadDatabase()
{
  //db->LoadDatabase("users");
  cout << "Database loaded for locations..." << endl;
}
