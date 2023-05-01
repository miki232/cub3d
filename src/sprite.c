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
//m 1 is 840 shitft
void    drawSprite(t_data *mlx, float px, float py, float pa, int *depth, int m, t_image *data)
{
    int x,y,s;
    for(s=0;s<2;s++)
    {
        float sx=sp[s].x-px; //temp float variables
        float sy=sp[s].y-py;
        float sz=sp[s].z;
        float CS=cos(degtorad(pa)), SN=sin(degtorad(pa)); //rotate around origin
        float a=sy*CS+sx*SN; 
        float b=sx*CS-sy*SN; 
        sx=a; sy=b;
        sx=(sx*((WIDTH)-12.0)/sy)+(WIDTH/2); //convert to screen x,y
        sy=(sz*((WIDTH)-12.0)/sy)+(HEIGHT/2);
        
        int scale=64*(HEIGHT)/b;   //scale sprite based on distance
        if (scale<0){ scale=0;} if(scale>(WIDTH)){ scale=(WIDTH);}

        //loading texture
        float t_x=0, t_y=0, t_x_step=31.5/(float)scale, t_y_step=32.0/(float)scale;
       
        for(x=sx-scale/2;x<sx+scale/2;x++)
        {
            t_y=31;
            for(y=0;y<scale;y++)
            {
                if(sp[s].state==1 && x>0 && x<WIDTH && b<depth[x])
                {
                     int pixel=((int)t_y*32+(int)t_x)*3+(sp[s].map*32*32*3);
                    int red =sprites[pixel+0];
                    int green =sprites[pixel+1];
                    int blue =sprites[pixel+2];
                    mlx->map->color = (red<<16 | green <<8 | blue);
                    int temp = y*1;
                    if(red!=255 && green!=0 && blue!=255)
                    {
                        while (temp <((y*1)+1))
                        {  
                            int tempx = x*1;
                            while (tempx <= ((x*1)+1))
                            {
                                int ii = sy-temp;
                                if(ii>=(HEIGHT) || ii < 1){ ii=1;}
                                // printf("ii = %d\n", ii);
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
