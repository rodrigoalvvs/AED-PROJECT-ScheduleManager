//
// Created by admin1 on 19-10-2023.
//

#ifndef AED_PROJ_PERIOD_H
#define AED_PROJ_PERIOD_H

#include <string>

class Period{
private:
    float startHour;
    float duration;
    std::string weekDay;
    std::string type;
public:
    // Constructors and destructors
    Period(const std::string& weekDay_, float startHour_, float duration_, const std::string& type_);

    // Class getters and setters
    const std::string& getWeekDay() const;
    const std::string& getClassType() const;
    float getStartHour() const;
    float getDuration() const;

    void setWeekDay( const std::string& weekDay_);
    void setClassType(const std::string& classType_);
    void setStartHour(float startHour_);
    void setDuration(float duration_);

    // Class methods
};


#endif //AED_PROJ_PERIOD_H
