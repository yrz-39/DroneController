#include "MyDroneController.h"
#include <iostream>
DroneController::DroneController() : altitude(0), speed(0), battery(100) {
    handlers["takeoff"] = &DroneController::handleTakeOff;
    handlers["speedup"] =&DroneController::handleSpeedUp;
    handlers["hover"]=&DroneController::handleHover;
    handlers["charge"]=&DroneController::handleCharge;
};
void DroneController::addBattery(int val)
{
    this->battery += val;
}
void DroneController::costBattery(int val)
{
    this->battery -= val;
}
int DroneController::getAltitude()
{
    return this->altitude;
}
int DroneController::getBattery()
{
    return this->battery;
}
int DroneController::getSpeed()
{
    return this->speed;
}
int DroneController::execute(const std::string&command,int val){
    auto it=handlers.find(command);
    if(it==handlers.end()){
        return -1;
    }
    CommandHandler handler=it->second;
    return (this->*handler)(val);
}