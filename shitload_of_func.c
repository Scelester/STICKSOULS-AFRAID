
#include <stdio.h>
#include <math.h>


struct New_points
{
    int x;
    int y;
};


struct New_points calculate_new_points_in_circle(int center_x, int center_y,int px,int py,int angle)
{
    float angle_to_radian = (3.14159265358979/180)*angle;
    float sinA = sin(angle_to_radian);
    float cosA = cos(angle_to_radian);

    int new_x = center_x + (px-center_x)*cosA - (py-center_y)*sinA;
    int new_y = center_y + (px-center_x)*sinA + (py-center_y)*cosA;

    struct New_points ret_point = {new_x, new_y}; 

    return ret_point;
}



int get_each_trangle_rotation(int center_x, int center_y, int p1x,int p2x,int p3x, int p1y,int p2y,int p3y,int angle)
{
    int new_points[10];

    int x_points[] = {p1x,p2x,p3x};
    int y_points[] = {p1y,p2y,p3y};
    
    int int_angle = floor(angle);

    for (size_t i = 0; i < 3; i++)
    {
        struct New_points recieve = calculate_new_points_in_circle(center_x, center_y, 
                                                                    x_points[i], y_points[i],
                                                                    int_angle);
        printf("point x :%d ", recieve.x);
        printf("point y : %d\n",recieve.y);
    }
    

    return new_points;
}