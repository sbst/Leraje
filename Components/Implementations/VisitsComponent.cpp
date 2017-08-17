#include "pch.h"
#include "VisitsComponent.h"

using namespace Leraje::Components;
using std::cout;
using std::endl;

VisitsComponent::VisitsComponent(fastcgi::ComponentContext *context)
  : fastcgi::Component(context), Leraje::Components::Component(context)
{}

void VisitsComponent::handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context)
{
  request->setContentType("text/plain");
  std::stringbuf buffer("Hello " + (request->hasArg("name") ? request->getArg("name") : "stranger") + " I am visits");
  request->write(&buffer);
}

void VisitsComponent::loadDatabase()
{
  cout << "Loading database for visits..." << endl;
}
