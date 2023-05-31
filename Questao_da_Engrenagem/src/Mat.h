#ifndef MAT_H
#define MAT_H

#include "gl_canvas2d.h"
#include <stdio.h>

class Mat
{
    public:
        Mat(int n, int m)
        {
            this->n = n;
            this->m = m;
            internal_matrix = new float*[n];
            int i, j;
            for (i = 0; i < n; i++)
            {
                internal_matrix[i] = new float[m];
                for (j = 0; j < m; j++)
                {
                    internal_matrix[i][j] = 0.0;
                }
            }
        }

        float* At(int i, int j){return &internal_matrix[i][j];}

        void ShowMatrix()
        {
            printf("\n");
            int i, j;
            for (i = 0; i < n; i++)
            {
                for (j = 0; j < m; j++)
                {
                    printf("%f ", internal_matrix[i][j]);
                }
                printf("\n");
            }
        }

        void Draw(int x, int y, int color)
        {

            int i;
            for (i = 0; i < m; i++)
            {
                CV::color(color);
                CV::circle(x+internal_matrix[0][i], y-internal_matrix[1][i], 5, 30);
            }
        }

        static Mat* Mult(Mat* A, Mat* B)
        {
            if(A->m == B->n)
            {
                Mat* C = new Mat(A->n, B->m);

                int i, j, k;
                for (i = 0; i < C->n; i++)
                {
                    for (j = 0; j < C->m; j++)
                    {
                        float val = 0.0;

                        for(k = 0; k < A->n; k++) // Cada elemento da linha de A
                        {
                            val += (*A->At(i, k)) * (*B->At(k, j));
                        }

                        *C->At(i, j) = val;
                    }
                }

                return C;
            }
            else
            {
                return nullptr;
            }
        }

        int n, m;
    private:
        float** internal_matrix;
};
#endif // MAT_H
