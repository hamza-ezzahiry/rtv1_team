#include "rtv1.h"

void init_mlx(t_mlx *mlx, char *str)
{
    mlx->fov = 60 * M_PI / 180;
    mlx->mlx_ptr = mlx_init();
    mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, str);
    mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    mlx->img.data = (unsigned char *)mlx_get_data_addr(mlx->img.img_ptr,
                                                       &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
}

int main()
{
    int j;
    t_mlx mlx;
    init_mlx(&mlx, "TEST");
    for (int i = 0; i < WIN_WIDTH; i++)
    {
        j = 0;
        while (j < WIN_HEIGHT)
        {
            if (j % 3 && i % 3)
            {
                mlx.img.data[(i * 4 + 4 * WIN_HEIGHT * j)] = 165;     //blue
                mlx.img.data[(i * 4 + 4 * WIN_HEIGHT * j) + 1] = 255; //green
                mlx.img.data[(i * 4 + 4 * WIN_HEIGHT * j) + 2] = 25; //red
            }
            //mlx.img.data[(i * WIN_HEIGHT + j) + 1] = 255;
            //mlx.img.data[(i * WIN_HEIGHT + j) + 2] = 0;
            j++;
        }
    }
    mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
    mlx_loop(mlx.mlx_ptr);
    return (0);
}