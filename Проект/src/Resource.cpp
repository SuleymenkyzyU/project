#include "Resource.h"

namespace res {
oxygine::Resources ui; // NOLINT

void
load()
{
  ui.loadXML("res.xml");
}

void
free()
{
  ui.free();
}
}