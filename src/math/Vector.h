//
// Created by q on 2023/10/17.
//

#ifndef MYSOFTWARERENDERPIPE_VECTOR_H
#define MYSOFTWARERENDERPIPE_VECTOR_H

#include <ostream>
#include <math.h>
#include "Matrix.h"

template<typename Data_Type, size_t Dim>
class Vector : private Matrix<Data_Type, Dim, 1> {
    using Matrix_Type = Matrix<Data_Type, Dim, 1>;
public:
    explicit Vector() : Matrix_Type() {}

    explicit Vector(const Data_Type init_value) : Matrix_Type(init_value) {}

    Vector(const std::initializer_list<Data_Type> &initializerList) : Matrix_Type(initializerList) {}

    Vector &operator=(Vector &&) = default;

    Vector &operator=(const Vector &) = default;

    Vector(const Vector &) = default;

    Vector(Vector &&) = default;

    explicit Vector(const Matrix_Type &matrix) : Matrix_Type(matrix) {}

    explicit Vector(Matrix_Type &&matrix) : Matrix_Type(matrix) {}

    Matrix_Type &asMatrix() {
        return *this;
    }

    Data_Type &operator[](const size_t &x) &{
        return Matrix_Type::operator[](x)[0];
    }

    auto operator[](const size_t &x) const &{
        return Matrix_Type::operator[](x)[0];
    }

    Vector operator+(const Vector another) {
        return (Vector) Matrix_Type::operator+(another);
    }

    Vector operator+=(const Vector another) {
        return (Vector) Matrix_Type::operator+=(another);
    }

    Vector operator-(const Vector another) {
        return (Vector) Matrix_Type::operator-(another);
    }

    Vector operator-=(const Vector another) {
        return (Vector) Matrix_Type::operator-=(another);
    }

    Vector operator*(const Vector another) {
        return (Vector) Matrix_Type::operator*(another);
    }

    Vector operator*=(const Vector another) {
        return (Vector) Matrix_Type::operator*=(another);
    }

    /**
     * 向量乘以一个数
     * @tparam Multiplier_Type 乘数的数据类型
     * @param num 乘数
     * @return 乘法运算结果
     */
    template<typename Multiplier_Type>
    typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, Vector>::type operator*(const Multiplier_Type &num) {
        return static_cast<Vector>(Matrix_Type::operator*(num));
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
    typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, Vector>::type operator/(const Multiplier_Type &num) {
        return static_cast<Vector>(Matrix_Type::operator/(num));
    }

    template<typename Multiplier_Type>
    typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, void>::type operator/=(const Multiplier_Type &num) {
        Matrix_Type::operator/=(num);
    }

    Vector operator/(const Vector another) {
        return (Vector) Matrix_Type::operator/(another);
    }

    Vector operator/=(const Vector another) {
        return (Vector) Matrix_Type::operator/=(another);
    }

    /**
     * 向量点乘
     * @param another
     * @return
     */
    Data_Type dot(const Vector &another) const;

    /**
     * 向量叉乘
     * @param another
     * @return
     */
    auto cross(const Vector &another);

    template<typename Multiplier_Type>
    friend typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, Vector>::type
    operator*(const Multiplier_Type &num, const Vector &vec) {
        Vector ans{};
        for (int i = 0; i < Dim; ++i) {
            ans[i] = vec[i] * num;
        }
        return ans;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector &vec) {
        out << "Vector" << Dim << '{';
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
    Data_Type abs() {
        Data_Type sum{};
        for (int i = 0; i < Dim; ++i) {
            sum += operator[](i) * operator[](i);
        }
        return sqrt(sum);
    }

    Vector &normalize() {
        operator/=(abs());
        return *this;
    }

    Vector norm_vec() {
        Vector vec = *this;
        return vec.normalize();
    }
};


template<typename Data_Type, size_t Dim>
auto dot(const Vector<Data_Type, Dim> &v1, const Vector<Data_Type, Dim> &v2) {
    Data_Type ans{};
    for (int i = 0; i < Dim; ++i) {
        ans += v1[i] * v2[i];
    }
    return ans;
}

template<typename Data_Type, size_t Dim>
Data_Type Vector<Data_Type, Dim>::dot(const Vector<Data_Type, Dim> &another) const {
    return ::dot(*this, another);
}

template<typename Data_Type>
auto cross(const Vector<Data_Type, 2> &v1, const Vector<Data_Type, 2> &v2) {
    return v1[0] * v2[1] - v1[1] * v2[0];
}

template<typename Data_Type>
auto cross(const Vector<Data_Type, 3> &v1, const Vector<Data_Type, 3> &v2) {
    return Vector<Data_Type, 3>{v1[1] * v2[2] - v1[2] * v2[1],
                                v1[2] * v2[0] - v1[0] * v2[2],
                                v1[0] * v2[1] - v1[1] * v2[0]};
}


template<typename Data_Type, size_t Dim>
auto Vector<Data_Type, Dim>::cross(const Vector &another) {
    static_assert(Dim == 2 || Dim == 3);
    return ::cross(*this, another);
}

#endif //MYSOFTWARERENDERPIPE_VECTOR_H
