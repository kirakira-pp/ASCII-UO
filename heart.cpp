                #include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
// An implementation of gotoxy() function for smoother animation
// without scrolling or clearing screen.
// void gotoxy(SHORT x, SHORT y)
// {
//   static HANDLE h = NULL;  
//   if(!h)
//     h = GetStdHandle(STD_OUTPUT_HANDLE);
//   COORD c = { x, y };  
//   SetConsoleCursorPosition(h,c);
// }

//              k;double sin()
//          ,cos();main(){float A=
//        0,B=0,i,j,z[1760];char b[
//      1760];printf("\x1b[2J");for(;;
//   ){memset(b,32,1760);memset(z,0,7040)
//   ;for(j=0;6.28>j;j+=0.07)for(i=0;6.28
//  >i;i+=0.02){float c=sin(i),d=cos(j),e=
//  sin(A),f=sin(j),g=cos(A),h=d+2,D=1/(c*
//  h*e+f*g+5),l=cos      (i),m=cos(B),n=s\
// in(B),t=c*h*g-f*        e;int x=40+30*D*
// (l*h*m-t*n),y=            12+15*D*(l*h*n
// +t*m),o=x+80*y,          N=8*((f*e-c*d*g
//  )*m-c*d*e-f*g-l        *d*n);if(22>y&&
//  y>0&&x>0&&80>x&&D>z[o]){z[o]=D;;;b[o]=
//  ".,-~:;=!*#$@"[N>0?N:0];}}/*#****!!-*/
//   printf("\x1b[H");for(k=0;1761>k;k++)
//    putchar(k%80?b[k]:10);A+=0.04;B+=
//      0.02;}}/*****####*******!!=;:~
//        ~::==!!!**********!!!==::-
//          .,~~;;;========;;;:~-.
//              ..,--------,*/

int main()
{
    // R1 is taken as 1, since it is only multiplied with terms,
    // we can neglect it in this program.

    // A, B
    float A = 0, B = 0;

    //phi, theta
    float i, j, k2[2];
    
    //K1
    int K;

    //z-buffer
    float zb[1760];
    char bA[1760];
    std::cout << "\x1b[2J";
    while (true)
    {
        memset(bA, 32, 1760);  // X:Width(80) Y:Height(22) 
        memset(zb, 0, 7040);
        for (i = 0; i < 3.14; i += 0.07)  // i = theta
        {
            for (j = 0; j < 6.28; j += 0.07)  // j = phi
            {
                // We will calculate the position and luminance of each point.
                
                float sinA = sin(A); // sin(A)
                float cosA = cos(A); // cos(A)
                float cosB = cos(B); // cos(B)
                float sinB = sin(B); // sin(B)

                float sinI = sin(i);
                float cosI = cos(i);
                float sinJ = sin(j);
                float sin2J = sin(2*j);
                float sin3J = sin(3*j);
                float cosJ = cos(j);
                float cos2J = cos(2*j);
                float cos3J = cos(3*j);

                float xi = sinI*(15*sinJ - 4*sin3J);
                float yi = 8*cosI;
                float zi = sinI*(15*cosJ - 6*cos2J - 2*cos3J);

                float x = xi*cosB-sinB*(yi*cosA-zi*sinA);
                float y = xi*sinB+cosB*(yi*cosA-zi*sinA);
                float z = yi*sinA + zi*cosA;
                
                float D = 1 / (z+50); // 1/(z + K2) //K2 is taken as 5
                int X = 40 + 30*D*x, Y = 12 + 30*D*y;
                
                // Varible to store rendered ASCII character in the buffer.
                // We are using a 1D array.
                int o = X + 80 * Y;

                // Luminance
                float a = cosI*(15*sinJ - 4*sin3J); // dx/dI
                float b = -8 * sinI;
                float c = cosI*(15*cosJ - 6*cos2J - 2*cos3J);
                float d = sinI*(15*cosJ - 12*cos3J);
                float f = sinI*(-15*sinJ + 12*sin2J + 6*sin3J);

                float Nx = b*f;
                float Ny = c*d - a*f;
                float Nz = -b*d;
                float norm = sqrt(Nx*Nx + Ny*Ny + Nz*Nz);
                Nx /= norm; Ny /= norm; Nz /= norm;
                int N = 8 * (-Nx*sinB - cosB*(Ny*cosA - Nz*sinA) - Ny*sinA - Nz*cosA);
                
                if (22 > Y && Y > 0 && X > 0 && 80 > X && D > zb[o])
                {
                    // String D in z-buffer
                    zb[o] = D;

                    // Choosing ASCII character based on Luminance and storing it in buffer
                    bA[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
                
            
            }
        }
        
        std::cout << "\x1b[H";
        for (K = 0; K < 1761; K++)
        {
            putchar(K % 80 ? bA[K] : 10);
            A += 0.00002;
            B += 0.00001;
        }
        
        if (A > 6.28) A-=6.28;
        if (B > 6.28) B-=6.28;

        usleep(20000);
		//for(int i = 0; i < 1000; i++)
		//	for(int j = 0; j < 10000; j++) ;
   }


    return 0;
}
