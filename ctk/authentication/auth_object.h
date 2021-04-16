#pragma once

#include <vector>

namespace ctk {

// TODO: 
//  - create unit tests
//  - rename attribute data and its methods
//  - create demo for authentication
class AuthObject {
public:
    AuthObject() = default;
    AuthObject(const AuthObject &that);
    AuthObject(std::vector<float> &d);

    AuthObject& operator=(const AuthObject &that);

    void Setup(int s);

    void SetData(std::vector<float> &d);
    std::vector<float>& GetData();

    void SetFeature(int i, float v);
    float GetFeature(int i);

    double Compare(AuthObject &that);
    double Compare(std::vector<float> &that);

protected:
    // TODO: rename this attribute - data it too generic
    std::vector<float> m_data;
};

class AuthSet {
public:
    AuthSet();
    AuthSet(const AuthSet &that);

    AuthSet& operator=(const AuthSet &that);


    void Setup(int set_size, int smp_size);

    void SetReference(AuthObject &obj);
    void SetReference(std::vector<float> &data);
    AuthObject &GetReference();

    void AddSample(AuthObject &smp);
    void AddSample(std::vector<float> &data);

    void SetSample(int i, AuthObject &smp);

    AuthObject &GetSample(int i);
    std::vector<float> &GetSampleData(int i);
    AuthObject &operator[](int i);

    double Distance(AuthObject &sample);
    double Distance(std::vector<float> &data);

    bool Validate(AuthObject &sample, double t);
    bool Validate(std::vector<float> &data, double t);

protected:
    std::vector<AuthObject> m_samples;
    AuthObject m_reference;

    int m_smp_size;
};

class AuthDb {
public:
    AuthDb(double t=0.0);
    AuthDb(const AuthDb &that);

    AuthDb& operator=(const AuthDb &that);

    void Setup(int db_size, double thresh);
    void SetupSets(int set_size, int smp_size);
    void SetupSet(int setIdx, int set_size, int smp_size);

    void AddAuthset(AuthSet& set);
    void SetAuthset(int i, AuthSet& set);
    AuthSet& GetAuthset(int i);
    AuthSet &operator[](int i);

    void SetReference(int setIdx, AuthObject &ref);
    AuthObject &GetReference(int setIdx);

    void AddSample(int setIdx, AuthObject &smp);
    void SetSample(int setIdx, int smpIdx, AuthObject &smp);
    AuthObject &GetSample(int setIdx, int smpIdx);
    std::vector<float> &GetSampleData(int setIdx, int smpIdx);

    double Distance(int setIdx, AuthObject &smp);
    double Distance(int setIdx, std::vector<float> &data);

    bool Validate(int setIdx, AuthObject &smp, double t);
    bool Validate(int setIdx, std::vector<float> &data, double t);

protected:
    std::vector<AuthSet> m_sets;
    double m_threshold;
};

}
