#include "ctk/authentication/authentication.h"

namespace ctk {

Authentication::Authentication() {
}


Authentication::Authentication(const Authentication &that) {
    m_db = that.m_db;
    m_ver_thresh = that.m_ver_thresh;
}

Authentication &Authentication::operator=(const Authentication &that) {
    m_db = that.m_db;
    m_ver_thresh = that.m_ver_thresh;
    return *this;
}

void Authentication::set_db(AuthDb &db) {
    m_db = db;
}

AuthDb &Authentication::db() {
    return m_db;
}

void Authentication::set_verification_threshold(double thresh) {
    m_ver_thresh = thresh;
}

void Authentication::DefineThreshold(double vi, double vf, double inc) {
    //TODO: implement this method
    vi = vf+inc; //TODO: remove it - just to remove the warning
}

bool Authentication::IsSeparable() {
    //TODO: implement this method
    return false;
}

bool Authentication::Verify(int setIdx, AuthObject &sample) {
    return m_db[setIdx].Validate(sample, m_ver_thresh);
}

int Authentication::Identify(AuthObject &sample) {
    //TODO: implement this method
    sample.setup(0); //TODO: remove it - just to remove the warning
    return 0;
}

}

