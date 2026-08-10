#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <vector>

struct Project {
    std::string type;
    std::string name;
    int devMonths = 0;
    int runMonths = 0;
    int marketingMonths = 0;
    int sponsorAmount = 0;
};

// Các hàm xử lý
std::vector<Project> readProjects(const std::string &filename);
void printProjects(const std::vector<Project> &projects);

#endif
