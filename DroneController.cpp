#include "DroneController.h"
#include <iostream>

using namespace std;

DroneController::DroneController() : altitude(0), speed(0), battery(100) {}

int DroneController::getAltitude() const { return altitude; }
void DroneController::addAltitude(int val) { altitude += val; }
int DroneController::getSpeed() const { return speed; }
void DroneController::addSpeed(int val) { speed += val; }
int DroneController::getBattery() const { return battery; }
void DroneController::costBattery(int val) { battery -= val; }
void DroneController::addBattery(int val) { battery += val; }

// ==========================================
// TODO 1: 实现命令处理函数 (使用 void* 转换)
// ==========================================
int handleTakeOff(void* ctx, int val) {
    // 【示例】这里已经给出完整的 TakeOff 实现，供你参考：
    // 1. 将 void* ctx 转换为 DroneController* 类型的指针
    DroneController* drone = (DroneController*)ctx;

    int cost = 10; // 起飞固定消耗 10 点电量
    // 2. 检查电量是否足够
    if (drone->getBattery() < cost) {
        return -1; // 电量不足，直接返回 -1
    }

    // 3. 扣除电量并更新状态
    drone->costBattery(cost);
    drone->addAltitude(val);

    // 4. 返回当前高度
    return drone->getAltitude();
}

int handleSpeedUp(void* ctx, int val) {
    // 1. 将 ctx 转换为 DroneController* 指针 (参考 handleTakeOff)
    // 2. 计算消耗 (val / 2)
    // 3. 检查电量是否足够，如果不足返回 -1
    // 4. 扣除电量并更新速度
    // 5. 返回当前速度
    DroneController* drone = (DroneController *) ctx;
    int cost = val / 2;
    if (drone->getBattery() < cost) return -1;
    drone->costBattery(cost);
    drone->addSpeed(val);
    return drone->getSpeed();
}

int handleHover(void* ctx, int val) {
    // 1. 转换指针
    // 2. 计算消耗 (悬停消耗 val 点电量)
    // 3. 检查电量并扣除 (状态不变)
    // 4. 返回当前电量
    DroneController* drone = (DroneController*)ctx;
    int cost = val;
    if(drone->getBattery()<cost)
    return -1;
    drone->costBattery(cost);
    return drone->getBattery();
}

int handleCharge(void* ctx, int val) {
    // 充电无需校验电量消耗
    // 直接增加电量(val)，然后返回当前电量
    DroneController* drone = (DroneController*)ctx;
    drone->addBattery(val);
    return drone->getBattery();
}

// ==========================================
// TODO 2: 实现核心执行逻辑 (解析字符串 + 使用函数指针)
// ==========================================
int DroneController::execute(const string& command) {
    size_t leftPos = command.find('(');
    size_t rightPos = command.find(')');


    // 【提示】这里帮你完成了字符串的解析，提取出操作名和数值
    string opName = command.substr(0, leftPos);
    int len = rightPos - leftPos - 1;
    int val = stoi(command.substr(leftPos + 1, len));

    // 函数指针定义
    CommandHandler handler = nullptr;

    // 根据 opName 分配对应的函数指针
    if (opName == "TakeOff") {
        handler = handleTakeOff;
    }
    else if (opName == "SpeedUp") {
        handler = handleSpeedUp;
    }
    // TODO: 请继续补充 Hover 和 Charge 的 else if 判断，并绑定对应的 handler
    // else if (...) {
    //     ...
    // }
    else if (opName == "Hover") {
        handler = handleHover;
    }
    else if (opName == "Charge") {
        handler = handleCharge;
    }

    if (handler != nullptr) {
        // 【提示】：如何调用函数指针？
        // 这里的 handler 实际上指向了上面的某一个函数（例如 handleTakeOff）。
        // handleTakeOff 的签名是：int handleTakeOff(void* ctx, int val)
        // 
        // 第一个参数需要当前对象的地址，以便它能修改自己的状态。在类内部，用 this 指针代表自己！
        // 当传入 this 时，C++ 会自动将 DroneController* 隐式转为期望的 void*
        // 第二个参数则是解析出来的数值 val。
        //
        // TODO: 请取消下方代码的注释，并简单补充，完成回调执行
        int result = handler(this, val);
        return result;

    }

    return -1;
}

