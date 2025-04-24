#include <iostream>

namespace Gu {
    static int gu_strlen(const char* str) {
        int length = 0;
        while (str[length] != '\0') {
            length++;
        }
        return length;
    }

    static char* gu_strcpy(char *dest, const char *src) {
        char *original_dest = dest;
        while ((*dest++ = *src++) != '\0');
        return original_dest;
    }

    class GuString {
    public:
        GuString(const char* data);      // constructor
        GuString(const GuString& other); // copy constructor
        GuString(GuString&& other);      // move constructor
        ~GuString() {
            delete[] data_;
        }

        GuString& operator=(const GuString& other); // 복사 대입
        GuString& operator=(GuString&& other);      // 이동 대입
        GuString operator+(const GuString& rhs) const;
        bool operator==(const GuString& rhs) const;
        bool operator!=(const GuString& rhs) const;
        char& operator[](int index);
        const char& operator[](int index) const;
        //std::ostream& operator<<(std::ostream& os, const GuString& str);

        int length() const;
        void print() const;
        const char* c_str() const;
        void reserve(int new_capacity);
        void append(const char* str);
        void clear();
        void shrink_to_fit();

    private:
        char* data_;
        int len_;
        int capacity_;
    };

    GuString::GuString(const char* data){
        if (data == nullptr) {
            len_ = 0;
            capacity_ = len_ + 1;
            data_ = new char[capacity_];
            data_[0] = '\0';
        }
        else {
            len_ = gu_strlen(data);
            capacity_ = len_ + 1;
            data_ = new char[capacity_];
            gu_strcpy(data_, data);
        }
    }

    GuString::GuString(const GuString& other) {
        len_ = other.len_;
        capacity_ = len_ + 1;
        data_ = new char[capacity_];
        gu_strcpy(data_, other.data_);
    }

    GuString::GuString(GuString&& other) {
        len_ = other.len_;
        capacity_ = other.capacity_;
        data_ = other.data_;
        other.data_ = nullptr;
        other.len_ = 0;
    }

    GuString& GuString::operator=(const GuString& other) {
        if (this == &other) {
            return *this;
        }
        
        if (capacity_ >= other.len_ + 1) {
            len_ = other.len_;
            gu_strcpy(data_, other.data_);
        }
        else {
            delete[] data_;
            len_ = other.len_;
            capacity_ = len_ + 1;
            data_ = new char[capacity_];
            gu_strcpy(data_, other.data_);
        }
        return *this;
    }

    GuString& GuString::operator=(GuString&& other) {
        if (this != &other) {
            delete[] data_;
            len_ = other.len_;
            capacity_ = other.capacity_;
            data_ = other.data_;

            other.data_ = nullptr;
            other.len_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    GuString GuString::operator+(const GuString& rhs) const {
        int total_len = len_ + rhs.len_;
        
        GuString ret("");
        ret.reserve(total_len + 1);
        gu_strcpy(ret.data_, data_);
        gu_strcpy(ret.data_ + len_, rhs.data_);
        ret.len_ = total_len;
        
        return ret;
    }

    bool GuString::operator==(const GuString& rhs) const {
        if(len_ != rhs.len_) {
            return false;
        }

        for (int i = 0; i < len_; i++) {
            if(data_[i] != rhs.data_[i]) return false;
        }

        return true;
    }
    
    bool GuString::operator!=(const GuString& rhs) const {
        return !(*this == rhs);
    }

    char& GuString::operator[](int index) {
        return data_[index];
    }

    const char& GuString::operator[](int index) const {
        return data_[index];
    }

    std::ostream& operator<<(std::ostream& os, const GuString& str) {
        return os << str.c_str();
    }

    int GuString::length() const {
        return len_;
    }

    void GuString::print() const {
        std::cout << data_ << std::endl;
    }

    const char* GuString::c_str() const {
        return data_;
    }

    void GuString::reserve(int new_capacity) {
        if (capacity_ >= new_capacity) {
            return;
        }

        char* new_data = new char[new_capacity];
        gu_strcpy(new_data, data_);
        capacity_ = new_capacity;
        delete[] data_;
        data_ = new_data;
    }
    
    void GuString::append(const char* str) {
        int append_len = gu_strlen(str);

        if(capacity_ < len_ + append_len + 1) {
            reserve((len_ + append_len + 1)*2);
        }

        gu_strcpy(data_ + len_, str);
        len_ = len_ + append_len;
    }

    void GuString::clear() {
        len_ = 0;
        data_[0] = '\0';
    }

    void GuString::shrink_to_fit() {
        if (len_ + 1 == capacity_) {
            return;
        }

        int new_capacity = len_ + 1;
        char* new_data = new char[new_capacity];
        gu_strcpy(new_data, data_);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }
}


int main() {
    Gu::GuString first_gus = Gu::GuString("abcd");
    const Gu::GuString second_gus = Gu::GuString("-efg");
    Gu::GuString third_gus = first_gus + second_gus;

    std::cout << "Welcome to OnlineIDE Pro!" << std::endl;
    third_gus.print();
    std::cout << (first_gus != second_gus) << first_gus[2] << second_gus[2] << third_gus << std::endl;
    return 0;
}
