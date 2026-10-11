#ifndef __CAR_H__
#define __CAR_H__
#include <string>


class Car{
private:
    std::string brand;
    std::string model;
    std::string color;
    int speed = 0;
    int fuelLevel = 100;
    bool engineState = false;

public:
    Car();
    Car(const Car&);
    void setBrand(const std::string&);
    void setModel(const std::string&);
    void setColor(const std::string&);

    std::string getBrand() const;
    std::string getModel() const;
    std::string getColor() const;
    int getSpeed() const;
    int getFuelLevel() const;
    bool getEngineState() const;

    std::string toString() const;

    bool startEngine();
    bool killEngine();
    bool accelerate();
    bool brake();
    bool addFuel();

};
#endif // __CAR_H__