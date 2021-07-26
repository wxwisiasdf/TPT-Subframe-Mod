#ifndef ELEMENTCLASSES_H
#define ELEMENTCLASSES_H

#include <vector>

#include "SimulationData.h"
#include "Element.h"

#define ELEMENT_NUMBERS_ENUMERATE
#include "ElementNumbers.h"
#undef ELEMENT_NUMBERS_ENUMERATE

std::vector<Element> const &GetElements();

const String FILT_MODES[] = {"set colour", "AND", "OR", "subtract colour", "red shift", "blue shift", "no effect", "XOR", "NOT", "old QRTZ scattering", "variable red shift", "variable blue shift"};
const int FILT_NUM_MODES = sizeof(FILT_MODES) / sizeof(FILT_MODES[0]);

#endif
