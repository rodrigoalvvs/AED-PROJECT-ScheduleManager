//
// Created by admin1 on 19-10-2023.
//

#include <iostream>
#include <sstream>
#include "../include/Period.h"


/**
 * @brief Constructs a Period object with specified attributes.
 *
 * This constructor initializes a Period object with the given attributes, including the day of the week (weekDay_), start hour (startHour_),
 * duration (duration_), and type (type_) of the class period.

 * @param weekDay_ The day of the week on which the class period occurs.
 * @param startHour_ The start hour of the class period.
 * @param duration_ The duration of the class period.
 * @param type_ The type of the class period (e.g., T, TP, PL).
 */
Period::Period(const std::string& weekDay_, float startHour_, float duration_, const std::string& type_) {
    this->weekDay = weekDay_;
    this->startHour = startHour_;
    this->duration = duration_;
    this->type = type_;
}

/**
 * @brief Retrieves the day of the week for this class period.
 *
 * @return A constant reference to the day of the week (e.g., "Monday").
 */
const std::string& Period::getWeekDay() const {
    return this->weekDay;
}

/**
 * @brief Retrieves the type of this class period.
 *
 * @return A constant reference to the class period type (e.g., "lecture", "lab").
 */
const std::string& Period::getPeriodType() const {
    return this->type;
}

/**
 * @brief Retrieves the start time of this class period.
 *
 * @return An `Hour` object representing the start time.
 */
Hour Period::getStartTime() const {
    int startHour_ = this->startHour;
    int startMinute_ = (this->startHour - startHour_) * 60;
    return {startHour_, startMinute_};
}

/**
 * @brief Retrieves the end time of this class period.
 *
 * @return An `Hour` object representing the end time.
 */
Hour Period::getEndTime() const {
    int endHour_ = this->startHour + this->duration;
    int endMinute_ = (this->startHour + this->duration - endHour_) * 60;
    return {endHour_, endMinute_};
}

/**
 * @brief Retrieves the duration of this class period in hours.
 *
 * @return The duration of the class period in hours.
 */
float Period::getDuration() const {
    return this->duration;
}

/**
 * @brief Set the day of the week for this class period.
 *
 * This function allows setting the day of the week for this class period.

 * @param weekDay_ A constant reference to the new day of the week (e.g., "Monday").
 */
void Period::setWeekDay(const std::string &weekDay_) {
    this->weekDay = weekDay_;
}

/**
 * @brief Set the type of this class period.
 *
 * This function allows setting the type of this class period, such as "lecture" or "lab."

 * @param classType_ A constant reference to the new class period type.
 */
void Period::setPeriodType(const std::string &classType_) {
    this->type = classType_;
}

/**
 * @brief Set the start hour for this class period.
 *
 * This function allows setting the start hour for this class period.

 * @param startHour_ The new start hour for the class period.
 */
void Period::setStartHour(float startHour_) {
    this->startHour = startHour_;
}

/**
 * @brief Set the duration for this class period.
 *
 * This function allows setting the duration for this class period in hours.

 * @param duration_ The new duration in hours for the class period.
 */

void Period::setDuration(float duration_) {
    this->duration = duration_;
}


/**
 * @brief Checks if this class period overlaps with another.
 *
 * This function checks if this class period overlaps with another class period provided as a shared pointer.

 * @param otherPeriod A shared pointer to another class period.
 * @return true if there is an overlap, false if there is no overlap.
 */
bool Period::overlaps(std::shared_ptr<Period> otherPeriod) const {
    if (this->getStartTime() < otherPeriod->getEndTime() && this->getEndTime() > otherPeriod->getStartTime()) {
        // There is an overlap
        return true;
    }

    // No overlap
    return false;
}
