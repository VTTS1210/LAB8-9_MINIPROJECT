#include "Project.h"
#include <vector>

int main() {
    std::vector<Project> projects = readProjects("MayProposals.txt");
    printProjects(projects);
    return 0;
}
