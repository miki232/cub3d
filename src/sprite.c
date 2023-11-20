/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:45:07 by mtoia             #+#    #+#             */
/*   Updated: 2023/05/01 17:28:01 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

float distance(float ax, float ay, float bx, float by)
{
    return (sqrt((bx-ax)*(bx-ax)+(by-ay)*(by-ay)));
}

//m 1 is 840 shitft
void    drawSprite(t_data *mlx, float px, float py, float pa, int *depth, int m, t_image *data)
{
    int x,y,s;
    for (int i = 2; i < mlx->multi->sprit_num; i++)
    {
        if (mlx->sp[i].state == 1)
        {
            if (((fabs(mlx->sp[i].x - mlx->sp[1].x) < 20) && (fabs(mlx->sp[i].y - mlx->sp[1].y) < 10)) ||
                mlx->map->map[(int)mlx->sp[i].y/64][(int)mlx->sp[i].x/64] == '1')
            {
			    mlx->sp[i].state = 0;
                if (((fabs(mlx->sp[i].x - mlx->sp[1].x) < 20) && (fabs(mlx->sp[i].y - mlx->sp[1].y) < 10)))
                {
                    printf("You win\n");
                    exit(0);
                }
            }
            else
            {
                mlx->sp[i].x += mlx->sp[i].dx * 3;
                mlx->sp[i].y += mlx->sp[i].dy * 3;
            }
        }
    }
    
    for(s=0;s<mlx->multi->sprit_num;s++)
    {
        float sx=mlx->sp[s].x-px; //temp float variables
        float sy=mlx->sp[s].y-py;
        float sz=mlx->sp[s].z;
        float CS=cos(degtorad(pa)), SN=sin(degtorad(pa)); //rotate around origin
        float a=sy*CS+sx*SN; 
        float b=sx*CS-sy*SN; 
        sx=a; sy=b;
        sx=(sx*((WIDTH)-12.0)/sy)+(WIDTH/2); //convert to screen x,y
        sy=(sz*((WIDTH)-12.0)/sy)+(HEIGHT/2);
        // printf("sx = %f, sy = %f\n", sx, sy);
        int scale=64*(HEIGHT)/b;   //scale sprite based on distance
        if (scale<0){ scale=0;} if(scale>(WIDTH)){ scale=(WIDTH);}

        //loading texture
        float t_x=0, t_y=0, t_x_step=63.5/(float)scale, t_y_step=64.0/(float)scale;
       
        for(x=sx-scale/2;x<sx+scale/2;x++)
        {
            t_y=63;
            for(y=0;y<scale;y++)
            {
                if(mlx->sp[s].state==1 && x>0 && x<WIDTH && b<depth[x])
                {
                    mlx->map->color = get_pixel(mlx->sp[s].texture, t_x, t_y);
                    int temp = y*1;
                    if(mlx->map->color != 0xC628AD && mlx->map->color != 0x00000001)
                    {
                        while (temp <((y*1)+1))
                        {  
                            int tempx = x*1;
                            while (tempx <= ((x*1)+1))
                            {
                                int ii = sy-temp;
                                if(ii>=(HEIGHT) || ii < 1){ ii=1;}
                                my_mlx_pixel_put(data, tempx, ii, mlx->map->color);
                                tempx++;
                            }
                            temp++;
                        }
                    }
                    t_y-=t_y_step; if(t_y<0){ t_y=0;}
                }
            }
            t_x+=t_x_step;
        }
    }
    if (m == 1)
        mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, data->img, 840, 0);
    else
        mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, data->img, 0, 0);
}

void ft_draw_line(int px, int py, int rx, int ry, t_data *mlx)
{
    int dx = rx - px;
    int dy = ry - py;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;
    float x = px;
    float y = py;
    int i;

    for (i = 0; i <= steps; i++) {
        my_mlx_pixel_put(mlx->img, x, y, 0xFFFFFF);
        x += x_inc;
        y += y_inc;
    }
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img->img, 0, 0);
}

float distance2(float ax, float ay, float bx, float by, float ang){ return cos(degtorad(ang))*(bx-ax)-sin(degtorad(ang))*(by-ay);}

#define p2 PI/2
#define p3 3*PI/2

void    shoot(t_data *mlx)
{
    int sdo = 0;
    float dx = cos(ft_fixang(mlx->map->pa) * PI / 180);
    float dy = -sin(ft_fixang(mlx->map->pa) * PI / 180);

    // Inizializza le coordinate del raggio
    float rx = mlx->map->px;
    float ry = mlx->map->py;

    // Avanza il raggio finché non collide con la sprite o va fuori dallo schermo
    while (rx >= 0 && ry >= 0  && sdo < 5) {
        // printf("rx = %f, ry = %f\n", rx, ry);
        if ((fabs(rx - mlx->sp[1].x) < 20 && fabs(ry - mlx->sp[1].y) < 10) || sdo >= 5) {
            // printf("Colpito!\n");
            sdo = 1001;
            break;
        }
        sdo++;
        rx += dx;
        ry += dy;
    }
    mlx->sp[mlx->multi->sprit_num - 1].rx = rx;
    mlx->sp[mlx->multi->sprit_num - 1].ry = ry;
}