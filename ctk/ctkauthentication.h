#ifndef CTKAUTHENTICATION_H
#define CTKAUTHENTICATION_H

#include "ctkauthobject.h"

namespace ctk {

class Authentication
{
public:
    Authentication();
    Authentication(const Authentication &that);

    Authentication& operator=(const Authentication &that);

    void set_db(AuthDb &db);
    AuthDb &db();

    void set_verification_threshold(double thresh);

    void DefineThreshold(double vi, double vf, double inc);
    bool IsSeparable();

    bool Verify(int setIdx, AuthObject &sample);
    int Identify(AuthObject &sample);

protected:
    AuthDb m_db;

    double m_ver_thresh;
};

};

#endif // CTKAUTHENTICATION_H
