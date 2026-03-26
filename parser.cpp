#include "parser.h"

#include <memory>
#include <string>
#include <vector>

#include "parser_helper.h"
#include "parser_object_creation.h"

// Processes the SVG file to build internal graphics.
std::vector<std::shared_ptr<GraphicsObject>> SVGParser::parse(
    std::string filename) {
  // Load the file content into a string.
  std::string svgContent = readFile(filename);

  // Extract the individual tags from the file content.
  std::vector<std::string> tags = extractTags(svgContent);

  // List to store the resulting graphics objects.
  std::vector<std::shared_ptr<GraphicsObject>> objects;

  // Iterate through tags to instantiate the shape classes.
  for (size_t i = 0; i < tags.size(); i++) {
    std::string currentTag = tags[i];

    // Creating object from the current tag.
    std::shared_ptr<GraphicsObject> obj = createGraphicsObject(currentTag);

    // Add valid objects to the list for rendering and editing.
    if (obj != nullptr) {
      objects.push_back(obj);
    }
  }
  return objects;
}
