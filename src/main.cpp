#include <libff/common/default_types/ec_pp.hpp>
#include <libff/algebra/curves/bn128/bn128_pp.hpp>
#include <libff/algebra/curves/mnt/mnt4/mnt4_pp.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <libff/common/profiling.hpp>

using namespace libsnark;
using namespace std;

template<typename ppT>
bool driver_bn() {

    libff::GT<ppT> a;

    // e(Identity, all elements) = Identity
    a = ppT::reduced_pairing(libff::G1<ppT>::zero(), libff::Fr<ppT>::random_element() * libff::G2<ppT>::one());
    if (a == libff::GT<ppT>::one()) cout << "1. IDENTITY" << endl;
    else cout <<"1. " << endl;

    // e(all elements, Identity) = Identity
    a = ppT::reduced_pairing(libff::Fr<ppT>::random_element() * libff::G1<ppT>::one(), libff::G2<ppT>::zero());
    if (a == libff::GT<ppT>::one()) cout << "2. IDENTITY" << endl;
    else cout <<"2. " << endl;

    // e(Identity, Identity) = Identity
    a = ppT::reduced_pairing(libff::G1<ppT>::zero(), libff::G2<ppT>::zero());
    if (a == libff::GT<ppT>::one()) cout << "3. IDENTITY" << endl;
    else cout <<"3. " << endl;

    // else if (a == libff::GT<ppT>::zero()) cout <<"1. ZERO" << endl;
    // else if (a == libff::GT<ppT>::zero()) cout <<"2. ZERO" << endl;
    // else if (a == libff::GT<ppT>::zero()) cout <<"3. ZERO" << endl;



    return 0;
}

template <typename ppT>
bool driver_mnt() {


    libff::GT<ppT> a;

    // e(Identity, all elements) = Identity
    a = ppT::reduced_pairing(libff::G1<ppT>::zero(), libff::Fr<ppT>::random_element() * libff::G2<ppT>::one());
    if (a == libff::GT<ppT>::one()) cout << "1. IDENTITY" << endl;
    else if (a == libff::GT<ppT>::zero()) cout <<"1. ZERO" << endl;
    else cout <<"1. " << endl;

    // e(all elements, Identity) = Identity
    a = ppT::reduced_pairing(libff::Fr<ppT>::random_element() * libff::G1<ppT>::one(), libff::G2<ppT>::zero());
    if (a == libff::GT<ppT>::one()) cout << "2. IDENTITY" << endl;
    else if (a == libff::GT<ppT>::zero()) cout <<"2. ZERO" << endl;
    else cout <<"2. " << endl;

    // e(Identity, Identity) = Identity
    a = ppT::reduced_pairing(libff::G1<ppT>::zero(), libff::G2<ppT>::zero());
    if (a == libff::GT<ppT>::one()) cout << "3. IDENTITY" << endl;
    else if (a == libff::GT<ppT>::zero()) cout <<"3. ZERO" << endl;
    else cout <<"3. " << endl;

    return 0;
}


template <typename ppT>
bool brute_bn() {


    string label1[] = {"0", "1", "27"};
    vector<libff::G1<ppT> > g1{libff::G1<ppT>::zero(), libff::G1<ppT>::one(), libff::Fr<ppT>(label1[2].c_str()) * libff::G1<ppT>::one()};
    // vector<libff::G1<ppT> > g1{libff::G1<ppT>::zero(), libff::G1<ppT>::one(), libff::G1<ppT>::random_element()};

    string label2[] = {"0", "1", "81"};
    vector<libff::G2<ppT> > g2{libff::G2<ppT>::zero(), libff::G2<ppT>::one(), libff::Fr<ppT>(label2[2].c_str()) * libff::G2<ppT>::one()};
    // vector<libff::G2<ppT> > g2{libff::G2<ppT>::zero(), libff::G2<ppT>::one(), libff::G2<ppT>::random_element()};

    string labelt[] = {"1"};
    vector<libff::GT<ppT> > gt{libff::GT<ppT>::one()};

    libff::GT<ppT> a;

    for (size_t i = 0; i < g1.size(); ++i){
        for (size_t j = 0; j < g2.size(); ++j){
            for (size_t k = 0; k < gt.size(); ++k){
                a = ppT::reduced_pairing(g1[i], g2[j]);
                cout << "e(" << label1[i] << ", " << label2[j] << ") == " << labelt[k] << " " << (a == gt[k] ? "TRUE" : "FALSE") << endl;
            }
            cout << endl;
        }
    }

    // a = ppT::reduced_pairing(libff::G1<ppT>::zero(), libff::Fr<ppT>::random_element() * libff::G2<ppT>::one());
    // a = ppT::reduced_pairing(libff::G1<ppT>::zero(), libff::Fr<ppT>::random_element() * libff::G2<ppT>::one());

    return 0;
}

template <typename ppT>
bool brute_mnt() {


    string label1[] = {"0", "1", "27"};
    vector<libff::G1<ppT> > g1{libff::G1<ppT>::zero(), libff::G1<ppT>::one(), libff::Fr<ppT>(label1[2].c_str()) * libff::G1<ppT>::one()};

    string label2[] = {"0", "1", "81"};
    vector<libff::G2<ppT> > g2{libff::G2<ppT>::zero(), libff::G2<ppT>::one(), libff::Fr<ppT>(label2[2].c_str()) * libff::G2<ppT>::one()};

    string labelt[] = {"0", "1", "49"};
    vector<libff::GT<ppT> > gt{libff::GT<ppT>::zero(), libff::GT<ppT>::one(), libff::GT<ppT>::random_element()};

    libff::GT<ppT> a;

    for (size_t i = 0; i < g1.size(); ++i){
        for (size_t j = 0; j < g2.size(); ++j){
            for (size_t k = 0; k < gt.size(); ++k){
                a = ppT::reduced_pairing(g1[i], g2[j]);
                cout << "e(" << label1[i] << ", " << label2[j] << ") == " << labelt[k] << " " << (a == gt[k] ? "TRUE" : "FALSE") << endl;
            }
            cout << endl;
        }
    }

    // a = ppT::reduced_pairing(libff::G1<ppT>::zero(), libff::Fr<ppT>::random_element() * libff::G2<ppT>::one());
    // a = ppT::reduced_pairing(libff::G1<ppT>::zero(), libff::Fr<ppT>::random_element() * libff::G2<ppT>::one());

    return 0;
}


int main () {

    libff::inhibit_profiling_info = true;
    libff::inhibit_profiling_counters = true;

    libff::bn128_pp::init_public_params();
    libff::mnt4_pp::init_public_params();
    libff::mnt6_pp::init_public_params();

    // puts("CURVE_BN128");
    // driver_bn<libff::bn128_pp>();

    // puts("CURVE_MNT4");
    // driver_mnt<libff::mnt4_pp>();

    // puts("CURVE_MNT6");
    // driver_mnt<libff::mnt6_pp>();

    puts("BRUTE FORCE: CURVE_BN128");
    brute_bn<libff::bn128_pp>();

    puts("BRUTE FORCE: CURVE_MNT4");
    brute_mnt<libff::mnt4_pp>();

    puts("BRUTE FORCE: CURVE_MNT6");
    brute_mnt<libff::mnt6_pp>();


    return 0;
}
