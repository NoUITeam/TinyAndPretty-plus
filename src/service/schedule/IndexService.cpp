#include<service/schedule/ScheduleControl.h>
#include <service/sys/ServerSys.h>
#include <service/user/UserControl.h>
using namespace std;
using namespace NEDBSTD;
using namespace UTILSTD;

def_HttpEntry(ScheduleIndex,req){
    std::string userid(req.queryHeader("userid"));
    std::string token(req.queryHeader("token"));
    std::string function(req.queryHeader("function"));
    std::string body = req.getBody();
    CONSOLE_LOG(0,1,1,"Sche-Req [function='%s', userid='%s', token='%s']\n", function.c_str(),userid.c_str(),token.c_str());
    if(function != "fetch" && function != "add" && function != "update"){
        return new HttpResponse{"REQUEST_FUNCTION_UNKNOWN",HTTP_STATUS_400};
    }
    if(TokenCheck(userid,token) != TOKEN_ACCESS){
        return new HttpResponse("ACCESS_DENIED",HTTP_STATUS_401);
    }
    
}

def_HttpEntry(TimetableIndex,req){
    std::string userid(req.queryHeader("userid"));
    std::string token(req.queryHeader("token"));
    std::string function(req.queryHeader("function"));
    std::string body = req.getBody();
    CONSOLE_LOG(0,1,1,"Table-Req [function='%s', userid='%s', token='%s']\n", function.c_str(),userid.c_str(),token.c_str());
    if(function != "fetch"){
        return new HttpResponse{"REQUEST_FUNCTION_UNKNOWN",HTTP_STATUS_400};
    }
    if(TokenCheck(userid,token) != TOKEN_ACCESS){
        return new HttpResponse("ACCESS_DENIED",HTTP_STATUS_401);
    }
    User user(userid);
    user.Init();
    Course course(userid);
    course.setClass(user.getClass());
    course.setSchool(user.getSchool());
    Json j = course.getTimeTable();
    //CONSOLE_LOG(0,1,1,"User Info '%s'",j.stringize());
    JsonResponse *JResp = new JsonResponse{j};
    JResp->appendHeader("msg","NO_ERROR");
    return JResp;
    // }else if(function == "update"){
    //     int errCode = user.setInfo(body);
    //     HttpResponse* HResp = new HttpResponse{""};
    //     HResp->appendHeader("msg",NEexceptionName[errCode]);
    //     return HResp;
    // }

}