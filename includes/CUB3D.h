/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CUB3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:18:31 by hmoubal           #+#    #+#             */
/*   Updated: 2022/09/16 18:05:06 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
/* # include "/usr/X11/include/mlx.h" */
# include "../libft/includes/libft.h"
# define BUFFER_SIZE 1

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
}	t_mlx;

typedef struct s_paraup
{
	char	*dir;
	char	*value;
	struct s_paraup	*next;
}	t_paraup;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
}	t_map;

typedef struct s_global
{
	t_paraup	*up;
	t_map		*map;
	t_mlx		*mlx;
}	t_global;

char	*ft_strjoin_free(char const *s1,	char const *s2);
int	parse_map_walls(char **av, t_global *all);
char	*get_next_line(int fd);
#endif
