//
// Created by q on 2023/10/17.
//
#include <cassert>
#include "iostream"

#ifndef MYSOFTWARERENDERPIPE_TENSOR_H
#define MYSOFTWARERENDERPIPE_TENSOR_H


/**
 *
 * @tparam Data_Type 数据类型
 * @tparam M 行数
 * @tparam N 列数
 */
template<typename Data_Type, size_t M, size_t N>
class Matrix {
public:
    explicit Matrix() : data{} {
    }

    explicit Matrix(const Data_Type init_value) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                data[i][j] = init_value;
            }
        }
    }

    Matrix(std::initializer_list<Data_Type> initializerList) {
        auto ptr = data[0];
        for (auto val: initializerList) {
            *(ptr++) = val;
        }
        while ((*(data + M-1) + N) - ptr>0) {
            *(ptr++) = 0;
        }
    }

    Matrix &operator=(Matrix &&) = default;

    Matrix &operator=(const Matrix &) = default;

    Matrix(const Matrix &) = default;

    Matrix(Matrix &&) = default;


    auto operator[](const size_t &x) &{
        return data[x];
    }

    auto operator[](const size_t &x) const &{
        return data[x];
    }

    Matrix operator+(const Matrix &another) const {
        Matrix<Data_Type, M, N> ans{};
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                ans[i][j] = data[i][j] + another.data[i][j];
            }
        }
        return ans;
    }

    Matrix &operator+=(const Matrix &another) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                data[i][j] += another.data[i][j];
            }
        }
        return *this;
    }

    Matrix operator-(const Matrix &another) const {
        Matrix<Data_Type, M, N> ans{};
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                ans[i][j] = data[i][j] - another.data[i][j];
            }
        }
        return ans;
    }

    Matrix &operator-=(const Matrix &another) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                data[i][j] -= another.data[i][j];
            }
        }
        return *this;
    }

    /**
     * 矩阵乘法
     * @tparam M2 第二个矩阵的行数
     * @tparam N2 第二个矩阵的列数
     * @param another 第二个矩阵
     * @return
     */
    template<size_t M2, size_t N2>
    Matrix<Data_Type, M, N2> operator*(const Matrix<Data_Type, M2, N2> &another) const {
        static_assert(M2 == N);
        Matrix<Data_Type, M, N2> ans{};
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N2; ++j) {
                for (int k = 0; k < N; ++k) {
                    ans[i][j] += data[i][k] * another[k][j];
                }
            }
        }
        return ans;
    }

    /**
     * 矩阵乘以一个数
     * @tparam Multiplier_Type 乘数的数据类型
     * @param num 乘数
     * @return 乘法运算结果
     */
    template<typename Multiplier_Type>
    typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, Matrix>::type operator*(const Multiplier_Type &num) {
        Matrix ans{};
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                ans[i][j] = data[i][j] * num;
            }
        }
        return ans;
    }

    template<typename Multiplier_Type>
    typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, void>::type
    operator*=(const Multiplier_Type &num) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                data[i][j] *= num;
            }
        }
    }

    /**
     * 矩阵除以一个数
     * @tparam Multiplier_Type 除数的数据类型
     * @param num 除数
     * @return 除法运算结果
     */
    template<typename Multiplier_Type>
    typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, Matrix>::type operator/(const Multiplier_Type &num) {
        assert(num != 0);
        Matrix ans{};
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                ans[i][j] = data[i][j] / num;
            }
        }
        return ans;
    }

    template<typename Multiplier_Type>
    typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, void>::type operator/=(const Multiplier_Type &num) {
        assert(num != 0);
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                data[i][j] /= num;
            }
        }
    }

    template<typename Multiplier_Type>
    friend typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, Matrix>::type
    operator*(const Multiplier_Type &num, const Matrix &matrix) {
        Matrix ans{};
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                ans[i][j] = matrix[i][j] * num;
            }
        }
        return ans;
    }

    Matrix<Data_Type, N, M> transpose() const {
        Matrix<Data_Type, N, M> ans;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                ans[j][i] = data[i][j];
            }
        }
        return ans;
    }


    friend std::ostream &operator<<(std::ostream &out, const Matrix<Data_Type, M, N> &matrix) {
        out << "Matrix" << M << "x" << N << "{\n";
        for (int i = 0; i < M; ++i) {
            out << '{';
            for (int j = 0; j < N; ++j) {
                out << matrix[i][j] << '\t';
                if (j == N - 1) {
                    out << "}\n";
                } else {
                    out << ",";
                }
            }
        }
        out << "}\n";
        return out;
    }

protected:
    Data_Type data[M][N];
};


#endif //MYSOFTWARERENDERPIPE_TENSOR_H
