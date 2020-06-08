#ifndef CTKAUTHOBJECT_H
#define CTKAUTHOBJECT_H

#include <vector>

namespace ctk {

class AuthObject {
public:
    AuthObject();
    AuthObject(const AuthObject &that);
    AuthObject(std::vector<float> &d);

    AuthObject& operator=(const AuthObject &that);

    void setup(int s);

    void set_data(std::vector<float> &d);
    std::vector<float>& data();

    void set_feature(int i, float v);
    float get_feature(int i);

    double Compare(AuthObject &that);
    double Compare(std::vector<float> &that);


protected:
    std::vector<float> m_data;
};

class AuthSet {
public:
    AuthSet();
    AuthSet(const AuthSet &that);

    AuthSet& operator=(const AuthSet &that);


    void setup(int set_size, int smp_size);

    void set_reference(AuthObject &obj);
    void set_reference(std::vector<float> &data);
    AuthObject &reference();

    void add_sample(AuthObject &smp);
    void add_sample(std::vector<float> &data);

    void set_sample(int i, AuthObject &smp);

    AuthObject &sample(int i);
    std::vector<float> &get_sample_data(int i);
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

    void setup(int db_size, double thresh);
    void setup_sets(int set_size, int smp_size);
    void setup_set(int setIdx, int set_size, int smp_size);

    void add_authset(AuthSet& set);
    void set_authset(int i, AuthSet& set);
    AuthSet& authset(int i);
    AuthSet &operator[](int i);

    void set_reference(int setIdx, AuthObject &ref);
    AuthObject &reference(int setIdx);

    void add_sample(int setIdx, AuthObject &smp);
    void set_sample(int setIdx, int smpIdx, AuthObject &smp);
    AuthObject &sample(int setIdx, int smpIdx);
    std::vector<float> &get_sample_data(int setIdx, int smpIdx);

    double Distance(int setIdx, AuthObject &smp);
    double Distance(int setIdx, std::vector<float> &data);

    bool Validate(int setIdx, AuthObject &smp, double t);
    bool Validate(int setIdx, std::vector<float> &data, double t);

protected:
    std::vector<AuthSet> m_sets;
    double m_threshold;
};

};


#endif // CTKAUTHOBJECT_H
