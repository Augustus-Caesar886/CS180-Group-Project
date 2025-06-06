#include <httplib.h>
#include <nlohmann/json.hpp>
#include "../header/StudentAccountStorage.h"
#include "../header/TeacherAccountStorage.h"
#include "../header/Teacher.h"
#include "../header/Student.h"
#include "../header/md5.h"

using json = nlohmann::json;
using namespace std;
using namespace httplib;

int main() {

    Server svr;

    svr.set_pre_routing_handler([](const Request& req, Response& res) {
        res.set_header("Access-Control-Allow-Origin", "http://localhost:3000");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        return Server::HandlerResponse::Unhandled;
    });

    svr.Options(".*", [](const Request &req, Response &res){
        res.status = 200;
    });

    svr.set_default_headers({
        {"Access-Control-Allow-Methods", "GET, POST, OPTIONS"},
        {"Access-Control-Allow-Headers", "Content-Type"},
    });

    svr.Post("/login", [](const Request &req, Response &res){
        
        try{
            json req_json = json::parse(req.body);
            string username = req_json["username"];
            string password = req_json["password"];
            string role = req_json.value("role", "student");

            string hashedInput = md5(password); //hashing password entered to compare w/ one in JSON

            if(role == "student"){
                StudentAccountStorage storage("../jinfo/students.json");
                vector<Student> students = storage.loadStudents();

                for(const Student& s : students){
                    if(s.getUsername() == username && s.getPasskey() == hashedInput){
                        json response = {
                            {"status", "success"},
                            {"message", "Login successful"}
                        };

                        res.set_content(response.dump(), "application/json");
                        return;
                    }
                }
            }else if(role == "teacher"){
                TeacherAccountStorage storage("../jinfo/teachers.json");
                vector<Teacher> teachers = storage.loadTeachers();

                for(const Teacher& t : teachers){
                    if (t.getUsername() == username && t.getPasskey() == hashedInput){
                        json response{
                            {"status", "success"},
                            {"message", "Login successful"}
                        };

                        res.set_content(response.dump(), "application/json");
                        return;
                    }
                }
            }

            //no match at all
            json error = {
                {"status", "fail"},
                {"message", "Invalid credentials"}
            };
            res.status = 401;
            res.set_content(error.dump(), "application/json"); 
        }
        catch(const exception& e){
            json error = {
                {"status", "error"},
                {"message", "Bad request"}
            };

            res.status = 400;
            res.set_content(error.dump(), "application/json");
        }
    });

    //registration
    svr.Post("/register", [&](const Request &req, Response &res){
        try{
            json req_json = json::parse(req.body);
            string username = req_json["username"];
            string password = req_json["password"];
            int classroomCode = req_json.value("classroomCode",0);
            string role = req_json["role"];
            

            if(role == "student"){
                Student student = Student::builder()
                .username(username)
                .passkey(password)
                .classroomCode(classroomCode)
                .currentMajor("") //defaulting to empty
                .build();

                StudentAccountStorage storage("../jinfo/students.json");
                vector<Student> students = storage.loadStudents();
                students.push_back(student);
                storage.saveStudents(students);
            }else if(role == "teacher"){
                Teacher teacher = Teacher::builder()
                    .username(username)
                    .passkey(password)
                    .build();

                TeacherAccountStorage storage("../jinfo/teachers.json");
                vector<Teacher> teachers = storage.loadTeachers();
                teachers.push_back(teacher);
                storage.saveTeachers(teachers);
            }else{
                res.status = 400;
                res.set_content(R"({"status":"error","message":"Invalid role"})", "application/json");
                return;
            }
            res.set_content(R"({"status":"success","message":"Account registered"})", "application/json");
        } catch(const exception &e){
            res.status = 500;
            res.set_content(R"({"status":"error","message":"Registration failed"})", "application/json");
        }
    });

    svr.Post("/updateMajor", [](const Request &req, Response &res){
        try{
            json req_json = json::parse(req.body);
            string username = req_json["username"];
            string updateMajor = req_json["major"];

            StudentAccountStorage storage("../jinfo/students.json");
            vector<Student> students = storage.loadStudents();

            bool isUserFound = false;
            for(Student& s : students){
                if(s.getUsername() == username){
                    s.setUpdateMajor(updateMajor);
                    isUserFound = true;
                    break;
                }
            }
            if(isUserFound){
                storage.saveStudents(students);
                res.set_content(R"({"status":"success","message":"Major updated"})", "application/json");
            }else{
                res.status = 404;
                res.set_content(R"({"status":"fail","message":"Student not found"})", "application/json");
            }
        }catch(const exception &e){
            res.status = 500;
            res.set_content(R"({"status":"error","message":"Invalid data"})", "application/json");
        }
    });

    svr.listen("0.0.0.0", 8080);

    return 0;
}