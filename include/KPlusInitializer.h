#ifndef KPlusInitializer_H
#define KPlusInitializer_H

#include "data.h"
#include <bits/stdc++.h>
#include "Initializer.h"

class KPlusInitializer: public Initializer{
    public : 
        virtual vector<DataPoint>Initialise(DataSet &d,int k) override;
};




#endif