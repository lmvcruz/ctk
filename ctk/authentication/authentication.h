#pragma once

#include "ctk/authentication/auth_object.h"

namespace ctk {

class Authentication
{
public:
    Authentication() = default;
    Authentication(const Authentication &that);

    Authentication& operator=(const Authentication &that);

    void SetDb(AuthDb &db);
    AuthDb &GetDb();

    void SetVerificationThreshold(double thresh);
    void DefineThreshold(double vi, double vf, double inc);
    bool IsSeparable();

    bool Verify(int setIdx, AuthObject &sample);
    int Identify(AuthObject &sample);

protected:
    AuthDb m_db;

    double m_ver_thresh;
};

};
