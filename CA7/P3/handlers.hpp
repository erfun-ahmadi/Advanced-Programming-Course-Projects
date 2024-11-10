#ifndef HANDLER_H
#define HANDLER_H

#include "server/server.hpp"
#include "7.2/utaxi.h"

class Signup : public RequestHandler {
private:
    Utaxi *utaxi;
public:
    Signup(Utaxi *_utaxi);
    Response *callback(Request *);
};

class AskForTrip : public RequestHandler {
private:
    Utaxi *utaxi;
public:
    AskForTrip(Utaxi *_utaxi);
    Response *callback(Request *);
};

class ShowCost : public RequestHandler {
private:
    Utaxi *utaxi;
public:
    ShowCost(Utaxi *_utaxi);
    Response *callback(Request *);
};

class DeleteTrip : public RequestHandler {
private:
    Utaxi *utaxi;
public:
    DeleteTrip(Utaxi *_utaxi);
    Response *callback(Request *);
};

class GetAllTrips : public RequestHandler {
private:
    Utaxi *utaxi;
public:
    GetAllTrips(Utaxi *_utaxi);
    Response *callback(Request *); 
};

class GetOneTrip : public RequestHandler {
private:
    Utaxi *utaxi;
public:
    GetOneTrip(Utaxi *_utaxi);
    Response *callback(Request *); 
};

class AcceptTrip : public RequestHandler {
private:
    Utaxi *utaxi;
public:
    AcceptTrip(Utaxi *_utaxi);
    Response *callback(Request *); 
};

class FinishTrip : public RequestHandler {
private:
    Utaxi *utaxi;
public:
    FinishTrip(Utaxi *_utaxi);
    Response *callback(Request *); 
};


#endif