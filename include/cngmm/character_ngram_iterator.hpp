#ifndef NGRAM_ITERATOR_HPP
#define NGRAM_ITERATOR_HPP

#include <string>
#include <iterator>

namespace tngi {
    class CharacterNGramIterator {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = std::tuple<std::string, std::string>;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::forward_iterator_tag;

    private:
        const std::string& str_;
        const std::size_t n_;
        std::size_t pos_;

    public:
        CharacterNGramIterator(const std::string& str, std::size_t n, std::size_t pos = 0)
            : str_(str), n_(n), pos_(pos) {}

        bool operator!=(const CharacterNGramIterator& other) const {
            return pos_ != other.pos_;
        }

        CharacterNGramIterator& operator++() {
            ++pos_;
            return *this;
        }

        value_type operator*() const {
            return std::make_tuple(str_.substr(pos_, n_ - 1), str_.substr(pos_ + n_ - 1, 1));
        }

        CharacterNGramIterator begin() const {
            return CharacterNGramIterator(str_, n_);
        }

        CharacterNGramIterator end() const {
            return CharacterNGramIterator(str_, n_, str_.size() - n_ + 1);
        }
    };
}

#endif
