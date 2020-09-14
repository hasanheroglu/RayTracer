#include <iostream>

#define MATRIX_SIZE 16

#ifndef MATRIX4_H
#define MATRIX4_H

template <typename T>
class Mat4
{
    public:
        T elements[MATRIX_SIZE];

        Mat4()
        {
            for(size_t i=0; i<MATRIX_SIZE; i++)
            {
                elements[i] = 0;
            }

            elements[0]=T(1);elements[5]=T(1);elements[10]=T(1);elements[15]=T(1);
        }

        Mat4(T v)
        {
            for(size_t i=0; i<MATRIX_SIZE; i++)
            {
                elements[i] = v;
            }
        }

        Mat4(T a00, T a01, T a02, T a03,
                T a10, T a11, T a12, T a13,
                T a20, T a21, T a22, T a23,
                T a30, T a31, T a32, T a33)
        {
            elements[0]=a00;elements[1]=a01;elements[2]=a02;elements[3]=a03;
            elements[4]=a10;elements[5]=a11;elements[6]=a12;elements[7]=a13;
            elements[8]=a20;elements[9]=a21;elements[10]=a22;elements[11]=a23;
            elements[12]=a30;elements[13]=a31;elements[14]=a32;elements[15]=a33;
        }

        Mat4<T> operator +(const Mat4<T>& m)
        {
            return Mat4(
                get(0,0) + m.get(0,0), get(0,1) + m.get(0,1), get(0,2) + m.get(0,2), get(0,3) + m.get(0,3),
                get(1,0) + m.get(1,0), get(1,1) + m.get(1,1), get(1,2) + m.get(1,2), get(1,3) + m.get(1,3),
                get(2,0) + m.get(2,0), get(2,1) + m.get(2,1), get(2,2) + m.get(2,2), get(2,3) + m.get(2,3),
                get(3,0) + m.get(3,0), get(3,1) + m.get(3,1), get(3,2) + m.get(3,2), get(3,3) + m.get(3,3)
            );
        }

        Mat4<T> operator -(const Mat4<T>& m)
        {
            return Mat4(
                get(0,0) - m.get(0,0), get(0,1) - m.get(0,1), get(0,2) - m.get(0,2), get(0,3) - m.get(0,3),
                get(1,0) - m.get(1,0), get(1,1) - m.get(1,1), get(1,2) - m.get(1,2), get(1,3) - m.get(1,3),
                get(2,0) - m.get(2,0), get(2,1) - m.get(2,1), get(2,2) - m.get(2,2), get(2,3) - m.get(2,3),
                get(3,0) - m.get(3,0), get(3,1) - m.get(3,1), get(3,2) - m.get(3,2), get(3,3) - m.get(3,3)
            );
        }

        Mat4<T>& operator +=(const Mat4<T>& m)
        {
            for(size_t r=0; r<4; r++)
            {
                for(size_t c=0; c<4; c++)
                {
                    elements[r*4+c] += m.get(r, c); 
                }
            }

            return *this;
        }

        Mat4<T>& operator -=(const Mat4<T>& m)
        {
            for(size_t r=0; r<4; r++)
            {
                for(size_t c=0; c<4; c++)
                {
                    elements[r*4+c] -= m.get(r, c); 
                }
            }

            return *this;
        }

        Mat4<T> operator *(const T s)
        {
            return Mat4<T>(
                get(0,0)*s, get(0,1)*s, get(0,2)*s, get(0,3)*s,
                get(1,0)*s, get(1,1)*s, get(1,2)*s, get(1,3)*s,
                get(2,0)*s, get(2,1)*s, get(2,2)*s, get(2,3)*s,
                get(3,0)*s, get(3,1)*s, get(3,2)*s, get(3,3)*s
            );
        }

        Mat4<T> operator *(const Mat4<T> &m)
        {
            return Mat4<T>(
                getMultiplication(m, 0, 0), getMultiplication(m, 0, 1), getMultiplication(m, 0, 2), getMultiplication(m, 0, 3),
                getMultiplication(m, 1, 0), getMultiplication(m, 1, 1), getMultiplication(m, 1, 2), getMultiplication(m, 1, 3),
                getMultiplication(m, 2, 0), getMultiplication(m, 2, 1), getMultiplication(m, 2, 2), getMultiplication(m, 2, 3),
                getMultiplication(m, 3, 0), getMultiplication(m, 3, 1), getMultiplication(m, 3, 2), getMultiplication(m, 3, 3)
            );
        }

        Mat4<T>& operator *=(const T s)
        {
            for(size_t i=0; i<MATRIX_SIZE; i++)
            {
                elements[i] *= s;
            }

            return *this;
        }

        Mat4<T>& operator *=(const Mat4<T> &m)
        {
            for(size_t r=0; r<4; r++)
            {
                for(size_t c=0; c<4; c++)
                {
                    elements[r*4+c] = getMultiplication(m, r, c);
                }
            }

            return *this;
        }

        Mat4<T>& operator =(const Mat4<T>& m)
        {
            for(size_t i=0; i<MATRIX_SIZE; i++)
            {
                elements[i] = m.elements[i];
            }

            return *this;
        }

        T get(unsigned int r, unsigned int c) const
        {
            if(r > 3 || c > 3) { return T(0); } //bad logic change here

            return elements[r*4+c];
        }

        Mat4<T>& transpose()
        {
            Mat4<T> temp(
                get(0,0), get(1,0), get(2,0), get(3,0),
                get(0,1), get(1,1), get(2,1), get(3,1),
                get(0,2), get(1,2), get(2,2), get(3,2),
                get(0,3), get(1,3), get(2,3), get(3,3)
            );

            *this = temp;
            return *this;
        }

        Mat4<T> inverse()
        {
            Mat4<T> temp;
            Mat4<T> inverse;
            temp = *this;
                        
            //Forward Elimination
            for(size_t i=0; i<4; i++)
            {
                T pivot = temp.get(i,i);
                for (unsigned int j=i+1; j<4 && pivot == T(0); j++, pivot = temp.get(i,i))
                {
                    temp.exchangeRows(i, j);
                    inverse.exchangeRows(i, j);
                }

                //inverse does not exist
                if(pivot == T(0))
                {
                    return Mat4<T>(T(0));
                }

                else
                {
                    for(size_t j=0; j<4; j++)
                    {
                        temp.elements[i*4+j] /= pivot;
                        inverse.elements[i*4+j] /= pivot;
                    }
                }
                
                
                for(size_t j=i+1; j<4; j++)
                {
                    T eliminationMultiplier = temp.get(j,i);
                    for(size_t k=0; k<4; k++)
                    {
                        temp.elements[j*4+k] -= temp.elements[i*4+k]*eliminationMultiplier;
                        inverse.elements[j*4+k] -= inverse.elements[i*4+k]*eliminationMultiplier;
                    }
                }                
            }
            
            //Backward Elimination
            for(int i=3; i>0; i--)
            {
                for(int j=i-1; j>=0; j--)
                {
                    T eliminationMultiplier = temp.get(j,i);
                    for(int k=3; k>=0; k--)
                    {
                        temp.elements[j*4+k] -= temp.elements[i*4+k]*eliminationMultiplier;
                        inverse.elements[j*4+k] -= inverse.elements[i*4+k]*eliminationMultiplier;
                    }
                }
            }

            return inverse;
        }

        void print()
        {
            for(size_t i=0; i<MATRIX_SIZE; i++)
            {
                printf("%.3f", elements[i]);
                printf("\t");

                if(i % 4 == 3)
                {
                    printf("\n");
                }
            }        
            
            printf("\n");
        }
        
    private:
        T getMultiplication(const Mat4<T> &m, unsigned int r, unsigned int c)
        {
            return get(r,0)*m.get(0,c) + get(r,1)*m.get(1,c) + get(r,2)*m.get(2,c) + get(r,3)*m.get(3,c);
        }
        
        void exchangeRows(unsigned int r1, unsigned int r2)
        {
            if((r1>=0 && r1<4) && (r2>=0 && r2<4))
            {
                for(size_t i=0; i<4; i++)
                {
                    T temp = elements[r2*4+i];
                    elements[r2*4+i] = elements[r1*4+i];
                    elements[r1*4+i] = temp;
                }
            }
        }
};

typedef Mat4<float> Mat4f;

#endif