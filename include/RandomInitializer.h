#ifndef RandomInitializer_h
#define RandomInitializer_h
#include "data.h"
#include <bits/stdc++.h>
#include "Initializer.h"

class RandomInitializer:public Initializer{
    public:
        virtual vector<DataPoint>Initialise (DataSet &d,int k) override;
};

#endif