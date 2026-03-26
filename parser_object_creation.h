#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <memory>
#include <string>

#include "objects.h"

// Creates a shape object based on the SVG tag.
std::shared_ptr<GraphicsObject> createGraphicsObject(std::string tag);

#endif
