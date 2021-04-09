#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TreeSort.h"
#include "pugixml.hpp"

struct ExperimentNode
{
    ExperimentNode(std::string name, int minElement, int maxElement, 
        int startLength, int maxLength, int diff, int repeat) 
        :name(name), minElement(minElement), maxElement(maxElement), 
        startLength(startLength), maxLength(maxLength), diff(diff), repeat(repeat){}

    std::string name;
    int minElement;
    int maxElement;
    int startLength;
    int maxLength;
    int diff;
    int repeat;
};

std::vector<ExperimentNode> readXML(const char* source)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(source);
    std::vector<ExperimentNode> res;
    if (result)
    {
        auto experiments = doc.child("experiments").first_child().children();
        for (auto& node : experiments)
            res.push_back(
                ExperimentNode(node.attribute("name").value(),
                     std::stoi(node.attribute("minElement").value()),
                     std::stoi(node.attribute("maxElement").value()),
                     std::stoi(node.attribute("startLength").value()),
                     std::stoi(node.attribute("maxLength").value()),
                     std::stoi(node.attribute("diff").value()),
                     std::stoi(node.attribute("repeat").value())));
    }
    return res;
}

std::string GenerateString(ExperimentNode& experiment, int length)
{
    std::string res;
    for (int i = 0; i < length; ++i)
        res += experiment.minElement + (rand() % (experiment.minElement - experiment.minElement + 1));
    return res;
}

int main()
{
    std::ifstream t("input.xml");
    std::string input;
    t.seekg(0, std::ios::end);
    input.reserve(t.tellg());
    t.seekg(0, std::ios::beg);
    input.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    auto experiments = readXML(input.c_str());
    for (auto& experiment : experiments)
    {
        std::ofstream of(experiment.name + ".csv");
        for (int i = 0; i < experiment.repeat; ++i)
            for (int j = experiment.startLength; j <= experiment.maxLength; j += experiment.diff)
            {
                auto s = GenerateString(experiment, j);
                of << j << ';' << TreeSort::treeSort(s) << '\n';
            }
        of.close();
    }
    return 0;
}
