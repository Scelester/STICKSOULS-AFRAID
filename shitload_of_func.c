
#include <stdio.h>
#include <math.h>


struct New_points
{
    float x;
    float y;
};


struct New_points calculate_new_points_in_circle(int center_x, int center_y,float px,float py,float angle)
{
    float angle_to_radian = (3.14159265358979/180)*angle;
    float sinA = sin(angle_to_radian);
    float cosA = cos(angle_to_radian);

    float new_x = center_x + (px-center_x)*cosA - (py-center_y)*sinA;
    float new_y = center_y + (px-center_x)*sinA + (py-center_y)*cosA;

    struct New_points ret_point = {new_x, new_y}; 

    return ret_point;
}



float * get_each_trangle_rotation(int center_x, int center_y, float p1x,float p2x,float p3x, float p1y,float p2y,float p3y,float angle)
{
    static float new_points[10];

    float x_points[] = {p1x,p2x,p3x};
    float y_points[] = {p1y,p2y,p3y};

    struct New_points recieve;

    int ret_pointer_sizert = 0;

    for (size_t i = 0; i < 3; i++)
    {
        recieve = calculate_new_points_in_circle(center_x, center_y, 
                                                x_points[i], y_points[i],
                                                angle);

        new_points[ret_pointer_sizert] = recieve.x;
        new_points[ret_pointer_sizert + 1] = recieve.y; 

        ret_pointer_sizert += 2;

    }
    

    return new_points;
}