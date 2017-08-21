#include "pch.h"
#include "VisitsComponent.h"

using namespace Leraje::Components;
using std::cout;
using std::endl;

VisitsComponent::VisitsComponent(fastcgi::ComponentContext *context)
  : fastcgi::Component(context), Leraje::Components::Component(context)
{}

bool VisitsComponent::handleCustomRequest(fastcgi::Request& request)
{
  request.setStatus(404);
  return true;
}

void VisitsComponent::loadDatabase()
{
  cout << "Loading database for visits..." << endl;
  //db->LoadDatabase("users");
  cout << "Database loaded for visits..." << endl;
}
