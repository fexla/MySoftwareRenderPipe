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
class matrix {
public:
    explicit matrix() : data{} {
    }

    explicit matrix(const Data_Type init_value) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                data[i][j] = init_value;
            }
        }
    }

    matrix(std::initializer_list<Data_Type> initializerList) {
        auto ptr = data[0];
        for (auto val: initializerList) {
            *(ptr++) = val;
        }
        while ((*(data + M - 1) + N) - ptr > 0) {
            *(ptr++) = 0;
        }
    }

    matrix &operator=(matrix &&) = default;

    matrix &operator=(const matrix &) = default;

    matrix(const matrix &) = default;

    matrix(matrix &&) = default;


    auto operator[](const size_t &x) &{
        return data[x];
    }

    auto operator[](const size_t &x) const &{
        return data[x];
    }

    matrix operator+(const matrix &another) const {
        matrix<Data_Type, M, N> ans{};
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                ans[i][j] = data[i][j] + another.data[i][j];
            }
        }
        return ans;
    }

    matrix &operator+=(const matrix &another) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                data[i][j] += another.data[i][j];
            }
        }
        return *this;
    }

    matrix operator-(const matrix &another) const {
        matrix<Data_Type, M, N> ans{};
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                ans[i][j] = data[i][j] - another.data[i][j];
            }
        }
        return ans;
    }

    matrix &operator-=(const matrix &another) {
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
    matrix<Data_Type, M, N2> operator*(const matrix<Data_Type, M2, N2> &another) const {
        static_assert(M2 == N);
        matrix<Data_Type, M, N2> ans{};
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
    typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, matrix>::type operator*(const Multiplier_Type &num) {
        matrix ans{};
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                ans[i][j] = data[i][j] * num;
            }
        }
        return ans;
    }

    template<typename Multiplier_Type>
    typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, matrix &>::type
    operator*=(const Multiplier_Type &num) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                data[i][j] *= num;
            }
        }
        return *this;
    }

    /**
     * 矩阵除以一个数
     * @tparam Multiplier_Type 除数的数据类型
     * @param num 除数
     * @return 除法运算结果
     */
    template<typename Multiplier_Type>
    typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, matrix>::type operator/(const Multiplier_Type &num) {
        assert(num != 0);
        if constexpr (std::is_floating_point_v<Multiplier_Type>) {
            Multiplier_Type inv = 1 / num;
            return operator*(inv);
        } else {
            matrix ans{};
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < N; ++j) {
                    ans[i][j] = data[i][j] / num;
                }
            }
            return ans;
        }
    }

    template<typename Multiplier_Type>
    typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, matrix &>::type
    operator/=(const Multiplier_Type &num) {
        assert(num != 0);
        if constexpr (std::is_floating_point_v<Multiplier_Type>) {
            Multiplier_Type inv = 1 / num;
            operator*=(inv);
        } else {
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < N; ++j) {
                    data[i][j] /= num;
                }
            }
        }
        return *this;
    }

    bool operator==(const matrix &rhs) const {
        bool ans = 1;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                ans &= data[i][j] == rhs[i][j];
            }
        }
        return ans;
    }

    bool operator!=(const matrix &rhs) const {
        return !(rhs == *this);
    }

    template<typename Multiplier_Type>
    friend typename std::enable_if<std::is_arithmetic_v<Multiplier_Type>, matrix>::type
    operator*(const Multiplier_Type &num, const matrix &mat) {
        matrix ans{};
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                ans[i][j] = mat[i][j] * num;
            }
        }
        return ans;
    }

    matrix<Data_Type, N, M> transpose() const {
        matrix<Data_Type, N, M> ans;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                ans[j][i] = data[i][j];
            }
        }
        return ans;
    }


    friend std::ostream &operator<<(std::ostream &out, const matrix<Data_Type, M, N> &mat) {
        out << "matrix" << M << "x" << N << "{\n";
        for (int i = 0; i < M; ++i) {
            out << '{';
            for (int j = 0; j < N; ++j) {
                out << mat[i][j] << '\t';
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
