#include "pch.h"
#include "LocationsComponent.h"

using namespace Leraje::Components;
using std::cout;
using std::endl;

LocationsComponent::LocationsComponent(fastcgi::ComponentContext *context)
  : fastcgi::Component(context), Leraje::Components::Component(context)
{}

void LocationsComponent::handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context)
{
  request->setContentType("text/plain");
  std::stringbuf buffer("Hello " + (request->hasArg("name") ? request->getArg("name") : "stranger") + " I am locations");
  request->write(&buffer);
}

void LocationsComponent::loadDatabase()
{
  cout << "Loading database for locations..." << endl;
}
