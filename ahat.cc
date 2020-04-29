#include<memory>
#include<vector>
#include<iostream>
#include<string>
#include<algorithm>
#include <math.h>

#include "ahat.h"

namespace pdaggerq {

ahat::ahat() {

  skip = false;
  data = (std::shared_ptr<StringData>)(new StringData());


}
ahat::~ahat() {
}

void ahat::check_occ_vir() {

   // OCC: I,J,K,L,M,N
   // VIR: A,B,C,D,E,F
   // GEN: P,Q,R,S,T,U,V,W

   for (int i = 0; i < (int)delta1.size(); i++ ) {
       bool first_is_occ = false;
       if ( delta1[i].at(0) == 'I' || delta1[i].at(0) == 'i') {
           first_is_occ = true;
       }else if ( delta1[i].at(0) == 'J' || delta1[i].at(0) == 'j') {
           first_is_occ = true;
       }else if ( delta1[i].at(0) == 'K' || delta1[i].at(0) == 'k') {
           first_is_occ = true;
       }else if ( delta1[i].at(0) == 'L' || delta1[i].at(0) == 'l') {
           first_is_occ = true;
       }else if ( delta1[i].at(0) == 'M' || delta1[i].at(0) == 'm') {
           first_is_occ = true;
       }else if ( delta1[i].at(0) == 'N' || delta1[i].at(0) == 'n') {
           first_is_occ = true;
       }else if ( delta1[i].at(0) == 'A' || delta1[i].at(0) == 'a') {
           first_is_occ = false;
       }else if ( delta1[i].at(0) == 'B' || delta1[i].at(0) == 'b') {
           first_is_occ = false;
       }else if ( delta1[i].at(0) == 'C' || delta1[i].at(0) == 'c') {
           first_is_occ = false;
       }else if ( delta1[i].at(0) == 'D' || delta1[i].at(0) == 'd') {
           first_is_occ = false;
       }else if ( delta1[i].at(0) == 'E' || delta1[i].at(0) == 'e') {
           first_is_occ = false;
       }else if ( delta1[i].at(0) == 'F' || delta1[i].at(0) == 'f') {
           first_is_occ = false;
       }else {
           continue;
       }

       bool second_is_occ = false;
       if ( delta2[i].at(0) == 'I' || delta2[i].at(0) == 'i') {
           second_is_occ = true;
       }else if ( delta2[i].at(0) == 'J' || delta2[i].at(0) == 'j') {
           second_is_occ = true;
       }else if ( delta2[i].at(0) == 'K' || delta2[i].at(0) == 'k') {
           second_is_occ = true;
       }else if ( delta2[i].at(0) == 'L' || delta2[i].at(0) == 'l') {
           second_is_occ = true;
       }else if ( delta2[i].at(0) == 'M' || delta2[i].at(0) == 'm') {
           second_is_occ = true;
       }else if ( delta2[i].at(0) == 'N' || delta2[i].at(0) == 'n') {
           second_is_occ = true;
       }else if ( delta2[i].at(0) == 'A' || delta2[i].at(0) == 'a') {
           second_is_occ = false;
       }else if ( delta2[i].at(0) == 'B' || delta2[i].at(0) == 'b') {
           second_is_occ = false;
       }else if ( delta2[i].at(0) == 'C' || delta2[i].at(0) == 'c') {
           second_is_occ = false;
       }else if ( delta2[i].at(0) == 'D' || delta2[i].at(0) == 'd') {
           second_is_occ = false;
       }else if ( delta2[i].at(0) == 'E' || delta2[i].at(0) == 'e') {
           second_is_occ = false;
       }else if ( delta2[i].at(0) == 'F' || delta2[i].at(0) == 'f') {
           second_is_occ = false;
       }else {
           continue;
       }

       if ( first_is_occ != second_is_occ ) {
           skip = true;
       }

   }

}

void ahat::check_spin() {

    // check A/B in delta functions
    for (int j = 0; j < (int)delta1.size(); j++) {
        if ( delta1[j].length() == 2 ) {
            if ( delta1[j].at(1) == 'A' && delta2[j].at(1) == 'B' ) {
                skip = true;
                break;
            }else if ( delta1[j].at(1) == 'B' && delta2[j].at(1) == 'A' ) {
                skip = true;
                break;
            }
        }
    }

    // check A/B in two-index data->tensors
    if ( (int)data->tensor.size() == 2 ) {
        if ( data->tensor[0].length() == 2 ) {
            if ( data->tensor[1].length() == 2 ) {

                if ( data->tensor[0].at(1) == 'A' && data->tensor[1].at(1) == 'B' ) {
                    skip = true;
                    return;
                }else if ( data->tensor[0].at(1) == 'B' && data->tensor[1].at(1) == 'A' ) {
                    skip = true;
                    return;
                }
            
            }
        }
    }

    // check A/B in four-index data->tensors
    if ( (int)data->tensor.size() == 4 ) {
        // check bra
        if ( data->tensor[0].length() == 2 ) {
            if ( data->tensor[1].length() == 2 ) {

                if ( data->tensor[0].at(1) == 'A' && data->tensor[1].at(1) == 'B' ) {
                    skip = true;
                    return;
                }else if ( data->tensor[0].at(1) == 'B' && data->tensor[1].at(1) == 'A' ) {
                    skip = true;
                    return;
                }
            
            }
        }
        // check ket
        if ( data->tensor[2].length() == 2 ) {
            if ( data->tensor[3].length() == 2 ) {

                if ( data->tensor[2].at(1) == 'A' && data->tensor[3].at(1) == 'B' ) {
                    skip = true;
                    return;
                }else if ( data->tensor[2].at(1) == 'B' && data->tensor[3].at(1) == 'A' ) {
                    skip = true;
                    return;
                }
            
            }
        }

    }


}

void ahat::print() {
    if ( skip ) return;
    printf("    ");
    printf("//     ");
    printf("%c", sign > 0 ? '+' : '-');
    printf(" ");
    printf("%7.5lf", fabs(data->factor));
    printf(" ");
    for (int i = 0; i < (int)symbol.size(); i++) {
        printf("%s",symbol[i].c_str());
        if ( is_dagger[i] ) {
            printf("%c",'*');
        }
        printf(" ");
    }
    for (int i = 0; i < (int)delta1.size(); i++) {
        printf("d(%s%s)",delta1[i].c_str(),delta2[i].c_str());
        printf(" ");
    }
    if ( (int)data->tensor.size() > 0 ) {
        // two-electron integrals
        if ( (int)data->tensor.size() == 4 ) {
            printf("(");
            for (int i = 0; i < 2; i++) {
                printf("%s",data->tensor[i].c_str());
            }
            printf("|");
            for (int i = 2; i < 4; i++) {
                printf("%s",data->tensor[i].c_str());
            }
            printf(")");
        }
        // one-electron integrals
        if ( (int)data->tensor.size() == 2 ) {
            printf("h(");
            for (int i = 0; i < 2; i++) {
                printf("%s",data->tensor[i].c_str());
            }
            printf(")");
        }
        printf(" ");
    }

    // amplitudes
    if ( (int)data->amplitudes.size() > 0 ) {
        for (int i = 0; i < (int)data->amplitudes.size(); i++) {
           
            if ( (int)data->amplitudes[i].size() > 0 ) {
                // t1
                if ( (int)data->amplitudes[i].size() == 2 ) {
                    printf("t1(");
                    for (int j = 0; j < 2; j++) {
                        printf("%s",data->amplitudes[i][j].c_str());
                    }
                    printf(")");
                }
                // t2
                if ( (int)data->amplitudes[i].size() == 4 ) {
                    printf("t2(");
                    for (int j = 0; j < 4; j++) {
                        printf("%s",data->amplitudes[i][j].c_str());
                    }
                    printf(")");
                }
                printf(" ");
            } 
        }
    }
    printf("\n");
}

bool ahat::is_normal_order() {

    // don't bother bringing to normal order if we're going to skip this string
    if (skip) return true;

    for (int i = 0; i < (int)symbol.size()-1; i++) {
        if ( !is_dagger[i] && is_dagger[i+1] ) {
            return false;
        }
    }
    return true;
}

// in order to compare strings, the creation and annihilation 
// operators should be ordered in some consistent way.
// alphabetically seems reasonable enough
void ahat::alphabetize(std::vector<std::shared_ptr<ahat> > &ordered) {

    // alphabetize string
    for (int i = 0; i < (int)ordered.size(); i++) {

        // creation
        bool not_alphabetized = false;
        do {
            not_alphabetized = false;
            int ndagger = 0;
            for (int j = 0; j < (int)ordered[i]->symbol.size(); j++) {
                if ( ordered[i]->is_dagger[j] ) ndagger++;
            }
            for (int j = 0; j < ndagger-1; j++) {
                int val1 = ordered[i]->symbol[j].c_str()[0];
                int val2 = ordered[i]->symbol[j+1].c_str()[0];
                if ( val2 < val1 ) {
                    std::string dum = ordered[i]->symbol[j];
                    ordered[i]->symbol[j] = ordered[i]->symbol[j+1];
                    ordered[i]->symbol[j+1] = dum;
                    ordered[i]->sign = -ordered[i]->sign;
                    not_alphabetized = true;
                    j = (int)ordered[i]->symbol.size() + 1;
                    not_alphabetized = true;
                }
            }
        }while(not_alphabetized);
        // annihilation
        not_alphabetized = false;
        do {
            not_alphabetized = false;
            int ndagger = 0;
            for (int j = 0; j < (int)ordered[i]->symbol.size(); j++) {
                if ( ordered[i]->is_dagger[j] ) ndagger++;
            }
            for (int j = ndagger; j < (int)ordered[i]->symbol.size()-1; j++) {
                int val1 = ordered[i]->symbol[j].c_str()[0];
                int val2 = ordered[i]->symbol[j+1].c_str()[0];
                if ( val2 < val1 ) {
                    std::string dum = ordered[i]->symbol[j];
                    ordered[i]->symbol[j] = ordered[i]->symbol[j+1];
                    ordered[i]->symbol[j+1] = dum;
                    ordered[i]->sign = -ordered[i]->sign;
                    not_alphabetized = true;
                    j = (int)ordered[i]->symbol.size() + 1;
                    not_alphabetized = true;
                }
            }
        }while(not_alphabetized);
    }

    // alphabetize deltas
    for (int i = 0; i < (int)ordered.size(); i++) {
        for (int j = 0; j < (int)ordered[i]->delta1.size(); j++) {
            int val1 = ordered[i]->delta1[j].c_str()[0];
            int val2 = ordered[i]->delta2[j].c_str()[0];
            if ( val2 < val1 ) {
                std::string dum = ordered[i]->delta1[j];
                ordered[i]->delta1[j] = ordered[i]->delta2[j];
                ordered[i]->delta2[j] = dum;
            }
        }
    }
}

// once strings are alphabetized, we can compare them
// and remove terms that cancel. 

// NOTE AMPLITUDES AREN'T BEING CONSIDERED
void ahat::cleanup(std::vector<std::shared_ptr<ahat> > &ordered) {

    for (int i = 0; i < (int)ordered.size(); i++) {

        for (int j = i+1; j < (int)ordered.size(); j++) {

            // are factors same?
            if ( ordered[i]->data->factor != ordered[j]->data->factor ) continue;

            // are signs opposite?
            if ( ordered[i]->sign == ordered[j]->sign ) continue;

            // are strings same?
            if ( ordered[i]->symbol.size() != ordered[j]->symbol.size() ) continue;
            int nsame_s = 0;
            for (int k = 0; k < (int)ordered[i]->symbol.size(); k++) {
                if ( ordered[i]->symbol[k] == ordered[j]->symbol[k] ) {
                    nsame_s++;
                }
            }
            if ( nsame_s != ordered[i]->symbol.size() ) continue;

            // are tensors same?
            if ( ordered[i]->data->tensor.size() != ordered[j]->data->tensor.size() ) continue;
            int nsame_t = 0;
            for (int k = 0; k < (int)data->tensor.size(); k++) {
                if ( ordered[i]->data->tensor[k] == ordered[j]->data->tensor[k] ) {
                    nsame_t++;
                }
            }
            if ( nsame_t != ordered[i]->data->tensor.size() ) continue;

            // same delta functions (recall these aren't sorted in any way)
            int nsame_d = 0;
            for (int k = 0; k < (int)ordered[i]->delta1.size(); k++) {
                for (int l = 0; l < (int)ordered[j]->delta1.size(); l++) {
                    if ( ordered[i]->delta1[k] == ordered[j]->delta1[l] && ordered[i]->delta2[k] == ordered[j]->delta2[l] ) {
                        nsame_d++;
                        break;
                    }else if ( ordered[i]->delta2[k] == ordered[j]->delta1[l] && ordered[i]->delta1[k] == ordered[j]->delta2[l] ) {
                        nsame_d++;
                        break;
                    }
                }
            }
            if ( nsame_d != (int)ordered[i]->delta1.size() ) continue;

            // amplitudes, which can be complicated since they aren't sorted

            // same number of amplitudes?
            if ( ordered[i]->data->amplitudes.size() != ordered[j]->data->amplitudes.size() ) continue;
         
            int nsame_amps = 0;
            for (int ii = 0; ii < (int)ordered[i]->data->amplitudes.size(); ii++) {
                for (int jj = 0; jj < (int)ordered[j]->data->amplitudes.size(); jj++) {

                    // t1 vs t2?
                    if ( ordered[i]->data->amplitudes[ii].size() != ordered[j]->data->amplitudes[jj].size() ) continue;

                    // indices?
                    int nsame_idx = 0;
                    for (int iii = 0; iii < (int)ordered[i]->data->amplitudes[ii].size(); iii++) {
                        for (int jjj = 0; jjj < (int)ordered[j]->data->amplitudes[jj].size(); jjj++) {
                            if ( ordered[i]->data->amplitudes[ii][iii] == ordered[j]->data->amplitudes[jj][jjj] ) {
                                nsame_idx++;
                                break;
                            }
                        }
                    }
                    // if all indices are the same, the amplitudes must be the same
                    if ( nsame_idx == (int)ordered[i]->data->amplitudes[ii].size() ) {
                        nsame_amps++;
                        break;
                    }
                }
            }
            if ( nsame_amps != (int)ordered[i]->data->amplitudes.size() ) continue;

            // well, i guess they cancel
            ordered[i]->skip = true;
            ordered[j]->skip = true;

            // break j so we don't cancel any other terms j with i
            break;
            
        }

    }

}

// copy all data, except symbols and daggers
void ahat::shallow_copy(void * copy_me) { 

    ahat * in = reinterpret_cast<ahat * >(copy_me);

    // skip string?
    skip   = in->skip;
    
    // sign
    sign   = in->sign;
    
    // factor
    data->factor = in->data->factor;
    
    // data->tensor
    for (int j = 0; j < (int)in->data->tensor.size(); j++) {
        // does data->tensor index show up in a delta function?
        bool skipme = false;
        for (int k = 0; k < (int)in->delta1.size(); k++) {
            if ( in->data->tensor[j] == in->delta1[k] ) {
                data->tensor.push_back(in->delta2[k]);
                skipme = true;
                break;
            }
            if ( in->data->tensor[j] == in->delta2[k] ) {
                data->tensor.push_back(in->delta1[k]);
                skipme = true;
                break;
            }
        }
        if ( skipme ) continue;
        data->tensor.push_back(in->data->tensor[j]);
    }
    for (int j = 0; j < (int)in->delta1.size(); j++) {
        bool skipme = false;
        for (int k = 0; k < (int)in->data->tensor.size(); k++) {
            if ( in->data->tensor[k] == in->delta1[j] ) {
                skipme = true;
                break;
            }
            if ( in->data->tensor[k] == in->delta2[j] ) {
                skipme = true;
                break;
            }
        }
        if ( skipme ) continue;
    
        delta1.push_back(in->delta1[j]);
        delta2.push_back(in->delta2[j]);
    }

    // amplitudes
    for (int i = 0; i < (int)in->data->amplitudes.size(); i++) {
        std::vector<std::string> tmp;
        for (int j = 0; j < (int)in->data->amplitudes[i].size(); j++) {
            tmp.push_back(in->data->amplitudes[i][j]);
        }
        data->amplitudes.push_back(tmp);
    }

}

// copy all data, including symbols and daggers
void ahat::copy(void * copy_me) { 

    shallow_copy(copy_me);

    ahat * in = reinterpret_cast<ahat * >(copy_me);

    // dagger?
    for (int j = 0; j < (int)in->is_dagger.size(); j++) {
        is_dagger.push_back(in->is_dagger[j]);
    }
    
    // operators
    for (int j = 0; j < (int)in->symbol.size(); j++) {
        symbol.push_back(in->symbol[j]);
    }
    
}

void ahat::normal_order(std::vector<std::shared_ptr<ahat> > &ordered) {
    if ( skip ) return;

    if ( is_normal_order() ) {

        // push current ordered operator onto running list
        std::shared_ptr<ahat> newguy (new ahat());

        newguy->copy((void*)this);

        ordered.push_back(newguy);

        return;
    }

    // new strings
    std::shared_ptr<ahat> s1 ( new ahat() );
    std::shared_ptr<ahat> s2 ( new ahat() );

    // copy data common to both new strings
    s1->shallow_copy((void*)this);
    s2->shallow_copy((void*)this);

    // rearrange operators
    for (int i = 0; i < (int)symbol.size()-1; i++) {

        if ( !is_dagger[i] && is_dagger[i+1] ) {

            s1->delta1.push_back(symbol[i]);
            s1->delta2.push_back(symbol[i+1]);

            // check spin in delta functions
            for (int j = 0; j < (int)delta1.size(); j++) {
                if ( s1->delta1[j].length() != 2 ) {
                    //throw PsiException("be sure to specify spin as second character in labels",__FILE__,__LINE__);
                    break;
                }
                if ( s1->delta1[j].at(1) == 'A' && s1->delta2[j].at(1) == 'B' ) {
                    s1->skip = true;
                }else if ( s1->delta1[j].at(1) == 'B' && s1->delta2[j].at(1) == 'A' ) {
                    s1->skip = true;
                }
            }

            s2->sign = -s2->sign;
            s2->symbol.push_back(symbol[i+1]);
            s2->symbol.push_back(symbol[i]);
            s2->is_dagger.push_back(is_dagger[i+1]);
            s2->is_dagger.push_back(is_dagger[i]);

            for (int j = i+2; j < (int)symbol.size(); j++) {

                s1->symbol.push_back(symbol[j]);
                s2->symbol.push_back(symbol[j]);

                s1->is_dagger.push_back(is_dagger[j]);
                s2->is_dagger.push_back(is_dagger[j]);

            }
            break;

        }else {

            s1->symbol.push_back(symbol[i]);
            s2->symbol.push_back(symbol[i]);

            s1->is_dagger.push_back(is_dagger[i]);
            s2->is_dagger.push_back(is_dagger[i]);

        }
    }

    s1->normal_order(ordered);
    s2->normal_order(ordered);

}

} // End namespaces

