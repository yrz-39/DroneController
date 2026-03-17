#ifndef DRONECONTROLLER_H
#define DRONECONTROLLER_H

#include <string>

class DroneController {
private:
    int altitude;
    int speed;
    int battery;

public:
    DroneController();

    // 状态读写辅助函数
    int getAltitude() const;
    void addAltitude(int val);
    int getSpeed() const;
    void addSpeed(int val);
    int getBattery() const;
    void costBattery(int val);
    void addBattery(int val);

    // 核心执行逻辑
    int execute(const std::string& command);
};

// 定义函数指针类型，ctx将传入 DroneController*
typedef int (*CommandHandler)(void* ctx, int val);

// 命令处理函数声明
int handleTakeOff(void* ctx, int val);
int handleSpeedUp(void* ctx, int val);
int handleHover(void* ctx, int val);
int handleCharge(void* ctx, int val);

#endif
