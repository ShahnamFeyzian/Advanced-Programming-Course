#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include"utaxi_app.hpp"
#include "../server/server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>


class ActionHandler : public RequestHandler
{
public:
  ActionHandler(UtaxiApp* _app) {app = _app;}
protected:
  UtaxiApp* app;
};

class SignupHandler : public ActionHandler 
{
public:
  SignupHandler(UtaxiApp* app) : ActionHandler(app) {}
  Response *callback(Request *);
};

class AddTripHandler : public ActionHandler
{
public:
  AddTripHandler(UtaxiApp* app) : ActionHandler(app) {}
  Response* callback(Request*);
};

class DeleteTripHandler : public ActionHandler
{
public:
  DeleteTripHandler(UtaxiApp* app) : ActionHandler(app) {}
  Response* callback(Request*);
};

class ShowListHandler : public ActionHandler
{
public:
  ShowListHandler(UtaxiApp* app) : ActionHandler(app) {}
  Response* callback(Request*);
};

class AcceptTripHandler : public ActionHandler
{
public:
  AcceptTripHandler(UtaxiApp* app) : ActionHandler(app) {}
  Response* callback(Request*);
};

class FinishTripHandler : public ActionHandler
{
public:
  FinishTripHandler(UtaxiApp* app) : ActionHandler(app) {}
  Response* callback(Request*);
};





class RandomNumberHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class UploadHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class ColorHandler : public TemplateHandler {
public:
  ColorHandler(std::string filePath);
  std::map<std::string, std::string> handle(Request *req);
};

#endif
