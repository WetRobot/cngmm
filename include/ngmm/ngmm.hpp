#ifndef NGMM_HPP
#define NGMM_HPP

#include <iostream>
#include <string>
#include "./mm/include/mm/mm.hpp"

namespace ngmm {
    #include "./text_ngram_iterator.hpp"
    namespace mm = mm;

    class NgramModel : public mm::MarkovModel<std::string> {
    protected:
        int n;
    public:
        NgramModel(
            int n = 3,
            double alpha = 1.0,
            double unseen_alpha = 1.0,
            bool normalise_length = true
        ) : mm::MarkovModel<std::string>(alpha, unseen_alpha, normalise_length), n(n) {}

        void print() const {
            std::cout << "n: ";
            mm::print::print(n);
            this->mm::MarkovModel<std::string>::print();
        }

        using mm::MarkovModel<std::string>::update;

        void update(
            const std::string& text
        ) {
            tngi::TextNGramIterator it(
                text,
                n,
                0
            );
            update(mm::it::ByIterable(it.begin(), it.end()));
        }
        
        using mm::MarkovModel<std::string>::lpmf;
        
        void lpmf(
            const std::string& text,
            double out
        ) {
            tngi::TextNGramIterator it(
                text,
                n,
                0
            );
            lpmf(mm::it::SumIterable(it.begin(), it.end()), out);
        }
        double lpmf(
            const std::string& text
        ) {
            tngi::TextNGramIterator it(
                text,
                n,
                0
            );
            return lpmf(mm::it::SumIterable(it.begin(), it.end()));
        }
        std::vector<double> lpmf(
            const std::vector<std::string>& texts
        ) {
            tngi::TextNGramIterator it(
                text,
                n,
                0
            );
            return lpmf(mm::it::SumIterable(it.begin(), it.end()));
        }

    };

}

#endif
