#include "car.hpp"
using namespace std;

Car::Car(){ }

Car::Car(const Car& c) : brand(c.brand), model(c.model), color(c.color), speed(c.speed), fuelLevel(c.fuelLevel), engineState(c.engineState) { }

void Car::setBrand(const std::string& b){
    this->brand=b;
}

void Car::setModel(const std::string& m){
    this->model=m;
}

void Car::setColor(const std::string& c){
    this->color=c;
}

string Car::getBrand() const{
    return this->brand;
    }

string Car::getModel() const{
    return this->model;
    }

string Car::getColor() const{
    return this->color;
    }
    
int Car::getSpeed() const{
    return this->speed;
    }

int Car::getFuelLevel() const{
    return this->fuelLevel;
    }

bool Car::getEngineState() const{
        return this->engineState;
    }
    

std::string Car::toString() const{
    std::string result;
    result+=getBrand();
    result += " | ";
    result+=getModel();
    result += " | ";
    result+=getColor();
    result += " | ";
    result += to_string(getSpeed());
    result += " | ";
    result += to_string(getFuelLevel());
    result += " | ";
    if (getEngineState() == true){
        result+= "Encendido";
    } else {
        result += "Apagado";
    }
    return result;
    }

bool Car::startEngine(){
    if(fuelLevel > 0 and engineState==false ){
        this->engineState = true;
        return true;
    }
    else {
        return false; 
    }
    }

bool Car::killEngine(){
    if(engineState==true ){
        this->engineState = false;
        return true;
    }
    else {
        return false;
    }
}

bool Car::accelerate(){
    if(this->engineState == true and this->fuelLevel >= 5 and this->speed < 200){
        this->speed = this->speed + 10;
        this->fuelLevel = this->fuelLevel - 5;
        return true;
    }
    else {
        return false;
    }
}

bool Car::brake(){
    if(this->speed > 10){
        this->speed = this->speed -10;
        return true;
    }
    else {
        return false;
    }
}

bool Car::addFuel(){
    if(this->fuelLevel < 100){
        this->fuelLevel = this->fuelLevel + 5;
        return true;
    }
    else {
        return false;
    }
}

