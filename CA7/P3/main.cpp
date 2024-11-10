#include "handlers.hpp"
#include <iostream>
#include <iomanip>


using namespace std;

int main(int argc, char* argv[]) {
    Utaxi utaxi;
    utaxi.add_locations(argv);
    Server server(5000);
    
    server.get("/", new ShowPage("html_files/home.html"));
    server.get("/signup-form", new ShowPage("html_files/signup.html"));
    server.get("/style.css", new ShowPage("html_files/style.css"));
    server.get("/taxi_driver.png", new ShowImage("html_files/taxi_driver.png"));
    server.get("/SignUp.jpg", new ShowImage("html_files/SignUp.jpg"));
    server.get("/AskTrip.jpg", new ShowImage("html_files/AskTrip.jpg"));
    server.get("/CancelTrip.jpg", new ShowImage("html_files/CancelTrip.jpg"));
    server.get("/AcceptTrip.jpg", new ShowImage("html_files/AcceptTrip.jpg"));
    server.get("/FinishTrip.jpg", new ShowImage("html_files/FinishTrip.jpg"));
    server.get("/TripDetails.jpg", new ShowImage("html_files/TripDetails.jpg"));
    server.get("/TripList.jpg", new ShowImage("html_files/TripList.jpg"));
    server.get("/BadRequest.jpg", new ShowImage("html_files/BadRequest.jpg"));
    server.get("/Empty.jpg", new ShowImage("html_files/Empty.jpg"));
    server.get("/NotFound.jpg", new ShowImage("html_files/NotFound.jpg"));
    server.get("/PermissionDenied.jpg", new ShowImage("html_files/PermissionDenied.jpg"));
    server.get("/Home.jpg", new ShowImage("html_files/Home.jpg"));
    server.get("/Ok.jpg", new ShowImage("html_files/Ok.jpg"));
    server.post("/signup", new Signup(&utaxi));
    server.get("/ok", new ShowPage("html_files/ok_response.html"));
    server.get("/Bad_Request", new ShowPage("html_files/BadRequest_response.html"));
    server.get("/Permission_Denied", new ShowPage("html_files/PermissionDenied_response.html"));
    server.get("/Not_Found", new ShowPage("html_files/NotFound_response.html"));
    server.get("/EMPTY", new ShowPage("html_files/Empty_response.html"));   
    server.get("/post-trips-form", new ShowPage("html_files/post_trips.html"));  
    server.get("/post-trips", new AskForTrip(&utaxi));
    server.get("/show-cost", new ShowCost(&utaxi)); 
    server.get("/delete-trip-form", new ShowPage("html_files/delete-trip.html"));
    server.get("/delete-trip", new DeleteTrip(&utaxi));
    server.get("/get-all-trips-form", new ShowPage("html_files/get-all-trips.html"));
    server.get("/get-all-trips", new GetAllTrips(&utaxi));
    server.get("/get-a-trip-form", new ShowPage("html_files/get-one-trip.html"));
    server.get("/get-a-trip", new GetOneTrip(&utaxi));
    server.get("/accept-a-trip-form", new ShowPage("html_files/accept-trip.html"));
    server.get("/accept-a-trip", new AcceptTrip(&utaxi));
    server.get("/finish-a-trip-form", new ShowPage("html_files/finish-trip.html"));
    server.get("/finish-a-trip", new FinishTrip(&utaxi));
    
    server.run();
    return 0;
}