#ifndef SVGPARSER_H
#define SVGPARSER_H

#include <vector>

#include "objects.h"

using namespace std;

// Main parser class to handle SVG file processing.
class SVGParser {
 public:
  // Reads a file and converts its tags into a vector of graphics objects.
  vector<shared_ptr<GraphicsObject>> parse(string filename);
};

#endif
