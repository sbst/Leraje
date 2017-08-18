#include "pch.h"
#include "UsersComponent.h"

using namespace Leraje::Components;
using std::cout;
using std::endl;

UsersComponent::UsersComponent(fastcgi::ComponentContext* context)
  : fastcgi::Component(context), Leraje::Components::Component(context)
{}

void UsersComponent::handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context)
{
  std::cout << "POPALI" << request->getURI() << std::endl;
  request->setContentType("text/plain");
  std::stringbuf buffer("Hello " + (request->hasArg("name") ? request->getArg("name") : "stranger") + " I am users");
  request->write(&buffer);
}

void UsersComponent::loadDatabase()
{
  db->LoadDatabase("users");
}
