#ifndef MYDRONECONTROLLER.H
#define MYDRONECONTROLLER .H
#include<string>
#include<unordered_map>
class DroneController
{
  private:
    int altitude;
    int speed;
    int battery;
    
  public:
    DroneController();
    //CommandHandler是一个指针，指向DroneController类中参数为int 返回值为int的成员函数
    using CommandHandler=int (DroneController::*)(int); 
    //辅助函数
    int getAltitude();
    int getSpeed();
    int getBattery();
    void costBattery(int val);
    void addBattery(int val);
    void addSpeed(int val);
    void addAltitude(int val);
    //执行函数
    int handleTakeOff(int val);
    int handleSpeedUp(int val);
    int handleHover(int val);
    int handleCharge(int val);

    int execute(const std::string&command,int val);
    private:
    std::unordered_map<std::string,CommandHandler>handlers;
};

#endif