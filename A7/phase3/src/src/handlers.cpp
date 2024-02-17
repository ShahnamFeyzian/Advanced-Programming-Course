#include "handlers.hpp"

using namespace std;

Response *SignupHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string init_role = req->getBodyParam("role");
  
  Role role;
  if(init_role == "driver") role = driver;
  else role = passenger;

  try
  {
    app->add_user(username, role);
  }
  catch(Exception& exp)
  {
    exp.show_message();
    return Response::redirect("/signup_inc");
  }
  
  cout << "username: " << username << ",\trole: " << init_role << endl;
  Response *res = Response::redirect("/success");
  return res;
}

Response *AddTripHandler::callback(Request *req)
{
  string name = req->getBodyParam("username");
  string origin = req->getBodyParam("origin");
  string destination = req->getBodyParam("destination");
  string in_hurry = req->getBodyParam("in_hurry");
  string action = req->getBodyParam("action");

  bool get_cost = (action=="cost");
  bool hurry = (in_hurry=="yes");
  float result;
  string title = (get_cost ? "Travel Cost: " : "Travel ID: ");

  try
  {
    if(get_cost) result = app->get_cost(name, origin, destination, hurry); 
    else result = app->add_trip(name, origin, destination, hurry);
  }
  catch(Exception& exp)
  {
    if(exp.get_code() == 401) return Response::redirect("/401");
    if(exp.get_code() == 402) return Response::redirect("/402");
    if(exp.get_code() == 403) return Response::redirect("/403");
  }

  cout << name << " " << origin << " " << destination << " " << hurry << endl;

  Response* res = new Response;
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>UTYAXI</h1>";
  body += "<p>";
  body += title;
  body += to_string(result);
  body += "</p><br/>";
  body += "<a href=\"/\">Home</a>";
  body += "</body>";
  body += "</html>";
  res->setHeader("Content-Type", "text/html");
  res->setBody(body);
  return res;
}

Response *DeleteTripHandler::callback(Request *req)
{
  string name = req->getBodyParam("username");
  string id = req->getBodyParam("id");

  try
  {
    app->delete_trip(name, stoi(id));
  }
  catch(Exception& exp)
  {
    if(exp.get_code() == 401) return Response::redirect("/401");
    if(exp.get_code() == 402) return Response::redirect("/402");
    if(exp.get_code() == 403) return Response::redirect("/403");
  }

  cout << name << " " << id << endl;

  return Response::redirect("/success");
}

Response *ShowListHandler::callback(Request *req)
{
  string name = req->getBodyParam("username");
  string sort = req->getBodyParam("sort");

  bool by_cost = (sort=="cost");
  vector<vector<string>> list;

  try
  {
    list = app->present_all_trips(name, by_cost);
  }
  catch(Exception& exp)
  {
    if(exp.get_code() == 400) return Response::redirect("/400");
    if(exp.get_code() == 401) return Response::redirect("/401");
    if(exp.get_code() == 403) return Response::redirect("/403");
  }

  cout << name << " " << sort << endl;

  Response* res = new Response;
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"margin=5px\">";
  body += "<h1 style=\"text-align: center;\">Trips</h1>";
  body += "<ul>";
  for(int i=0; i<list.size(); i++)
  {
    if(list[i].size() == 0) continue;
    body += "<li>";
    for(int j=0; j<list[i].size(); j++) body += (list[i][j] + " ");
    body += "</li>";
  }
  body += "</ul>";
  body += "<a href=\"/\"><button>Home</button></a>";
  body += "<a href=\"/accept\"><button>Accept</button></a>";
  body += "<a href=\"/finish\"><button>Finish</button></a>";
  body += "</body>";
  body += "</html>";
  res->setHeader("Content-Type", "text/html");
  res->setBody(body);
  return res;
}

Response *AcceptTripHandler::callback(Request *req)
{
  string name = req->getBodyParam("username");
  string id = req->getBodyParam("id");

  try
  {
    app->accept_trip(name, stoi(id));
  }
  catch(Exception& exp)
  {
    if(exp.get_code() == 401) return Response::redirect("/401");
    if(exp.get_code() == 402) return Response::redirect("/402");
    if(exp.get_code() == 403) return Response::redirect("/403");
  }

  cout << name << " " << id << endl;

  return Response::redirect("/success");
}

Response *FinishTripHandler::callback(Request *req)
{
  string name = req->getBodyParam("username");
  string id = req->getBodyParam("id");

  try
  {
    app->finish_trip(name, stoi(id));
  }
  catch(Exception& exp)
  {
    if(exp.get_code() == 401) return Response::redirect("/401");
    if(exp.get_code() == 402) return Response::redirect("/402");
    if(exp.get_code() == 403) return Response::redirect("/403");
  }

  cout << name << " " << id << endl;

  return Response::redirect("/success");
}

