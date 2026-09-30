#ifndef Initializer_h
#define Initializer_h

#include "data.h"
#include <bits/stdc++.h>

class Initializer{
    public:
        virtual vector<DataPoint>Initialise(DataSet &d,int k) =0;
        virtual ~Initializer() = default;
};

#endif