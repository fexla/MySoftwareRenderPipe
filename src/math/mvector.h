//
// Created by q on 2023/10/17.
//

#ifndef MYSOFTWARERENDERPIPE_MVECTOR_H
#define MYSOFTWARERENDERPIPE_MVECTOR_H

#include <ostream>
#include <cmath>

#include "matrix.h"

template<typename Data_Type, size_t Dim>
class mvector : private matrix<Data_Type, Dim, 1> {
    using Matrix_Type = matrix<Data_Type, Dim, 1>;
public:
    explicit mvector() : Matrix_Type() {}

    explicit mvector(const Data_Type init_value) : Matrix_Type(init_value) {}

    mvector(const std::initializer_list<Data_Type> &initializerList) : Matrix_Type(initializerList) {}

    mvector &operator=(mvector &&) = default;

    mvector &operator=(const mvector &) = default;

    mvector(const mvector &) = default;

    mvector(mvector &&) = default;

    explicit mvector(const Matrix_Type &matrix) : Matrix_Type(matrix) {}

    explicit mvector(Matrix_Type &&matrix) : Matrix_Type(matrix) {}

    Matrix_Type &asMatrix() {
        return *this;
    }

    const Matrix_Type &asMatrix() const {
        return *this;
    }

    Data_Type &operator[](const size_t &x) {
        return Matrix_Type::operator[](x)[0];
    }

    auto operator[](const size_t &x) const {
        return Matrix_Type::operator[](x)[0];
    }

    mvector operator+(const mvector &another) const {
        return (mvector) Matrix_Type::operator+(another);
    }

    mvector &operator+=(const mvector &another) {
        return (mvector &) Matrix_Type::operator+=(another);
    }

    mvector operator-(const mvector &another) const {
        return (mvector) Matrix_Type::operator-(another);
    }

    mvector &operator-=(const mvector &another) {
        return (mvector &) Matrix_Type::operator-=(another);
    }

    template<size_t M, size_t N>
    auto operator*(const matrix<Data_Type, M, N> &another) const {
        auto x = asMatrix() * (another);
        return x;
    }

    template<size_t M>
    friend mvector<Data_Type, M> operator*(matrix<Data_Type, M, Dim> matrix, mvector vector) {
        return static_cast<mvector<Data_Type, M>>(matrix * vector.asMatrix());
    }

    /**
     * 向量乘以一个数
     * @tparam Multiplier_Type 乘数的数据类型
     * @param num 乘数
     * @return 乘法运算结果
     */
    template<typename Multiplier_Type>
    typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, mvector>::type
    operator*(const Multiplier_Type &num) const {
        return static_cast<mvector>(Matrix_Type::operator*(num));
    }

    template<typename Multiplier_Type>
    typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, void>::type operator*=(const Multiplier_Type &num) {
        Matrix_Type::operator*=(num);
    }

    /**
     * 向量除以一个数
     * @tparam Multiplier_Type 除数的数据类型
     * @param num 除数
     * @return 除法运算结果
     */
    template<typename Multiplier_Type>
    typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, mvector>::type
    operator/(const Multiplier_Type &num) {
        return static_cast<mvector>(Matrix_Type::operator/(num));
    }

    template<typename Multiplier_Type>
    typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, void>::type operator/=(const Multiplier_Type &num) {
        Matrix_Type::operator/=(num);
    }


    bool operator==(const mvector rhs) const {
        return Matrix_Type::operator==(rhs);
    }

    bool operator!=(const mvector rhs) const {
        return Matrix_Type::operator!=(rhs);
    }

    /**
     * 向量点乘
     * @param another
     * @return
     */
    Data_Type dot(const mvector &another) const;

    /**
     * 向量叉乘
     * @param another
     * @return
     */
    auto cross(const mvector &another);

    template<typename Multiplier_Type>
    friend typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, mvector>::type
    operator*(const Multiplier_Type &num, const mvector &vec) {
        mvector ans{};
        for (int i = 0; i < Dim; ++i) {
            ans[i] = vec[i] * num;
        }
        return ans;
    }

    friend std::ostream &operator<<(std::ostream &out, const mvector &vec) {
        out << "mvector" << Dim << '{';
        for (int i = 0; i < Dim; ++i) {
            out << vec[i];
            if (i == Dim - 1) {
                out << "}";
            } else {
                out << ",";
            }
        }
        return out;
    }

    /**
     * 得到向量的模
     * @return
     */
    auto abs() const {
        double sum{};
        for (int i = 0; i < Dim; ++i) {
            sum += operator[](i) * operator[](i);
        }
        return sqrt(sum);
    }

    /**
     * 得到向量的模的平方
     * @return
     */
    auto abs_sq() const {
        double sum{};
        for (int i = 0; i < Dim; ++i) {
            sum += operator[](i) * operator[](i);
        }
        return sum;
    }

    /**
     * 得到两个向量之间的距离
     * @param another 另一个向量
     * @return 距离
     */
    auto dist(const mvector &another) const {
        mvector dif = operator-(another);
        return dif.abs();
    }

    /**
     * 得到两个向量之间的距离的平方
     * @param another 另一个向量
     * @return 距离的平方
     */
    auto dist_sq(const mvector &another) const {
        mvector dif = operator-(another);
        return dif.abs_sq();
    }

    mvector &normalize() {
        operator/=(abs());
        return *this;
    }

    mvector norm_vec() {
        mvector vec = *this;
        return vec.normalize();
    }

    /**
     * 得到一个长度为NewDim的新向量，如果新向量长度大于原向量，则多出来的位置会补充defaultValue为默认值。
     * @tparam NewDim 新向量长度
     * @param defaultValue 默认值
     * @return 长度为NewDim的新向量
     */
    template<size_t NewDim>
    mvector<Data_Type, NewDim> resize(Data_Type defaultValue = 0) {
        constexpr size_t SmallSize = std::min(NewDim, Dim);
        mvector<Data_Type, NewDim> res;
        for (int i = 0; i < SmallSize; ++i) {
            res[i] = (*this)[i];
        }
        if constexpr (NewDim > Dim) {
            for (int i = Dim; i < NewDim; ++i) {
                res[i] = defaultValue;
            }
        }
        return res;
    }
};


template<typename Data_Type, size_t Dim>
auto dot(const mvector<Data_Type, Dim> &v1, const mvector<Data_Type, Dim> &v2) {
    Data_Type ans{};
    for (int i = 0; i < Dim; ++i) {
        ans += v1[i] * v2[i];
    }
    return ans;
}

template<typename Data_Type, size_t Dim>
Data_Type mvector<Data_Type, Dim>::dot(const mvector<Data_Type, Dim> &another) const {
    return ::dot(*this, another);
}

template<typename Data_Type>
auto cross(const mvector<Data_Type, 2> &v1, const mvector<Data_Type, 2> &v2) {
    return v1[0] * v2[1] - v1[1] * v2[0];
}

template<typename Data_Type>
auto cross(const mvector<Data_Type, 3> &v1, const mvector<Data_Type, 3> &v2) {
    return mvector<Data_Type, 3>{v1[1] * v2[2] - v1[2] * v2[1],
                                 v1[2] * v2[0] - v1[0] * v2[2],
                                 v1[0] * v2[1] - v1[1] * v2[0]};
}


template<typename Data_Type, size_t Dim>
auto mvector<Data_Type, Dim>::cross(const mvector &another) {
    static_assert(Dim == 2 || Dim == 3);
    return ::cross(*this, another);
}

template<typename Data_Type, size_t Dim>
auto dist(const mvector<Data_Type, Dim> &v1, const mvector<Data_Type, Dim> &v2) {
    return v1.dist(v2);
}

template<typename Data_Type, size_t Dim>
auto dist_sq(const mvector<Data_Type, Dim> &v1, const mvector<Data_Type, Dim> &v2) {
    return v1.dist_sq(v2);
}

#endif //MYSOFTWARERENDERPIPE_MVECTOR_H
