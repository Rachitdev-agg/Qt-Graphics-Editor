#ifndef SVG_WRITER_H
#define SVG_WRITER_H

#include <string>
#include <vector>

#include "objects.h"

// Class to handle exporting graphics objects to an SVG file.
class SVGwritter {
 public:
  // Writes the SVG header, object tags, and footer to a file.
  static void writeToFile(
      const std::vector<std::shared_ptr<GraphicsObject>>& objects,
      const std::string& filename);
};

#endif  // SVG_WRITER_H
