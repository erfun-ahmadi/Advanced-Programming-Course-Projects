#include "handlers.hpp"

using namespace std;

Signup::Signup(Utaxi *_utaxi) {
    utaxi = _utaxi;
}

Response *Signup::callback(Request *req) {
    string username = req->getBodyParam(USERNAME);
    string role = req->getBodyParam(ROLE);
    vector <string> commands = {username, role};
    try {
        utaxi->signup(commands);
        return Response::redirect("/ok");
    }
    catch (Error &error) {
        string slash = "/";
        string error_type = slash + error.get_error();
        return Response::redirect(error_type);
    }
}




AskForTrip::AskForTrip(Utaxi *_utaxi) {
    utaxi = _utaxi;
}

Response *AskForTrip::callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string username = req->getQueryParam(USERNAME);
    string origin = req->getQueryParam(ORIGIN);
    string destination = req->getQueryParam(DESTINATION);
    string is_in_hurry = req->getQueryParam(IN_HURRY);
    vector <string> commands = {username, origin, destination, is_in_hurry};
    try {
        int id = utaxi->aplly_for_trip(commands);
        ostringstream body;
        body 
            << "<!DOCTYPE html>" << endl
            << "<html>" << endl
            << "<head><title>Utaxi</title><link rel='stylesheet' href='style.css'></head>" << endl
            << "<body><p class='Text'>" << id << "</p><br><br><a href='/' ><img class='Image' src='Home.jpg'></a><br>" << endl
            << "</html>" << endl;
        res->setBody(body.str());
        return res;
    }
    catch (Error &error) {
        string slash = "/";
        string error_type = slash + error.get_error();
        return Response::redirect(error_type);
    }
}




ShowCost::ShowCost(Utaxi *_utaxi) {
    utaxi = _utaxi;
}

Response *ShowCost::callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string username = req->getQueryParam(USERNAME);
    string origin = req->getQueryParam(ORIGIN);
    string destination = req->getQueryParam(DESTINATION);
    string is_in_hurry = req->getQueryParam(IN_HURRY);
    vector <string> commands = {username, origin, destination, is_in_hurry};
    try {
        double cost = utaxi->get_price(commands);
        ostringstream body;
        body 
            << "<!DOCTYPE html>" << endl
            << "<html>" << endl
            << "<head><title>Utaxi</title><link rel='stylesheet' href='style.css'></head>" << endl
            << "<body><p class='Text'>" << cost << "</p><br><br>img class='Image' src='Home.jpg'></a></body>" << endl
            << "</html>" << endl;
        res->setBody(body.str());
        return res;
    }
    catch (Error &error) {
        string slash = "/";
        string error_type = slash + error.get_error();
        return Response::redirect(error_type); 
    }
}





DeleteTrip::DeleteTrip(Utaxi *_utaxi) {
    utaxi = _utaxi;
}

Response *DeleteTrip::callback(Request *req) {
    string username = req->getQueryParam(USERNAME);
    string trip_id = req->getQueryParam("trip_id");
    vector <string> commands = {username, trip_id};
    try {
        utaxi->delete_trip(commands);
        return Response::redirect("/ok");
    }
    catch (Error &error) {
        string slash = "/";
        string error_type = slash + error.get_error();
        return Response::redirect(error_type);
    }
}





GetAllTrips::GetAllTrips(Utaxi *_utaxi) {
    utaxi = _utaxi;
}

Response *GetAllTrips::callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string username = req->getQueryParam(USERNAME);
    string is_sorted_by_cost = req->getQueryParam("sort_by_cost");
    vector <string> commands = {username, is_sorted_by_cost};
    try {
        vector <Trip*> all_trips = utaxi->show_all_trips(commands);
        ostringstream body;
        body 
            << "<!DOCTYPE html>" << endl
            << "<html>" << endl
            << "<head><title>Utaxi</title><link rel='stylesheet' href='style.css'></head>" << endl
            << "<body><table>" << endl 
            << "<tr>" << endl
            << "<th>ID</th>" << endl
            << "<th>Username</th>" << endl
            << "<th>Origin</th>" << endl
            << "<th>Destination</th>" << endl
            << "<th>Cost</th>" << endl
            << "<th>Status</th>" << endl
            << "</tr>" << endl;
        for (int num_of_trip = 0; num_of_trip < all_trips.size(); num_of_trip++) {
            body
                << "<tr><td>" << all_trips[num_of_trip]->get_id() << "</td><td>" << all_trips[num_of_trip]->get_username() << "</td><td>" <<
                   all_trips[num_of_trip]->get_origin() << "</td><td>" << all_trips[num_of_trip]->get_destination() << 
                   "</td><td>" << all_trips[num_of_trip]->get_cost() << "</td><td>" << all_trips[num_of_trip]->get_status() << "</td></tr>" << endl;
        }
        body 
            << "</table>" << endl
            << "<a href='/' ><img class='Image' src='Home.jpg'></a></body>" << endl
            << "</html>" << endl;
        res->setBody(body.str());
        return res;
    }
    catch (Error &error) {
        string slash = "/";
        string error_type = slash + error.get_error();
        return Response::redirect(error_type);
    }
}





GetOneTrip::GetOneTrip(Utaxi *_utaxi) {
    utaxi = _utaxi;
}

Response *GetOneTrip::callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string username = req->getQueryParam(USERNAME);
    string trip_id = req->getQueryParam("trip_id");
    vector <string> commands = {username, trip_id};
    try {
        Trip* wanted_trip = utaxi->show_specefic_trip(commands);
        ostringstream body;
        body 
                << "<!DOCTYPE html>" << endl
                << "<html>" << endl
                << "<head><title>Utaxi</title><link rel='stylesheet' href='style.css'></head>" << endl
                << "<body><table>" << endl 
                << "<tr>" << endl
                << "<th>ID</th>" << endl
                << "<th>Username</th>" << endl
                << "<th>Origin</th>" << endl
                << "<th>Destination</th>" << endl
                << "<th>Cost</th>" << endl
                << "<th>Status</th>" << endl
                << "</tr>" << endl << 
                "<tr><td>" << wanted_trip->get_id() << "</td><td>" << wanted_trip->get_username() << "</td><td>" <<
                wanted_trip->get_origin() << "</td><td>" << wanted_trip->get_destination() << "</td><td>" <<
                wanted_trip->get_cost() << "</td><td>" << wanted_trip->get_status() << "</td></tr>" << 
                "</table>" << endl <<
                "<a href='/' ><img class='Image' src='Home.jpg'></a></body>" << endl <<
                "</html>" << endl;
        res->setBody(body.str());
        return res;
    }
    catch (Error &error) {
        string slash = "/";
        string error_type = slash + error.get_error();
        return Response::redirect(error_type);
    }
}





AcceptTrip::AcceptTrip(Utaxi *_utaxi) {
    utaxi = _utaxi;
}

Response *AcceptTrip::callback(Request *req) {
    string username = req->getQueryParam(USERNAME);
    string trip_id = req->getQueryParam("trip_id");
    vector <string> commands = {username, trip_id};
    try {
        utaxi->accept_trip(commands);
        return Response::redirect("/ok");
    }
    catch (Error &error) {
        string slash = "/";
        string error_type = slash + error.get_error();
        return Response::redirect(error_type);
    }
}





FinishTrip::FinishTrip(Utaxi *_utaxi) {
    utaxi = _utaxi;
}

Response *FinishTrip::callback(Request *req) {
    string username = req->getQueryParam(USERNAME);
    string trip_id = req->getQueryParam("trip_id");
    vector <string> commands = {username, trip_id};
    try {
        utaxi->finish_trip(commands);
        return Response::redirect("/ok");
    }
    catch (Error &error) {
        string slash = "/";
        string error_type = slash + error.get_error();
        return Response::redirect(error_type);
    }
}