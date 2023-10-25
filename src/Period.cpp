//
// Created by admin1 on 19-10-2023.
//

#include <iostream>
#include <sstream>
#include "../include/Period.h"

Period::Period(const std::string& weekDay_, float startHour_, float duration_, const std::string& type_) {
    this->weekDay = weekDay_;
    this->startHour = startHour_;
    this->duration = duration_;
    this->type = type_;
}

const std::string& Period::getWeekDay() const {
    return this->weekDay;
}

const std::string& Period::getClassType() const {
    return this->type;
}

float Period::getStartHour() const {
    return this->startHour;
}

float Period::getDuration() const {
    return this->duration;
}

void Period::setWeekDay(const std::string &weekDay_) {
    this->weekDay = weekDay_;
}

void Period::setClassType(const std::string &classType_) {
    this->type = classType_;
}

void Period::setStartHour(float startHour_) {
    this->startHour = startHour_;
}

void Period::setDuration(float duration_) {
    this->duration = duration_;
}

