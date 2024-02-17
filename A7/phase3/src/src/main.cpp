#include "handlers.hpp"
#include "my_server.hpp"
#include"utaxi_app.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  srand(time(NULL)); // for rand

  try {
    UtaxiApp* app = new UtaxiApp(argv[1]);
    MyServer server(5000);
    server.setNotFoundErrPage("static/404.html");
    server.get("/signup", new ShowPage("static/signup.html"));
    server.get("/signup_inc", new ShowPage("static/signup_inc.html"));
    server.post("/signup", new SignupHandler(app));
    server.get("/passenger", new ShowPage("static/passenger.html"));
    server.get("/add_trip", new ShowPage("static/add_trip.html"));
    server.post("/add_trip", new AddTripHandler(app));
    server.get("/delete_trip", new ShowPage("static/delete_trip.html"));
    server.post("/delete_trip", new DeleteTripHandler(app));
    server.get("/driver", new ShowPage("static/driver.html"));
    server.get("/list", new ShowPage("static/list_form.html"));
    server.post("/list", new ShowListHandler(app));
    server.get("/accept", new ShowPage("static/accept_form.html"));
    server.post("/accept", new AcceptTripHandler(app));
    server.get("/finish", new ShowPage("static/finish_form.html"));
    server.post("/finish", new FinishTripHandler(app));

    server.get("/400", new ShowPage("static/400.html"));
    server.get("/401", new ShowPage("static/401.html"));
    server.get("/402", new ShowPage("static/402.html"));
    server.get("/403", new ShowPage("static/403.html"));
    server.get("/success", new ShowPage("static/success.html"));

    server.get("/", new ShowPage("static/home.html"));
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
