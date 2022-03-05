#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
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
    float i, j;
    
    //K1
    int k;

    //z-buffer
    float zb[1760];
    char b[1760];
    std::cout << "\x1b[2J";
    while (true)
    {
        memset(b, 32, 1760);
        memset(zb, 0, 7040);
        for (i = -1; i < 1; i += 0.03)
        {
            for (j = -1.0 + fabs(i); j < 1.0 - fabs(i); j += 0.03)
            {
                // We will calculate the position and luminance of each point.
                
                float sinA = sin(A); // sin(A)
                float cosA = cos(A); // cos(A)
                float cosB = cos(B); // cos(B)
                float sinB = sin(B); // sin(B)
                float kp = 1 - fabs(i) - fabs(j);
                float km = -kp;
                
                float zm = km*cosA;
                float zp = kp*cosA;
                float k = (zm<zp) ? km : kp;

                float x = i*cosB-sinB*(j*cosA-k*sinA);
                float y = i*sinB+cosB*(j*cosA-k*sinA);
                float z = j*sinA + k*cosA;

                
                float D = 1 / (z+5); // 1/(z + K2) //K2 is taken as 5
                float X = 40 + 30*D*x, Y = 12 + 15*D*y;
                
                
                // Varible to store rendered ASCII character in the buffer.
                // We are using a 1D array.
                int o = X + 80 * Y;

                // Luminance
                float Nx = (i>0)? sqrt(1.0/3.0) : -sqrt(1.0/3.0);
                float Ny = (j>0)? sqrt(1.0/3.0) : -sqrt(1.0/3.0);
                float Nz = (k>0)? sqrt(1.0/3.0) : -sqrt(1.0/3.0);
                int N = 8 * (Nx*sinB + cosB*(Ny*cosA - Nz*sinA) - Ny*sinA - Nz*cosA);
                if (22 > Y && Y > 0 && X > 0 && 80 > X && D > zb[o])
                {
                    // String D in z-buffer
                    zb[o] = D;

                    // Choosing ASCII character based on Luminance and storing it in buffer
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        
        std::cout << "\x1b[H";
        for (k = 0; k < 1761; k++)
        {
            putchar(k % 80 ? b[k] : 10);
            A += 0.00004;
            B += 0.00002;
        }
        
	//	for(int i = 0; i < 10000; i++)
			for(int j = 0; j < 10000; j++) ;
   }


    return 0;
}
