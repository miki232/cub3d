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
#include "sprites.ppm"

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
			// printf("spritnums = %d\n", i);
            // mlx->sp[2].x += 0.5;
            // mlx->sp[2].y -= 0.5;
            if (fabs(mlx->sp[i].x - mlx->sp[1].x) < 20 && fabs(mlx->sp[i].y - mlx->sp[1].y) < 10 ||
                mlx->map->map[(int)mlx->sp[i].y/64][(int)mlx->sp[i].x/64] > '0')
            {
			    mlx->sp[i].state = 0;
                // mlx->multi->sprit_num--;
                printf("You win\n");
                // printf("Nub = %d  state=%d\n", 2, mlx->sp[2].state);
                // printf("Nub = %d  state=%d\n", 3, mlx->sp[3].state);

                // printf("sp[%d].x = %c, sp[%d].y = %f\n",i, mlx->map->map[(int)mlx->sp[i].y/64][(int)mlx->sp[i].x/64],i,  mlx->sp[i].y);    

            }
            else
            {
                mlx->sp[i].x += mlx->sp[i].dx * 0.5;
                mlx->sp[i].y += mlx->sp[i].dy * 0.5;
            }
            // printf("sp[2].x = %c, sp[2].y = %f\n", mlx->map->map[(int)mlx->sp[2].y/64][(int)mlx->sp[2].x/64], mlx->sp[2].y);    
        }
    }
    
    for(s=0;s<mlx->multi->sprit_num;s++)
    {
        // printf("%d\n", s);
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
                    //  int pixel=((int)t_y*32+(int)t_x)*3+(mlx->sp[s].map*32*32*3);
                    // int red =sprites[pixel+0];
                    // int green =sprites[pixel+1];
                    // int blue =sprites[pixel+2];
                    // mlx->map->color = (red<<16 | green <<8 | blue);
                    mlx->map->color = get_pixel(mlx->sp[s].texture, t_x, t_y);
                    // printf("sx = %f, sy = %f\n", sx - scale/2, sy);

                    // if (mlx->sp[2].state == 1)
                    //     printf("t_x %f t_y %f\n", t_x, t_y);
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
                                // printf("ii = %d\n", ii);
                                // my_mlx_pixel_put(data,  mlx->map->color);
                                // usleep(100);
                                // printf("%x\n", (mlx->sprite->addr + (ii * mlx->sprite->line_length + tempx * (mlx->sprite->bits_per_pixel / 8))));
                                // exit(0);
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
        // if (mlx->sp[2].state == 1)
        //     mlx->sp[2].state = 0;
    }
    if (m == 1)
        mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, data->img, 840, 0);
    else
        mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, data->img, 0, 0);
}



void    movesprite(t_data *mlx, float ex, float ey, float speed)
{
    if (mlx->multi->on == 1)
    {
        float dist = distance(mlx->map->px, mlx->map->py, ex, ey);
        float dx = ((ex - mlx->map->px) / dist) + 0.10;
        float dy = ((ey - mlx->map->py) / dist) + 0.10;
        while (distance(mlx->sp[0].x, mlx->sp[0].y, ex, ey) > speed)
        {
            // printf("x = %f, y = %f dist %f\n", mlx->sp[0].x, mlx->sp[0].y, distance(ex, ey, mlx->sp[0].x, mlx->sp[0].y));
            mlx->sp[0].x += dx * speed;
            mlx->sp[0].y += dy * speed;
            drawSprite(mlx, mlx->map->px, mlx->map->py, mlx->map->pa, mlx->map->depth, 0, mlx->img);
            if (fabs(mlx->sp[0].x - mlx->sp[1].x) < 20 && fabs(mlx->sp[0].y - mlx->sp[1].y) < 10)
            {
                printf("You lose\n");
                break;
            }
            if (distance(ex, ey, mlx->sp[0].x, mlx->sp[0].y) > 1000)
                break;
        }
    }
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
    while (rx >= 0 && ry >= 0  && sdo < 10) {
        // printf("rx = %f, ry = %f\n", rx, ry);
        if (fabs(rx - mlx->sp[1].x) < 20 && fabs(ry - mlx->sp[1].y) < 10) {
            // printf("Colpito!\n");
            sdo = 1001;
            break;
        }
        sdo++;
        rx += dx;
        ry += dy;
    }
    // if (sdo == 1001)
    // movesprite(mlx,rx, ry, 0.3);
    mlx->sp[mlx->multi->sprit_num - 1].rx = rx;
    mlx->sp[mlx->multi->sprit_num - 1].ry = ry;
    printf("sp[1].x = %f, sp[1].y = %f\n", mlx->sp[1].x, mlx->sp[1].y);
}