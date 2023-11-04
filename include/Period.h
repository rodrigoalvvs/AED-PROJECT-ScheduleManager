//
// Created by admin1 on 19-10-2023.
//

#ifndef AED_PROJ_PERIOD_H
#define AED_PROJ_PERIOD_H

#include <string>
#include <memory>
/**
 * @struct Hour
 * @brief Represents a time of day in hours and minutes.
 */
struct Hour {
    int hour;     ///< The hour component.
    int minute;   ///< The minute component.

    /**
     * @brief Compare two Hour objects.
     * @param other Another Hour object to compare with.
     * @return True if this Hour is less than other, otherwise false.
     */
    bool operator<(const Hour& other) const {
        int totalMinutesA = this->hour * 60 + this->minute;
        int totalMinutesB = other.hour * 60 + other.minute;
        return totalMinutesA < totalMinutesB;
    }

    /**
     * @brief Compare two Hour objects.
     * @param other Another Hour object to compare with.
     * @return True if this Hour is greater than other, otherwise false.
     */
    bool operator>(const Hour& other) const {
        int totalMinutesA = this->hour * 60 + this->minute;
        int totalMinutesB = other.hour * 60 + other.minute;
        return totalMinutesA > totalMinutesB;
    }

    /**
     * @brief Compare two Hour objects.
     * @param other Another Hour object to compare with.
     * @return True if this Hour is greater than or equal to other, otherwise false.
     */
    bool operator>=(const Hour& other) const {
        int totalMinutesA = this->hour * 60 + this->minute;
        int totalMinutesB = other.hour * 60 + other.minute;
        return totalMinutesA >= totalMinutesB;
    }

    /**
     * @brief Compare two Hour objects.
     * @param other Another Hour object to compare with.
     * @return True if this Hour is inferior than or equal to other, otherwise false.
     */
    bool operator<=(const Hour& other) const {
        int totalMinutesA = this->hour * 60 + this->minute;
        int totalMinutesB = other.hour * 60 + other.minute;
        return totalMinutesA <= totalMinutesB;
    }

    /**
     * @brief Compare two Hour objects for equality.
     * @param other Another Hour object to compare with.
     * @return True if this Hour is equal to other, otherwise false.
     */
    bool operator==(const Hour& other) const {
        return hour == other.hour && minute == other.minute;
    }
};

/**
 * @class Period
 * @brief Represents a time period with a start hour, duration, day of the week, and type.
 */
class Period {
private:
    float startHour;       ///< The starting hour of the period.
    float duration;        ///< The duration of the period.
    std::string weekDay;   ///< The day of the week for the period.
    std::string type;      ///< The type of the period (e.g., "TP", "T", "PL").

public:
    // Constructors and destructors
    Period(const std::string& weekDay_, float startHour_, float duration_, const std::string& type_);

    // Class getters and setters
    const std::string& getWeekDay() const;
    const std::string& getPeriodType() const;

    Hour getStartTime() const;
    Hour getEndTime() const;
    float getDuration() const;

    void setWeekDay( const std::string& weekDay_);
    void setPeriodType(const std::string& classType_);
    void setStartHour(float startHour_);
    void setDuration(float duration_);

    bool overlaps(std::shared_ptr<Period> otherPeriod) const;

    // Class methods
};


#endif //AED_PROJ_PERIOD_H
