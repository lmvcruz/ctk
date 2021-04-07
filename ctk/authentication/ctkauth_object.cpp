#include "ctkauth_object.h"

#include "ctkvectoraux.h"

namespace ctk {

//
// Class AuthObject
//

/**
 * @brief AuthObject::AuthObject
 */
AuthObject::AuthObject() {
}

AuthObject::AuthObject(const AuthObject &that) {
    m_data = that.m_data;
}

AuthObject::AuthObject(std::vector<float> &d) {
    m_data = d;
}

AuthObject &AuthObject::operator=(const AuthObject &that) {
    m_data = that.m_data;
    return *this;
}

void AuthObject::setup(int s) {
    m_data.resize(s);
}

void AuthObject::set_data(std::vector<float> &d) {
    m_data = d;
}

std::vector<float> &AuthObject::data() {
    return m_data;
}

void AuthObject::set_feature(int i, float v) {
   //TODO: input v
    m_data[i] = 0;
}

float AuthObject::get_feature(int i) {
    return m_data[i];
}

double AuthObject::Compare(AuthObject &that) {
    return Distance(m_data, that.m_data);
}

double AuthObject::Compare(std::vector<float> &that) {
    return Distance(m_data, that);
}

//
// Class AuthObject
//

/**
 * @brief AuthSet::AuthSet
 */
AuthSet::AuthSet() {
    m_smp_size = 0;
}

AuthSet::AuthSet(const AuthSet &that) {
    m_samples = that.m_samples;
    m_reference = that.m_reference;
    m_smp_size = that.m_smp_size;
}

AuthSet &AuthSet::operator=(const AuthSet &that) {
    m_samples = that.m_samples;
    m_reference = that.m_reference;
    m_smp_size = that.m_smp_size;
    return *this;
}

void AuthSet::setup(int set_size, int smp_size) {
    m_samples.resize(set_size);
    for (auto &s: m_samples) s.setup(smp_size);
}

void AuthSet::set_reference(AuthObject &ref) {
    m_reference = ref;
}

void AuthSet::set_reference(std::vector<float> &data) {
    m_reference.set_data(data);
}

AuthObject &AuthSet::reference() {
    return m_reference;
}

void AuthSet::add_sample(AuthObject &smp) {
    m_samples.push_back(smp);
}

void AuthSet::add_sample(std::vector<float> &data) {
    m_samples.push_back( AuthObject(data) );
}

void AuthSet::set_sample(int i, AuthObject &smp) {
    m_samples[i] = smp;
}

AuthObject &AuthSet::sample(int i) {
    return m_samples[i];
}

std::vector<float> &AuthSet::get_sample_data(int i) {
    return m_samples[i].data();
}

double AuthSet::Distance(AuthObject &sample) {
    return m_reference.Compare(sample);
}

double AuthSet::Distance(std::vector<float> &data) {
    return m_reference.Compare(data);
}

bool AuthSet::Validate(AuthObject &sample, double t) {
    return (m_reference.Compare(sample)<t);
}

bool AuthSet::Validate(std::vector<float> &data, double t) {
    return (m_reference.Compare(data)<t);
}

//
// Class AuthObject
//

/**
 * @brief AuthDb::AuthDb
 * @param t
 */
AuthDb::AuthDb(double t)
    : m_threshold(t) {
}

AuthDb::AuthDb(const AuthDb &that) {
    m_sets = that.m_sets;
    m_threshold = that.m_threshold;
}

AuthDb &AuthDb::operator=(const AuthDb &that) {
    m_sets = that.m_sets;
    m_threshold = that.m_threshold;
    return *this;
}

void AuthDb::setup(int db_size, double thresh) {
    m_sets.resize(db_size);
    m_threshold = thresh;
}

void AuthDb::setup_sets(int set_size, int smp_size) {
    for (auto &s: m_sets) s.setup(set_size, smp_size);
}

void AuthDb::setup_set(int setIdx, int set_size, int smp_size) {
    m_sets[setIdx].setup(set_size, smp_size);
}

void AuthDb::add_authset(AuthSet &set) {
    m_sets.push_back(set);
}

void AuthDb::set_authset(int i, AuthSet &set) {
    m_sets[i] = set;
}

AuthSet &AuthDb::authset(int i) {
    return m_sets[i];
}

AuthSet &AuthDb::operator[](int i) {
    return m_sets[i];
}

void AuthDb::set_reference(int setIdx, AuthObject &ref) {
    m_sets[setIdx].set_reference(ref);
}

AuthObject &AuthDb::reference(int setIdx) {
    return m_sets[setIdx].reference();
}

void AuthDb::add_sample(int setIdx, AuthObject &smp) {
    m_sets[setIdx].add_sample(smp);
}

void AuthDb::set_sample(int setIdx, int smpIdx, AuthObject &smp) {
    m_sets[setIdx][smpIdx] = smp;
}

AuthObject &AuthDb::sample(int setIdx, int smpIdx) {
    return m_sets[setIdx][smpIdx];
}

std::vector<float> &AuthDb::get_sample_data(int setIdx, int smpIdx) {
    return m_sets[setIdx][smpIdx].data();
}

double AuthDb::Distance(int setIdx, AuthObject &smp) {
    return m_sets[setIdx].Distance(smp);
}

double AuthDb::Distance(int setIdx, std::vector<float> &data) {
    return m_sets[setIdx].Distance(data);
}

bool AuthDb::Validate(int setIdx, AuthObject &smp, double t) {
    return (m_sets[setIdx].Distance(smp)<t);
}

bool AuthDb::Validate(int setIdx, std::vector<float> &data, double t) {
    return (m_sets[setIdx].Distance(data)<t);
}

}
