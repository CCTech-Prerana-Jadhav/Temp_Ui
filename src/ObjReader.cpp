#include "ObjReader.h"
#include "Point.h"
#include "Reader.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#define TOLERANCE 0.0000001

ObjReader::ObjReader()
{
}

ObjReader::~ObjReader()
{
}

bool ObjReader::operator()(double a, double b) const
{
	return fabs(a - b) > TOLERANCE ? a < b : false;
}

void ObjReader::read(const std::string& fileName, Triangulation& triangulation)
{
    std::map<double, int, ObjReader> uniqueMap;
    double xyz[3];
    std::vector<int> pointIndices;
    std::vector<double> normal;

    std::ifstream infile(fileName);

    if (infile.is_open()) {
        std::string line;
        while (getline(infile, line)) {
            std::stringstream ss(line);
            std::string word;

            if (line.empty() || line[0] == '#') {
                continue; 
            }

            ss >> word;
            if (word == "v") {
                ss >> xyz[0] >> xyz[1] >> xyz[2];
                triangulation.UniqueNumbers.push_back(xyz[0]);
                triangulation.UniqueNumbers.push_back(xyz[1]);
                triangulation.UniqueNumbers.push_back(xyz[2]);
            }
            else if (word == "vn") {
                std::vector<double> normal(3);
                ss >> normal[0] >> normal[1] >> normal[2];
                normals.push_back(normal);
            }
            else if (word == "f") {
                pointIndices.clear();
                std::string vertexData;
                while (ss >> vertexData) {
                    std::string vertexIndexStr = vertexData.substr(0, vertexData.find('/'));
                    int vertexIndex = std::stoi(vertexIndexStr) - 1;

                    pointIndices.push_back(vertexIndex * 3); 
                }

                if (pointIndices.size() == 6) {
                    for (int i = 0; i < 3; ++i) {
                        Point p1 = Point(pointIndices[i * 3], pointIndices[i * 3 + 1], pointIndices[i * 3 + 2]);
                        Point p2 = Point(pointIndices[(i + 1) % 3 * 3], pointIndices[(i + 1) % 3 * 3 + 1], pointIndices[(i + 1) % 3 * 3 + 2]);
                        Point p3 = Point(pointIndices[3], pointIndices[4], pointIndices[5]);

                        // Assuming the first normal is associated with this triangle
                        Triangle t(p1, p2, p3, normals[0]); // You may need to adjust which normal is used
                        triangulation.Triangles.push_back(t);
                    }
                }
            }
        }
    }
}
