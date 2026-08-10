#include "Project.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

// Inject giá trị hỗ trợ (không hard-code trong logic)
const int IDEA_SUPPORT = 2200;
const int MVP_RUN_SUPPORT = 930;
const int MVP_MARKETING_SUPPORT = 500;

std::vector<Project> readProjects(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<Project> projects;

    if (!file.is_open()) {
        std::cerr << "Không thể mở file " << filename << "\n";
        return projects;
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        Project p;

        if (line.find("Idea:") == 0) {
            p.type = "Ý tưởng";
            ss.ignore(6); // bỏ "Idea: "
            getline(ss, p.name, ',');
            ss.ignore(11); // bỏ "DevMonths="
            ss >> p.devMonths;
            p.sponsorAmount = p.devMonths * IDEA_SUPPORT;
        } else if (line.find("Mvp:") == 0) {
            p.type = "Sản phẩm";
            ss.ignore(5); // bỏ "Mvp: "
            getline(ss, p.name, ',');
            ss.ignore(11); // bỏ "RunMonths="
            ss >> p.runMonths;
            ss.ignore(12); // bỏ ", Marketing="
            ss >> p.marketingMonths;
            p.sponsorAmount = p.runMonths * MVP_RUN_SUPPORT + p.marketingMonths * MVP_MARKETING_SUPPORT;
        }

        projects.push_back(p);
    }

    // Sắp xếp theo kinh phí tăng dần
    std::sort(projects.begin(), projects.end(), [](const Project &a, const Project &b) {
        return a.sponsorAmount < b.sponsorAmount;
    });

    return projects;
}

void printProjects(const std::vector<Project> &projects) {
    std::cout << "Kế hoạch tài trợ dự án startup nội bộ công ty AlphaTech\n";
    std::cout << "Tháng: 05/2024\n\n";
    std::cout << "STT | Loại dự án  | Tên dự án       | Thông tin                                | Kinh phí\n";
    std::cout << "-------------------------------------------------------------------------------------------------\n";

    int totalSponsor = 0;
    int stt = 1;
    for (auto &p : projects) {
        std::cout << std::setw(3) << stt++ << " | "
                  << std::setw(10) << std::left << p.type << " | "
                  << std::setw(12) << std::left << p.name << " | ";

        if (p.type == "Ý tưởng") {
            std::cout << "Phát triển: " << p.devMonths << " tháng";
        } else {
            std::cout << "Vận hành: " << p.runMonths << " tháng. Marketing: " << p.marketingMonths << " tháng";
        }

        std::cout << " | $" << p.sponsorAmount << "\n";
        totalSponsor += p.sponsorAmount;
    }

    std::cout << "\nTổng kinh phí tài trợ: $" << totalSponsor << "\n";
}  
