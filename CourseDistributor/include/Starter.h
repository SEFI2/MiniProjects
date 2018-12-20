#ifndef STARTER_H
#define STARTER_H

#include "DataGiven.h"
#include "Command.h"
#include "ConstructAndStartAlgorithm.h"
#include "Output.h"


void go () {
    getGivenData();
    cmd ();
    ConstructAndStartAlgorithm ();
    Output ();
}

#endif // STARTER_H
