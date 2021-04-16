#include "ctk/authentication/auth_object.h"

#include "ctk/misc/vector_aux.h"

namespace ctk {

//
// Class AuthObject
//

/**
 * @brief AuthObject::AuthObject
 */

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

void AuthObject::Setup(int s) {
    m_data.resize(s);
}

void AuthObject::SetData(std::vector<float> &d) {
    m_data = d;
}

std::vector<float> &AuthObject::GetData() {
    return m_data;
}

void AuthObject::SetFeature(int i, float v) {
   //TODO: input v
    m_data[i] = 0;
}

float AuthObject::GetFeature(int i) {
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

void AuthSet::Setup(int set_size, int smp_size) {
    m_samples.resize(set_size);
    for (auto &s: m_samples) s.Setup(smp_size);
}

void AuthSet::SetReference(AuthObject &ref) {
    m_reference = ref;
}

void AuthSet::SetReference(std::vector<float> &data) {
    m_reference.SetData(data);
}

AuthObject &AuthSet::GetReference() {
    return m_reference;
}

void AuthSet::AddSample(AuthObject &smp) {
    m_samples.push_back(smp);
}

void AuthSet::AddSample(std::vector<float> &data) {
    m_samples.push_back( AuthObject(data) );
}

void AuthSet::SetSample(int i, AuthObject &smp) {
    m_samples[i] = smp;
}

AuthObject &AuthSet::GetSample(int i) {
    return m_samples[i];
}

std::vector<float> &AuthSet::GetSampleData(int i) {
    return m_samples[i].GetData();
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

void AuthDb::Setup(int db_size, double thresh) {
    m_sets.resize(db_size);
    m_threshold = thresh;
}

void AuthDb::SetupSets(int set_size, int smp_size) {
    for (auto &s: m_sets) s.Setup(set_size, smp_size);
}

void AuthDb::SetupSet(int setIdx, int set_size, int smp_size) {
    m_sets[setIdx].Setup(set_size, smp_size);
}

void AuthDb::AddAuthset(AuthSet &set) {
    m_sets.push_back(set);
}

void AuthDb::SetAuthset(int i, AuthSet &set) {
    m_sets[i] = set;
}

AuthSet &AuthDb::GetAuthset(int i) {
    return m_sets[i];
}

AuthSet &AuthDb::operator[](int i) {
    return m_sets[i];
}

void AuthDb::SetReference(int setIdx, AuthObject &ref) {
    m_sets[setIdx].SetReference(ref);
}

AuthObject &AuthDb::GetReference(int setIdx) {
    return m_sets[setIdx].GetReference();
}

void AuthDb::AddSample(int setIdx, AuthObject &smp) {
    m_sets[setIdx].AddSample(smp);
}

void AuthDb::SetSample(int setIdx, int smpIdx, AuthObject &smp) {
    m_sets[setIdx][smpIdx] = smp;
}

AuthObject &AuthDb::GetSample(int setIdx, int smpIdx) {
    return m_sets[setIdx][smpIdx];
}

std::vector<float> &AuthDb::GetSampleData(int setIdx, int smpIdx) {
    return m_sets[setIdx][smpIdx].GetData();
}

double AuthDb::Distance(int setIdx, AuthObject &smp) {
    return m_sets[setIdx].Distance(smp);
}

double AuthDb::Distance(int setIdx, std::vector<float> &data) {
    return m_sets[setIdx].Distance(data);
}

bool AuthDb::Validate(int setIdx, AuthObject &smp, double t) {
    return (m_sets[setIdx].Distance(smp) < t);
}

bool AuthDb::Validate(int setIdx, std::vector<float> &data, double t) {
    return (m_sets[setIdx].Distance(data) < t);
}

}
