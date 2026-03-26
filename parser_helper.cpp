#include <QFile>
#include <QTextStream>
#include <iostream>

#include "parser_helper.h"

// Opens a file and returns its content as a string.
std::string readFile(std::string filename) {
  QFile file(QString::fromStdString(filename));
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    std::cout << "FAILED TO OPEN RESOURCE: " << filename << std::endl;
    return "";
  }
  QTextStream in(&file);
  return in.readAll().toStdString();
}

// Parses the SVG input to isolate valid shape and text tags.
std::vector<std::string> extractTags(std::string svg) {
  std::vector<std::string> tags;
  size_t pos = 0;
  while (true) {
    size_t start = svg.find("<", pos);
    if (start == std::string::npos) break;
    size_t end = svg.find(">", start);
    if (end == std::string::npos) break;

    std::string tag = svg.substr(start, end - start + 1);
    if (tag.find("<text") == 0) {
      size_t close = svg.find("</text>", end);
      if (close != std::string::npos) {
        tags.push_back(svg.substr(start, close - start + 7));
        pos = close + 7;
        continue;
      }
    }
    if (tag.find("<circle") != std::string::npos ||
        tag.find("<rect") != std::string::npos ||
        tag.find("<line") != std::string::npos ||
        tag.find("<polygon") != std::string::npos ||
        tag.find("<polyline") != std::string::npos) {
      tags.push_back(tag);
    }
    pos = end + 1;
  }
  return tags;
}

// Searches for a specific key and returns its value from an XML tag.
std::string getAttr(std::string tag, std::string key) {
  size_t p = tag.find(" " + key + "=\"");
  if (p == std::string::npos) {
    p = tag.find(key + "=\"");
    if (p == std::string::npos) return "";
    if (p > 0) {
      char prev = tag[p - 1];
      if (isalnum(prev) || prev == '-') return "";
    }
  }
  p = tag.find("=\"", p) + 2;
  size_t q = tag.find("\"", p);
  if (q == std::string::npos) return "";
  return tag.substr(p, q - p);
}

// Retrieves an attribute value and converts it to a double.
double getNum(std::string tag, std::string key) {
  std::string v = getAttr(tag, key);
  return v.empty() ? 0.0 : std::stod(v);
}

// Parses coordinate strings by splitting on commas or spaces.
std::vector<double> parsePoints(std::string pointsStr) {
  std::vector<double> points;
  std::string num = "";
  for (size_t i = 0; i < pointsStr.length(); i++) {
    char c = pointsStr[i];
    if (c == ',' || c == ' ') {
      if (!num.empty()) {
        points.push_back(std::stod(num));
        num = "";
      }
    } else {
      num += c;
    }
  }
  if (!num.empty()) points.push_back(std::stod(num));
  return points;
}

// Retrieves raw content located between the opening and closing tag brackets.
std::string extractContent(std::string tag) {
  size_t p = tag.find(">");
  size_t q = tag.rfind("<");
  if (p != std::string::npos && q > p) {
    return tag.substr(p + 1, q - p - 1);
  }
  return "";
}
