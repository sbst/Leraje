#include "pch.h"
#include "UsersComponent.h"

using namespace Leraje::Components;
using namespace std;

UsersComponent::UsersComponent(fastcgi::ComponentContext* context)
  : fastcgi::Component(context), Leraje::Components::Component(context)
{}

bool UsersComponent::handleCustomRequest(fastcgi::Request& request)
{
  request.setStatus(404);
  return true;
}

void UsersComponent::loadDatabase()
{
  db->LoadDatabase("users");
  cout << "Database loaded for users..." << endl;
}
