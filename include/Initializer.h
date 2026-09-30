<<<<<<< HEAD
#ifndef Initializer_h
#define Initializer_h

#include "data.h"
#include <bits/stdc++.h>

class Initializer{
    public:
        virtual vector<DataPoint>Initialise(DataSet &d,int k) =0;
        virtual ~Initializer() = default;
};

=======
#ifndef Initializer_h
#define Initializer_h

#include "data.h"
#include <bits/stdc++.h>

class Initializer{
    public:
        virtual vector<DataPoint>Initialise(DataSet &d,int k) =0;
        virtual ~Initializer() = default;
};

>>>>>>> 3ad2529 (Update project files)
#endif