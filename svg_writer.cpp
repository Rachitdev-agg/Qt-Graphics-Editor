#include "svg_writer.h"

#include <fstream>
#include <memory>
#include <string>

// Converts the vector of graphics objects into a standard SVG XML format file.
void SVGwritter::writeToFile(
    const std::vector<std::shared_ptr<GraphicsObject>>& objects,
    const std::string& filename) {
  std::ofstream out(filename);

  // Write the mandatory SVG namespace header.
  out << "<svg xmlns=\"http://www.w3.org/2000/svg\">\n";

  // Iterate through the list and call the toSVG() method for each object.
  int n = objects.size();
  for (int i = 0; i < n; i++) {
    out << objects[i]->toSVG() << "\n";
  }

  // Close the root SVG tag and finalize the file.
  out << "</svg>\n";
  out.close();
}
