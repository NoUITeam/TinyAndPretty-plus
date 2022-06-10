#ifndef __SCHEDULE_CONTROL_H__
#define __SCHEDULE_CONTROL_H__
#include<common.h>
#include<interfaces.h>
#define WEEK_NUM_TERM 20

#define SET_TIME(code,timenum) ({code |= (1 << (timenum-1));})
#define WEEK_CHECK(weeks,week) ({(weeks >> (week-1)) & 0x1;})

class Course{
private:
    std::string id;
    std::string name;
    int time;
    std::string professor;
    std::string location;
    std::string room;
public:
    Course(std::string id = "0");
    int Query();
    SimpleJson::Object Format();
};

class Event{
private:
    std::string id;
    std::string name;
    std::string start;
    std::string end;
    std::string location;
    std::string describe;
public:
    Event(std::string id="0");
    int Parse(std::string detail);
    SimpleJson::Object Format();
};

#endif