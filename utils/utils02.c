#include "../cub.h"

void    printmatrix(t_map *map)
{
 for (int i = 0; i <= map->rows; i++) {
		for (int j = 0; j < map->cols; j++) {
			printf("%c", map->map[i][j]);
		}
		printf("\n");
}
}

int	ft_close(void)
{
	//free_game()
	exit(0);
}
