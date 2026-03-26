#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include <string>
#include <vector>

// Reads the entire file content into a string.
std::string readFile(std::string filename);

// Splits the SVG string into individual tags.
std::vector<std::string> extractTags(std::string svg);

// Extracts a string attribute from a tag.
std::string getAttr(std::string tag, std::string key);

// Extracts a numeric attribute from a tag.
double getNum(std::string tag, std::string key);

// Helper to parse coordinate strings into a vector.
std::vector<double> parsePoints(std::string pointsStr);

// Helper to extract text content between tags.
std::string extractContent(std::string tag);

#endif
